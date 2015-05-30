#include "test_client_protobuf_session.h"
#include "iod_test.pb.h"

test_client_protobuf_session::test_client_protobuf_session(void) : login_stat(LOGIN_STATE_NONE), last_send_command_time(0)
{
	username[0] = 0;
}

test_client_protobuf_session::~test_client_protobuf_session(void)
{
}

void test_client_protobuf_session::on_message( iod::protobuf::common::base_msg* msg )
{

}

void test_client_protobuf_session::on_closed( int reason )
{
	//iod_log_info("user %s, connection closed %d", get_username(), reason);

	login_stat = LOGIN_STATE_NONE;
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

void test_client_protobuf_session::start_login( const char* authentication, int length )
{
	iod::protobuf::test::req_authentication req;
	req.set_userid(get_username());
	req.set_authentication(authentication, length);

	iod::protobuf::common::base_msg msg;
	msg.MutableExtension(iod::protobuf::test::_req_authentication)->CopyFrom(req);

	msg.set_messge_id(iod::protobuf::test::kReqAuthenticationFieldNumber);

	send_message(&msg);

	set_login_state(LOGIN_STATE_LOGINING);
}
