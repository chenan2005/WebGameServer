//#pragma once
#ifndef _MYSQLFIELD_H_
#define _MYSQLFIELD_H_

#include "iod_utility.h"

#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>
#include <errmsg.h>
#include <my_getopt.h>
#include <m_string.h>
#include <mysqld_error.h>

#define TRACE(...)
#define IOD_SRV_SYS_INFO(...)
#define IOD_SRV_SYS_ERROR(...)
#define IOD_SRV_SYS_CRIT(...)
#define IOD_SRV_ERROR(...)
#define IOD_SRV_CRIT(...)
#define IOD_SRV_INFO(...)

extern "C" {
	char *strptime(const char *buf, const char *fmt, struct tm *tm);
};

//声明类相关表字段
#define DECLARE_TABLE_INFO(className)	\
private:\
	static CMySqlTable<className> ms_table;\
	MYSQL* m_pConn;\
public:\
	className(MYSQL* pConn = NULL) { memset(this, 0, sizeof(className)); m_pConn = pConn; } \
	static const STFieldDescriptor& GetFieldDescriptor();\
	DECLARE_AND_IMP_QUERY(className);\
	DECLARE_AND_IMP_UPDATE(className);\
	DECLARE_AND_IMP_INSERT(className);\
	DECLARE_AND_IMP_DELETE(className);
//	DECLARE_AND_IMP_FILTER(className);	

//插入数据 声明+实现
#define DECLARE_AND_IMP_INSERT(className)	inline const char* InsertToDb(const char* pszValidFieldNames = NULL) \
{ return ms_table.InsertRecord(m_pConn, *this, pszValidFieldNames); }

//查询数据 声明+实现
#define DECLARE_AND_IMP_QUERY(className)	inline const char* QueryFromDb(className* pRecords, unsigned long* pulResultCount, EIODFieldKey eKeyType, unsigned long ulStart = 0, unsigned long ulResultMaxCount = 0) \
{ return ms_table.QueryRecord(m_pConn, *this, pRecords, pulResultCount, eKeyType, ulStart, ulResultMaxCount); } \
	inline const char* QueryFromDb(className* pRecords, unsigned long* pulResultCount, const char* pszCompareFieldNames, unsigned long ulStart = 0, unsigned long ulResultMaxCount = 0) \
{ return ms_table.QueryRecord(m_pConn, *this, pRecords, pulResultCount, pszCompareFieldNames, ulStart, ulResultMaxCount); }\
	inline const char* QueryFromDb(className* pRecords, unsigned long* pulResultCount, const char* pszCompareFieldNames, const char* pszReturnFieldNames, unsigned long ulStart = 0, unsigned long ulResultMaxCount = 0) \
{ return ms_table.QueryRecord(m_pConn, *this, pRecords, pulResultCount, pszCompareFieldNames, pszReturnFieldNames, ulStart, ulResultMaxCount); }\
	inline const char* QueryFromDb(const char* pszSql, className* pRecords, unsigned long* pulResultCount, unsigned long ulResultMaxCount = 0) \
{ return ms_table.QueryRecord(m_pConn, pszSql, pRecords, pulResultCount, ulResultMaxCount); }

//更新数据 声明+实现
#define DECLARE_AND_IMP_UPDATE(className)	inline const char* UpdateToDb(EIODFieldKey eKeyType, unsigned long* pulAffectedRows = NULL, const char* pszUpdateFieldNames = NULL) \
{ return ms_table.UpdateRecord(m_pConn, *this, eKeyType, pulAffectedRows, pszUpdateFieldNames); } \
	inline const char* UpdateToDb(const char* pszCompareFieldNames, unsigned long* pulAffectedRows = NULL, const char* pszUpdateFieldNames = NULL) \
{ return ms_table.UpdateRecord(m_pConn, *this, pszCompareFieldNames, pulAffectedRows, pszUpdateFieldNames); } \
	inline const char* UpdateToDb(const char* pszSql, unsigned long* pulResultCount, unsigned long ulResultMaxCount = 0) \
{ return ms_table.UpdateRecord(m_pConn, pszSql, pulResultCount); }


