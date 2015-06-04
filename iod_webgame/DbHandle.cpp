#include "DbHandle.h"
#include "IODWebGame.pb.h"
using namespace com::iod::pb::webgame;

REG_PB_MSG_HANDLE_BEGIN(DbHandle)

ADD_PB_MSG_HANDLE(ReqLogin, DbHandle::onReqLogin)

REG_PB_MSG_HANDLE_END()

DbHandle::DbHandle(void)
{
}

DbHandle::~DbHandle(void)
{
}

void* DbHandle::onReqLogin(connection_info* conn_info, BaseMsgPb* msg)
{
	return 0;
}

