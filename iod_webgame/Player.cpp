#include "Player.h"
#include "IODLogSystem.h"
#include "IODWebGame.pb.h"
#include "IODWebGameInternal.pb.h"
#include "WebGameServer.h"
#include "DbHandle.h"
#include "RoomManager.h"

//ÁÙÊ±
#ifdef SEND_MESSAGE_TO_SESSION
#undef SEND_MESSAGE_TO_SESSION
#define SEND_MESSAGE_TO_SESSION(session, protocol_name, var) DISPATCH_MSG(session, conn_info, protocol_name, var)
#endif

#define CHECK_PLAYER_READY() if (_roleInfo == NULL) return 0

REG_PB_MSG_HANDLE_BEGIN(Player)

ADD_PB_MSG_HANDLE(ReqLogin, Player::onReqLogin)
ADD_PB_MSG_HANDLE(ReqTestInfo, Player::onReqTestInfo)
ADD_PB_MSG_HANDLE(ReqLogout, Player::onReqLogout)
ADD_PB_MSG_HANDLE(ReqTestResponseTime, Player::onReqTestResponseTime)
ADD_PB_MSG_HANDLE(ReqCreateRole, Player::onReqCreateRole)
ADD_PB_MSG_HANDLE(ReqCreateRoom, Player::onReqCreateRoom)
ADD_PB_MSG_HANDLE(ReqJoinRoom, Player::onReqJoinRoom)
ADD_PB_MSG_HANDLE(ReqLeaveRoom, Player::onReqLeaveRoom)
ADD_PB_MSG_HANDLE(ReqStartGame, Player::onReqStartGame)
ADD_PB_MSG_HANDLE(ReqLeaveGame, Player::onReqLeaveGame)
ADD_PB_MSG_HANDLE(ReqBroadCastInfo, Player::onReqBroadCastInfo)

ADD_PB_MSG_HANDLE(ResCreateRoom, Player::onResCreateRoom)
ADD_PB_MSG_HANDLE(ResLeaveRoom, Player::onResLeaveRoom)

ADD_PB_MSG_HANDLE(DbResRoleInfo, Player::onDbResRoleInfo)
ADD_PB_MSG_HANDLE(DbResCreateRole, Player::onDbResCreateRole)

REG_PB_MSG_HANDLE_END()


Player::Player(void) : login_stat(LOGIN_STATE_NONE), last_send_command_time(0), _roleInfo(0), _playerInfo(0)
{
	account[0] = 0;
}

Player::~Player(void)
{
	delete _roleInfo;
	delete _playerInfo;
}


Room* Player::createRoom( const RoomCreateOption& option )
{
	if (_playerInfo->has_room_id())
		return 0;

	return 0;
}

bool Player::joinRoom( int roomId )
{
	return false;
}


bool Player::leaveRoom()
{
	return false;
}


bool Player::startGame( int gameId )
{
	return false;
}


bool Player::leaveGame()
{
	return false;
}

void* Player::onReqLogin(connection_info* conn_info, BaseMsgPb* msg)
{
	SAFE_GET_EXTENSION(msg, ReqLogin, req);

	set_login_state(LOGIN_STATE_LOGINED);

	if (_roleInfo) {
		ResLogin res;
		res.set_result(0);
		res.mutable_role_info()->CopyFrom(*_roleInfo);
		SESSION_SEND_MESSAGE(ResLogin, res);
	}
	else {
		DbReqRoleInfo dbReq;
		dbReq.set_account(req.account());
		wait_query_role_timer_uid = shedule_timer(5000, (FNC_TIMER_CALLBACK)&Player::onTimerQueryRoleTimeout);
		SEND_MESSAGE_TO_SESSION(DbHandle::instance(), DbReqRoleInfo, dbReq);
	}

	return 0;
}

void* Player::onReqTestInfo(connection_info* conn_info, BaseMsgPb* msg)
{
	SAFE_GET_EXTENSION(msg, ReqTestInfo, req);
	ResTestInfo res;
	res.set_info("response" + req.info());
	SESSION_SEND_MESSAGE(ResTestInfo, res);

	return 0;
}

void* Player::onReqLogout(connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, ReqLogout, req);
	close(0);

	return 0;
}

void* Player::onReqTestResponseTime(connection_info* conn_info, BaseMsgPb* msg)
{
	SAFE_GET_EXTENSION(msg, ReqTestResponseTime, req);
	ResTestResponseTime res;
	res.set_req_timestamp(req.req_timestamp());
	SESSION_SEND_MESSAGE(ResTestResponseTime, res);

	return 0;
}

