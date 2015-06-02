#include "test_client_pb_session.h"
#include "iod_test.pb.h"
#include "iod_logsystem.h"

using namespace com::iod::pb::test;

REG_PROTO_MSG_HANDLE_BEGIN(test_client_protobuf_session, iod_session_pb)

ADD_PROTO_MSG_HANDLE(ResAuthentication, test_client_protobuf_session::onResAuthentication)
ADD_PROTO_MSG_HANDLE(ResLogin, test_client_protobuf_session::onResLogin)
ADD_PROTO_MSG_HANDLE(ResTestInfo, test_client_protobuf_session::onResTestInfo)
ADD_PROTO_MSG_HANDLE(ResTestResponseTime, test_client_protobuf_session::onResTestResponseTime)
ADD_PROTO_MSG_HANDLE(NotifyKickout, test_client_protobuf_session::onNotifyKickout)

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

void test_client_protobuf_session::sendReqAuthentication(const char* authentication, int length)
{
	if (length == 0)
		length = (int)strlen(authentication);

	ReqAuthentication req;
	req.set_user_id(get_username());
	req.set_authentication(authentication, length);

	SESSION_SEND_MESSAGE(ReqAuthentication, req);

	set_login_state(LOGIN_STATE_AUTHENTICATING);

	update_last_send_command_time();
}

void test_client_protobuf_session::sendReqLogin(const char* authorization, int length /*= 0*/)
{
	if (length == 0)
		length = (int)strlen(authorization);

	ReqLogin req;
	req.set_user_id(get_username());
	req.set_authorization(authorization, length);

	SESSION_SEND_MESSAGE(ReqLogin, req);

	set_login_state(LOGIN_STATE_LOGINING);

	update_last_send_command_time();
}

void test_client_protobuf_session::sendReqTestInfo(const char* info, int length /*= 0*/)
{
	if (length == 0)
		length = (int)strlen(info);
	
	ReqTestInfo req;
	req.set_info(info, length);

	SESSION_SEND_MESSAGE(ReqTestInfo, req);

	update_last_send_command_time();
}

void test_client_protobuf_session::sendReqLogout()
{
	ReqLogout req;
	SESSION_SEND_MESSAGE(ReqLogout, req);
	update_last_send_command_time();
}

void test_client_protobuf_session::sendReqTestResponseTime(ev_uint64_t t)
{
	ReqTestResponseTime req;
	req.set_req_timestamp(t);
	SESSION_SEND_MESSAGE(ReqTestResponseTime, req);
	//update_last_send_command_time();
}

void test_client_protobuf_session::onResAuthentication(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, ResAuthentication, res);
	if (res.result() == 0) {
		set_login_state(LOGIN_STATE_AUTHENTICATED);
		this->authorization = res.authorization();
	}
	else {
		set_login_state(LOGIN_STATE_NONE);
	}
}

void test_client_protobuf_session::onResLogin(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, ResLogin, res);
	if (res.result() == 0) {
		set_login_state(LOGIN_STATE_LOGINED);
	}
	else {
		set_login_state(LOGIN_STATE_NONE);
	}
}

void test_client_protobuf_session::onResTestInfo(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, ResTestInfo, res);
}

void test_client_protobuf_session::onResTestResponseTime(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, ResTestResponseTime, res);
	iod_log_info("user %s, response time %llu", get_username(), iod_utility::get_time_usec() - res.req_timestamp());
}

void test_client_protobuf_session::onNotifyKickout(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, NotifyKickout, notify);
	iod_log_info("user %s kickout by server, reason %d", get_username(), notify.kick_reason());
}
