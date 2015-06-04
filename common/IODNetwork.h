#ifndef __IOD_NETWORK_H__
#define __IOD_NETWORK_H__

#include "IODPacket.h"
#include "IODSession.h"
#include "IODSessionManager.h"

#define DEFAULT_CONNECTION_HIGHMARK 1048576u

#ifdef WIN32
#define iod_net_last_errno WSAGetLastError()
#else
#define iod_net_last_errno errno
#endif

namespace IODNetwork {

enum 
{
	CONNECTION_CLOSE_BY_LOCAL = 0,
	CONNECTION_CLOSE_BY_REMOTE = 1,
	CONNECTION_CLOSE_BY_TIMEOUT = 2,
	CONNECTION_CLOSE_BY_NETERROR = 3,
};

extern struct event_base *evbase;

//初始化
bool initialize();

//更新
inline int update() {
	event_base_loop(evbase, EVLOOP_ONCE | EVLOOP_NONBLOCK);
	return 0;
}

//销毁
inline void shutdown() {
	if(evbase)	event_base_free(evbase);
}

//开启监听
struct listener_info* start_listener(IODSessionManager* session_creator, //对话创建器
	const char* bind_addr,  //监听地址，格式为 hostname:port
	int conn_timeout_secs = 120,		//每个连接的超时时间：超过该时间没有收到数据则关闭连接
	int conn_highmark = DEFAULT_CONNECTION_HIGHMARK		//缓冲区上限：如果缓冲区中超过highmark字节未处理，则不再接收数据。0为不限制
	);

//连接远程地址
struct connection_info* start_connection(IODSession* session,	//处理消息的对话实例
	const char* target_addr,  //目标地址，格式为 hostname:port
	int conn_timeout_secs = 120,		//每个连接的超时时间：超过该时间没有收到数据则关闭连接
	int conn_highmark = DEFAULT_CONNECTION_HIGHMARK		//缓冲区上限：如果缓冲区中超过highmark字节未处理，则不再接收数据。0为不限制
	);

//关闭监听
inline void shutdown_listener(struct listener_info* l_info) {
	if (l_info->listener)
		evconnlistener_free(l_info->listener);
	delete l_info;
}

//关闭/销毁连接
inline void destroy_connection(struct connection_info* conn_info, int reason) {	
	if (conn_info->session) {
		conn_info->session->on_closed(reason);
		unbind_session_connection(conn_info, conn_info->session);
	}
	if (conn_info->conn_buffev)
		bufferevent_free(conn_info->conn_buffev);

	if (conn_info->session_creator)
		conn_info->session_creator->netstatistics.incoming_conn_close_count++;

	delete conn_info;
}

inline void flush_connection(struct connection_info* conn_info) {
	if (conn_info && conn_info->conn_buffev)
		bufferevent_flush(conn_info->conn_buffev, EV_WRITE, BEV_FLUSH);
}

//新连接回调
void new_connection_cb(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);

//读取数据回调
void conn_readcb(struct bufferevent *bev, void *user_data);

//写数据回调
void conn_writecb(struct bufferevent *bev, void *user_data);

//网络事件回调
void conn_eventcb(struct bufferevent *bev, short events, void *user_data);

//处理网络数据（已建立会话）
int process_session_data(IODSession* session, struct bufferevent *bev);

//处理网络数据（未建立会话）
int process_none_session_data(IODSessionManager* session_creator, connection_info* conn_info);

}

//绑定网络连接和会话
inline void bind_session_connection(struct connection_info* conn_info, IODSession* session, int net_state) {
	session->conn_info = conn_info;
	conn_info->session = session;
	session->set_net_state((IODSession::session_net_state)net_state);
}

inline void unbind_session_connection(struct connection_info* conn_info, IODSession* session) {
	if (conn_info->session == session)
		conn_info->session = 0;
	if (session->conn_info == conn_info)
		session->conn_info = 0;
	session->set_net_state(IODSession::SNS_NONE);
}

#endif
