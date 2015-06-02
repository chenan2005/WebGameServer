#include "test_client_pb_session.h"
#include "iod_test.pb.h"
#include "iod_logsystem.h"

using namespace iod_pb::test;

REG_PROTO_MSG_HANDLE_BEGIN(test_client_protobuf_session, iod_session_pb)

ADD_PROTO_MSG_HANDLE(_res_authentication, test_client_protobuf_session::on_res_authentication)
ADD_PROTO_MSG_HANDLE(_res_login, test_client_protobuf_session::on_res_login)
ADD_PROTO_MSG_HANDLE(_res_test_info, test_client_protobuf_session::on_res_test_info)
ADD_PROTO_MSG_HANDLE(_res_test_response_time, test_client_protobuf_session::on_res_test_response_time)
ADD_PROTO_MSG_HANDLE(_notify_kickout, test_client_protobuf_session::on_notify_kickout)

REG_PROTO_MSG_HANDLE_END(test_client_protobuf_session)

test_client_protobuf_session::test_client_protobuf_session(void) : login_stat(LOGIN_STATE_NONE), last_send_command_time(0), next_try_login_time(0)
{
	username[0] = 0;
}

test_client_protobuf_session::~test_client_protobuf_session(void)
{
}

void test_client_protobuf_session::on_closed( int reason )
{
	//iod_log_info("user %s, connection closed %d", get_username(), reason);

	set_login_state(LOGIN_STATE_NONE);
}

void test_client_protobuf_session::set_username( const char* username, int length /*= 0*/ )
{
	if (length == 0)
		length = (int)strlen(username);
	
	if (length >= sizeof(this->username))
		length = sizeof(this->username) - 1;

	memcpy(this->username, username, length);
	this->username[length] = 0;
}

void test_client_protobuf_session::send_req_authentication(const char* authentication, int length)
{
	if (length == 0)
		length = (int)strlen(authentication);

	req_authentication req;
	req.set_userid(get_username());
	req.set_authentication(authentication, length);

	send_message(_req_authentication, req);

	set_login_state(LOGIN_STATE_AUTHENTICATING);

	update_last_send_command_time();
}

void test_client_protobuf_session::send_req_login(const char* authorization, int length /*= 0*/)
{
	if (length == 0)
		length = (int)strlen(authorization);

	req_login req;
	req.set_userid(get_username());
	req.set_authorization(authorization, length);

	send_message(_req_login, req);

	set_login_state(LOGIN_STATE_LOGINING);

	update_last_send_command_time();
}

void test_client_protobuf_session::send_req_test_info(const char* info, int length /*= 0*/)
{
	if (length == 0)
		length = (int)strlen(info);
	
	req_test_info req;
	req.set_info(info, length);

	send_message(_req_test_info, req);

	update_last_send_command_time();
}

void test_client_protobuf_session::send_req_logout()
{
	req_logout req;
	send_message(_req_logout, req);
	update_last_send_command_time();
}

void test_client_protobuf_session::send_req_test_response_time(ev_uint64_t t)
{
	req_test_response_time req;
	req.set_req_timestamp(t);
	send_message(_req_test_response_time, req);
	//update_last_send_command_time();
}

void test_client_protobuf_session::on_res_authentication(iod_pb::common::base_msg* msg)
{
	SAFE_GET_EXTENSION(msg, res_authentication, res);
	if (res.result() == 0) {
		set_login_state(LOGIN_STATE_AUTHENTICATED);
		this->authorization = res.authorization();
	}
	else {
		set_login_state(LOGIN_STATE_NONE);
	}
}

void test_client_protobuf_session::on_res_login(iod_pb::common::base_msg* msg)
{
	SAFE_GET_EXTENSION(msg, res_login, res);
	if (res.result() == 0) {
		set_login_state(LOGIN_STATE_LOGINED);
	}
	else {
		set_login_state(LOGIN_STATE_NONE);
	}
}

void test_client_protobuf_session::on_res_test_info(iod_pb::common::base_msg* msg)
{
	SAFE_GET_EXTENSION(msg, res_test_info, res);
}

void test_client_protobuf_session::on_res_test_response_time(iod_pb::common::base_msg* msg)
{
	SAFE_GET_EXTENSION(msg, res_test_response_time, res);
	iod_log_info("user %s, response time %llu", get_username(), iod_utility::get_time_usec() - res.req_timestamp());
}

void test_client_protobuf_session::on_notify_kickout(iod_pb::common::base_msg* msg)
{
	SAFE_GET_EXTENSION(msg, notify_kickout, notify);
	iod_log_info("user %s kickout by server, reason %d", get_username(), notify.kick_reason());
}
