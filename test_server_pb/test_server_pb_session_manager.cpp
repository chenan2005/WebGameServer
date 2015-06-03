#include "test_server_pb_session_manager.h"
#include "test_server_pb_session.h"
#include "iod_test.pb.h"
#include "iod_utility.h"
#include "iod_logsystem.h"

using namespace com::iod::pb::test;

REG_PROTO_MSG_HANDLE_BEGIN(test_server_pb_session_manager, iod_session_manager_pb)

ADD_PROTO_MSG_HANDLE(ReqAuthentication, test_server_pb_session_manager::onReqAuthentication)

ADD_PROTO_MSG_HANDLE(ReqLogin, test_server_pb_session_manager::onReqLogin)

ADD_PROTO_MSG_HANDLE(TestMsg1, test_server_pb_session_manager::onTestMsg1);

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

iod_session* test_server_pb_session_manager::onReqAuthentication( struct connection_info* conn_info, com::iod::pb::common::BaseMsg* msg )
{
	SAFE_GET_NONE_SESSION_EXTENSION(msg, ReqAuthentication, req);

	com::iod::pb::test::ResAuthentication res;

	string authoriztion("");
	if (!validate_authentication(req.user_id(), req.authentication(), authoriztion)) {
		res.set_result(-1);
	}
	else {
		res.set_result(0);
		res.set_authorization(authoriztion);
	}
	
	SEND_MESSAGE_TO(conn_info, ResAuthentication, res);
	
	return 0;
}

iod_session* test_server_pb_session_manager::onReqLogin( struct connection_info* conn_info, com::iod::pb::common::BaseMsg* msg )
{
	SAFE_GET_NONE_SESSION_EXTENSION(msg, ReqLogin, req);

	ResLogin res;
	res.set_user_id(req.user_id());

	if (validate_authorization(req.user_id(), req.authorization())) {
		const char* username = req.user_id().c_str();
		if (sessions.find(username) == sessions.end()) {
			test_server_pb_session* session = new test_server_pb_session;
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

iod_session* test_server_pb_session_manager::onTestMsg1(struct connection_info* conn_info, com::iod::pb::common::BaseMsg* msg)
{
	SAFE_GET_NONE_SESSION_EXTENSION(msg, TestMsg1, req);
	TestMsg1 res;
	std::string testData = "dfasdfdssdafksda;ljfa;lkrwepsdvcmksdapocmsdac;'asd'csdafadopramcd;acd;";
	for (int i = 0; i < 8; i++) {
		testData += testData;
	}
	res.set_test_data(testData);
	SEND_MESSAGE_TO(conn_info, TestMsg1, res);

	return 0;
}

void test_server_pb_session_manager::kickout(iod_session* session, int reason)
{
	NotifyKickout notify;
	notify.set_kick_reason(reason);
	SEND_MESSAGE_TO(session->get_connection_info(), NotifyKickout, notify);
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
