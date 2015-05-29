#include "sample_session_manager.h"
#include "sample_session.h"
#include "test_helper.h"
#include "iod_utility.h"

sample_session_manager::sample_session_manager(void) : create_session_count(0), destroy_session_count(0)
{
}

sample_session_manager::~sample_session_manager(void)
{
	std::map< std::string, sample_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		delete it->second;
		it++;
	}
}

iod_session* sample_session_manager::on_none_session_packet( connection_info* conn_info, iod_packet* packet )
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
			sample_session* session = new sample_session;
			session->set_username(username);
			sessions[username] = session;
			create_session_count++;
		}

		return sessions[username];
	}

	return 0;
}

iod_packet* sample_session_manager::preproc_session_packet( iod_session* session, iod_packet* packet )
{
	return packet;
}

void sample_session_manager::check_sessions()
{
	std::map< std::string, sample_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		if (it->second->get_net_stat() != iod_session::SNS_CONNECTED
			&& iod_utility::get_time_msec() > it->second->get_last_net_state_time() + 20000) {
			delete it->second;
			destroy_session_count++;
			it = sessions.erase(it);
			continue;
		}
		it++;
	}
}
