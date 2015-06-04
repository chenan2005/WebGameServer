#include "test_server_pb_session.h"
#include "IODLogSystem.h"
#include "IODTest.pb.h"

using namespace com::iod::pb::test;

REG_PROTO_MSG_HANDLE_BEGIN(test_server_pb_session, IODSessionPb)

ADD_PROTO_MSG_HANDLE(ReqLogin, test_server_pb_session::onReqLogin);
ADD_PROTO_MSG_HANDLE(ReqTestInfo, test_server_pb_session::onReqTestInfo);
ADD_PROTO_MSG_HANDLE(ReqLogout, test_server_pb_session::onReqLogout);
ADD_PROTO_MSG_HANDLE(ReqTestResponseTime, test_server_pb_session::onReqTestResponseTime);
ADD_PROTO_MSG_HANDLE(TestMsg1, test_server_pb_session::onTestMsg1);

REG_PROTO_MSG_HANDLE_END(test_server_pb_session)


test_server_pb_session::test_server_pb_session(void) : login_stat(LOGIN_STATE_NONE), last_send_command_time(0)
{
	username[0] = 0;
}

test_server_pb_session::~test_server_pb_session(void)
{
}

void test_server_pb_session::onReqLogin(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, ReqLogin, req);

	set_login_state(LOGIN_STATE_LOGINED);
}

void test_server_pb_session::onReqTestInfo(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, ReqTestInfo, req);
	ResTestInfo res;
	res.set_info("response" + req.info());
	SESSION_SEND_MESSAGE(ResTestInfo, res);
}

void test_server_pb_session::onReqLogout( com::iod::pb::common::BaseMsg* msg )
{
	SAFE_GET_EXTENSION(msg, ReqLogout, req);
	close(0);
}

void test_server_pb_session::onReqTestResponseTime(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, ReqTestResponseTime, req);
	ResTestResponseTime res;
	res.set_req_timestamp(req.req_timestamp());
	SESSION_SEND_MESSAGE(ResTestResponseTime, res);
}

void test_server_pb_session::onTestMsg1(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, TestMsg1, req);
	TestMsg1 res;
	res.set_test_data("dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;"
		"dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;");
	SESSION_SEND_MESSAGE(TestMsg1, res);
}

void test_server_pb_session::on_closed( int reason )
{
	//iod_log_info("user %s, connection closed %d", get_username(), reason);

	login_stat = LOGIN_STATE_NONE;
}

void test_server_pb_session::set_username( const char* username, int length /*= 0*/ )
{
	if (length == 0)
		length = (int)strlen(username);
	
	if (length >= sizeof(this->username))
		length = sizeof(this->username) - 1;

	memcpy(this->username, username, length);
	this->username[length] = 0;
}
