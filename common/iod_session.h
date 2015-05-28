/**
********************************************************************************************
�Ự���ࡣʵ����ȱʡ����Ϣ����������ʹ��protobuff����ȱʡ�Ĺر���Ϊ��
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

	//�Ự������״̬
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
	//��Ϊ
	//----------------------------------------------------

	bool connect(const char* target_addr);

	void close(int reason);

	//----------------------------------------------------
	//�ص�
	//----------------------------------------------------

	virtual iod_packet* create_packet() { return iod_packet::create(); }

	virtual void on_packet(iod_packet* packet);

	virtual void on_connected();

	virtual void on_closed(int reason);

	//----------------------------------------------------
	//����
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
