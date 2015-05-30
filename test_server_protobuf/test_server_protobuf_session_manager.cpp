#include "test_server_protobuf_session_manager.h"
#include "test_server_protobuf_session.h"
#include "iod_test.pb.h"
#include "iod_utility.h"
#include "iod_logsystem.h"

REG_PROTO_MSG_HANDLE_BEGIN(test_server_protobuf_session_manager, iod_session_creator_with_proto_base_msg)

ADD_PROTO_MSG_HANDLE(iod::protobuf::test::kReqAuthenticationFieldNumber, test_server_protobuf_session_manager::on_req_login)

REG_PROTO_MSG_HANDLE_END(test_server_protobuf_session_manager)


test_server_protobuf_session_manager::test_server_protobuf_session_manager(void) : create_session_count(0), destroy_session_count(0), l_info(0)
{
}

test_server_protobuf_session_manager::~test_server_protobuf_session_manager(void)
{
	std::map< std::string, test_server_protobuf_session* >::iterator it = sessions.begin();
	while (it != sessions.end()) {
		delete it->second;
		it++;
	}
}

void test_server_protobuf_session_manager::check_sessions()
{
	std::map< std::string, test_server_protobuf_session* >::iterator it = sessions.begin();
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

iod_session* test_server_protobuf_session_manager::on_req_login( struct connection_info* conn_info, iod::protobuf::common::base_msg* msg )
{
	iod_log_info("on_req_login");
	return 0;
}
