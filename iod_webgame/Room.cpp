#include "Room.h"

REG_PB_MSG_HANDLE_BEGIN(Room)
REG_PB_MSG_HANDLE_END()

unsigned int Room::autoIncUidOfRoom = 0;

void Room::initialize( int mapId, const RoomCreateOption& option, PlayerInfo* firstPlayer )
{
	this->roomInfo.set_room_id(autoIncUidOfRoom++);
	this->roomInfo.set_map_id(mapId);
	this->roomInfo.mutable_create_option()->CopyFrom(option);
	this->roomInfo.set_flags("");
	players.insert(firstPlayer);
}

bool Room::addPlayer( PlayerInfo* playerInfo )
{
	if (players.find(playerInfo) != players.end())
		return false;
	players.insert(playerInfo);
	return true;
}

bool Room::removePlayer( PlayerInfo* playerInfo )
{
	if (players.find(playerInfo) != players.end())
		return false;
	players.erase(playerInfo);
	return true;
}

bool Room::startGame()
{
	if (strategy != 0)
		return false;

	strategy = new Strategy;

	return true;
}

void Room::fetchRoomInfo( RoomInfo& roomInfo )
{
	roomInfo.CopyFrom(this->roomInfo);
	int idx = 0;
	for (std::set< PlayerInfo* >::iterator it = players.begin(); it != players.end(); it++, idx++) {
		roomInfo.mutable_players()->Add();
		roomInfo.mutable_players(idx)->CopyFrom(**it);
	}
}

Room::Room() : strategy(0)
{
}

Room::~Room(void)
{
	if (strategy)
		delete strategy;
}
