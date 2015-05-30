#pragma once

#include "iod_session_manager.h"

class test_server_session;

class test_server_session_manager :
	public iod_session_manager
{
public:
	test_server_session_manager(void);
	virtual ~test_server_session_manager(void);

	virtual iod_session* on_none_session_packet(connection_info* conn_info, iod_packet* packet);

	virtual iod_packet* preproc_session_packet(iod_session* session, iod_packet* packet);

	void check_sessions();

	inline unsigned int get_session_count() const { return (unsigned int)sessions.size(); }

	unsigned int create_session_count;

	unsigned int destroy_session_count;

	listener_info* l_info;

protected:

	std::map< std::string, test_server_session* > sessions;
};
