//#pragma once
#ifndef _MYSQLDB_H_
#define _MYSQLDB_H_

#include "IODMyField.h"

namespace IODMyDb
{
	extern MYSQL* common_mysql_connection;

	bool initCommonConnection(const char* address, unsigned short port, const char* user, const char* pass, const char* dbname);

	//返回值写入szRet字符串，用逗号隔开
	const char* freeQuery(MYSQL* pConn, const char* pszSql, char* szRet = NULL);

	//类似sscanf读取上面调用的字符串
	const char* freeQuery(MYSQL* pConn, const char* pszSql, const char* pszRetValueFormat, ...);

	//返回到一个结构体（数组）中，需要通过__out_field宏来指定返回域对应的字段
	//__out_field(fieldName, className, memberName, fieldValueType)
	template<typename returnType>
	const char* freeQuery(MYSQL* pConn, const char* pszSql, returnType* pRecords, unsigned long* pulResultCount, unsigned long ulResultMaxCount, 
		const STOutFieldInfo* pOutField, unsigned int outputFieldCount);

	const char* getValueFromSzIntoField( void* pRecord, const STOutFieldInfo& field, const char* szValue, unsigned long ulLength );

	//测试代码
	void TestFreeQuery(MYSQL* pConn);
}

template<typename returnType>
const char* IODMyDb::freeQuery( MYSQL* pConn, const char* pszSql, returnType* pRecords, unsigned long* pulResultCount, unsigned long ulResultMaxCount, const STOutFieldInfo* pOutField, unsigned int outputFieldCount)
{
	{
		//IODDB::STAutoTiming stAutoTiming(pszSql, 1);
		if (int iError = mysql_real_query(pConn, pszSql, (unsigned long)strlen(pszSql)))
		{
			//IOD_SRV_ERROR("query error code %d", iError);
			//IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
	}

	MYSQL_RES* pRes = mysql_store_result(pConn);

	if (!pRes)
	{
		const char* pszErr = mysql_error(pConn);
		if (pszErr || strlen(pszErr) == 0)
		{
			return NULL;
		}
		else
		{
			return pszErr;
		}
	}


	unsigned long num_rows = (unsigned long)mysql_num_rows(pRes);
	if (ulResultMaxCount && num_rows > ulResultMaxCount)
	{
		num_rows = ulResultMaxCount;
	}

	if (pRecords)
	{
		//const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

		if (outputFieldCount > mysql_num_fields(pRes))
		{
			return "invalid out field count!!!";
		}		

		MYSQL_ROW row = 0;

		const STOutFieldInfo* fieldInfo = pOutField;

		for (unsigned long ulIdx = 0; ulIdx < num_rows; ulIdx++)
		{
			if (!(row = mysql_fetch_row(pRes)))
			{
				return "fetch result failed\n";
			}

			unsigned long* lengths = mysql_fetch_lengths(pRes); 

			for (unsigned int ui = 0; ui < outputFieldCount; ui++)
			{
				if (const char* pszResult = getValueFromSzIntoField(pRecords + ulIdx, fieldInfo[ui], row[ui], lengths[ui]))
				{
					return pszResult;
				}
			}
		}
	}

	if (pulResultCount)
	{
		*pulResultCount = num_rows;
	}

	mysql_free_result(pRes);

	//CMySqlDB::GetInstance().UnlockConn(iConn);

	return NULL;
}

#endif
