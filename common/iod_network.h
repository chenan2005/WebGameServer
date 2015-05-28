#pragma once

#include "iod_packet.h"
#include "iod_session.h"
#include "iod_session_creator.h"

#define DEFAULT_CONNECTION_HIGHMARK 1048576u

#ifdef WIN32
#define iod_net_last_errno WSAGetLastError()
#else
#define iod_net_last_errno errno
#endif

namespace iod_network {

enum 
{
	CONNECTION_CLOSE_BY_LOCAL = 0,
	CONNECTION_CLOSE_BY_REMOTE = 1,
	CONNECTION_CLOSE_BY_TIMEOUT = 2,
	CONNECTION_CLOSE_BY_NETERROR = 3,
};

extern struct event_base *evbase;

//��ʼ��
bool initialize();

//����
inline int update() {
	event_base_loop(evbase, EVLOOP_ONCE | EVLOOP_NONBLOCK);
	return 0;
}

//����
inline void shutdown() {
	if(evbase)	event_base_free(evbase);
}

//��������
struct listener_info* start_listener(iod_session_creator* session_creator, //�Ի�������
	const char* bind_addr,  //������ַ����ʽΪ hostname:port
	int conn_timeout_secs = 120,		//ÿ�����ӵĳ�ʱʱ�䣺������ʱ��û���յ�������ر�����
	int conn_highmark = DEFAULT_CONNECTION_HIGHMARK		//���������ޣ�����������г���highmark�ֽ�δ�������ٽ������ݡ�0Ϊ������
	);

//����Զ�̵�ַ
struct connection_info* start_connection(iod_session* session,	//������Ϣ�ĶԻ�ʵ��
	const char* target_addr,  //Ŀ���ַ����ʽΪ hostname:port
	int conn_timeout_secs = 120,		//ÿ�����ӵĳ�ʱʱ�䣺������ʱ��û���յ�������ر�����
	int conn_highmark = DEFAULT_CONNECTION_HIGHMARK		//���������ޣ�����������г���highmark�ֽ�δ�������ٽ������ݡ�0Ϊ������
	);

//�رռ���
inline void shutdown_listener(struct listener_info* l_info) {
	if (l_info->listener)
		evconnlistener_free(l_info->listener);
	delete l_info;
}

//�ر�/��������
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

//�����ӻص�
void new_connection_cb(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);

//��ȡ���ݻص�
void conn_readcb(struct bufferevent *bev, void *user_data);

//д���ݻص�
void conn_writecb(struct bufferevent *bev, void *user_data);

//�����¼��ص�
void conn_eventcb(struct bufferevent *bev, short events, void *user_data);

//�����������ݣ��ѽ����Ự��
int process_session_data(iod_session* session, struct bufferevent *bev);

//�����������ݣ�δ�����Ự��
int process_none_session_data(iod_session_creator* session_creator, connection_info* conn_info);

}

//���������ӺͻỰ
inline void bind_session_connection(struct connection_info* conn_info, iod_session* session, int net_state) {
	session->conn_info = conn_info;
	conn_info->session = session;
	session->set_net_state((iod_session::session_net_state)net_state);
}

inline void unbind_session_connection(struct connection_info* conn_info, iod_session* session) {
	if (conn_info->session == session)
		conn_info->session = 0;
	if (session->conn_info == conn_info)
		session->conn_info = 0;
	session->set_net_state(iod_session::SNS_NONE);
}
