#pragma once

#include "IODSessionPb.h"

class DbHandle : public IODSessionPb
{
	DEC_REG_PROTO_MSG_HANDLE(DbHandle)

public:
	DbHandle(void);
	virtual ~DbHandle(void);
};
