#include "iod_network.h"
#include "iod_logsystem.h"

namespace iod_network {

bool is_initialized = false;

struct event_base *evbase = 0;

bool initialize()
{
	if (is_initialized)
		return true;

#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	evbase = event_base_new();
	if (!evbase) {
		iod_log_crit("initialize event base failed!");
		return false;
	}
	
	is_initialized = true;

	return true;
}

struct listener_info* start_listener(iod_session_manager* session_creator, /*对话创建器 */ const char* bind_addr, /*监听地址，格式为 hostname:port */ int conn_timeout_secs /*= 120*/, /*每个连接的超时时间：超过该时间没有收到数据则关闭连接 */ int conn_highmark /*= DEFAULT_CONNECTION_HIGHMARK /*缓冲区上限：如果缓冲区中超过highmark字节未处理，则不再接收数据。0为不限制 */)
{
	if (!is_initialized)
		initialize();

	char ip[32] = {0};
	unsigned short port = 0;
	if(sscanf(bind_addr, "%[^:]:%hd", ip, &port) != 2)
	{
		iod_log_crit("add_listener %s failed, invalid address string!", bind_addr);
		return 0;
	}

	struct sockaddr_in sin = {0};
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(ip);

	listener_info* l_info = new listener_info();
	memset(l_info, 0, sizeof(listener_info));
	l_info->session_creator = session_creator;
	l_info->timeout_secs = conn_timeout_secs;
	l_info->highmark = conn_highmark;

	struct evconnlistener *listener = evconnlistener_new_bind(evbase, new_connection_cb, (void *)l_info,
		LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&sin,
		sizeof(sin));

	if (!listener)
	{
		iod_log_crit("add_listener %s failed, could not create listener : %d!", bind_addr, iod_net_last_errno);
		shutdown_listener(l_info);
		return 0;
	}

	l_info->listener = listener;

	iod_log_info("listening on %s", bind_addr);

	return l_info;
}

struct connection_info* iod_network::start_connection(iod_session* session, /*处理消息的对话实例 */ const char* target_addr, /*目标地址，格式为 hostname:port */ int conn_timeout_secs /*= 120*/, /*每个连接的超时时间：超过该时间没有收到数据则关闭连接 */ int conn_highmark /*= DEFAULT_CONNECTION_HIGHMARK /*缓冲区上限：如果缓冲区中超过highmark字节未处理，则不再接收数据。0为不限制 */)
{
	if (!is_initialized)
		initialize();

	char ip[32] = {0};
	unsigned short port = 0;
	if(sscanf(target_addr, "%[^:]:%hd", ip, &port) != 2)
	{
		iod_log_crit("add_connection %s failed, invalid address string!", target_addr);
		return 0;
	}

	struct sockaddr_in sin = {0};
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(ip);

	struct bufferevent *bev = bufferevent_socket_new(evbase, -1, BEV_OPT_CLOSE_ON_FREE);

	connection_info* conn_info = new connection_info();
	memset(conn_info, 0, sizeof(connection_info));
	conn_info->timeout_secs = conn_timeout_secs;
	conn_info->highmark = conn_highmark;
	conn_info->conn_buffev = bev;

	bufferevent_setcb(bev, 0, 0, conn_eventcb, conn_info);

	if (bufferevent_socket_connect(bev, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		iod_log_crit("can not start connect %s", target_addr);
		destroy_connection(conn_info, 0);
		return 0;
	}

	bind_session_connection(conn_info, session, iod_session::SNS_CONNECTING);

	//iod_log_info("start connecting %s", target_addr);

	return conn_info;
}

void new_connection_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data)
{
	listener_info* l_info = (listener_info*)user_data;

	//init r/w buffer
	struct bufferevent *bev = bufferevent_socket_new(evbase, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		iod_log_crit("could not constructing bufferevent!");
		return;
	}

	struct sockaddr_in* sin = (struct sockaddr_in*)sa;
	//iod_log_info("new incomming connection %s:%d, socket %d", inet_ntoa(sin->sin_addr), ntohs(sin->sin_port), (int)fd);

	connection_info* conn_info = new connection_info();
	memset(conn_info, 0, sizeof(connection_info));
	conn_info->session_creator = l_info->session_creator;
	conn_info->conn_buffev = bev;
	conn_info->timeout_secs = l_info->timeout_secs;
	conn_info->highmark = l_info->highmark;

	if (conn_info->timeout_secs > 0) {
		struct timeval timeout;
		timeout.tv_sec = conn_info->timeout_secs;
		timeout.tv_usec = 0;
		bufferevent_set_timeouts(bev, &timeout, 0);
	}

	if (conn_info->highmark > 0) {
		bufferevent_setwatermark(bev, EV_READ, 0, conn_info->highmark);
	}

	bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, conn_info);
	bufferevent_enable(bev, conn_info->timeout_secs > 0 ? (EV_READ | EV_TIMEOUT) : EV_READ);

