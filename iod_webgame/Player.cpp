#include "Player.h"
#include "IODLogSystem.h"
#include "IODWebGame.pb.h"
#include "IODMyDb.h"

using namespace com::iod::pb::webgame;

REG_PB_MSG_HANDLE_BEGIN(Player)

ADD_PB_MSG_HANDLE(ReqLogin, Player::onReqLogin)
ADD_PB_MSG_HANDLE(ReqTestInfo, Player::onReqTestInfo)
ADD_PB_MSG_HANDLE(ReqLogout, Player::onReqLogout)
ADD_PB_MSG_HANDLE(ReqTestResponseTime, Player::onReqTestResponseTime)
ADD_PB_MSG_HANDLE(ReqCreateRole, Player::onReqCreateRole)

REG_PB_MSG_HANDLE_END()


Player::Player(void) : login_stat(LOGIN_STATE_NONE), last_send_command_time(0), roomId(-1), gameId(-1)
{
	account[0] = 0;
}

Player::~Player(void)
{
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
	return 0;
}

void Player::on_closed( int reason )
{
	//iod_log_info("user %s, connection closed %d", get_username(), reason);

	login_stat = LOGIN_STATE_NONE;
}
