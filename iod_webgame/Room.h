#pragma once

#include "IODMicroHelperPb.h"
#include "Player.h"
#include "Strategy.h"

class Room
{
	DEC_PB_MSG_HANDLE(Room);

public:
	
	void initialize(int mapId, const RoomCreateOption& option, PlayerInfo* firstPlayer);

	bool addPlayer(PlayerInfo* playerInfo);

	bool removePlayer(PlayerInfo* playerInfo);

	bool startGame();

	unsigned int getUid() const { return roomInfo.room_id(); }
	
	void fetchRoomInfo(RoomInfo& roomInfo);

	inline int getPlayerCount() const { return players.size(); }

	inline Strategy* getStrategy() const { return strategy; }

private:
	
	Room();
	virtual ~Room(void);

	static unsigned int autoIncUidOfRoom;

	RoomInfo roomInfo;
	std::set< PlayerInfo* > players;

	Strategy* strategy;

	friend class RoomManager;
};