//删除数据 声明+实现
#define DECLARE_AND_IMP_DELETE(className)	inline const char* DeleteFromDb(EIODFieldKey eKeyType, unsigned long* pulAffectedRows = NULL) \
{ return ms_table.DeleteRecord(m_pConn, *this, eKeyType, pulAffectedRows); }	\
	inline const char* DeleteFromDb(const char* pszCompareFieldNames, unsigned long* pulAffectedRows = NULL) \
{ return ms_table.DeleteRecord(m_pConn, *this, pszCompareFieldNames, pulAffectedRows); }


////过滤（查询多个）数据 声明+实现
//#define DECLARE_AND_IMP_FILTER(className)	inline const char* FilterFromDb(className* resultRecords, unsigned long& ulResultCount, const unsigned long ulResultMaxSize, EIODFieldKey eKeyType = IOD_FIELD_KEY_FILTER_0, const unsigned long ulStart = 0) \
//{ return ms_table.FilterRecord(resultRecords, ulResultCount, ulResultMaxSize, *this, eKeyType, ulStart); }				

//实现类相关表字段
#define IMPLEMENT_TABLE_INIT_BEGIN(className, tableName) \
	CMySqlTable<className> className::ms_table;\
	const STFieldDescriptor& className::GetFieldDescriptor() \
{\
	className* pObject = 0;\
	static STFieldInfo s_##tableName_FieldInfo[] = {

#define	IMPLEMENT_FIELD_INFO(className, memberName, fieldValueType, fieldName, defaultValue, fieldKeyType)	\
{fieldName, defaultValue, offsetof(struct className, memberName), sizeof(pObject->memberName), fieldValueType, fieldKeyType, 0},

#define	IMPLEMENT_FIELD_INFO_EX(className, memberName, fieldValueType, fieldName, defaultValue, fieldKeyType, sizeMemberName)	\
{fieldName, defaultValue, offsetof(struct className, memberName), sizeof(pObject->memberName), fieldValueType, fieldKeyType, offsetof(struct className, sizeMemberName) - offsetof(struct className, memberName)},

#define	IMPLEMENT_FIELD_UNIQUE_0(className, memberName, fieldValueType, fieldName, defaultValue)	\
{fieldName, defaultValue, offsetof(struct className, memberName), sizeof(pObject->memberName), fieldValueType, IOD_FIELD_KEY_UNIQUE_0, 0},

#define	IMPLEMENT_FIELD_UNIQUE_1(className, memberName, fieldValueType, fieldName, defaultValue)	\
{fieldName, defaultValue, offsetof(struct className, memberName), sizeof(pObject->memberName), fieldValueType, IOD_FIELD_KEY_UNIQUE_1, 0},

#define	IMPLEMENT_FIELD_UNIQUE_2(className, memberName, fieldValueType, fieldName, defaultValue)	\
{fieldName, defaultValue, offsetof(struct className, memberName), sizeof(pObject->memberName), fieldValueType, IOD_FIELD_KEY_UNIQUE_2, 0},

#define	IMPLEMENT_FIELD_FILTER_0(className, memberName, fieldValueType, fieldName, defaultValue)	\
{fieldName, defaultValue, offsetof(struct className, memberName), sizeof(pObject->memberName), fieldValueType, IOD_FIELD_KEY_FILTER_0, 0},

#define	IMPLEMENT_FIELD_FILTER_1(className, memberName, fieldValueType, fieldName, defaultValue)	\
{fieldName, defaultValue, offsetof(struct className, memberName), sizeof(pObject->memberName), fieldValueType, IOD_FIELD_KEY_FILTER_1, 0},

#define	IMPLEMENT_FIELD_FILTER_2(className, memberName, fieldValueType, fieldName, defaultValue)	\
{fieldName, defaultValue, offsetof(struct className, memberName), sizeof(pObject->memberName), fieldValueType, IOD_FIELD_KEY_FILTER_2, 0},

#define	IMPLEMENT_FIELD_NORMAL(className, memberName, fieldValueType, fieldName, defaultValue)	\
{fieldName, defaultValue, offsetof(struct className, memberName), sizeof(pObject->memberName), fieldValueType, IOD_FIELD_KEY_NONE, 0},

#define IMPLEMENT_TABLE_INIT_END(className, tableName) \
}; \
	static STFieldDescriptor s_##tableName_FieldDescriptor = {s_##tableName_FieldInfo, sizeof(s_##tableName_FieldInfo)/sizeof(STFieldInfo), #tableName};\
	return s_##tableName_FieldDescriptor;\
}

