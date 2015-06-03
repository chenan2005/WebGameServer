#include "iod_webgame_session.h"
#include "iod_logsystem.h"
#include "iod_test.pb.h"

using namespace com::iod::pb::test;

REG_PROTO_MSG_HANDLE_BEGIN(iod_webgame_session, iod_session_pb)

ADD_PROTO_MSG_HANDLE(ReqLogin, iod_webgame_session::onReqLogin);
ADD_PROTO_MSG_HANDLE(ReqTestInfo, iod_webgame_session::onReqTestInfo);
ADD_PROTO_MSG_HANDLE(ReqLogout, iod_webgame_session::onReqLogout);
ADD_PROTO_MSG_HANDLE(ReqTestResponseTime, iod_webgame_session::onReqTestResponseTime);
ADD_PROTO_MSG_HANDLE(TestMsg1, iod_webgame_session::onTestMsg1);

REG_PROTO_MSG_HANDLE_END(iod_webgame_session)


iod_webgame_session::iod_webgame_session(void) : login_stat(LOGIN_STATE_NONE), last_send_command_time(0)
{
	username[0] = 0;
}

iod_webgame_session::~iod_webgame_session(void)
{
}

void iod_webgame_session::onReqLogin(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, ReqLogin, req);

	set_login_state(LOGIN_STATE_LOGINED);
}

void iod_webgame_session::onReqTestInfo(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, ReqTestInfo, req);
	ResTestInfo res;
	res.set_info("response" + req.info());
	SESSION_SEND_MESSAGE(ResTestInfo, res);
}

void iod_webgame_session::onReqLogout( com::iod::pb::common::BaseMsg* msg )
{
	SAFE_GET_EXTENSION(msg, ReqLogout, req);
	close(0);
}

void iod_webgame_session::onReqTestResponseTime(com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_EXTENSION(msg, ReqTestResponseTime, req);
	ResTestResponseTime res;
	res.set_req_timestamp(req.req_timestamp());
	SESSION_SEND_MESSAGE(ResTestResponseTime, res);
}

void iod_webgame_session::onTestMsg1(com::iod::pb::common::BaseMsg* msg)
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

void iod_webgame_session::on_closed( int reason )
{
	//iod_log_info("user %s, connection closed %d", get_username(), reason);

	login_stat = LOGIN_STATE_NONE;
}

void iod_webgame_session::set_username( const char* username, int length /*= 0*/ )
{
	if (length == 0)
		length = (int)strlen(username);
	
	if (length >= sizeof(this->username))
		length = sizeof(this->username) - 1;

	memcpy(this->username, username, length);
	this->username[length] = 0;
}
