#include "test_client.h"
#include "iod_common.h"
#include "test_helper.h"
#include "test_client_session.h"
#include "iod_logsystem.h"

implement_server_instance(test_client);

const int TEST_SESSION_COUNT = 2000;

test_client::test_client(void)
{
}

test_client::~test_client(void)
{
}

bool test_client::initialize_server()
{
	for (int i = 0; i < TEST_SESSION_COUNT; i++) {
		test_client_session* session = new test_client_session();
		char username[32];
		sprintf(username, "test_user_%05d", i);
		session->set_username(username);
		sessions.insert(session);
	}

	srand((unsigned int)time(0));

	return true;
}

int test_client::update_server()
{
	std::set< test_client_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		test_client_session* session = *it;
		if (session->get_net_stat() == iod_session::SNS_NONE && iod_utility::get_time_msec() > session->get_last_net_state_time() + 1000) {
			session->connect("127.0.0.1:12345");
		}
		else if (session->get_net_stat() == iod_session::SNS_CONNECTED && iod_utility::get_time_msec() > session->get_last_send_command_time() + 5) {
			
			if (session->get_login_state() == test_client_session::LOGIN_STATE_NONE) {
				session->send_command(SESSION_CMD_LOGIN, session->get_username());
			}
			else if (session->get_login_state() == test_client_session::LOGIN_STATE_LOGINED) {
				int r = rand() % 100;
				if (r == 1) {
					session->send_command(SESSION_CMD_LOGOUT, 0);
				}
				else {
					session->send_command(SESSION_CMD_INFO, "test info");
					session->send_command(SESSION_CMD_INFO, "test info 1");	
				}
				//session->send_command(SESSION_CMD_INFO, "test info");
			}
		}
		it++;
	}
	
	return 0;
}

void test_client::shutdown_server()
{
	std::set< test_client_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		delete *it;
		it++;
	}
}