void* Player::onReqCreateRole(connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, ReqCreateRole, req);
	DbReqCreateRole dbReq;
	dbReq.set_account(req.account());
	dbReq.set_name(req.name());

	wait_create_role_timer_uid = shedule_timer(5000, (FNC_TIMER_CALLBACK)&Player::onTimerCreateRoleTimeout);

	SEND_MESSAGE_TO_SESSION(DbHandle::instance(), DbReqCreateRole, dbReq);

	return 0;
}

void* Player::onReqCreateRoom( connection_info* conn_info, BaseMsgPb* msg )
{
	CHECK_PLAYER_READY();
	SAFE_GET_EXTENSION(msg, ReqCreateRoom, req);
	
	ReqCreateRoom roomReq;
	roomReq.CopyFrom(req);
	roomReq.mutable_player_info()->CopyFrom(*_playerInfo);
	SEND_MESSAGE_TO_SESSION(RoomManager::instance(), ReqCreateRoom, roomReq);

	return 0;
}

void* Player::onReqJoinRoom( connection_info* conn_info, BaseMsgPb* msg )
{
	return 0;
}

void* Player::onReqLeaveRoom( connection_info* conn_info, BaseMsgPb* msg )
{
	CHECK_PLAYER_READY();
	SAFE_GET_EXTENSION(msg, ReqLeaveRoom, req);
	
	ReqLeaveRoom roomReq;
	roomReq.CopyFrom(req);
	roomReq.set_name(_roleInfo->name());
	SEND_MESSAGE_TO_SESSION(RoomManager::instance(), ReqLeaveRoom, roomReq);

	return 0;
}

void* Player::onReqStartGame( connection_info* conn_info, BaseMsgPb* msg )
{
	CHECK_PLAYER_READY();
	SAFE_GET_EXTENSION(msg, ReqStartGame, req);

	ReqStartGame roomReq;
	roomReq.CopyFrom(req);
	roomReq.set_name(_roleInfo->name());
	SEND_MESSAGE_TO_SESSION(RoomManager::instance(), ReqStartGame, roomReq);

	return 0;
}

void* Player::onReqLeaveGame( connection_info* conn_info, BaseMsgPb* msg )
{
	return 0;
}

void* Player::onReqBroadCastInfo( connection_info* conn_info, BaseMsgPb* msg )
{
	return 0;
}

void* Player::onResCreateRoom( connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, ResCreateRoom, res);
	if (res.result() == 0) {
		_playerInfo->set_room_id(res.room_info().room_id());
	}

	SESSION_SEND_MESSAGE(ResCreateRoom, res);
	return 0;
}

void* Player::onResLeaveRoom( connection_info* conn_info, BaseMsgPb* msg )
{
	_playerInfo->clear_room_id();

	ResLeaveRoom res;
	SESSION_SEND_MESSAGE(ResLeaveRoom, res);
	return 0;
}

void* Player::onDbResRoleInfo( connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, DbResRoleInfo, dbRes);
	ResLogin res;
	res.set_result(dbRes.result());
	if (dbRes.has_role_info()) {
		initWithRoleInfo(dbRes.role_info());
		res.mutable_role_info()->CopyFrom(dbRes.role_info());		
	}
	SESSION_SEND_MESSAGE(ResLogin, res);
	remove_timer(wait_query_role_timer_uid);
	return 0;
}

void* Player::onDbResCreateRole( connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, DbResCreateRole, dbRes);
	ResCreateRole res;
	res.set_result(dbRes.result());
	if (dbRes.has_role_info()) {
		initWithRoleInfo(dbRes.role_info());
		res.mutable_role_info()->CopyFrom(dbRes.role_info());
	}
	SESSION_SEND_MESSAGE(ResCreateRole, res);
	remove_timer(wait_create_role_timer_uid);
	return 0;
}

void Player::onTimerQueryRoleTimeout(void*)
{
	iod_log_error("waiting query role timeout!");
	close();
}

void Player::onTimerCreateRoleTimeout( void* )
{
	iod_log_error("waiting create role timeout!");
	close();
}

void Player::initWithRoleInfo( const RoleInfo& roleInfo )
{
	if (_roleInfo)
		delete _roleInfo;
	_roleInfo = new RoleInfo;
	_roleInfo->CopyFrom(roleInfo);

	if (_playerInfo)
		delete _playerInfo;
	_playerInfo = new PlayerInfo;
	_playerInfo->set_id(0);
	_playerInfo->set_name(_roleInfo->name());
	_playerInfo->set_flags("");
}

void Player::on_closed( int reason )
{
	//iod_log_info("user %s, connection closed %d", get_username(), reason);

	login_stat = LOGIN_STATE_NONE;
}
