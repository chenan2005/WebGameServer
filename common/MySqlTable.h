//#pragma once
#ifndef _MYSQLTABLE_H_
#define _MYSQLTABLE_H_

#include "MySqlDB.h"
#include "MySqlField.h"

#define SQL_STMT_LENGTH 10240
#define SQL_VALUE_LENGTH 10240

#define UNLIMITED_RECORD_COUNT 0xffffffff

#define IS_CHAR_AVIALABLE(x) ((x <= 'z' && x >= 'a') || (x <= 'Z' && x >= 'A') || (x <= '9' && x >= '0') || (x == '_'))

inline bool is_field_in(const char* strFieldList, const char* strField)
{
	int idx = 0;
	int wordStart = 0;
	int wordEnd = 0;
	while (wordEnd < (int)strlen(strFieldList) + 1)
	{
		if (IS_CHAR_AVIALABLE(strFieldList[wordEnd]))
		{
			wordEnd++;
		}
		else
		{
			if (wordEnd - wordStart == (int)strlen(strField) && memcmp(strFieldList + wordStart, strField, wordEnd - wordStart) == 0)
			{
				return true;
			}
			
			wordEnd++;
			wordStart = wordEnd;
		}		
	}

	return false;

	//const char* p = strstr(strFieldList, strField);

	//if (!p)
	//{
	//	return false;
	//}
	//else
	//{
	//	if (p == strFieldList)
	//	{
	//		char c = p[strlen(strField)];

	//		return !IS_CHAR_AVIALABLE(c);
	//	}
	//	else
	//	{
	//		if (IS_CHAR_AVIALABLE((p - 1)[0]))
	//		{
	//			return false;
	//		}

	//		char c = p[strlen(strField)];

	//		return !IS_CHAR_AVIALABLE(c);
	//	}
	//}
}

template<typename T>
void GetFieldSzValue( const T& record, const STFieldInfo& field, const unsigned int uiMaxSize, char* szValue, size_t& sSize, const MYSQL* pConn );

template<typename T>
const char* GetValueFromSzField( T& record, const STFieldInfo& field, const char* szValue, unsigned long ulLength );

template<typename T>
bool GetQueryStmt( EIODFieldKey eKeyType, const T& record, char* pszStmt, size_t& size, MYSQL* pConn );

template<typename T>
bool GetQueryStmt( const char* pszCompareFieldNames, const T& record, char* pszStmt, size_t& size, MYSQL* pConn, const char* pszReturnFieldNames = NULL);

template<typename T>
bool GetQueryStmtEx( EIODFieldKey eKeyType, const T& record, char* pszStmt, size_t& size, MYSQL* pConn, unsigned long ulStart, unsigned long ulMaxCount);

template<typename T>
bool GetQueryStmtEx( const char* pszCompareFieldNames, const T& record, char* pszStmt, size_t& size, MYSQL* pConn, unsigned long ulStart, unsigned long ulMaxCount, const char* pszReturnFieldNames = NULL);

template<typename T>
bool GetUpdateStmt( EIODFieldKey eKeyType, const T& record, char* pszStmt, size_t& size, MYSQL* pConn, const char* pszUpdateFieldNames );

template<typename T>
bool GetUpdateStmt( const char* pszCompareFieldNames, const T& record, char* pszStmt, size_t& size, MYSQL* pConn, const char* pszUpdateFieldNames );

template<typename T>
bool GetDeleteStmt( EIODFieldKey eKeyType, const T& record, char* pszStmt, size_t& size, MYSQL* pConn );

template<typename T>
bool GetDeleteStmt( const char* pszCompareFieldNames, const T& record, char* pszStmt, size_t& size, MYSQL* pConn );

template<typename T>
bool GetInsertStmt( const T& record, char* pszStmt, size_t& size, MYSQL* pConn, const char* pszValidFieldNames );

template<typename T>
class CMySqlTable
{
public:
	CMySqlTable(void){}

	~CMySqlTable(void) {}

	const char* QueryRecord(MYSQL* pConn, const T& queryRecord, T* pRecords, unsigned long* pulResultCount, EIODFieldKey eKeyType, unsigned long ulStart, unsigned long ulResultMaxCount);

	const char* QueryRecord(MYSQL* pConn, const T& queryRecord, T* pRecords, unsigned long* pulResultCount, const char* pszCompareFieldNames, unsigned long ulStart, unsigned long ulResultMaxCount);

	const char* QueryRecord(MYSQL* pConn, const T& queryRecord, T* pRecords, unsigned long* pulResultCount, const char* pszCompareFieldNames, const char* pszReturnFields, unsigned long ulStart, unsigned long ulResultMaxCount);

	const char* QueryRecord(MYSQL* pConn, const char* pszSql, T* pRecords, unsigned long* pulResultCount, unsigned long ulResultMaxCount);

	const char* InsertRecord(MYSQL* pConn, const T& insertRecord, const char* pszValidFieldNames);

	const char* UpdateRecord(MYSQL* pConn, const T& updateRecord, EIODFieldKey eKeyType, unsigned long* pulAffectedRows, const char* pszUpdateFieldNames);

	const char* UpdateRecord(MYSQL* pConn, const T& updateRecord, const char* pszCompareFieldNames, unsigned long* pulAffectedRows, const char* pszUpdateFieldNames);

	const char* UpdateRecord(MYSQL* pConn, const char* pszSql, unsigned long* pulAffectedRows);

	const char* DeleteRecord(MYSQL* pConn, const T& queryRecord, EIODFieldKey eKeyType, unsigned long* pulAffectedRows);

	const char* DeleteRecord(MYSQL* pConn, const T& queryRecord, const char* pszCompareFieldNames, unsigned long* pulAffectedRows);

	//const char* InsertRecord(const T& record);

	//const char* QueryRecord(T& record, EIODFieldKey eKeyType);

	//const char* UpdateRecord(const T& record, EIODFieldKey eKeyType, my_ulonglong& affectedRows);

	//const char* DeleteRecord(const T& record, EIODFieldKey eKeyType, my_ulonglong& affectedRows);

	//const char* FilterRecord(T* resultRecords, unsigned long& ulResultCount, const unsigned long ulResultMaxSize,
	//	const T& queryRecord, EIODFieldKey eKeyType, const unsigned long ulStart = 0);

	//const char* PrepareStmts();

	//const char* CloseStmts();

private:
	
	//bool PrepareInsert();

	//bool PrepareQuery(EIODFieldKey eKeyType);

	//bool PrepareFilter(EIODFieldKey eKeyType);

	//bool PrepareUpdate(EIODFieldKey eKeyType);

	//bool PrepareDelete(EIODFieldKey eKeyType);

	//void BindField(MYSQL_BIND& bind, const T& record, const STFieldInfo& field);

	//void BindRecord(MYSQL_BIND* bind, const T& record, EIODFieldKey eKeyType = IOD_FIELD_KEY_NONE, const unsigned int uiBindMaxSize = 0, unsigned int* puiBindReturnSize = 0);

	//MYSQL_BIND* CreateBind(const T& record, EIODFieldKey eKeyType = IOD_FIELD_KEY_NONE, const unsigned int reserveSize = 0, unsigned int* puiCreatedSize = 0);

	//MYSQL_BIND* CreateUpdateBind(const T& record, EIODFieldKey eKeyType);

private:

	//MYSQL_STMT* m_stmtInsert;

	//MYSQL_STMT* m_stmtQuery0;
	//MYSQL_STMT* m_stmtQuery1;
	//MYSQL_STMT* m_stmtQuery2;

	//MYSQL_STMT* m_stmtUpdate0;
	//MYSQL_STMT* m_stmtUpdate1;
	//MYSQL_STMT* m_stmtUpdate2;

	//MYSQL_STMT* m_stmtFilter0;
	//MYSQL_STMT* m_stmtFilter1;
	//MYSQL_STMT* m_stmtFilter2;

	//MYSQL_STMT* m_stmtDelete0;
	//MYSQL_STMT* m_stmtDelete1;
	//MYSQL_STMT* m_stmtDelete2;
	//MYSQL_STMT* m_stmtMultiDelete0;
	//MYSQL_STMT* m_stmtMultiDelete1;
	//MYSQL_STMT* m_stmtMultiDelete2;
};


