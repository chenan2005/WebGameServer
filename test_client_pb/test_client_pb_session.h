#pragma once
#include "IODSessionPb.h"
#include "common/IODCommon.pb.h"

class test_client_protobuf_session :
	public IODSessionPb
{

	DEC_REG_PROTO_MSG_HANDLE(test_client_protobuf_session)

public:

	enum {
		LOGIN_STATE_NONE = 0,
		LOGIN_STATE_AUTHENTICATING,
		LOGIN_STATE_AUTHENTICATED, 
		LOGIN_STATE_LOGINING,
		LOGIN_STATE_LOGINED,
	};

	test_client_protobuf_session(void);

	virtual ~test_client_protobuf_session(void);

	//----------------------------------------------------------
	//message senders
	//----------------------------------------------------------

	void sendReqAuthentication(const char* authentication, int length = 0);

	void sendReqLogin(const char* authorization, int length = 0);

	void sendReqTestInfo(const char* info, int length = 0);

	void sendReqLogout();

	void sendReqTestResponseTime(ev_uint64_t t);

	//----------------------------------------------------------

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

	inline const string& get_authorization() const {
		return authorization;
	}

	inline unsigned int get_next_try_login_time() const {
		return next_try_login_time;
	}

	//---------------------------------------------------------------------
	//message handlers
	//---------------------------------------------------------------------

	virtual void onResAuthentication(com::iod::pb::common::BaseMsg* msg);

	virtual void onResLogin(com::iod::pb::common::BaseMsg* msg);

	virtual void onResTestInfo(com::iod::pb::common::BaseMsg* msg);

	virtual void onResTestResponseTime(com::iod::pb::common::BaseMsg* msg);

	virtual void onNotifyKickout(com::iod::pb::common::BaseMsg* msg);

	//---------------------------------------------------------------------

	virtual void on_closed(int reason);

protected:

	inline void update_last_send_command_time() {
		last_send_command_time = IODUtility::get_time_msec();
	}

	inline void set_login_state(int state) {
		if (state != this->login_stat) {
			this->login_stat = state;
			if (state == LOGIN_STATE_NONE)
				next_try_login_time = IODUtility::get_time_msec() + rand() % 11000;
		}
	}

	char username[32];

	std::string authorization;

	int login_stat;

	unsigned int last_send_command_time;

	unsigned int next_try_login_time;
};
