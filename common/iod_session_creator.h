#pragma once

#include "iod_session.h"

struct listener_info {
	iod_session_creator* session_creator;
	struct evconnlistener* listener;
	int timeout_secs;
	int highmark;
};

class iod_session_creator
{
public:
	iod_session_creator(void);
	virtual ~iod_session_creator(void);

	virtual iod_packet* create_packet() { return iod_packet::create(); }
	virtual iod_session* on_none_session_packet(connection_info* conn_info, iod_packet* packet);
};
