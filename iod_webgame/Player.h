#pragma once
#include "IODSessionPb.h"

class Room;

class Player :
	public IODSessionPb
{
	DEC_REG_PROTO_MSG_HANDLE(Player)

public:

	enum {
		LOGIN_STATE_NONE = 0,
		LOGIN_STATE_LOGINING,
		LOGIN_STATE_LOGINED,
	};

	Player(void);

	virtual ~Player(void);

	Room* createRoom();

	bool joinRoom(int roomId);

	bool leaveRoom();

	bool startGame(int gameId);

	bool leaveGame();

	void setAccount(const std::string& account) { this->account = account; }

	inline const std::string& getAccount() const { return account;}

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

	virtual void onReqCreateRole(com::iod::pb::common::BaseMsg* msg);

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

	std::string account;

	int login_stat;

	unsigned int last_send_command_time;

private:

	int roomId;

	int gameId;
};
