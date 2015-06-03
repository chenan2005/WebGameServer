#pragma once
#include "iod_session_pb.h"

class iod_webgame_session :
	public iod_session_pb
{
	DEC_REG_PROTO_MSG_HANDLE(iod_webgame_session)

public:

	enum {
		LOGIN_STATE_NONE = 0,
		LOGIN_STATE_LOGINING,
		LOGIN_STATE_LOGINED,
	};

	iod_webgame_session(void);

	virtual ~iod_webgame_session(void);

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

	virtual void onReqLogin(com::iod::pb::common::BaseMsg* msg);

	virtual void onReqTestInfo(com::iod::pb::common::BaseMsg* msg);

	virtual void onReqLogout(com::iod::pb::common::BaseMsg* msg);

	virtual void onReqTestResponseTime(com::iod::pb::common::BaseMsg* msg);

	virtual void onTestMsg1(com::iod::pb::common::BaseMsg* msg);

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
