#pragma once
#include "iod_session_with_proto_base_msg.h"
#include "common/iod_common.pb.h"

class test_client_protobuf_session :
	public iod_session_with_proto_base_msg
{

	DEC_REG_PROTO_MSG_HANDLE(test_client_protobuf_session)

public:

	enum {
		LOGIN_STATE_NONE = 0,
		LOGIN_STATE_AUTHENTICATING,
		LOGIN_STATE_AUTHENTICATED, 
		LOGIN_STATE_LOGINING,
		LOGIN_STATE_LOGINED,
	};

	test_client_protobuf_session(void);
	virtual ~test_client_protobuf_session(void);

	virtual void on_closed(int reason);

	void set_username(const char* username, int length = 0);

	//发消息
	void send_req_authentication(const char* authentication, int length = 0);
	void send_req_login(const char* authorization, int length = 0);
	void send_req_test_info(const char* info, int length = 0);
	void send_req_logout();

	//处理消息
	virtual void on_res_authentication(iod::protobuf::common::base_msg* msg);
	virtual void on_res_login(iod::protobuf::common::base_msg* msg);
	virtual void on_res_test_info(iod::protobuf::common::base_msg* msg);

	inline const char* get_username() const {
		return username;
	}

	inline int get_login_state() const {
		return login_stat;
	}

	inline unsigned int get_last_send_command_time() const {
		return last_send_command_time;
	}

	inline const string& get_authorization() const {
		return authorization;
	}

protected:

	inline void set_login_state(int state) {
		this->login_stat = state;
	}

	inline void update_last_send_command_time() {
		last_send_command_time = iod_utility::get_time_msec();
	}

	char username[32];

	std::string authorization;

	int login_stat;

	unsigned int last_send_command_time;
};
