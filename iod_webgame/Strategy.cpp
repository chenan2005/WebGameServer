#include "Strategy.h"


Strategy::Strategy(void)
{
}

Strategy::~Strategy(void)
{
}

void Strategy::initialize()
{

}

void Strategy::update()
{
	
}

bool Strategy::addPlayer( PlayerInfo* playerInfo)
{
	if (players.find(playerInfo) != players.end())
		return false;
	players.insert(playerInfo);
	return true;
}

bool Strategy::removePlayer( PlayerInfo* playerInfo)
{
	if (players.find(playerInfo) != players.end())
		return false;
	players.erase(playerInfo);
	return true;
}
