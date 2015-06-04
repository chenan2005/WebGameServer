#pragma once

#include "iod_session_pb.h"

class DbHandle : public iod_session_pb
{
	DEC_REG_PROTO_MSG_HANDLE(DbHandle)

public:
	DbHandle(void);
	virtual ~DbHandle(void);
};
