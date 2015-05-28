/**
********************************************************************************************
会话基类。实现了缺省的消息解析函数（使用protobuff），缺省的关闭行为等
********************************************************************************************
*/

#pragma once

#include "iod_packet.h"

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

class iod_session
{
	friend void bind_connection_session(struct connection_info *, iod_session *);

public:

	//会话的网络状态
	enum session_net_state
	{
		SNS_NONE = 0,
		SNS_CONNECTING,
		SNS_CONNECTED,
		SNS_LOST,
	};
	
	iod_session();

	virtual ~iod_session(void);

	//----------------------------------------------------
	//行为
	//----------------------------------------------------

	bool connect(const char* target_addr);

	void close(int reason);

	//----------------------------------------------------
	//回调
	//----------------------------------------------------

	virtual iod_packet* create_packet() { return iod_packet::create(); }

	virtual void on_packet(iod_packet* packet);

	virtual void on_connected();

	virtual void on_closed(int reason);

	//----------------------------------------------------
	//属性
	//----------------------------------------------------

	inline const struct connection_info * get_connection_info() const { return conn_info; }

	inline session_net_state get_net_stat() const { return net_state; }

	//----------------------------------------------------

private:

	void set_net_state(session_net_state net_state);

	struct connection_info *conn_info;

	session_net_state net_state;

	unsigned int last_net_state_time;
};
