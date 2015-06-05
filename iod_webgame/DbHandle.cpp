#include "DbHandle.h"
#include "IODWebGameInternal.pb.h"
#include "IODWebGameTable.h"
using namespace com::iod::pb::webgame;

//ÁÙÊ±¶¨Òå
#ifdef SESSION_SEND_MESSAGE
#undef SESSION_SEND_MESSAGE
#define SESSION_SEND_MESSAGE(protocol_name, var) DISPATCH_MSG((IODSessionPb*)conn_info->session, conn_info, protocol_name, var);
#endif

REG_PB_MSG_HANDLE_BEGIN(DbHandle)

ADD_PB_MSG_HANDLE(DbReqRoleInfo, DbHandle::onDbReqRoleInfo)
ADD_PB_MSG_HANDLE(DbReqCreateRole, DbHandle::onDbReqCreateRole)

REG_PB_MSG_HANDLE_END()

bool DbHandle::initialize( const char* address, unsigned short port, const char* user, const char* pass, const char* dbname )
{
	myConn = IODMyDb::createConnection(address, port, user, pass, dbname);
	return myConn != 0;
}

void* DbHandle::onDbReqRoleInfo(connection_info* conn_info, BaseMsgPb* msg)
{
	SAFE_GET_EXTENSION(msg, DbReqRoleInfo, req);

	DbResRoleInfo res;
	res.set_account(req.account());

	STRoleInfo roleInfoTb(myConn);
	strcpy(roleInfoTb.m_szaccount, req.account().c_str());
	unsigned long queryCount = 0;
	const char* dbQueryError = roleInfoTb.QueryFromDb(&roleInfoTb, &queryCount, "account");
	if (dbQueryError) {
		res.set_result(-1);
	}
	else {
		if (queryCount == 1) {
			RoleInfo* roleInfo = res.mutable_role_info();
			roleInfo->set_uid(roleInfoTb.m_ui64uid);
			roleInfo->set_account(roleInfoTb.m_szaccount);
			roleInfo->set_name(roleInfoTb.m_szname);
			roleInfo->set_create_time((int)roleInfoTb.m_tmcreate_time);
			string flagsData("");
			flagsData.copy((char*)&roleInfoTb.m_ui64flags, sizeof(roleInfoTb.m_ui64flags));
			roleInfo->set_flags(flagsData);			
		}
		res.set_result(0);
	}


	SESSION_SEND_MESSAGE(DbResRoleInfo, res);

	return 0;
}

void* DbHandle::onDbReqCreateRole( connection_info* conn_info, BaseMsgPb* msg )
{
	SAFE_GET_EXTENSION(msg, DbReqCreateRole, req);

	DbResCreateRole res;

	STRoleInfo roleInfoTb(myConn);
	strcpy(roleInfoTb.m_szaccount, req.account().c_str());
	strcpy(roleInfoTb.m_szname, req.name().c_str());
	const char* dbQueryError = roleInfoTb.InsertToDb();
	if (dbQueryError) {
		res.set_result(-1);
	}
	else {
		unsigned long queryCount = 0;
		roleInfoTb.QueryFromDb(&roleInfoTb, &queryCount, "account");
		if (queryCount != 1) {
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
	}


	SESSION_SEND_MESSAGE(DbResCreateRole, res);

	return 0;
}

DbHandle::DbHandle()
{
}

DbHandle::~DbHandle(void)
{
}
