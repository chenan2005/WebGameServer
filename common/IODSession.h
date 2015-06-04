#ifndef __IOD_SESSION_H__
#define __IOD_SESSION_H__

/**
********************************************************************************************
会话基类。实现了缺省的消息解析函数（使用protobuff），缺省的关闭行为等
********************************************************************************************
*/

#include "IODPacket.h"
#include "IODTimerHandler.h"

class IODSession;
class IODSessionManager;

struct connection_info
{
	IODSessionManager* session_creator;
	IODSession* session;
	struct bufferevent *conn_buffev;
	int timeout_secs;
	int highmark;
};

class IODSession : public IODTimerHandler
{
public:

	//会话的网络状态
	enum session_net_state
	{
		SNS_NONE = 0,
		SNS_CONNECTING,
		SNS_CONNECTED,
	};
	
	IODSession();

	virtual ~IODSession(void);

	bool connect(const char* target_addr);

	void close(int reason = 0);

	bool send(IODPacket* packet);

	bool send_to(connection_info* conn_info, IODPacket* packet);

	void flush();

	inline struct connection_info * get_connection_info() const { return conn_info; }

	inline session_net_state get_net_stat() const { return net_state; }

	inline unsigned int get_last_net_state_time() const { return last_net_state_time; }

	inline virtual IODPacket* create_packet() { return IODPacket::create(); }

	inline virtual void destroy_packet(IODPacket* packet) { IODPacket::destroy(packet); } 

	virtual void on_packet(IODPacket* packet) = 0;

	virtual void on_connected();

	virtual void on_closed(int reason);

private:

	void set_net_state(session_net_state net_state);

	struct connection_info *conn_info;

	session_net_state net_state;

	unsigned int last_net_state_time;

	friend void bind_session_connection(struct connection_info *, IODSession *, int);

	friend void unbind_session_connection(struct connection_info *, IODSession *);

};

#endif
