#include "RoomManager.h"
#include "IODLogSystem.h"

//ÁÙÊ±¶¨Òå
#ifdef SESSION_SEND_MESSAGE
#undef SESSION_SEND_MESSAGE
#define SESSION_SEND_MESSAGE(protocol_name, var) DISPATCH_MSG((IODSessionPb*)conn_info->session, conn_info, protocol_name, var);
#endif


REG_PB_MSG_HANDLE_BEGIN(RoomManager)

ADD_PB_MSG_HANDLE(ReqCreateRoom, onReqCreateRoom)
ADD_PB_MSG_HANDLE(ReqLeaveRoom, onReqLeaveRoom)
ADD_PB_MSG_HANDLE(ReqJoinRoom, onReqJoinRoom)
ADD_PB_MSG_HANDLE(ReqStartGame, onReqStartGame)

REG_PB_MSG_HANDLE_END()

RoomManager::RoomManager(void)
{
}

RoomManager::~RoomManager(void)
{
}

void RoomManager::updateStrategy()
{
	std::map< unsigned int, Room* >::iterator it = roomMap.begin();
	while (it != roomMap.end()) {
		if (it->second->getStrategy())
			it->second->getStrategy()->update();
	}
}

void* RoomManager::onReqCreateRoom( connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, ReqCreateRoom, req);
	ResCreateRoom res;
	if (!req.has_player_info()) {
		res.set_result(-1);	
	}
	else
	{
		PlayerInfo* playerInfo = getPlayerInfo(req.player_info().name());
		if (playerInfo && playerInfo->has_room_id()) {
			res.set_result(-1);
		}
		else
		{
			if (!playerInfo) {
				playerInfo = new PlayerInfo;
				playerInfo->CopyFrom(req.player_info());
				playerMap[playerInfo->name()] = playerInfo;
			}
			Room* room = new Room();
			room->initialize(req.map_id(), req.create_option(), playerInfo);
			playerInfo->set_room_id(room->getUid());
			roomMap[room->getUid()] = room;

			res.set_result(0);
			room->fetchRoomInfo(*res.mutable_room_info());

			SESSION_SEND_MESSAGE(ResCreateRoom, res);
		}
	}

	return 0;
}

void* RoomManager::onReqLeaveRoom( connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, ReqLeaveRoom, req);
	if (!req.has_name())
		return 0;
	
	PlayerInfo* playerInfo = getPlayerInfo(req.name());
	if (!playerInfo || !playerInfo->has_room_id())
		return 0;

	Room* room = getRoom(playerInfo->room_id());
	if (!room) {
		iod_log_crit("impossible error!");
		return 0;
	}

	room->removePlayer(playerInfo);
	playerInfo->clear_room_id();

	if (room->getPlayerCount() == 0) {
		roomMap.erase(room->getUid());
		delete room;
	}

	ResLeaveRoom res;
	SESSION_SEND_MESSAGE(ResLeaveRoom, res);

	return 0;
}

void* RoomManager::onReqJoinRoom( connection_info* conn_info, BaseMsgPb* msg )
{
	return 0;
}

void* RoomManager::onReqStartGame( connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, ReqStartGame, req);
	if (!req.has_name())
		return 0;

	PlayerInfo* playerInfo = getPlayerInfo(req.name());
	if (!playerInfo || !playerInfo->has_room_id())
		return 0;

	Room* room = getRoom(playerInfo->room_id());
	if (!room) {
		iod_log_crit("impossible error!");
		return 0;
	}

	room->startGame();

	return 0;
}
