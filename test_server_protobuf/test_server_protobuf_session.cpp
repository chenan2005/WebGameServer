#include "test_server_protobuf_session.h"
#include "iod_logsystem.h"
#include "iod_test.pb.h"

test_server_protobuf_session::test_server_protobuf_session(void) : login_stat(LOGIN_STATE_NONE), last_send_command_time(0)
{
	username[0] = 0;

	msg_handler_map[iod::protobuf::test::kReqLoginFieldNumber] = (GProtoHandlerFunc)&test_server_protobuf_session::on_req_login;
}

test_server_protobuf_session::~test_server_protobuf_session(void)
{
}

void test_server_protobuf_session::on_message( iod::protobuf::common::base_msg* msg )
{
	if (msg->HasExtension(iod::protobuf::test::_req_authentication))
	{
		iod_log_info("receive login req");
	}
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

void test_server_protobuf_session::on_req_login( iod::protobuf::common::base_msg* msg )
{

}
