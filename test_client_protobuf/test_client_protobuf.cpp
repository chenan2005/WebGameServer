#include "test_client_protobuf.h"
#include "iod_common.h"
#include "test_client_protobuf_session.h"

implement_server_instance(test_client_protobuf);

const int TEST_SESSION_COUNT = 1;

test_client_protobuf::test_client_protobuf(void)
{
}

test_client_protobuf::~test_client_protobuf(void)
{
}

bool test_client_protobuf::initialize_server()
{
	for (int i = 0; i < TEST_SESSION_COUNT; i++) {
		test_client_protobuf_session* session = new test_client_protobuf_session();
		char username[32];
		sprintf(username, "test_user_%05d", i);
		session->set_username(username);
		sessions.insert(session);
	}

	srand((unsigned int)time(0));

	return true;
}

int test_client_protobuf::update_server()
{
	std::set< test_client_protobuf_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		test_client_protobuf_session* session = *it;
		if (session->get_net_stat() == iod_session::SNS_NONE && iod_utility::get_time_msec() > session->get_last_net_state_time() + 1000) {
			session->connect("127.0.0.1:12345");
		}
		else if (session->get_net_stat() == iod_session::SNS_CONNECTED && iod_utility::get_time_msec() > session->get_last_send_command_time() + 5) {
			
			if (session->get_login_state() == test_client_protobuf_session::LOGIN_STATE_NONE) {
				session->send_req_authentication(session->get_username());
			}
			else if (session->get_login_state() == test_client_protobuf_session::LOGIN_STATE_AUTHENTICATED) {
				session->send_req_login(session->get_authorization().c_str());
			}
			else if (session->get_login_state() == test_client_protobuf_session::LOGIN_STATE_LOGINED) {
				session->send_req_test_info("test info");
			}
		}
		it++;
	}
	
	return 0;
}

void test_client_protobuf::shutdown_server()
{
	std::set< test_client_protobuf_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		delete *it;
		it++;
	}
}
