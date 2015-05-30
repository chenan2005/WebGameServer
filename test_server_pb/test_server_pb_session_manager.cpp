#include "test_server_pb_session_manager.h"
#include "test_server_pb_session.h"
#include "iod_test.pb.h"
#include "iod_utility.h"
#include "iod_logsystem.h"

using namespace iod::protobuf::test;

REG_PROTO_MSG_HANDLE_BEGIN(test_server_pb_session_manager, iod_session_manager_pb)

ADD_PROTO_MSG_HANDLE(_req_authentication, test_server_pb_session_manager::on_req_authentication)

ADD_PROTO_MSG_HANDLE(_req_login, test_server_pb_session_manager::on_req_login)

REG_PROTO_MSG_HANDLE_END(test_server_pb_session_manager)


test_server_pb_session_manager::test_server_pb_session_manager(void) : create_session_count(0), destroy_session_count(0), l_info(0)
{
}

test_server_pb_session_manager::~test_server_pb_session_manager(void)
{
	std::map< std::string, test_server_pb_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		delete it->second;
		it++;
	}
}

iod_session* test_server_pb_session_manager::on_req_authentication( struct connection_info* conn_info, iod::protobuf::common::base_msg* msg )
{
	SAFE_GET_NONE_SESSION_EXTENSION(msg, req_authentication, req);

	iod::protobuf::test::res_authentication res;

	string authoriztion("");
	if (!validate_authentication(req.userid(), req.authentication(), authoriztion)) {
		res.set_result(-1);
	}
	else {
		res.set_result(0);
		res.set_authorization(authoriztion);
	}
	
	send_message_to(conn_info, iod::protobuf::test::_res_authentication, res);
	
	return 0;
}

iod_session* test_server_pb_session_manager::on_req_login( struct connection_info* conn_info, iod::protobuf::common::base_msg* msg )
{
	SAFE_GET_NONE_SESSION_EXTENSION(msg, req_login, req);

	res_login res;
	res.set_userid(req.userid());

	if (validate_authorization(req.userid(), req.authorization())) {
		const char* username = req.userid().c_str();
		if (sessions.find(username) == sessions.end()) {
			test_server_pb_session* session = new test_server_pb_session;
			session->set_username(username);
			sessions[username] = session;
			create_session_count++;
		}
		
		res.set_result(0);
		send_message_to(conn_info, _res_login, res);

		return sessions[username];
	}
	else {
		res.set_result(-1);
		send_message_to(conn_info, _res_login, res);
	}

	return 0;
}

void test_server_pb_session_manager::kickout(iod_session* session, int reason)
{
	notify_kickout notify;
	notify.set_kick_reason(reason);
	send_message_to(session->get_connection_info(), _notify_kickout, notify);
	session->flush();
	session->shedule_timer(2000, (iod_timer_handler::FNC_TIMER_CALLBACK)&test_server_pb_session::on_timer_close_session, 0, true);
}

void test_server_pb_session_manager::random_kick(int num)
{
	int kick_num = 0;
	std::map< std::string, test_server_pb_session* >::iterator it = sessions.begin();
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

void test_server_pb_session_manager::check_sessions()
{
	std::map< std::string, test_server_pb_session* >::iterator it = sessions.begin();
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

bool test_server_pb_session_manager::validate_authentication(const std::string& userid, const std::string& authentication, std::string& authorization)
{
	if (userid == authentication) {
		authorization = userid;
		return true;
	}
	return false;
}

bool test_server_pb_session_manager::validate_authorization(const std::string& userid, const std::string& authorization)
{
	return userid == authorization;
}
