#pragma once
#include "iod_session.h"

class test_client_session :
	public iod_session
{
public:

	enum {
		LOGIN_STATE_NONE = 0,
		LOGIN_STATE_LOGINING,
		LOGIN_STATE_LOGINED,
	};

	test_client_session(void);
	virtual ~test_client_session(void);

	virtual void on_packet(iod_packet* packet);

	virtual void on_closed(int reason);

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

protected:

	inline void set_login_state(int state) {
		this->login_stat = state;
	}

	char username[32];

	int login_stat;

	unsigned int last_send_command_time;
};
