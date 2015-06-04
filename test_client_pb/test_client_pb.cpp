#include "test_client_pb.h"
#include "IODCommon.h"
#include "test_client_pb_session.h"
#include "IODLogSystem.h"

IMPLEMENT_SINGLETON_INSTANCE(test_client_pb);

const int TEST_SESSION_COUNT = 200;

test_client_pb::test_client_pb(void)
{
}

test_client_pb::~test_client_pb(void)
{
}

bool test_client_pb::initialize_server()
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

int test_client_pb::update_server()
{
	std::set< test_client_protobuf_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		test_client_protobuf_session* session = *it;
		if (session->get_net_stat() == IODSession::SNS_NONE && IODUtility::get_time_msec() > session->get_next_try_login_time()) {
			session->connect("127.0.0.1:12345");
		}
		else if (session->get_net_stat() == IODSession::SNS_CONNECTED && IODUtility::get_time_msec() > session->get_last_send_command_time() + 5) {
			
			if (session->get_login_state() == test_client_protobuf_session::LOGIN_STATE_NONE) {
				session->sendReqAuthentication(session->get_username());
			}
			else if (session->get_login_state() == test_client_protobuf_session::LOGIN_STATE_AUTHENTICATED) {
				session->sendReqLogin(session->get_authorization().c_str());
			}
			else if (session->get_login_state() == test_client_protobuf_session::LOGIN_STATE_LOGINED) {
				int randvalue = rand() % 500;
				if (randvalue == 1)
					session->sendReqLogout();
				else
					session->sendReqTestInfo("test info");
				//session->send_req_test_info("test info");
			}
		}
		it++;
	}
	
	return 0;
}

void test_client_pb::shutdown_server()
{
	std::set< test_client_protobuf_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		delete *it;
		it++;
	}
}

void test_client_pb::on_winsys_kbhit(int c)
{
	if (c == 'p') {
		std::set< test_client_protobuf_session* >::iterator it = sessions.begin();
		bool has_send = false;
		while (it != sessions.end()) {
			test_client_protobuf_session* session = *it;
			if (session->get_login_state() == test_client_protobuf_session::LOGIN_STATE_LOGINED) {
				session->sendReqTestResponseTime(IODUtility::get_time_usec());
				has_send = true;
				break;
			}
			it++;
		}
		if (!has_send) {
			iod_log_error("no logined session!");
		}
	}
}

void test_client_pb::print_help_info()
{
#ifdef WIN32
	iod_log_info("\n  q: quit server"
		"\n  r: reload server config"
		"\n  p: test ping response time");
#endif
}
