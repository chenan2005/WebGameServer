#ifndef __IOD_SESSION_MANAGER_H__
#define __IOD_SESSION_MANAGER_H__

#include "IODSession.h"

class IODSessionManager;

struct listener_info {
	IODSessionManager* session_creator;
	struct evconnlistener* listener;
	int timeout_secs;
	int highmark;
};

struct iod_netstatistics
{
	ev_uint64_t recv_byte_count;
	ev_uint64_t send_byte_count;
	ev_uint32_t recv_packet_count;
	ev_uint32_t send_packet_count;
	ev_uint32_t incoming_conn_count;
	ev_uint32_t incoming_conn_close_count;
};

class IODSessionManager : public IODTimerHandler
{
public:

	IODSessionManager(void);

	virtual ~IODSessionManager(void);

	bool send_to(connection_info* conn_info, IODPacket* packet);

	inline virtual IODPacket* create_packet() { 
		return IODPacket::create(); 
	}

	inline virtual void destroy_packet(IODPacket* packet) { 
		IODPacket::destroy(packet); 
	}

	virtual IODSession* on_none_session_packet(connection_info* conn_info, IODPacket* packet) = 0;

	iod_netstatistics netstatistics;
};

#endif
