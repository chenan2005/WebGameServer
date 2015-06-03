#pragma once
#include "iod_session_pb.h"

class test_server_pb_session :
	public iod_session_pb
{
	DEC_REG_PROTO_MSG_HANDLE(test_server_pb_session)

public:

	enum {
		LOGIN_STATE_NONE = 0,
		LOGIN_STATE_LOGINING,
		LOGIN_STATE_LOGINED,
	};

	test_server_pb_session(void);

	virtual ~test_server_pb_session(void);

	void set_username(const char* username, int length = 0);

	inline const char* get_username() const {
		return username;
	}

	inline int get_login_state() const {
		return login_stat;
	}

	inline unsigned int get_last_send_command_time() const {
		return last_send_command_time;
	}

	virtual void on_closed(int reason);

	//---------------------------------------------------------------------
	//message handlers
	//---------------------------------------------------------------------

	virtual void on_req_login(com::iod::pb::common::base_msg* msg);

	virtual void on_req_test_info(com::iod::pb::common::base_msg* msg);

	virtual void on_req_logout(com::iod::pb::common::base_msg* msg);

	virtual void on_req_test_response_time(com::iod::pb::common::base_msg* msg);

	//--------------------------------------------------

	//--------------------------------------------------
	//timer handlers
	//--------------------------------------------------

	virtual void on_timer_close_session(void*) { close(); }

	//--------------------------------------------------

protected:

	inline void set_login_state(int state) {
		this->login_stat = state;
	}

	char username[32];

	int login_stat;

	unsigned int last_send_command_time;
};
