#pragma once
#include "IODSessionPb.h"
#include "IODWebGameCommon.pb.h"

using namespace com::iod::pb::webgame;

class Room;

class Player :
	public IODSessionPb
{
	DEC_PB_MSG_HANDLE(Player)

public:

	enum {
		LOGIN_STATE_NONE = 0,
		LOGIN_STATE_LOGINING,
		LOGIN_STATE_LOGINED,
	};

	Player(void);

	virtual ~Player(void);

	Room* createRoom(const RoomCreateOption& option);

	bool joinRoom(int roomId);

	bool leaveRoom();

	bool startGame(int gameId);

	bool leaveGame();

	void queryRoleInfo();

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

	virtual void* onReqLogin(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqTestInfo(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqLogout(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqTestResponseTime(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqCreateRole(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqCreateRoom(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqJoinRoom(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqLeaveRoom(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqStartGame(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqLeaveGame(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqBroadCastInfo(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onResCreateRoom(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onResLeaveRoom(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onDbResRoleInfo(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onDbResCreateRole(connection_info* conn_info, BaseMsgPb* msg);

	//--------------------------------------------------

	//--------------------------------------------------
	//timer handlers
	//--------------------------------------------------

	inline virtual void onTimerCloseSession(void*) { close(); }

	virtual void onTimerQueryRoleTimeout(void*);

	virtual void onTimerCreateRoleTimeout(void*);

	//--------------------------------------------------

protected:

	inline void set_login_state(int state) {
		this->login_stat = state;
	}

	std::string account;

	int login_stat;

	unsigned int last_send_command_time;

private:

	void initWithRoleInfo(const RoleInfo& roleInfo);

	RoleInfo* _roleInfo;
	PlayerInfo* _playerInfo;

	ev_uint64_t wait_query_role_timer_uid;
	ev_uint64_t wait_create_role_timer_uid;
};
