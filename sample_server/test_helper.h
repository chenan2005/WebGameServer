#pragma once

#include "iod_logsystem.h"
#include "iod_utility.h"

class iod_packet;

static const char* SESSION_CMD_LOGIN = "login.";
static const char* SESSION_CMD_LOGOUT = "logout.";
static const char* SESSION_CMD_INFO = "info.";
static const char* SESSION_CMD_LOGIN_RES = "login_res.";

class test_helper
{
public:

	test_helper(void);
	~test_helper(void);

	static bool check_cmd(iod_packet* packet, const char* cmd);
};
