#include "test_s_pb_conf_session.h"
#include "iod_logsystem.h"
#include "iod_test.pb.h"

using namespace com::iod::pb::test;

REG_PROTO_MSG_HANDLE_BEGIN(test_s_pb_conf_session, iod_session_pb)

ADD_PROTO_MSG_HANDLE(_req_login, test_s_pb_conf_session::on_req_login);
ADD_PROTO_MSG_HANDLE(_req_test_info, test_s_pb_conf_session::on_req_test_info);
ADD_PROTO_MSG_HANDLE(_req_logout, test_s_pb_conf_session::on_req_logout);
ADD_PROTO_MSG_HANDLE(_req_test_response_time, test_s_pb_conf_session::on_req_test_response_time);

REG_PROTO_MSG_HANDLE_END(test_s_pb_conf_session)


test_s_pb_conf_session::test_s_pb_conf_session(void) : login_stat(LOGIN_STATE_NONE), last_send_command_time(0)
{
	username[0] = 0;
}

test_s_pb_conf_session::~test_s_pb_conf_session(void)
{
}

void test_s_pb_conf_session::on_req_login(com::iod::pb::common::base_msg* msg)
{
	SAFE_GET_EXTENSION(msg, req_login, req);

	set_login_state(LOGIN_STATE_LOGINED);
}

void test_s_pb_conf_session::on_req_test_info(com::iod::pb::common::base_msg* msg)
{
	SAFE_GET_EXTENSION(msg, req_test_info, req);
	res_test_info res;
	res.set_info("response" + req.info());
	send_message(_res_test_info, res);
}

void test_s_pb_conf_session::on_req_logout( com::iod::pb::common::base_msg* msg )
{
	SAFE_GET_EXTENSION(msg, req_logout, req);
	close(0);
}

void test_s_pb_conf_session::on_req_test_response_time(com::iod::pb::common::base_msg* msg)
{
	SAFE_GET_EXTENSION(msg, req_test_response_time, req);
	res_test_response_time res;
	res.set_req_timestamp(req.req_timestamp());
	send_message(_res_test_response_time, res);
}

void test_s_pb_conf_session::on_closed( int reason )
{
	//iod_log_info("user %s, connection closed %d", get_username(), reason);

	login_stat = LOGIN_STATE_NONE;
}

void test_s_pb_conf_session::set_username( const char* username, int length /*= 0*/ )
{
	if (length == 0)
		length = (int)strlen(username);
	
	if (length >= sizeof(this->username))
		length = sizeof(this->username) - 1;

	memcpy(this->username, username, length);
	this->username[length] = 0;
}