	if (conn_info->session_creator)
		conn_info->session_creator->netstatistics.incoming_conn_count++;
}

void conn_readcb(struct bufferevent *bev, void *user_data)
{
	connection_info* conn_info = (connection_info*)user_data;

	int process_result = 0;

	if (conn_info->session)
		process_result = process_session_data(conn_info->session, bev);	
	else if (conn_info->session_creator)
		process_result = process_none_session_data(conn_info->session_creator, conn_info);

	if (process_result < 0)
		destroy_connection(conn_info, process_result);
}

void conn_writecb(struct bufferevent *bev, void *user_data)
{
}

void conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	connection_info* conn_info = (connection_info*)user_data;

	if (events & BEV_EVENT_EOF) {
		destroy_connection(conn_info, CONNECTION_CLOSE_BY_REMOTE);
	} else if (events & BEV_EVENT_ERROR) {		
		destroy_connection(conn_info, CONNECTION_CLOSE_BY_NETERROR);
	} else if (events & BEV_EVENT_TIMEOUT) {
		destroy_connection(conn_info, CONNECTION_CLOSE_BY_TIMEOUT);
	} else if (events & BEV_EVENT_CONNECTED) {
		if (conn_info) {
			if (conn_info->timeout_secs > 0) {
				struct timeval timeout;
				timeout.tv_sec = conn_info->timeout_secs;
				timeout.tv_usec = 0;
				bufferevent_set_timeouts(bev, &timeout, 0);
			}

			if (conn_info->highmark > 0) {
				bufferevent_setwatermark(bev, EV_READ, 0, conn_info->highmark);
			}

			bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, conn_info);
			bufferevent_enable(bev, conn_info->timeout_secs > 0 ? (EV_READ | EV_TIMEOUT) : EV_READ);

			if (conn_info->session) {
				bind_session_connection(conn_info, conn_info->session, iod_session::SNS_CONNECTED);
				conn_info->session->on_connected();
			}
		}
	}
}

int process_session_data(iod_session* session, struct bufferevent *bev)
{
	iod_packet* packet = 0;
	int read_result = 0;

	while (1) 
	{
		packet = session->create_packet();

		read_result = packet->read(bev);

		if (read_result > 0) {
			session->on_packet(packet);
			const connection_info* conn_info = session->get_connection_info();
			if (conn_info)
			{
				iod_session_manager* session_creator = conn_info->session_creator;
				if (session_creator) {
					session_creator->netstatistics.recv_byte_count += read_result;
					session_creator->netstatistics.recv_packet_count++;
				}
			}
		}
		else
			break;

		session->destroy_packet(packet);
	}

	session->destroy_packet(packet);

	return read_result;
}

int process_none_session_data(iod_session_manager* session_creator, connection_info* conn_info)
{
	iod_packet* packet = 0;
	int read_result = 0;

	while (1) 
	{
		packet = session_creator->create_packet();

		read_result = packet->read(conn_info->conn_buffev);

		if (read_result > 0) {
			iod_session* session = session_creator->on_none_session_packet(conn_info, packet);
			if (session) {
				bind_session_connection(conn_info, session, iod_session::SNS_CONNECTED);
				session->on_packet(packet);
				break;
			}
			session_creator->netstatistics.recv_byte_count += read_result;
			session_creator->netstatistics.recv_packet_count++;
		}
		else
			break;

		session_creator->destroy_packet(packet);
	}

	session_creator->destroy_packet(packet);

	return read_result;
}

}
