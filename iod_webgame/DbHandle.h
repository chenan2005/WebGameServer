#pragma once

#include "IODSessionPb.h"

class DbHandle : public IODSessionPb
{
	DEC_PB_MSG_HANDLE(DbHandle)

public:

	static DbHandle* instance() {
		static DbHandle* p = new DbHandle;
		return p;
	}

	bool initialize(const char* address, unsigned short port, const char* user, const char* pass, const char* dbname);

	virtual void* onDbReqRoleInfo(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onDbReqCreateRole(connection_info* conn_info, BaseMsgPb* msg);

private:

	DbHandle();
	virtual ~DbHandle(void);

	struct st_mysql* myConn;
};
