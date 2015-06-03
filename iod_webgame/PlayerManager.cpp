#include "PlayerManager.h"
#include "Player.h"
#include "iod_webgame.pb.h"
#include "iod_utility.h"
#include "iod_logsystem.h"

using namespace com::iod::pb::webgame;

REG_PROTO_MSG_HANDLE_BEGIN(PlayerManager, iod_session_manager_pb)

ADD_PROTO_MSG_HANDLE(ReqAuthentication, PlayerManager::onReqAuthentication)

ADD_PROTO_MSG_HANDLE(ReqLogin, PlayerManager::onReqLogin)

REG_PROTO_MSG_HANDLE_END(PlayerManager)


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

iod_session* PlayerManager::onReqAuthentication( struct connection_info* conn_info, com::iod::pb::common::BaseMsg* msg )
{
	SAFE_GET_NONE_SESSION_EXTENSION(msg, ReqAuthentication, req);

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

iod_session* PlayerManager::onReqLogin( struct connection_info* conn_info, com::iod::pb::common::BaseMsg* msg )
{
	SAFE_GET_NONE_SESSION_EXTENSION(msg, ReqLogin, req);

	ResLogin res;

	if (validate_authorization(req.account(), req.authorization())) {
		const char* username = req.account().c_str();
		if (sessions.find(username) == sessions.end()) {
			Player* session = new Player;
			session->set_username(username);
			sessions[username] = session;
			create_session_count++;
		}
		
		res.set_result(0);
		SEND_MESSAGE_TO(conn_info, ResLogin, res);

		return sessions[username];
	}
	else {
		res.set_result(-1);
		SEND_MESSAGE_TO(conn_info, ResLogin, res);
	}

	return 0;
}


void PlayerManager::kickout(iod_session* session, int reason)
{
	NotifyKickout notify;
	notify.set_kick_reason(reason);
	SEND_MESSAGE_TO(session->get_connection_info(), NotifyKickout, notify);
	session->flush();
	session->shedule_timer(2000, (iod_timer_handler::FNC_TIMER_CALLBACK)&Player::on_timer_close_session, 0, true);
}

void PlayerManager::random_kick(int num)
{
	int kick_num = 0;
	std::map< std::string, Player* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		if (it->second->get_net_stat() == iod_session::SNS_CONNECTED) {
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
		if (it->second->get_net_stat() != iod_session::SNS_CONNECTED
			&& iod_utility::get_time_msec() > it->second->get_last_net_state_time() + 10000) {
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