#define  __out_field(fieldName, className, memberName, fieldValueType) \
	STOutFieldInfo(fieldName, offsetof(struct className, memberName), sizeof(((className *)(0))->memberName), fieldValueType)

enum EIODFieldType
{
	IOD_FIELD_TYPE_UNKNOWN = 0,
	IOD_FIELD_TYPE_BOOL = 1,
	IOD_FIELD_TYPE_UINT1 = 2,
	IOD_FIELD_TYPE_UINT2 = 3,
	IOD_FIELD_TYPE_UINT4 = 4,
	IOD_FIELD_TYPE_UINT8 = 5,
	IOD_FIELD_TYPE_INT1 = 6,
	IOD_FIELD_TYPE_INT2 = 7,
	IOD_FIELD_TYPE_INT4 = 8,
	IOD_FIELD_TYPE_INT8 = 9,
	IOD_FIELD_TYPE_REAL4 = 10,
	IOD_FIELD_TYPE_REAL8 = 11,
	IOD_FIELD_TYPE_STRING = 12,
	IOD_FIELD_TYPE_TIME = 13,
	IOD_FIELD_TYPE_BLOB = 14,
	IOD_FIELD_TYPE_FLOAT = IOD_FIELD_TYPE_REAL4,
	IOD_FIELD_TYPE_DOUBLE = IOD_FIELD_TYPE_REAL8,
};

enum EIODFieldKey
{
	IOD_FIELD_KEY_NONE = 0,
	IOD_FIELD_KEY_UNIQUE_0 = 0x1,
	IOD_FIELD_KEY_UNIQUE_1 = 0x2,
	IOD_FIELD_KEY_UNIQUE_2 = 0x4,
	IOD_FIELD_KEY_FILTER_0 = 0x8,
	IOD_FIELD_KEY_FILTER_1 = 0x10,
	IOD_FIELD_KEY_FILTER_2 = 0x20,
	IOD_FIELD_KEY_AUTO_INC = 0x40,
	IOD_FIELD_KEY_FILTER_3 = 0x80,
	IOD_FIELD_KEY_UNIQUE_3 = 0x100,
	IOD_FIELD_KEY_UNIQUE_4 = 0x200,
	IOD_FIELD_KEY_UNIQUE_5 = 0x400,
	IOD_FIELD_KEY_UNIQUE_6 = 0x800,
	IOD_FIELD_KEY_UNIQUE_7 = 0x1000,
	IOD_FIELD_KEY_FILTER_4 = 0x2000,
	IOD_FIELD_KEY_FILTER_5 = 0x4000,
	IOD_FIELD_KEY_FILTER_6 = 0x8000,
	IOD_FIELD_KEY_FILTER_7 = 0x10000,
};

struct STFieldInfo
{
	const char* m_pszFieldName;
	const char* m_pszDefaultValue;
	size_t m_nOffset;
	size_t m_nSize;
	EIODFieldType m_eVType;
	int m_eKType;
	int m_iSizeMemberOffset;
};

struct STOutFieldInfo
{
	const char* m_pszFieldName;
	size_t m_nOffset;
	size_t m_nSize;
	EIODFieldType m_eVType;
	int m_iSizeMemberOffset;
	STOutFieldInfo() {}
	STOutFieldInfo(const char* pszFileName, size_t nOffset, size_t nSize, EIODFieldType eVType, int iSizeMemberOffset = 0) :
		m_pszFieldName(pszFileName), m_nOffset(nOffset), m_nSize(nSize), m_eVType(eVType), m_iSizeMemberOffset(iSizeMemberOffset)
	{}
};

struct STFieldDescriptor
{
	STFieldInfo* m_pFieldInfo;
	unsigned short m_usFieldCount;
	const char* m_pszTableName;

	const STFieldInfo* GetFieldInfo(const char* fieldName) const
	{
		for (unsigned short us = 0; us < m_usFieldCount; us++)
		{
			if (!strcmp(m_pFieldInfo[us].m_pszFieldName, fieldName))
			{
				return m_pFieldInfo + us;
			}			
		}
		
		return NULL;
	}
};

#endif
