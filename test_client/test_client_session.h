#pragma once
#include "IODSession.h"

class test_client_session :
	public IODSession
{
public:

	enum {
		LOGIN_STATE_NONE = 0,
		LOGIN_STATE_LOGINING,
		LOGIN_STATE_LOGINED,
	};

	test_client_session(void);

	virtual ~test_client_session(void);

	void set_username(const char* username, int length = 0);

	void send_command(const char* cmd, const char* data, int data_length = 0);

	inline const char* get_username() const {
		return username;
	}

	inline int get_login_state() const {
		return login_stat;
	}

	inline unsigned int get_last_send_command_time() const {
		return last_send_command_time;
	}

	virtual void on_packet(IODPacket* packet);

	virtual void on_closed(int reason);

protected:

	inline void set_login_state(int state) {
		this->login_stat = state;
	}

	char username[32];

	int login_stat;

	unsigned int last_send_command_time;
};
