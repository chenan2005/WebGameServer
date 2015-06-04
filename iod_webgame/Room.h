#pragma once

#include "iod_pb_msg_handler.h"

class Room : public iod_pb_msg_handler
{
	DEC_PB_MSG_HANDLE(Room);

public:
	Room(void);
	virtual ~Room(void);
};
