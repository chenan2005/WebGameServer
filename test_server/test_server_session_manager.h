#pragma once

#include "IODSessionManager.h"

class test_server_session;

class test_server_session_manager :
	public IODSessionManager
{
public:

	test_server_session_manager(void);

	virtual ~test_server_session_manager(void);

	void check_sessions();

	inline unsigned int get_session_count() const { return (unsigned int)sessions.size(); }

	virtual IODSession* on_none_session_packet(connection_info* conn_info, IODPacket* packet);

	virtual IODPacket* preproc_session_packet(IODSession* session, IODPacket* packet);

	unsigned int create_session_count;

	unsigned int destroy_session_count;

	listener_info* l_info;

protected:

	std::map< std::string, test_server_session* > sessions;
};
