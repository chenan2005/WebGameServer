#pragma once

#include "iod_session_manager_pb.h"

class test_server_pb_session;

class test_server_pb_session_manager :
	public iod_session_manager_pb
{
	DEC_REG_PROTO_MSG_HANDLE(test_server_pb_session_manager)

public:

	test_server_pb_session_manager(void);

	virtual ~test_server_pb_session_manager(void);

	void kickout(iod_session* session, int reason);

	void random_kick(int num);

	void check_sessions();

	//---------------------------------------------------------------------
	//message handlers
	//---------------------------------------------------------------------

	virtual iod_session* on_req_authentication(struct connection_info* conn_info, iod_pb::common::base_msg* msg);

	virtual iod_session* on_req_login(struct connection_info* conn_info, iod_pb::common::base_msg* msg);

	inline unsigned int get_session_count() const { return (unsigned int)sessions.size(); }

	//---------------------------------------------------------------------

	unsigned int create_session_count;

	unsigned int destroy_session_count;

	listener_info* l_info;

protected:

	bool validate_authentication(const std::string& userid, const std::string& authentication, std::string& authorization);

	bool validate_authorization(const std::string& userid, const std::string& authorization);

	std::map< std::string, test_server_pb_session* > sessions;
};
