#include "test_server_protobuf_session.h"
#include "iod_logsystem.h"
#include "iod_test.pb.h"

REG_PROTO_MSG_HANDLE_BEGIN(test_server_protobuf_session, iod_session_with_proto_base_msg)

ADD_PROTO_MSG_HANDLE(iod::protobuf::test::kReqTestInfoFieldNumber, test_server_protobuf_session::on_req_test_info);
ADD_PROTO_MSG_HANDLE(iod::protobuf::test::kReqLogoutFieldNumber, test_server_protobuf_session::on_req_logout);

REG_PROTO_MSG_HANDLE_END(test_server_protobuf_session)


test_server_protobuf_session::test_server_protobuf_session(void) : login_stat(LOGIN_STATE_NONE), last_send_command_time(0)
{
	username[0] = 0;
}

test_server_protobuf_session::~test_server_protobuf_session(void)
{
}

void test_server_protobuf_session::on_req_test_info(iod::protobuf::common::base_msg* msg)
{

}

void test_server_protobuf_session::on_req_logout( iod::protobuf::common::base_msg* msg )
{

}

void test_server_protobuf_session::on_closed( int reason )
{
	//iod_log_info("user %s, connection closed %d", get_username(), reason);

	login_stat = LOGIN_STATE_NONE;
}

void test_server_protobuf_session::set_username( const char* username, int length /*= 0*/ )
{
	if (length == 0)
		length = (int)strlen(username);
	
	if (length >= sizeof(this->username))
		length = sizeof(this->username) - 1;

	memcpy(this->username, username, length);
	this->username[length] = 0;
}
