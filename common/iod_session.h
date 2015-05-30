#ifndef __IOD_SESSION_H__
#define __IOD_SESSION_H__

/**
********************************************************************************************
会话基类。实现了缺省的消息解析函数（使用protobuff），缺省的关闭行为等
********************************************************************************************
*/

#include "iod_packet.h"
#include "iod_timer_handler.h"

class iod_session;
class iod_session_creator;

struct connection_info
{
	iod_session_creator* session_creator;
	iod_session* session;
	struct bufferevent *conn_buffev;
	int timeout_secs;
	int highmark;
};

class iod_session : public iod_timer_handler
{
	friend void bind_session_connection(struct connection_info *, iod_session *, int);
	friend void unbind_session_connection(struct connection_info *, iod_session *);

public:

	//会话的网络状态
	enum session_net_state
	{
		SNS_NONE = 0,
		SNS_CONNECTING,
		SNS_CONNECTED,
	};
	
	iod_session();

	virtual ~iod_session(void);

	//----------------------------------------------------
	//重载回调
	//----------------------------------------------------

	inline virtual iod_packet* create_packet() { return iod_packet::create(); }

	inline virtual void destroy_packet(iod_packet* packet) { iod_packet::destroy(packet); } 

	virtual void on_packet(iod_packet* packet) = 0;

	virtual void on_connected();

	virtual void on_closed(int reason);


	//----------------------------------------------------
	//行为
	//----------------------------------------------------

	bool connect(const char* target_addr);

	void close(int reason = 0);

	bool send(iod_packet* packet);

	void flush();

	//----------------------------------------------------
	//属性
	//----------------------------------------------------

	inline struct connection_info * get_connection_info() const { return conn_info; }

	inline session_net_state get_net_stat() const { return net_state; }

	inline unsigned int get_last_net_state_time() const { return last_net_state_time; }

	//----------------------------------------------------

private:

	void set_net_state(session_net_state net_state);

	struct connection_info *conn_info;

	session_net_state net_state;

	unsigned int last_net_state_time;
};

#endif
