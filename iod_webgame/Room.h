#pragma once

#include "IODMicroHelperPb.h"

class Room
{
	DEC_PB_MSG_HANDLE(Room);

public:
	Room(void);
	virtual ~Room(void);
};
