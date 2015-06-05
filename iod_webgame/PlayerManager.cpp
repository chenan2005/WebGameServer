#include "PlayerManager.h"
#include "Player.h"
#include "IODWebGame.pb.h"
#include "IODUtility.h"
#include "IODLogSystem.h"

using namespace com::iod::pb::webgame;

REG_PB_MSG_HANDLE_BEGIN(PlayerManager)

ADD_PB_MSG_HANDLE(ReqAuthentication, PlayerManager::onReqAuthentication)

ADD_PB_MSG_HANDLE(ReqLogin, PlayerManager::onReqLogin)

REG_PB_MSG_HANDLE_END()


PlayerManager::PlayerManager(void) : create_session_count(0), destroy_session_count(0), l_info(0)
{
}

PlayerManager::~PlayerManager(void)
{
	std::map< std::string, Player* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		delete it->second;
		it++;
	}
}

void* PlayerManager::onReqAuthentication( struct connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, ReqAuthentication, req);

	ResAuthentication res;

	string authoriztion("");
	if (!validate_authentication(req.account(), req.authentication(), authoriztion)) {
		res.set_result(-1);
	}
	else {
		res.set_result(0);
		res.set_authorization(authoriztion);
	}
	
	SEND_MESSAGE_TO(conn_info, ResAuthentication, res);
	
	return 0;
}

void* PlayerManager::onReqLogin( struct connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, ReqLogin, req);

	//ResLogin res;

	if (validate_authorization(req.account(), req.authorization())) {
		const std::string& account = req.account();
		if (sessions.find(account) == sessions.end()) {
			Player* session = new Player;
			session->setAccount(account);
			sessions[account] = session;
			create_session_count++;
		}
		
		//res.set_result(0);
		//SEND_MESSAGE_TO(conn_info, ResLogin, res);

		return sessions[account];
	}
	//else {
	//	res.set_result(-1);
	//	SEND_MESSAGE_TO(conn_info, ResLogin, res);
	//}

	return 0;
}


void PlayerManager::kickout(IODSession* session, int reason)
{
	NotifyKickout notify;
	notify.set_kick_reason(reason);
	SEND_MESSAGE_TO(session->get_connection_info(), NotifyKickout, notify);
	session->flush();
	session->shedule_timer(2000, (IODTimerHandler::FNC_TIMER_CALLBACK)&Player::onTimerCloseSession, 0, true);
}

void PlayerManager::random_kick(int num)
{
	int kick_num = 0;
	std::map< std::string, Player* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		if (it->second->get_net_stat() == IODSession::SNS_CONNECTED) {
			kickout(it->second, 1);
			kick_num++;
		}
		if (kick_num >= num)
			break;
		it++;
	}
}

void PlayerManager::check_sessions()
{
	std::map< std::string, Player* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		if (it->second->get_net_stat() != IODSession::SNS_CONNECTED
			&& IODUtility::get_time_msec() > it->second->get_last_net_state_time() + 10000) {
			delete it->second;
			destroy_session_count++;
			it = sessions.erase(it);
			continue;
		}
		it++;
	}
}

bool PlayerManager::validate_authentication(const std::string& userid, const std::string& authentication, std::string& authorization)
{
	if (userid == authentication) {
		authorization = userid;
		return true;
	}
	return false;
}

bool PlayerManager::validate_authorization(const std::string& userid, const std::string& authorization)
{
	return userid == authorization;
}
