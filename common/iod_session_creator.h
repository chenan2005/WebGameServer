#pragma once

#include "iod_session.h"

struct listener_info {
	iod_session_creator* session_creator;
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

class iod_session_creator
{
public:
	iod_session_creator(void);
	virtual ~iod_session_creator(void);

	inline virtual iod_packet* create_packet() { 
		return iod_packet::create(); 
	}

	inline virtual void destroy_packet(iod_packet* packet) { 
		iod_packet::destroy(packet); 
	}

	virtual iod_session* on_none_session_packet(connection_info* conn_info, iod_packet* packet) = 0;

	iod_netstatistics netstatistics;

private:
};
