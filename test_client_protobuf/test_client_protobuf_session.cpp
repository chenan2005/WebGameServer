#include "test_client_protobuf_session.h"
#include "test_helper.h"

test_client_protobuf_session::test_client_protobuf_session(void) : login_stat(LOGIN_STATE_NONE), last_send_command_time(0)
{
	username[0] = 0;
}

test_client_protobuf_session::~test_client_protobuf_session(void)
{
}

void test_client_protobuf_session::on_packet( iod_packet* packet )
{
	if (test_helper::check_cmd(packet, SESSION_CMD_LOGIN)) {
		send_command(SESSION_CMD_LOGIN_RES, get_username());
	}
	if (test_helper::check_cmd(packet, SESSION_CMD_INFO)) {
		char info[1024];
		int data_length = packet->get_length();
		int cmd_length = (int)strlen(SESSION_CMD_INFO);
		if (data_length - cmd_length >= sizeof(info)) {
			memcpy(info, packet->get_data() + cmd_length, sizeof(info) - 1);
			info[sizeof(info) - 1] = 0;
		}
		else {
			memcpy(info, packet->get_data() + cmd_length, data_length - cmd_length);
			info[data_length - cmd_length] = 0;
		}
		//iod_log_info("user %s, receive info: %s", username, info);

		if ((rand() % 200) == 1) {
			send_command(SESSION_CMD_INFO, "test info response");
		}
	}
	else if (test_helper::check_cmd(packet, SESSION_CMD_LOGOUT)) {
		//iod_log_info("user %s, logout", get_username());
		close(0);
	}
	else if (test_helper::check_cmd(packet, SESSION_CMD_LOGIN_RES)) {
		//iod_log_info("user %s, login sucess", get_username());
		login_stat = LOGIN_STATE_LOGINED;
	}
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

void test_client_protobuf_session::send_command( const char* cmd, const char* data, int data_length /*= 0*/ )
{
	static char s_send_buffer[_MAX_PACKET_LENGTH];

	int cmd_length = (int)strlen(cmd);
	int packet_data_length = cmd_length;
	memcpy(s_send_buffer, cmd, cmd_length);
	if (data) {
		if (data_length) {
			memcpy(s_send_buffer + cmd_length, data, data_length);
			packet_data_length += data_length;
		}
		else {
			memcpy(s_send_buffer + cmd_length, data, strlen(data));
			packet_data_length += (int)strlen(data);
		}
	}

	iod_packet* packet = create_packet();
	packet->set_data(s_send_buffer, packet_data_length);
	send(packet);
	destroy_packet(packet);

	last_send_command_time = iod_utility::get_time_msec();

	if (strcmp(cmd, SESSION_CMD_LOGIN) == 0 && get_login_state() == LOGIN_STATE_NONE) {
		login_stat = LOGIN_STATE_LOGINING;
	}
}