template<typename T>
const char* CMySqlTable<T>::DeleteRecord(MYSQL* pConn, const T& queryRecord, const char* pszCompareFieldNames, unsigned long* pulAffectedRows )
{
	char szSql[SQL_STMT_LENGTH];
	size_t size = 0;

	//MYSQL* pConn = 0;
	//int iConn = CMySqlDB::GetInstance().GetAndLockConn(&pConn);

	//if (iConn < 0)
	//{
	//	return "Get MySql Connection failed";
	//}

	//printf("iConn=[%lu]\n", iConn);

	if (!GetDeleteStmt<T>(pszCompareFieldNames, queryRecord, szSql, size, pConn))
	{
		return "can't get query statement\n";
	}

	{
		szSql[size] = 0;
		//IODDB::STAutoTiming stAutoTiming(szSql, 1);
		if (int iError = mysql_real_query(pConn, szSql, (unsigned long)strlen(szSql)))
		{
			IOD_SRV_ERROR("query error code %d", iError);
			//IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
		//if (mysql_real_query(pConn, szSql, (unsigned long)size))
		//{
		//	return mysql_error(pConn);
		//}
	}

	if (pulAffectedRows)
	{
		*pulAffectedRows = (unsigned long)mysql_affected_rows(pConn);
	}

	//CMySqlDB::GetInstance().UnlockConn(iConn);

	return NULL;
}

template<typename T>
const char* CMySqlTable<T>::UpdateRecord(MYSQL* pConn, const char* pszSql, unsigned long* pulAffectedRows)
{
	//IODDB::STAutoTiming stAutoTiming(pszSql, 1);
	if (int iError = mysql_real_query(pConn, pszSql, (unsigned long)strlen(pszSql)))
	{
		IOD_SRV_ERROR("query error code %d", iError);
		//IOD::on_query_failed_statistics();
		return mysql_error(pConn);
	}
	if (pulAffectedRows)
	{
		*pulAffectedRows = (int)mysql_affected_rows(pConn);
	}
	return NULL;
}

template<typename T>
const char* CMySqlTable<T>::UpdateRecord(MYSQL* pConn, const T& updateRecord, const char* pszCompareFieldNames, unsigned long* pulAffectedRows, const char* pszUpdateFieldNames )
{
	char szSql[SQL_STMT_LENGTH];
	size_t size = 0;

	//MYSQL* pConn = 0;
	//int iConn = CMySqlDB::GetInstance().GetAndLockConn(&pConn);

	//if (iConn < 0)
	//{
	//	return "Get MySql Connection failed\n";
	//}

	//printf("iConn=[%lu]\n", iConn);

	if (!GetUpdateStmt<T>(pszCompareFieldNames, updateRecord, szSql, size, pConn, pszUpdateFieldNames))
	{
		return "can't get query statement\n";
	}

	{
		szSql[size] = 0;
		//IODDB::STAutoTiming stAutoTiming(szSql, 1);
		if (int iError = mysql_real_query(pConn, szSql, (unsigned long)strlen(szSql)))
		{
			IOD_SRV_ERROR("query error code %d", iError);
			//IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
		//if (mysql_real_query(pConn, szSql, (unsigned long)strlen(szSql)))
		//{
		//	return mysql_error(pConn);
		//}
	}

	if (pulAffectedRows)
	{
		*pulAffectedRows = (int)mysql_affected_rows(pConn);
	}

	//CMySqlDB::GetInstance().UnlockConn(iConn);

	return NULL;
}

template<typename T>
const char* CMySqlTable<T>::QueryRecord(MYSQL* pConn, const T& queryRecord, T* pRecords, unsigned long* pulResultCount, const char* pszCompareFieldNames, unsigned long ulStart, unsigned long ulResultMaxCount )
{
	char szSql[SQL_STMT_LENGTH];
	size_t size = 0;

	//MYSQL* pConn = 0;
	//int iConn = CMySqlDB::GetInstance().GetAndLockConn(&pConn);

	//if (iConn < 0)
	//{
	//	return "Get MySql Connection failed\n";
	//}

	if (!GetQueryStmtEx<T>(pszCompareFieldNames, queryRecord, szSql, size, pConn, ulStart, ulResultMaxCount))
	{
		return "can't get query statement\n";
	}

	{
		szSql[size] = 0;
		//IODDB::STAutoTiming stAutoTiming(szSql, 1);
		if (int iError = mysql_real_query(pConn, szSql, (unsigned long)strlen(szSql)))
		{
			IOD_SRV_ERROR("query error code %d", iError);
			//IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
		//if (mysql_real_query(pConn, szSql, (unsigned long)size))
		//{
		//	return mysql_error(pConn);
		//}
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
		const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

		MYSQL_ROW row = 0;

		for (unsigned long ulIdx = 0; ulIdx < num_rows; ulIdx++)
		{
			if (!(row = mysql_fetch_row(pRes)))
			{
				return "fetch result failed\n";
			}

			unsigned long* lengths = mysql_fetch_lengths(pRes); 

			for (unsigned int ui = 0; ui < fieldDescriptor.m_usFieldCount; ui++)
			{
				if (const char* pszResult = GetValueFromSzField<T>(pRecords[ulIdx], fieldDescriptor.m_pFieldInfo[ui], row[ui], lengths[ui]))
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

//------------------------------------------------------------------------------------------------------------------------------------------------
template<typename T>
const char* CMySqlTable<T>::QueryRecord(MYSQL* pConn, const char* pszSql, T* pRecords, unsigned long* pulResultCount, unsigned long ulResultMaxCount)
{
	{
		////IODDB::STAutoTiming stAutoTiming(pszSql, 1);
		if (int iError = mysql_real_query(pConn, pszSql, (unsigned long)strlen(pszSql)))
		{
			IOD_SRV_ERROR("query error code %d", iError);
			////IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
		//if (mysql_real_query(pConn, pszSql, (unsigned long)strlen(pszSql)))
		//{
		//	return mysql_error(pConn);
		//}
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
		const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

		MYSQL_ROW row = 0;

		for (unsigned long ulIdx = 0; ulIdx < num_rows; ulIdx++)
		{
			if (!(row = mysql_fetch_row(pRes)))
			{
				return "fetch result failed\n";
			}

			unsigned long* lengths = mysql_fetch_lengths(pRes); 

			for (unsigned int ui = 0; ui < fieldDescriptor.m_usFieldCount; ui++)
			{
				if (const char* pszResult = GetValueFromSzField<T>(pRecords[ulIdx], fieldDescriptor.m_pFieldInfo[ui], row[ui], lengths[ui]))
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

//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
const char* CMySqlTable<T>::QueryRecord(MYSQL* pConn, const T& queryRecord, T* pRecords, unsigned long* pulResultCount, EIODFieldKey eKeyType, unsigned long ulStart, unsigned long ulResultMaxCount)
{
	char szSql[SQL_STMT_LENGTH];
	size_t size = 0;

	//MYSQL* pConn = 0;
	//int iConn = CMySqlDB::GetInstance().GetAndLockConn(&pConn);

	//if (iConn < 0)
	//{
	//	return "Get MySql Connection failed\n";
	//}
	
	if (!GetQueryStmtEx<T>(eKeyType, queryRecord, szSql, size, pConn, ulStart, ulResultMaxCount))
	{
		return "can't get query statement\n";
	}

	{
		szSql[size] = 0;
		//IODDB::STAutoTiming stAutoTiming(szSql, 1);
		if (int iError = mysql_real_query(pConn, szSql, (unsigned long)strlen(szSql)))
		{
			IOD_SRV_ERROR("query error code %d", iError);
			//IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
		//if (mysql_real_query(pConn, szSql, (unsigned long)size))
		//{
		//	return mysql_error(pConn);
		//}
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
		const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

		MYSQL_ROW row = 0;

		for (unsigned long ulIdx = 0; ulIdx < num_rows; ulIdx++)
		{
			if (!(row = mysql_fetch_row(pRes)))
			{
				return "fetch result failed\n";
			}

			unsigned long* lengths = mysql_fetch_lengths(pRes); 

			for (unsigned int ui = 0; ui < fieldDescriptor.m_usFieldCount; ui++)
			{
				if (const char* pszResult = GetValueFromSzField<T>(pRecords[ulIdx], fieldDescriptor.m_pFieldInfo[ui], row[ui], lengths[ui]))
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
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
const char* CMySqlTable<T>::QueryRecord(MYSQL* pConn, const T& queryRecord, T* pRecords, unsigned long* pulResultCount, const char* pszCompareFieldNames, const char* pszReturnFields, unsigned long ulStart, unsigned long ulResultMaxCount )
{
	char szSql[SQL_STMT_LENGTH];
	size_t size = 0;

	//MYSQL* pConn = 0;
	//int iConn = CMySqlDB::GetInstance().GetAndLockConn(&pConn);

	//if (iConn < 0)
	//{
	//	return "Get MySql Connection failed\n";
	//}

	if (!GetQueryStmtEx<T>(pszCompareFieldNames, queryRecord, szSql, size, pConn, ulStart, ulResultMaxCount, pszReturnFields))
	{
		return "can't get query statement\n";
	}

	{
		szSql[size] = 0;
		//IODDB::STAutoTiming stAutoTiming(szSql, 1);
		if (int iError = mysql_real_query(pConn, szSql, (unsigned long)strlen(szSql)))
		{
			IOD_SRV_ERROR("query error code %d", iError);
			//IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
		//if (mysql_real_query(pConn, szSql, (unsigned long)size))
		//{
		//	return mysql_error(pConn);
		//}
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

	unsigned long num_fields = (unsigned long)mysql_num_fields(pRes);

	if (pRecords)
	{
		const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

		MYSQL_ROW row = 0;

		for (unsigned long ulIdx = 0; ulIdx < num_rows; ulIdx++)
		{
			if (!(row = mysql_fetch_row(pRes)))
			{
				return "fetch result failed\n";
			}

			unsigned long* lengths = mysql_fetch_lengths(pRes); 

			if (pszCompareFieldNames)
			{
				MYSQL_FIELD* resFields = mysql_fetch_fields(pRes);
				for (unsigned int ui = 0; ui < num_fields; ui++)
				{
					if (const char* pszResult = GetValueFromSzField<T>(pRecords[ulIdx], *(fieldDescriptor.GetFieldInfo(resFields[ui].name)), row[ui], lengths[ui]))
					//if (const char* pszResult = GetValueFromSzField<T>(pRecords[ulIdx], fieldDescriptor.m_pFieldInfo[ui], row[ui], lengths[ui]))
					{
						return pszResult;
					}
				}
			}
			else
			{
				for (unsigned int ui = 0; ui < num_fields; ui++)
				{
					if (const char* pszResult = GetValueFromSzField<T>(pRecords[ulIdx], fieldDescriptor.m_pFieldInfo[ui], row[ui], lengths[ui]))
					{
						return pszResult;
					}
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

//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
const char* CMySqlTable<T>::UpdateRecord(MYSQL* pConn,  const T& updateRecord, EIODFieldKey eKeyType, unsigned long* pulAffectedRows, const char* pszUpdateFieldNames )
{
	//IOD_SRV_INFO("UpdateRecord");
	char szSql[SQL_STMT_LENGTH];
	size_t size = 0;

	//MYSQL* pConn = 0;
	//int iConn = CMySqlDB::GetInstance().GetAndLockConn(&pConn);

	//if (iConn < 0)
	//{
	//	return "Get MySql Connection failed\n";
	//}

	//printf("iConn=[%lu]\n", iConn);

	if (!GetUpdateStmt<T>(eKeyType, updateRecord, szSql, size, pConn, pszUpdateFieldNames))
	{
		return "can't get query statement\n";
	}

	{
		szSql[size] = 0;
		//IOD_SRV_INFO("statement:%s", szSql);
		//IODDB::STAutoTiming stAutoTiming(szSql, 1);
		if (int iError = mysql_real_query(pConn, szSql, (unsigned long)strlen(szSql)))
		{
			IOD_SRV_ERROR("query error code %d", iError);
			//IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
		//if (mysql_real_query(pConn, szSql, (unsigned long)size))
		//{
		//	return mysql_error(pConn);
		//}
	}

	if (pulAffectedRows)
	{
		*pulAffectedRows = (int)mysql_affected_rows(pConn);
	}

	//CMySqlDB::GetInstance().UnlockConn(iConn);

	return NULL;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
const char* CMySqlTable<T>::DeleteRecord(MYSQL* pConn, const T& queryRecord, EIODFieldKey eKeyType, unsigned long* pulAffectedRows)
{
	char szSql[SQL_STMT_LENGTH];
	size_t size = 0;

	//MYSQL* pConn = 0;
	//int iConn = CMySqlDB::GetInstance().GetAndLockConn(&pConn);

	//if (iConn < 0)
	//{
	//	return "Get MySql Connection failed";
	//}

	//printf("iConn=[%lu]\n", iConn);

	if (!GetDeleteStmt<T>(eKeyType, queryRecord, szSql, size, pConn))
	{
		return "can't get query statement\n";
	}

	{
		szSql[size] = 0;
		//IODDB::STAutoTiming stAutoTiming(szSql, 1);
		if (int iError = mysql_real_query(pConn, szSql, (unsigned long)strlen(szSql)))
		{
			IOD_SRV_ERROR("query error code %d", iError);
			//IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
		//if (mysql_real_query(pConn, szSql, (unsigned long)size))
		//{
		//	return mysql_error(pConn);
		//}
	}


	if (pulAffectedRows)
	{
		*pulAffectedRows = (unsigned long)mysql_affected_rows(pConn);
	}

	//CMySqlDB::GetInstance().UnlockConn(iConn);

	return NULL;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
const char* CMySqlTable<T>::InsertRecord(MYSQL* pConn,  const T& insertRecord, const char* pszValidFieldNames )
{
	char szSql[SQL_STMT_LENGTH];
	size_t size = 0;

	//MYSQL* pConn = 0;
	//int iConn = CMySqlDB::GetInstance().GetAndLockConn(&pConn);

	//if (iConn < 0)
	//{
	//	return "Get MySql Connection failed\n";
	//}

	if (!GetInsertStmt<T>(insertRecord, szSql, size, pConn, pszValidFieldNames))
	{
		return "can't get query statement\n";
	}

	{
		szSql[size] = 0;
		//IODDB::STAutoTiming stAutoTiming(szSql, 1);
		if (int iError = mysql_real_query(pConn, szSql, (unsigned long)strlen(szSql)))
		{
			IOD_SRV_ERROR("query error code %d", iError);
			//IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
		//if (mysql_real_query(pConn, szSql, (unsigned long)size))
		//{
		//	return mysql_error(pConn);
		//}
	}


	//CMySqlDB::GetInstance().UnlockConn(iConn);

	return NULL;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
bool GetUpdateStmt( EIODFieldKey eKeyType, const T& record, char* pszStmt, size_t& size, MYSQL* pConn, const char* pszUpdateFieldNames )
{
	//TRACE("GetUpdateStmt");
	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

	char szSetValue[SQL_STMT_LENGTH] = {0};
	char szWhere[SQL_STMT_LENGTH] = {0};
	size_t sWhereLength = 0;
	size_t sSetValueLength = 0;
	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
	{
		char szValue[SQL_VALUE_LENGTH];
		size_t sValueSize = 0;
		
		bool bValueGet = false;
		if ((!(fieldDescriptor.m_pFieldInfo[idx].m_eKType & IOD_FIELD_KEY_AUTO_INC)) && (!pszUpdateFieldNames || is_field_in(pszUpdateFieldNames, fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName)))
		{
			GetFieldSzValue<T>(record, fieldDescriptor.m_pFieldInfo[idx], SQL_VALUE_LENGTH, szValue, sValueSize, pConn);
			//TRACE("%s, %d, %s", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName, sValueSize, szValue);

			bValueGet = true;

			if (!szSetValue[0])
			{
				sprintf_s(szSetValue, SQL_STMT_LENGTH, " set %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sSetValueLength = strlen(szSetValue);
			}
			else
			{
				sprintf_s(szSetValue + sSetValueLength, SQL_STMT_LENGTH - sSetValueLength, ", %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sSetValueLength += (strlen(", =") + strlen(fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName));
			}

			memcpy(szSetValue + sSetValueLength, szValue, sValueSize);

			sSetValueLength += sValueSize;

		}
		
		//--------------------------------------------------------------------------------

		if (fieldDescriptor.m_pFieldInfo[idx].m_eKType & eKeyType)
		{
			if (!bValueGet)
			{
				GetFieldSzValue<T>(record, fieldDescriptor.m_pFieldInfo[idx], SQL_VALUE_LENGTH, szValue, sValueSize, pConn);
			}
			
			if (!szWhere[0])
			{
				sprintf_s(szWhere, SQL_STMT_LENGTH, " where %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sWhereLength = strlen(szWhere);
			}
			else
			{
				sprintf_s(szWhere + sWhereLength, SQL_STMT_LENGTH - sWhereLength, " and %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sWhereLength += (strlen(" and ") + strlen(fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName) + strlen("="));
			}

			memcpy(szWhere + sWhereLength, szValue, sValueSize);

			sWhereLength += sValueSize;
		}
	}
	if (!szWhere[0])
	{
		return false;
	}

	sprintf_s(pszStmt, SQL_STMT_LENGTH, "update %s", fieldDescriptor.m_pszTableName);
	size = strlen(pszStmt);

	//TRACE("%s, %d, %d, %d", pszStmt, size, sSetValueLength, sWhereLength);
	szSetValue[sSetValueLength] = 0;
	szWhere[sWhereLength] = 0;
	//TRACE("%s", szWhere);
	//TRACE("%s", szSetValue);

	memcpy(pszStmt + size, szSetValue, sSetValueLength);
	size += sSetValueLength;

	memcpy(pszStmt + size, szWhere, sWhereLength);
	size += sWhereLength;

	pszStmt[size] = 0;

	//TRACE("%s", pszStmt);

	return true;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
bool GetUpdateStmt( const char* pszCompareFieldNames, const T& record, char* pszStmt, size_t& size, MYSQL* pConn, const char* pszUpdateFieldNames )
{
	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

	char szSetValue[SQL_STMT_LENGTH] = {0};
	char szWhere[SQL_STMT_LENGTH] = {0};
	size_t sWhereLength = 0;
	size_t sSetValueLength = 0;
	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
	{
		char szValue[SQL_VALUE_LENGTH];
		size_t sValueSize = 0;
		
		bool bValueGet = false;
		if ((!(fieldDescriptor.m_pFieldInfo[idx].m_eKType & IOD_FIELD_KEY_AUTO_INC)) && (!pszUpdateFieldNames || is_field_in(pszUpdateFieldNames, fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName)))
		{
			GetFieldSzValue<T>(record, fieldDescriptor.m_pFieldInfo[idx], SQL_VALUE_LENGTH, szValue, sValueSize, pConn);
			bValueGet = true;

			if (!szSetValue[0])
			{
				sprintf_s(szSetValue, SQL_STMT_LENGTH, " set %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sSetValueLength = strlen(szSetValue);
			}
			else
			{
				sprintf_s(szSetValue + sSetValueLength, SQL_STMT_LENGTH - sSetValueLength, ", %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sSetValueLength += (strlen(", =") + strlen(fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName));
			}

			memcpy(szSetValue + sSetValueLength, szValue, sValueSize);

			sSetValueLength += sValueSize;

		}

		//--------------------------------------------------------------------------------

		if (is_field_in(pszCompareFieldNames, fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName))
		{
			if (!bValueGet)
			{
				GetFieldSzValue<T>(record, fieldDescriptor.m_pFieldInfo[idx], SQL_VALUE_LENGTH, szValue, sValueSize, pConn);
			}
			
			if (!szWhere[0])
			{
				sprintf_s(szWhere, SQL_STMT_LENGTH, " where %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sWhereLength = strlen(szWhere);
			}
			else
			{
				sprintf_s(szWhere + sWhereLength, SQL_STMT_LENGTH - sWhereLength, " and %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sWhereLength += (strlen(" and ") + strlen(fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName) + strlen("="));
			}

			memcpy(szWhere + sWhereLength, szValue, sValueSize);

			sWhereLength += sValueSize;
		}
	}
	if (!szWhere[0])
	{
		return false;
	}

	sprintf_s(pszStmt, SQL_STMT_LENGTH, "update %s", fieldDescriptor.m_pszTableName);
	size = strlen(pszStmt);

	memcpy(pszStmt + size, szSetValue, sSetValueLength);
	size += sSetValueLength;

	memcpy(pszStmt + size, szWhere, sWhereLength);
	size += sWhereLength;

	pszStmt[size] = 0;

	return true;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
bool GetInsertStmt( const T& record, char* pszStmt, size_t& size, MYSQL* pConn, const char* pszValidFieldNames )
{
	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

	char szInsertValue[SQL_STMT_LENGTH] = {0};
	char szColumns[SQL_STMT_LENGTH] = {0};
	size_t sInsertValueLength = 0;
	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
	{
		//忽略自增字段
		if (fieldDescriptor.m_pFieldInfo[idx].m_eKType & IOD_FIELD_KEY_AUTO_INC)
		{
			continue;
		}

		//如果pszValidFieldNames非空，忽略pszValidFieldNames不包含的字段
		if (pszValidFieldNames && !is_field_in(pszValidFieldNames, fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName))
		{
			continue;
		}
		
		if (!szColumns[0])
		{
			sprintf_s(szColumns, SQL_STMT_LENGTH, " (%s", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
		} 
		else
		{
			sprintf_s(szColumns + strlen(szColumns), SQL_STMT_LENGTH - strlen(szColumns), " ,%s", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
		}	

		if (!szInsertValue[0])
		{
			sprintf_s(szInsertValue, SQL_STMT_LENGTH, " value (");
			sInsertValueLength = strlen(szInsertValue);
		}
		else
		{
			sprintf_s(szInsertValue + sInsertValueLength, SQL_STMT_LENGTH - sInsertValueLength, ", ");
			sInsertValueLength += strlen(", ");
		}

		char szValue[SQL_VALUE_LENGTH];
		size_t sValueSize = 0;
		GetFieldSzValue<T>(record, fieldDescriptor.m_pFieldInfo[idx], SQL_VALUE_LENGTH, szValue, sValueSize, pConn);

		memcpy(szInsertValue + sInsertValueLength, szValue, sValueSize);

		sInsertValueLength += sValueSize;
	}

	memcpy(szColumns + strlen(szColumns), ")\0", 2);

	memcpy(szInsertValue + sInsertValueLength, ")", 1);
	sInsertValueLength += 1;


	sprintf_s(pszStmt, SQL_STMT_LENGTH, "insert %s %s", fieldDescriptor.m_pszTableName, szColumns);
	size = strlen(pszStmt);

	memcpy(pszStmt + size, szInsertValue, sInsertValueLength);
	size += sInsertValueLength;

	pszStmt[size] = 0;

	return true;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
bool GetDeleteStmt( EIODFieldKey eKeyType, const T& record, char* pszStmt, size_t& size, MYSQL* pConn  )
{
	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

	char szWhere[SQL_STMT_LENGTH] = {0};
	size_t sWhereLength = 0;
	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
	{
		//--------------------------------------------------------------------------------

		if (fieldDescriptor.m_pFieldInfo[idx].m_eKType & eKeyType)
		{
			char szValue[SQL_VALUE_LENGTH];
			size_t sValueSize = 0;
			GetFieldSzValue<T>(record, fieldDescriptor.m_pFieldInfo[idx], SQL_VALUE_LENGTH, szValue, sValueSize, pConn);

			if (!szWhere[0])
			{
				sprintf_s(szWhere, SQL_STMT_LENGTH, " where %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sWhereLength = strlen(szWhere);
			}
			else
			{
				sprintf_s(szWhere + sWhereLength, SQL_STMT_LENGTH - sWhereLength, " and %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sWhereLength += (strlen(" and ") + strlen(fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName) + strlen("="));
			}

			memcpy(szWhere + sWhereLength, szValue, sValueSize);

			sWhereLength += sValueSize;
		}
	}
	if (!szWhere[0])
	{
		return false;
	}
	

	sprintf_s(pszStmt, SQL_STMT_LENGTH, "delete from %s", fieldDescriptor.m_pszTableName);
	size = strlen(pszStmt);

	memcpy(pszStmt + size, szWhere, sWhereLength);
	size += sWhereLength;

	pszStmt[size] = 0;

	return true;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
bool GetDeleteStmt( const char* pszCompareFieldNames, const T& record, char* pszStmt, size_t& size, MYSQL* pConn  )
{
	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

	char szWhere[SQL_STMT_LENGTH] = {0};
	size_t sWhereLength = 0;
	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
	{
		//--------------------------------------------------------------------------------

		if (is_field_in(pszCompareFieldNames, fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName))
		{
			char szValue[SQL_VALUE_LENGTH];
			size_t sValueSize = 0;
			GetFieldSzValue<T>(record, fieldDescriptor.m_pFieldInfo[idx], SQL_VALUE_LENGTH, szValue, sValueSize, pConn);

			if (!szWhere[0])
			{
				sprintf_s(szWhere, SQL_STMT_LENGTH, " where %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sWhereLength = strlen(szWhere);
			}
			else
			{
				sprintf_s(szWhere + sWhereLength, SQL_STMT_LENGTH - sWhereLength, " and %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				sWhereLength += (strlen(" and ") + strlen(fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName) + strlen("="));
			}

			memcpy(szWhere + sWhereLength, szValue, sValueSize);

			sWhereLength += sValueSize;
		}
	}
	if (!szWhere[0])
	{
		return false;
	}


	sprintf_s(pszStmt, SQL_STMT_LENGTH, "delete from %s", fieldDescriptor.m_pszTableName);
	size = strlen(pszStmt);

	memcpy(pszStmt + size, szWhere, sWhereLength);
	size += sWhereLength;

	pszStmt[size] = 0;

	return true;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
bool GetQueryStmt( EIODFieldKey eKeyType, const T& record, char* pszStmt, size_t& size, MYSQL* pConn )
{
	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

	char szSelect[SQL_STMT_LENGTH] = {0};
	char szWhere[SQL_STMT_LENGTH] = {0};
	size_t szWhereLength = 0;
	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
	{
		if (!szSelect[0])
		{
			sprintf_s(szSelect, SQL_STMT_LENGTH, "select %s ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
		}
		else
		{
			sprintf_s(szSelect + strlen(szSelect), SQL_STMT_LENGTH - strlen(szSelect), ", %s ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
		}

		if (fieldDescriptor.m_pFieldInfo[idx].m_eKType & eKeyType)
		{
			char szValue[SQL_VALUE_LENGTH];
			size_t sValueSize = 0;
			GetFieldSzValue<T>(record, fieldDescriptor.m_pFieldInfo[idx], SQL_VALUE_LENGTH, szValue, sValueSize, pConn);
			if (!szWhere[0])
			{
				sprintf_s(szWhere, SQL_STMT_LENGTH, "where %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				szWhereLength = strlen(szWhere);
			}
			else
			{
				sprintf_s(szWhere + szWhereLength, SQL_STMT_LENGTH - szWhereLength, " and %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				szWhereLength += (strlen(" and ") + strlen(fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName) + strlen("="));
			}

			memcpy(szWhere + szWhereLength, szValue, sValueSize);

			szWhereLength += sValueSize;
		}
	}

	if (!szWhere[0])
	{
		return false;
	}

	sprintf_s(pszStmt, SQL_STMT_LENGTH, "%s from %s ", szSelect, fieldDescriptor.m_pszTableName);

	size = strlen(pszStmt) + szWhereLength;

	memcpy(pszStmt + strlen(pszStmt), szWhere, szWhereLength);

	pszStmt[size] = 0;

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
bool GetQueryStmt( const char* pszCompareFieldNames, const T& record, char* pszStmt, size_t& size, MYSQL* pConn, const char* pszReturnFieldNames)
{
	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();

	char szSelect[SQL_STMT_LENGTH] = {0};
	char szWhere[SQL_STMT_LENGTH] = {0};
	size_t szWhereLength = 0;
	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
	{
		if (pszReturnFieldNames == NULL || is_field_in(pszReturnFieldNames, fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName))
		{
			if (!szSelect[0])
			{
				sprintf_s(szSelect, SQL_STMT_LENGTH, "select %s ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
			}
			else
			{
				sprintf_s(szSelect + strlen(szSelect), SQL_STMT_LENGTH - strlen(szSelect), ", %s ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
			}
		}

		if (is_field_in(pszCompareFieldNames, fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName))
		{
			char szValue[SQL_VALUE_LENGTH];
			size_t sValueSize = 0;
			GetFieldSzValue<T>(record, fieldDescriptor.m_pFieldInfo[idx], SQL_VALUE_LENGTH, szValue, sValueSize, pConn);
			if (!szWhere[0])
			{
				sprintf_s(szWhere, SQL_STMT_LENGTH, "where %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				szWhereLength = strlen(szWhere);
			}
			else
			{
				sprintf_s(szWhere + szWhereLength, SQL_STMT_LENGTH - szWhereLength, " and %s=", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
				szWhereLength += (strlen(" and ") + strlen(fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName) + strlen("="));
			}

			memcpy(szWhere + szWhereLength, szValue, sValueSize);

			szWhereLength += sValueSize;
		}
	}

	if (!szWhere[0])
	{
		return false;
	}

	sprintf_s(pszStmt, SQL_STMT_LENGTH, "%s from %s ", szSelect, fieldDescriptor.m_pszTableName);

	size = strlen(pszStmt) + szWhereLength;

	memcpy(pszStmt + strlen(pszStmt), szWhere, szWhereLength);

	pszStmt[size] = 0;

	return true;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
bool GetQueryStmtEx( EIODFieldKey eKeyType, const T& record, char* pszStmt, size_t& size, MYSQL* pConn, unsigned long ulStart, unsigned long ulMaxCount)
{
	if (!GetQueryStmt(eKeyType, record, pszStmt, size, pConn))
	{
		return false;
	}
	
	if (ulMaxCount)
	{
		char appendix[256];
		sprintf_s(appendix, 256, " limit %lu, %lu", ulStart, ulMaxCount);
		memcpy(pszStmt + size, appendix, strlen(appendix));
		size += strlen(appendix);
	}

	return true;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
bool GetQueryStmtEx( const char* pszCompareFieldNames, const T& record, char* pszStmt, size_t& size, MYSQL* pConn, unsigned long ulStart, unsigned long ulMaxCount, const char* pszReturnFieldNames)
{
	if (!GetQueryStmt(pszCompareFieldNames, record, pszStmt, size, pConn, pszReturnFieldNames))
	{
		return false;
	}

	if (ulMaxCount)
	{
		char appendix[256];
		sprintf_s(appendix, 256, " limit %lu, %lu", ulStart, ulMaxCount);
		memcpy(pszStmt + size, appendix, strlen(appendix));
		size += strlen(appendix);
	}

	return true;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
const char* GetValueFromSzField( T& record, const STFieldInfo& field, const char* szValue, unsigned long ulLength )
{
	switch (field.m_eVType)
	{
	case IOD_FIELD_TYPE_BOOL:
		{
			//sscanf_s(szValue, "%s", (bool*)((char*)(&record) + field.m_nOffset));	
			if (szValue[0] == '0')
			{
				*(bool*)((char*)(&record) + field.m_nOffset) = false;
			}
			else
			{
				*(bool*)((char*)(&record) + field.m_nOffset) = true;
			}
		}
		break;
	case IOD_FIELD_TYPE_UINT1:
		{
			//sscanf_s(szValue, "%d", (uint8*)((char*)(&record) + field.m_nOffset));
			*(uint8*)((char*)(&record) + field.m_nOffset) = (uint8)strtoul(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_UINT2:
		{
			//sscanf_s(szValue, "%h", (uint16*)((char*)(&record) + field.m_nOffset));
			*(uint16*)((char*)(&record) + field.m_nOffset) = (uint16)strtoul(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_UINT4:
		{
			//sscanf_s(szValue, "%d", (uint32*)((char*)(&record) + field.m_nOffset));
			*(uint32*)((char*)(&record) + field.m_nOffset) = (uint32)strtoul(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_UINT8:
		{
			//sscanf_s(szValue, "%L", (uint64*)((char*)(&record) + field.m_nOffset));
			*(uint64*)((char*)(&record) + field.m_nOffset) = (uint64)strtoull(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_INT1:
		{
			//sscanf_s(szValue, "%d", (int8*)((char*)(&record) + field.m_nOffset));
			*(int8*)((char*)(&record) + field.m_nOffset) = (int8)strtol(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_INT2:
		{
			//sscanf_s(szValue, "%d", (int16*)((char*)(&record) + field.m_nOffset));
			*(int16*)((char*)(&record) + field.m_nOffset) = (int16)strtol(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_INT4:
		{
			//sscanf_s(szValue, "%d", (int32*)((char*)(&record) + field.m_nOffset));
			*(int32*)((char*)(&record) + field.m_nOffset) = (int32)strtol(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_INT8:
		{
			//sscanf_s(szValue, "%d", (int64*)((char*)(&record) + field.m_nOffset));
			*(int64*)((char*)(&record) + field.m_nOffset) = (int64)strtoll(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_REAL4:
		{
			//sscanf_s(szValue, "%f", (float*)((char*)(&record) + field.m_nOffset));
			*(float*)((char*)(&record) + field.m_nOffset) = (float)strtod(szValue, NULL);
		}
		break;
	case IOD_FIELD_TYPE_REAL8:
		{
			//sscanf_s(szValue, "%f", (double*)((char*)(&record) + field.m_nOffset));
			*(double*)((char*)(&record) + field.m_nOffset) = (double)strtod(szValue, NULL);
		}
		break;
	case IOD_FIELD_TYPE_STRING:
		{	
			if (ulLength >= field.m_nSize)
			{
				//printf("%s\n", field.m_pszFieldName);
				//return "mysql error: field value length overflow!\n";			
				ulLength = (unsigned long)field.m_nSize - 1;
				IOD_SRV_CRIT("field %s value length %lu overflow!", field.m_pszFieldName, ulLength);
			}
			memcpy((char*)(&record) + field.m_nOffset, szValue, ulLength);
			((char*)(&record) + field.m_nOffset)[ulLength] = 0;
		}
		break;
	case IOD_FIELD_TYPE_BLOB:
		{
			if (ulLength > field.m_nSize)
			{
				printf("%s\n", field.m_pszFieldName);
				return "mysql error: field value length overflow!\n";
			}			
			memcpy((char*)(&record) + field.m_nOffset, szValue, ulLength);
			((char*)(&record) + field.m_nOffset)[ulLength] = 0;

			//紧跟的下一个字段是blob长度
			*(uint16*)((char*)(&record) + field.m_nOffset + field.m_iSizeMemberOffset) = (uint16)ulLength;
		}
		break;
	case IOD_FIELD_TYPE_TIME:
		{
			//char szTest[128] = "2010-12-10 10:10:10";
			//tm tt;
			//strptime(szTest, "%Y-%m-%d %H:%M:%S", &tt);
			//time_t ttt = mktime(&tt);
			if (ulLength <= 4 || szValue[0] == 0 || memcmp(szValue, "NULL", 4) == 0)
			{
				*(time_t*)((char*)(&record) + field.m_nOffset) = 0;
			}
			else
			{
				tm tm1 = {0};
				strptime(szValue, "%Y-%m-%d %H:%M:%S", &tm1);
				if (tm1.tm_year < 0)
				{
					*(time_t*)((char*)(&record) + field.m_nOffset) = 0;
				}
				else
				{
					*(time_t*)((char*)(&record) + field.m_nOffset) = iod_utility::MKTime(&tm1);
				}				
			}
			
			//time_t t2 = mktime(&tm1);
		}
		break;
	default:
		{
			if (ulLength > field.m_nSize)
			{
				printf("%s\n", field.m_pszFieldName);
				return "mysql error: field value length overflow!\n";
			}	
			memcpy((char*)(&record) + field.m_nOffset, szValue, ulLength);
		}
		break;
	}

	return NULL;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
void GetFieldSzValue( const T& record, const STFieldInfo& field, const unsigned int uiMaxSize, char* szValue, size_t& sSize, const MYSQL* pConn )
{
	switch (field.m_eVType)
	{
	case IOD_FIELD_TYPE_BOOL:
		{
			sprintf_s(szValue, uiMaxSize, "%s", (((char*)(&record) + field.m_nOffset)[0] != 0) ? "TRUE" : "FALSE");
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_UINT1:
		{
			sprintf_s(szValue, uiMaxSize, "%lu", (unsigned long)(*(uint8*)((char*)(&record) + field.m_nOffset)));
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_UINT2:
		{
			sprintf_s(szValue, uiMaxSize, "%lu", (unsigned long)(*(uint16*)((char*)(&record) + field.m_nOffset)));
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_UINT4:
		{
			sprintf_s(szValue, uiMaxSize, "%lu", (unsigned long)(*(uint32*)((char*)(&record) + field.m_nOffset)));
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_UINT8:
		{
			sprintf_s(szValue, uiMaxSize, "%llu", *(uint64*)((char*)(&record) + field.m_nOffset));
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_INT1:
		{
			sprintf_s(szValue, uiMaxSize, "%ld", (long)(*(int8*)((char*)(&record) + field.m_nOffset)));
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_INT2:
		{
			sprintf_s(szValue, uiMaxSize, "%ld", (long)(*(int16*)((char*)(&record) + field.m_nOffset)));
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_INT4:
		{
			sprintf_s(szValue, uiMaxSize, "%ld", (long)(*(int32*)((char*)(&record) + field.m_nOffset)));
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_INT8:
		{
			sprintf_s(szValue, uiMaxSize, "%lld", *(int64*)((char*)(&record) + field.m_nOffset));
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_REAL4:
		{
			sprintf_s(szValue, uiMaxSize, "%f", *(float*)((char*)(&record) + field.m_nOffset));
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_REAL8:
		{
			sprintf_s(szValue, uiMaxSize, "%f", *(double*)((char*)(&record) + field.m_nOffset));
			sSize = strlen(szValue);
		}
		break;
	case IOD_FIELD_TYPE_STRING:
		{
			memset(szValue, 0, uiMaxSize);
			szValue[0] = '\'';
			memcpy(szValue + 1, (char*)(&record) + field.m_nOffset, field.m_nSize);
			sSize = strlen(szValue);
			szValue[sSize] = '\'';
			sSize++;
			
			for (size_t i = 1; i < sSize - 1; i++)
			{
				if (szValue[i] == '\'' || szValue[i] == '\\')
				{
					memmove(szValue + i + 1, szValue + i, sSize - i);
					szValue[i] = '\\';
					i++;
					sSize++;
				}				
			}
			
		}
		break;
	case IOD_FIELD_TYPE_TIME:
		{
			time_t t = *(time_t*)((char*)(&record) + field.m_nOffset);
			if (t == 0 && !strcmp(field.m_pszDefaultValue, "CURRENT_TIMESTAMP"))
			{
				//如果缺省值是当前时间的话，则时间参数不填
				memcpy(szValue, "NULL", 4);
				sSize = 4;
			}
			else
			{
				tm* plt = localtime(&t);
				if (plt != NULL)
				{
					strftime(szValue, uiMaxSize, "%Y%m%d%H%M%S", localtime(&t));
					sSize = strlen(szValue);
				}
				else
				{
					memcpy(szValue, "NULL", 4);
					sSize = 4;
				}			
			}
		}
		break;
	case IOD_FIELD_TYPE_BLOB:
		{
			sSize = *(uint16*)((char*)(&record) + field.m_nOffset + field.m_iSizeMemberOffset);	//可变长类型的下一个字段必紧跟其长度
			//TRACE("sSize %d", sSize);
			if (sSize == 0)
			{
				strcpy_s(szValue, uiMaxSize, "NULL");
				sSize = strlen("NULL");
			}
			else
			{
				//szValue[0] = '\'';
				//mysql_real_escape_string(pConn, szValue + 1, (char*)(&record) + field.m_nOffset, (unsigned long)uiSize);
				//uiSize = strlen(szValue);
				//szValue[uiSize] = '\'';
				//uiSize += 1;
				memcpy(szValue, "0x", 2);
				for (unsigned int ui = 0; ui < sSize; ui++)
				{
					sprintf_s(szValue + 2 + 2 * ui, uiMaxSize - 2 - 2 * ui, "%02x", *((unsigned char*)(&record) + field.m_nOffset + ui));
					//TRACE("uiMaxSize %d, ui %d, len %d, szValue %s", uiMaxSize, ui, strlen(szValue), szValue);
				}
				sSize = 2 * sSize + 2;
				//TRACE("sSize %d", sSize);
			}			
		}
		break;
	default:
		{
			memcpy(szValue + 1, (char*)(&record) + field.m_nOffset, sSize);
			sSize = field.m_nSize;
		}
		break;
	}

	return;
}

//template<typename T>
//const char* CMySqlTable<T>::FilterRecord( T* resultRecords, unsigned long& ulResultCount, const unsigned long ulResultMaxSize, const T& queryRecord, EIODFieldKey eKeyType, const unsigned long ulStart /*= 0*/ )
//{
//	if (eKeyType != IOD_FIELD_KEY_FILTER_0 &&
//		eKeyType != IOD_FIELD_KEY_FILTER_1 &&
//		eKeyType != IOD_FIELD_KEY_FILTER_2)
//	{
//		return "invalid key type\n";
//	}
//
//	char szSql[SQL_STMT_LENGTH];
//	size_t size = 0;
//
//	MYSQL* pConn = 0;
//	int iConn = CMySqlDB::GetInstance().GetAndLockConn(&pConn);
//
//	if (iConn < 0)
//	{
//		return "Get MySql Connection failed";
//	}
//
//	//printf("iConn=[%lu]\n", iConn);
//
//	if (!GetFilterStmt<T>(eKeyType, queryRecord, szSql, size, pConn, ulStart, ulResultMaxSize))
//	{
//		return "can't get query statement\n";
//	}
//
//	if (mysql_real_query(pConn, szSql, (unsigned long)size))
//	{
//		return mysql_error(pConn);
//	}
//
//	MYSQL_RES* pRes = mysql_store_result(pConn);
//
//	if (!pRes)
//	{
//		return mysql_error(pConn);
//	}
//
//	ulResultCount = (int)mysql_num_rows(pRes);
//
//	MYSQL_ROW row = 0;
//	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();
//	for (unsigned long ulIdx = 0; ulIdx < ulResultCount; ulIdx++)
//	{
//		if (!(row = mysql_fetch_row(pRes)))
//		{
//			return "fetch result failed\n";
//		}
//		
//		unsigned long* lengths=mysql_fetch_lengths(pRes); 
//
//		for (unsigned int ui = 0; ui < fieldDescriptor.m_usFieldCount; ui++)
//		{
//			if (const char* pszResult = GetValueFromSzField<T>(resultRecords[ulIdx], fieldDescriptor.m_pFieldInfo[ui], row[ui], lengths[ui]))
//			{
//				return pszResult;
//			}
//		}
//	}
//		
//	mysql_free_result(pRes);
//
//	CMySqlDB::GetInstance().UnlockConn(iConn);
//
//	return NULL;
//}

//template<typename T>
//const char* CMySqlTable<T>::DeleteRecord( const T& record, EIODFieldKey eKeyType, my_ulonglong& affectedRows )
//{
//	MYSQL_STMT* stmt = NULL;
//	switch (eKeyType)
//	{
//	case IOD_FIELD_KEY_UNIQUE_0:
//		stmt = m_stmtDelete0;
//		break;
//	case IOD_FIELD_KEY_UNIQUE_1:
//		stmt = m_stmtDelete1;
//		break;
//	case IOD_FIELD_KEY_UNIQUE_2:
//		stmt = m_stmtDelete2;
//		break;
//	case IOD_FIELD_KEY_FILTER_0:
//		stmt = m_stmtMultiDelete0;
//		break;
//	case IOD_FIELD_KEY_FILTER_1:
//		stmt = m_stmtMultiDelete1;
//		break;
//	case IOD_FIELD_KEY_FILTER_2:
//		stmt = m_stmtMultiDelete2;
//		break;
//	default:
//		break;
//	}
//
//	if (!stmt)
//	{
//		return "statement not prepared, call T::PrepareTable() first or invalid key type!\n";
//	}
//
//	if (!CMySqlDB::GetInstance().LockConn(stmt->mysql))
//	{
//		return "wait connection time out";
//	}
//
//	MYSQL_BIND* bind = CreateBind(record, eKeyType);
//
//	/* Bind the buffers */
//	if (mysql_stmt_bind_param(stmt, bind))
//	{
//		SAFE_QUIT_QUERY(stmt, bind, mysql_stmt_error(stmt));
//	}
//
//	if (mysql_stmt_execute(stmt))
//	{
//		SAFE_QUIT_QUERY(stmt, bind, mysql_stmt_error(stmt));
//	}
//
//	affectedRows = mysql_stmt_affected_rows(stmt);
//
//	SAFE_QUIT_QUERY(stmt, bind, NULL);
//}
//
//template<typename T>
//bool CMySqlTable<T>::PrepareDelete( EIODFieldKey eKeyType )
//{
//	if ((eKeyType == IOD_FIELD_KEY_UNIQUE_0 && m_stmtDelete0)
//		|| (eKeyType == IOD_FIELD_KEY_UNIQUE_1 && m_stmtDelete1)
//		|| (eKeyType == IOD_FIELD_KEY_UNIQUE_2 && m_stmtDelete2)
//		|| (eKeyType == IOD_FIELD_KEY_FILTER_0 && m_stmtMultiDelete0)
//		|| (eKeyType == IOD_FIELD_KEY_FILTER_1 && m_stmtMultiDelete1)
//		|| (eKeyType == IOD_FIELD_KEY_FILTER_2 && m_stmtMultiDelete2))
//	{
//		return true;
//	}
//
//	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
//	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();
//
//	char szWhere[SQL_STMT_LENGTH] = {0};
//	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
//	{
//		if (fieldDescriptor.m_pFieldInfo[idx].m_eKType == eKeyType)
//		{
//			if (!szWhere[0])
//			{
//				sprintf_s(szWhere, SQL_STMT_LENGTH, "where %s=? ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);				
//			}
//			else
//			{
//				sprintf_s(szWhere + strlen(szWhere), SQL_STMT_LENGTH - strlen(szWhere), "and %s=? ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//			}
//		}
//	}
//
//	if (!szWhere[0])
//	{
//		return false;
//	}
//
//	char szQuery[SQL_STMT_LENGTH];
//	sprintf_s(szQuery, SQL_STMT_LENGTH, "delete from %s %s", fieldDescriptor.m_pszTableName, szWhere);
//
//	switch (eKeyType)
//	{
//	case IOD_FIELD_KEY_UNIQUE_0:
//		m_stmtDelete0 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtDelete0 != NULL;
//	case IOD_FIELD_KEY_UNIQUE_1:
//		m_stmtDelete1 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtDelete1 != NULL;
//	case IOD_FIELD_KEY_UNIQUE_2:
//		m_stmtDelete2 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtDelete2 != NULL;
//	case IOD_FIELD_KEY_FILTER_0:
//		m_stmtMultiDelete0 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtMultiDelete0 != NULL;
//	case IOD_FIELD_KEY_FILTER_1:
//		m_stmtMultiDelete1 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtMultiDelete1 != NULL;
//	case IOD_FIELD_KEY_FILTER_2:
//		m_stmtMultiDelete2 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtMultiDelete2 != NULL;
//	default:
//		break;
//	}
//
//	return false;	
//}
//
//template<typename T>
//MYSQL_BIND* CMySqlTable<T>::CreateUpdateBind( const T& record, EIODFieldKey eKeyType )
//{
//	if (eKeyType != IOD_FIELD_KEY_UNIQUE_0 && eKeyType != IOD_FIELD_KEY_UNIQUE_1 && eKeyType != IOD_FIELD_KEY_UNIQUE_2)
//	{
//		return NULL;
//	}
//
//	//先计数
//	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();
//	unsigned int uiBindCount = fieldDescriptor.m_usFieldCount;
//
//	for (unsigned int ui = 0; ui < fieldDescriptor.m_usFieldCount; ui++)
//	{
//		if (fieldDescriptor.m_pFieldInfo[ui].m_eKType == eKeyType)
//		{
//			uiBindCount++;
//		}		
//	}
//
//	if (uiBindCount == fieldDescriptor.m_usFieldCount)
//	{
//		return NULL;
//	}
//
//	MYSQL_BIND* bind = new MYSQL_BIND[uiBindCount];
//
//	BindRecord(bind, record);
//
//	BindRecord(bind + fieldDescriptor.m_usFieldCount, record, eKeyType);
//
//	return bind;
//}
//
//template<typename T>
//void CMySqlTable<T>::BindRecord( MYSQL_BIND* bind, const T& record, EIODFieldKey eKeyType /*= IOD_FIELD_KEY_NONE*/, const unsigned int uiBindMaxSize /*= 0*/, unsigned int* puiBindReturnSize /*= 0*/ )
//{
//	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();
//
//	unsigned int uiBindCount = 0;
//	for (unsigned int ui = 0; ui < fieldDescriptor.m_usFieldCount; ui++)
//	{
//		if (eKeyType == IOD_FIELD_KEY_NONE || fieldDescriptor.m_pFieldInfo[ui].m_eKType == eKeyType)
//		{
//			memset(bind + uiBindCount, 0, sizeof(MYSQL_BIND));
//			BindField(bind[uiBindCount++], record, fieldDescriptor.m_pFieldInfo[ui]);	
//		}
//
//		if (uiBindMaxSize && uiBindCount == uiBindMaxSize)
//		{
//			break;
//		}
//	}
//
//	if (puiBindReturnSize)
//	{
//		*puiBindReturnSize = uiBindCount;
//	}
//
//	return;
//}
//
//
//template<typename T>
//MYSQL_BIND* CMySqlTable<T>::CreateBind( const T& record, EIODFieldKey eKeyType /*= IOD_FIELD_KEY_NONE*/, const unsigned int reserveSize /*= 0*/, unsigned int* puiCreatedSize /*= 0*/ )
//{
//	//先计数
//	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();
//	unsigned int uiBindCount = 0;
//	if (eKeyType == IOD_FIELD_KEY_NONE)
//	{
//		uiBindCount = fieldDescriptor.m_usFieldCount;		
//	}
//
//	else
//	{
//		for (unsigned int ui = 0; ui < fieldDescriptor.m_usFieldCount; ui++)
//		{
//			if (fieldDescriptor.m_pFieldInfo[ui].m_eKType == eKeyType)
//			{
//				uiBindCount++;
//			}		
//		}
//
//		if (!uiBindCount)
//		{
//			return NULL;
//		}
//	}
//
//	MYSQL_BIND* bind = new MYSQL_BIND[uiBindCount + reserveSize];
//
//	BindRecord(bind, record, eKeyType, uiBindCount + reserveSize);
//
//	if (puiCreatedSize)
//	{
//		*puiCreatedSize = uiBindCount + reserveSize;
//	}
//
//	return bind;
//}
//
//template<typename T>
//void CMySqlTable<T>::BindField( MYSQL_BIND& bind, const T& record, const STFieldInfo& field )
//{
//	bind.buffer = (char*)(&record) + field.m_nOffset;
//	bind.buffer_length = (unsigned long)field.m_nSize;
//	bind.is_null = 0;
//
//	switch (field.m_eVType)
//	{
//	case IOD_FIELD_TYPE_BOOL:
//		{
//			bind.buffer_type = MYSQL_TYPE_BIT;
//		}
//		break;
//	case IOD_FIELD_TYPE_UINT1:
//		{
//			bind.buffer_type = MYSQL_TYPE_TINY;
//		}
//		break;
//	case IOD_FIELD_TYPE_UINT2:
//	case IOD_FIELD_TYPE_INT2:
//		{
//			bind.buffer_type = MYSQL_TYPE_SHORT;
//		}
//		break;
//	case IOD_FIELD_TYPE_UINT4:
//	case IOD_FIELD_TYPE_INT4:
//		{
//			bind.buffer_type = MYSQL_TYPE_LONG;
//		}
//		break;
//	case IOD_FIELD_TYPE_REAL4:
//		{
//			bind.buffer_type = MYSQL_TYPE_FLOAT;
//		}
//		break;
//	case IOD_FIELD_TYPE_REAL8:
//		{
//			bind.buffer_type = MYSQL_TYPE_DOUBLE;
//		}
//		break;
//	case IOD_FIELD_TYPE_STRING:
//		{
//			bind.buffer_type = MYSQL_TYPE_STRING;
//			bind.length = (unsigned long*)((char*)bind.buffer + bind.buffer_length);
//		}
//		break;
//	case IOD_FIELD_TYPE_TIME:
//		{
//			bind.buffer_type = MYSQL_TYPE_TIME;
//		}
//		break;
//	case IOD_FIELD_TYPE_BLOB:
//		{
//			bind.buffer_type = MYSQL_TYPE_BLOB;
//		}
//		break;
//	default:
//		break;
//	}
//
//	return;
//}
//
//template<typename T>
//const char* CMySqlTable<T>::PrepareStmts()
//{
//	PrepareInsert();
//
//	PrepareQuery(IOD_FIELD_KEY_UNIQUE_0);
//	PrepareQuery(IOD_FIELD_KEY_UNIQUE_1);
//	PrepareQuery(IOD_FIELD_KEY_UNIQUE_2);
//
//	PrepareFilter(IOD_FIELD_KEY_FILTER_0);
//	PrepareFilter(IOD_FIELD_KEY_FILTER_1);
//	PrepareFilter(IOD_FIELD_KEY_FILTER_2);
//
//	PrepareUpdate(IOD_FIELD_KEY_UNIQUE_0);
//	PrepareUpdate(IOD_FIELD_KEY_UNIQUE_1);
//	PrepareUpdate(IOD_FIELD_KEY_UNIQUE_2);
//
//	PrepareDelete(IOD_FIELD_KEY_UNIQUE_0);
//	PrepareDelete(IOD_FIELD_KEY_UNIQUE_1);
//	PrepareDelete(IOD_FIELD_KEY_UNIQUE_2);
//	PrepareDelete(IOD_FIELD_KEY_FILTER_0);
//	PrepareDelete(IOD_FIELD_KEY_FILTER_1);
//	PrepareDelete(IOD_FIELD_KEY_FILTER_2);
//
//	return NULL;
//}
//
//template<typename T>
//const char* CMySqlTable<T>::CloseStmts()
//{
//	CLOSE_STMT(m_stmtInsert);
//
//	CLOSE_STMT(m_stmtQuery0);
//	CLOSE_STMT(m_stmtQuery1);
//	CLOSE_STMT(m_stmtQuery2);
//
//	CLOSE_STMT(m_stmtUpdate0);
//	CLOSE_STMT(m_stmtUpdate1);
//	CLOSE_STMT(m_stmtUpdate2);
//
//	CLOSE_STMT(m_stmtFilter0);
//	CLOSE_STMT(m_stmtFilter1);
//	CLOSE_STMT(m_stmtFilter2);
//
//	CLOSE_STMT(m_stmtDelete0);
//	CLOSE_STMT(m_stmtDelete1);
//	CLOSE_STMT(m_stmtDelete2);
//	CLOSE_STMT(m_stmtMultiDelete0);
//	CLOSE_STMT(m_stmtMultiDelete1);
//	CLOSE_STMT(m_stmtMultiDelete2);
//
//	return NULL;
//}
//
//template<typename T>
//bool CMySqlTable<T>::PrepareUpdate( EIODFieldKey eKeyType )
//{
//	if ((eKeyType == IOD_FIELD_KEY_UNIQUE_0 && m_stmtUpdate0)
//		|| (eKeyType == IOD_FIELD_KEY_UNIQUE_1 && m_stmtUpdate1)
//		|| (eKeyType == IOD_FIELD_KEY_UNIQUE_2 && m_stmtUpdate2))
//	{
//		return true;
//	}
//
//	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
//	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();
//
//	char szSetValue[SQL_STMT_LENGTH] = {0};
//	char szWhere[SQL_STMT_LENGTH] = {0};
//	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
//	{
//		if (!szSetValue[0])
//		{
//			sprintf_s(szSetValue, SQL_STMT_LENGTH, "set %s=? ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//		}
//		else
//		{
//			sprintf_s(szSetValue + strlen(szSetValue), SQL_STMT_LENGTH - strlen(szSetValue), ", %s=? ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//		}
//
//		if (fieldDescriptor.m_pFieldInfo[idx].m_eKType == eKeyType)
//		{
//			if (!szWhere[0])
//			{
//				sprintf_s(szWhere, SQL_STMT_LENGTH, "where %s=? ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);				
//			}
//			else
//			{
//				sprintf_s(szWhere + strlen(szWhere), SQL_STMT_LENGTH - strlen(szWhere), "and %s=? ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//			}
//		}
//	}
//
//	if (!szWhere[0])
//	{
//		return false;
//	}
//
//	char szQuery[SQL_STMT_LENGTH];
//	sprintf_s(szQuery, SQL_STMT_LENGTH, "update %s %s %s", fieldDescriptor.m_pszTableName, szSetValue, szWhere);
//
//	switch (eKeyType)
//	{
//	case IOD_FIELD_KEY_UNIQUE_0:
//		m_stmtUpdate0 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtUpdate0 != NULL;
//	case IOD_FIELD_KEY_UNIQUE_1:
//		m_stmtUpdate1 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtUpdate1 != NULL;
//	case IOD_FIELD_KEY_UNIQUE_2:
//		m_stmtUpdate2 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtUpdate2 != NULL;
//	default:
//		break;
//	}
//
//	return false;
//}
//
//template<typename T>
//bool CMySqlTable<T>::PrepareFilter( EIODFieldKey eKeyType )
//{
//	if ((eKeyType == IOD_FIELD_KEY_FILTER_0 && m_stmtFilter0)
//		|| (eKeyType == IOD_FIELD_KEY_FILTER_1 && m_stmtFilter1)
//		|| (eKeyType == IOD_FIELD_KEY_FILTER_2 && m_stmtFilter2))
//	{
//		return true;
//	}
//
//	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
//	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();
//
//	char szSelect[SQL_STMT_LENGTH] = {0};
//	char szWhere[SQL_STMT_LENGTH] = {0};
//	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
//	{
//		if (!szSelect[0])
//		{
//			sprintf_s(szSelect, SQL_STMT_LENGTH, "select %s ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//		}
//		else
//		{
//			sprintf_s(szSelect + strlen(szSelect), SQL_STMT_LENGTH - strlen(szSelect), ", %s ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//		}
//
//		if (fieldDescriptor.m_pFieldInfo[idx].m_eKType == eKeyType)
//		{
//			if (!szWhere[0])
//			{
//				sprintf_s(szWhere, SQL_STMT_LENGTH, "where %s=? ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);				
//			}
//			else
//			{
//				sprintf_s(szWhere + strlen(szWhere), SQL_STMT_LENGTH - strlen(szWhere), "and %s=? ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//			}
//		}
//	}
//
//	if (!szWhere[0])
//	{
//		return false;
//	}
//
//	char szQuery[SQL_STMT_LENGTH];
//	sprintf_s(szQuery, SQL_STMT_LENGTH, "%s from %s %s limit ?,?", szSelect, fieldDescriptor.m_pszTableName, szWhere);
//
//	switch (eKeyType)
//	{
//	case IOD_FIELD_KEY_FILTER_0:
//		m_stmtFilter0 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtQuery0 != NULL;
//	case IOD_FIELD_KEY_FILTER_1:
//		m_stmtFilter1 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtQuery1 != NULL;
//	case IOD_FIELD_KEY_FILTER_2:
//		m_stmtFilter2 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtQuery2 != NULL;
//	default:
//		break;
//	}
//
//	return false;
//}
//
//template<typename T>
//bool CMySqlTable<T>::PrepareInsert()
//{
//	if (m_stmtInsert)
//	{
//		return true;
//	}
//
//	char szQuery[SQL_STMT_LENGTH];
//	
//	//insert into TableName(field0, field1, ...) value(?, ?, ...);
//	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();
//	sprintf_s(szQuery, SQL_STMT_LENGTH, "insert into %s (", fieldDescriptor.m_pszTableName);
//	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
//	{
//		strcat_s(szQuery, SQL_STMT_LENGTH, fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//		if (idx != fieldDescriptor.m_usFieldCount - 1)
//		{
//			strcat_s(szQuery, SQL_STMT_LENGTH, ",");
//		}
//	}
//
//	strcat_s(szQuery, SQL_STMT_LENGTH, ") values(");
//
//	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
//	{
//		strcat_s(szQuery, SQL_STMT_LENGTH, "?");
//		if (idx != fieldDescriptor.m_usFieldCount - 1)
//		{
//			strcat_s(szQuery, SQL_STMT_LENGTH, ",");
//		}
//	}
//	strcat_s(szQuery, SQL_STMT_LENGTH, ")");
//	
//	m_stmtInsert = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//
//	return m_stmtInsert != NULL;
//}
//
//template<typename T>
//bool CMySqlTable<T>::PrepareQuery( EIODFieldKey eKeyType )
//{
//	if ((eKeyType == IOD_FIELD_KEY_UNIQUE_0 && m_stmtQuery0)
//		|| (eKeyType == IOD_FIELD_KEY_UNIQUE_1 && m_stmtQuery1)
//		|| (eKeyType == IOD_FIELD_KEY_UNIQUE_2 && m_stmtQuery2))
//	{
//		return true;
//	}
//
//
//	//select field0, field1,... from tableName where fieldkey0 = val0 and fieldkey1 = val1 and ...
//	const STFieldDescriptor& fieldDescriptor = T::GetFieldDescriptor();
//
//	char szSelect[SQL_STMT_LENGTH] = {0};
//	char szWhere[SQL_STMT_LENGTH] = {0};
//	for (unsigned short idx = 0; idx < fieldDescriptor.m_usFieldCount; idx++)
//	{
//		if (!szSelect[0])
//		{
//			sprintf_s(szSelect, SQL_STMT_LENGTH, "select %s ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//		}
//		else
//		{
//			sprintf_s(szSelect + strlen(szSelect), SQL_STMT_LENGTH - strlen(szSelect), ", %s ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//		}
//
//		if (fieldDescriptor.m_pFieldInfo[idx].m_eKType == eKeyType)
//		{
//			if (!szWhere[0])
//			{
//				sprintf_s(szWhere, SQL_STMT_LENGTH, "where %s=? ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);				
//			}
//			else
//			{
//				sprintf_s(szWhere + strlen(szWhere), SQL_STMT_LENGTH - strlen(szWhere), "and %s=? ", fieldDescriptor.m_pFieldInfo[idx].m_pszFieldName);
//			}
//		}
//	}
//
//	if (!szWhere[0])
//	{
//		return false;
//	}
//
//	char szQuery[SQL_STMT_LENGTH];
//	sprintf_s(szQuery, SQL_STMT_LENGTH, "%s from %s %s", szSelect, fieldDescriptor.m_pszTableName, szWhere);
//
//	switch (eKeyType)
//	{
//	case IOD_FIELD_KEY_UNIQUE_0:
//		m_stmtQuery0 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtQuery0 != NULL;
//	case IOD_FIELD_KEY_UNIQUE_1:
//		m_stmtQuery1 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtQuery1 != NULL;
//	case IOD_FIELD_KEY_UNIQUE_2:
//		m_stmtQuery2 = CMySqlDB::GetInstance().PrepareStmt(szQuery);
//		return m_stmtQuery2 != NULL;
//	default:
//		break;
//	}
//
//	return false;
//}
//
//template<typename T>
//const char* CMySqlTable<T>::InsertRecord(const T& record)
//{
//	if (!m_stmtInsert)
//	{
//		return "statement not prepared, call T::PrepareTable() first or invalid key type!\n";
//	}
//
//	if (!CMySqlDB::GetInstance().LockConn(m_stmtInsert->mysql))
//	{
//		return "wait connection time out";
//	}
//
//	MYSQL_BIND* bind = CreateBind(record);
//
//	/* Bind the buffers */
//	if (mysql_stmt_bind_param(m_stmtInsert, bind))
//	{
//		SAFE_QUIT_QUERY(m_stmtInsert, bind, mysql_stmt_error(m_stmtInsert));
//	}
//
//	if (mysql_stmt_execute(m_stmtInsert))
//	{
//		SAFE_QUIT_QUERY(m_stmtInsert, bind, mysql_stmt_error(m_stmtInsert));
//	}
//
//	SAFE_QUIT_QUERY(m_stmtInsert, bind, NULL);
//}
//
//template<typename T>
//const char* CMySqlTable<T>::QueryRecord(T& record, EIODFieldKey eKeyType)
//{
//	MYSQL_STMT* stmt = NULL;
//	switch (eKeyType)
//	{
//	case IOD_FIELD_KEY_UNIQUE_0:
//		stmt = m_stmtQuery0;
//		break;
//	case IOD_FIELD_KEY_UNIQUE_1:
//		stmt = m_stmtQuery1;
//		break;
//	case IOD_FIELD_KEY_UNIQUE_2:
//		stmt = m_stmtQuery2;
//		break;
//	default:
//		break;
//	}
//
//	if (!stmt)
//	{
//		return "statement not prepared, call T::PrepareTable() first or invalid key type!\n";
//	}
//
//	if (!CMySqlDB::GetInstance().LockConn(stmt->mysql))
//	{
//		return "wait connection time out";
//	}
//
//	MYSQL_BIND* bind = CreateBind(record, eKeyType);
//
//	/* Bind the buffers */
//	if (mysql_stmt_bind_param(stmt, bind))
//	{
//		SAFE_QUIT_QUERY(stmt, bind, mysql_stmt_error(stmt));
//	}
//
//	if (mysql_stmt_execute(stmt))
//	{
//		SAFE_QUIT_QUERY(stmt, bind, mysql_stmt_error(stmt));
//	}
//
//	delete[] bind;
//
//	//--------------------------------------------------------------------------------------------------------------------------------
//	
//	MYSQL_BIND* resultBind = CreateBind(record);
//
//	if (mysql_stmt_bind_result(stmt, resultBind))
//	{
//		SAFE_QUIT_QUERY(stmt, resultBind, mysql_stmt_error(stmt));
//	}
//
//	if (mysql_stmt_store_result(stmt))
//	{
//		SAFE_QUIT_QUERY(stmt, resultBind, mysql_stmt_error(stmt));
//	}
//
//	unsigned long uiResultCount = 0;
//	while (!mysql_stmt_fetch(stmt))
//	{
//		uiResultCount++;
//	}
//	
//	if (uiResultCount != 1)
//	{
//		SAFE_QUIT_QUERY(stmt, resultBind, "query result count is not 1\n");
//	}
//
//	mysql_stmt_free_result(stmt);
//
//	SAFE_QUIT_QUERY(stmt, resultBind, NULL);
//}
//
//template<typename T>
//const char* CMySqlTable<T>::UpdateRecord(const T& record, EIODFieldKey eKeyType, my_ulonglong& affectedRows)
//{
//	MYSQL_STMT* stmt = NULL;
//	switch (eKeyType)
//	{
//	case IOD_FIELD_KEY_UNIQUE_0:
//		stmt = m_stmtUpdate0;
//		break;
//	case IOD_FIELD_KEY_UNIQUE_1:
//		stmt = m_stmtUpdate1;
//		break;
//	case IOD_FIELD_KEY_UNIQUE_2:
//		stmt = m_stmtUpdate2;
//		break;
//	default:
//		break;
//	}
//
//	if (!stmt)
//	{
//		return "statement not prepared, call T::PrepareTable() first or invalid key type!\n";
//	}
//
//	if (!CMySqlDB::GetInstance().LockConn(stmt->mysql))
//	{
//		return "wait connection time out";
//	}
//
//	MYSQL_BIND* bind = CreateUpdateBind(record, eKeyType);
//
//	/* Bind the buffers */
//	if (mysql_stmt_bind_param(stmt, bind))
//	{
//		SAFE_QUIT_QUERY(stmt, bind, mysql_stmt_error(stmt));
//	}
//
//	if (mysql_stmt_execute(stmt))
//	{
//		SAFE_QUIT_QUERY(stmt, bind, mysql_stmt_error(stmt));
//	}
//
//	affectedRows = mysql_stmt_affected_rows(stmt);
//
//	SAFE_QUIT_QUERY(stmt, bind, NULL);
//}
//
//template<typename T>
//const char* CMySqlTable<T>::FilterRecord(T* resultRecords, unsigned long& ulResultCount, const unsigned long ulResultMaxSize,
//		const T& queryRecord, EIODFieldKey eKeyType, const unsigned long ulStart)
//{
//	MYSQL_STMT* stmt = NULL;
//	switch (eKeyType)
//	{
//	case IOD_FIELD_KEY_FILTER_0:
//		stmt = m_stmtFilter0;
//		break;
//	case IOD_FIELD_KEY_FILTER_1:
//		stmt = m_stmtFilter1;
//		break;
//	case IOD_FIELD_KEY_FILTER_2:
//		stmt = m_stmtFilter2;
//		break;
//	default:
//		break;
//	}
//
//	if (!stmt)
//	{
//		return "filter record failed, statement not prepared, call T::PrepareTable() first or invalid key type!\n";
//	}
//
//	if (!CMySqlDB::GetInstance().LockConn(stmt->mysql))
//	{
//		return "wait connection time out";
//	}
//
//	unsigned int uiCreateSize = 0;
//	MYSQL_BIND* bind = CreateBind(queryRecord, eKeyType, 2, &uiCreateSize);
//
//	if (!bind)
//	{
//		SAFE_QUIT_QUERY(stmt, bind, "filter record failed, create bind return null\n");
//	}
//
//	bind[uiCreateSize - 2].buffer = (char*)&ulStart;
//	bind[uiCreateSize - 2].buffer_length = sizeof(ulStart);
//	bind[uiCreateSize - 2].is_null = 0;
//	bind[uiCreateSize - 2].buffer_type = MYSQL_TYPE_LONG;
//
//	bind[uiCreateSize - 1].buffer = (char*)&ulResultMaxSize;
//	bind[uiCreateSize - 1].buffer_length = sizeof(ulResultMaxSize);
//	bind[uiCreateSize - 1].is_null = 0;
//	bind[uiCreateSize - 1].buffer_type = MYSQL_TYPE_LONG;
//
//	/* Bind the buffers */
//	if (mysql_stmt_bind_param(stmt, bind))
//	{
//		SAFE_QUIT_QUERY(stmt, bind, mysql_stmt_error(stmt));
//	}
//
//	if (mysql_stmt_execute(stmt))
//	{
//		SAFE_QUIT_QUERY(stmt, bind, mysql_stmt_error(stmt));
//	}
//
//	delete[] bind;
//
//	//--------------------------------------------------------------------------------------------------------------------------------
//	T tempRecord;
//	MYSQL_BIND* resultBind = CreateBind(tempRecord);
//
//	if (mysql_stmt_bind_result(stmt, resultBind))
//	{
//		SAFE_QUIT_QUERY(stmt, resultBind, mysql_stmt_error(stmt));
//	}
//
//	if (mysql_stmt_store_result(stmt))
//	{
//		SAFE_QUIT_QUERY(stmt, resultBind, mysql_stmt_error(stmt));
//	}
//
//	ulResultCount = 0;
//	while (!mysql_stmt_fetch(stmt))
//	{
//		memcpy(&resultRecords[ulResultCount], &tempRecord, sizeof(T));
//
//		ulResultCount++;
//
//		if (ulResultCount == ulResultMaxSize)
//		{
//			SAFE_QUIT_QUERY(stmt, resultBind, NULL);
//		}
//	}
//
//	mysql_stmt_free_result(stmt);
//
//	SAFE_QUIT_QUERY(stmt, resultBind, NULL);
//}

#endif
