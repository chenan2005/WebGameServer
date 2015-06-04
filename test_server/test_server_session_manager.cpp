#include "test_server_session_manager.h"
#include "test_server_session.h"
#include "test_helper.h"
#include "IODUtility.h"

test_server_session_manager::test_server_session_manager(void) : create_session_count(0), destroy_session_count(0), l_info(0)
{
}

test_server_session_manager::~test_server_session_manager(void)
{
	std::map< std::string, test_server_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		delete it->second;
		it++;
	}
}

IODSession* test_server_session_manager::on_none_session_packet( connection_info* conn_info, IODPacket* packet )
{
	if (test_helper::check_cmd(packet, SESSION_CMD_LOGIN)) {
		//iod_log_info("receive cmd %s", SESSION_CMD_LOGIN);
		int data_length = (int)strlen(SESSION_CMD_LOGIN);
		
		char username[32];
		int name_length = packet->get_length() - data_length;
		if (name_length >= sizeof(username))
			name_length = sizeof(username) - 1;		
		memcpy(username, packet->get_data() + data_length, name_length);
		username[name_length] = 0;
		
		if (sessions.find(username) == sessions.end()) {
			test_server_session* session = new test_server_session;
			session->set_username(username);
			sessions[username] = session;
			create_session_count++;
		}

		return sessions[username];
	}

	return 0;
}

IODPacket* test_server_session_manager::preproc_session_packet( IODSession* session, IODPacket* packet )
{
	return packet;
}

void test_server_session_manager::check_sessions()
{
	std::map< std::string, test_server_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		if (it->second->get_net_stat() != IODSession::SNS_CONNECTED
			&& IODUtility::get_time_msec() > it->second->get_last_net_state_time() + 10000) {
			delete it->second;
			destroy_session_count++;
			it = sessions.erase(it);
			continue;
		}
		it++;
	}
}
