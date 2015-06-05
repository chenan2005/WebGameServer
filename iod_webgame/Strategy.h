#pragma once

#include "IODCommon.h"
#include "IODWebGameCommon.pb.h"

using namespace com::iod::pb::webgame;

class Strategy
{
public:

	Strategy(void);

	~Strategy(void);

	void initialize();

	void update();

	bool addPlayer(PlayerInfo*);

	bool removePlayer(PlayerInfo*);

private:
	
	GameInfo gameInfo;
	std::set< PlayerInfo* > players;
};
