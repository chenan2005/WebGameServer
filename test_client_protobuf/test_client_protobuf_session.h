#pragma once
#include "iod_session_with_proto_base_msg.h"
#include "common/iod_common.pb.h"

class test_client_protobuf_session :
	public iod_session_with_proto_base_msg
{
public:

	enum {
		LOGIN_STATE_NONE = 0,
		LOGIN_STATE_LOGINING,
		LOGIN_STATE_LOGINED,
	};

	test_client_protobuf_session(void);
	virtual ~test_client_protobuf_session(void);

	virtual void on_message(iod::protobuf::common::base_msg* msg);

	virtual void on_closed(int reason);

	void set_username(const char* username, int length = 0);

	void start_login(const char* authentication, int length);

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
