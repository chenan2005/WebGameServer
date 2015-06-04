#pragma once

#include "IODPbMsgHandler.h"

class Room : public IODPbMsgHandler
{
	DEC_PB_MSG_HANDLE(Room);

public:
	Room(void);
	virtual ~Room(void);
};
