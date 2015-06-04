#pragma once

#include "IODSessionPb.h"

class DbHandle : public IODSessionPb
{
	DEC_PB_MSG_HANDLE(DbHandle)

public:
	DbHandle(void);
	virtual ~DbHandle(void);

	virtual void* onReqLogin(connection_info* conn_info, BaseMsgPb* msg);
};
