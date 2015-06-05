#ifndef _IODWEBGAMETABLE_H__
#define _IODWEBGAMETABLE_H__
//-----------------------------------------------------------------------------------
//由程序自动生成的头文件，定义数据库表与结构的映射，请及时添加注释
//-----------------------------------------------------------------------------------
#include "IODMyTableTpl.h"
//-----------------------------------------------------------------------------------
struct STItemIndexData {
	uint64    m_ui64item_uid;		//
	uint32    m_ui32idx;		//
	char    m_szdata[10240];		//
	uint16    m_ui16dataLength;		//m_szdata实际长度
	DECLARE_TABLE_INFO(STItemIndexData);
};
//-----------------------------------------------------------------------------------
struct STItemIndexValue {
	uint64    m_ui64item_uid;		//
	uint32    m_ui32idx;		//
	uint32    m_ui32value;		//
	DECLARE_TABLE_INFO(STItemIndexValue);
};
//-----------------------------------------------------------------------------------
struct STItemInfo {
	uint64    m_ui64uid;		//
	uint64    m_ui64owner_uid;		//
	uint32    m_ui32class_id;		//
	time_t    m_tmget_time;		//
	uint64    m_ui64flags;		//
	uint32    m_ui32amount;		//
	DECLARE_TABLE_INFO(STItemInfo);
};
//-----------------------------------------------------------------------------------
struct STRoleIndexData {
	uint64    m_ui64owner_uid;		//
	uint32    m_ui32idx;		//
	char    m_szdata[10240];		//
	uint16    m_ui16dataLength;		//m_szdata实际长度
	DECLARE_TABLE_INFO(STRoleIndexData);
};
//-----------------------------------------------------------------------------------
struct STRoleIndexValue {
	uint64    m_ui64owner_uid;		//
	uint32    m_ui32idx;		//
	uint32    m_ui32value;		//
	DECLARE_TABLE_INFO(STRoleIndexValue);
};
//-----------------------------------------------------------------------------------
struct STRoleInfo {
	uint64    m_ui64uid;		//
	char    m_szaccount[32];		//
	char    m_szname[32];		//
	time_t    m_tmcreate_time;		//
	uint64    m_ui64flags;		//
	DECLARE_TABLE_INFO(STRoleInfo);
};
//-----------------------------------------------------------------------------------
#endif