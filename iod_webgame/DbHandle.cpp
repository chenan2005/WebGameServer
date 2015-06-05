#include "DbHandle.h"
#include "IODWebGameInternal.pb.h"
#include "IODWebGameTable.h"
using namespace com::iod::pb::webgame;

REG_PB_MSG_HANDLE_BEGIN(DbHandle)

ADD_PB_MSG_HANDLE(ReqRoleInfo, DbHandle::onReqRoleInfo)

REG_PB_MSG_HANDLE_END()

DbHandle::DbHandle(void)
{
	IODMyDb::createConnection("192.168.1.240", 3306, "root", "", "IODWebGame");
}

DbHandle::~DbHandle(void)
{
}

void* DbHandle::onReqRoleInfo(connection_info* conn_info, BaseMsgPb* msg)
{
	SAFE_GET_EXTENSION(msg, ReqRoleInfo, req);

	ResRoleInfo res;
	res.set_account(req.account());

	STRoleInfo roleInfoTb(myConn);
	strcpy(roleInfoTb.m_szaccount, req.account().c_str());
	unsigned long queryCount = 0;
	roleInfoTb.QueryFromDb(&roleInfoTb, &queryCount, "account");
	if (queryCount == 0) {
		res.set_result(-1);
	}
	else {
		RoleInfo* roleInfo = res.mutable_role_info();
		roleInfo->set_uid(roleInfoTb.m_ui64uid);
		roleInfo->set_account(roleInfoTb.m_szaccount);
		roleInfo->set_name(roleInfoTb.m_szname);
		roleInfo->set_create_time((int)roleInfoTb.m_tmcreate_time);
		string flagsData("");
		flagsData.copy((char*)&roleInfoTb.m_ui64flags, sizeof(roleInfoTb.m_ui64flags));
		roleInfo->set_flags(flagsData);
		res.set_result(0);
	}

	DISPATCH_MSG((IODSessionPb*)conn_info->session, conn_info, ResRoleInfo, res);

	return 0;
}

