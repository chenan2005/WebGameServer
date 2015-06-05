#pragma once

#include "IODSessionPb.h"
#include "IODWebGame.pb.h"
#include "IODWebGameInternal.pb.h"
#include "Room.h"

using namespace com::iod::pb::webgame;


class RoomManager : public IODSessionPb
{
	DEC_PB_MSG_HANDLE(RoomManager)

public:

	static RoomManager* instance() { 
		static RoomManager* p = new RoomManager; 
		return p;
	}

	void updateStrategy();

	virtual void* onReqCreateRoom(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqLeaveRoom(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqJoinRoom(connection_info* conn_info, BaseMsgPb* msg);

	virtual void* onReqStartGame(connection_info* conn_info, BaseMsgPb* msg);

private:

	RoomManager(void);
	virtual ~RoomManager(void);

	inline PlayerInfo* getPlayerInfo(const std::string& name) {
		if (playerMap.find(name) == playerMap.end())
			return 0;
		return playerMap[name];
	}

	inline Room* getRoom(unsigned int uid) {
		if (roomMap.find(uid) == roomMap.end())
			return 0;
		return roomMap[uid];
	}

	std::map< unsigned int, Room* > roomMap;

	std::map< std::string, PlayerInfo* > playerMap;
};
