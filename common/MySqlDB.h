//#pragma once
#ifndef _MYSQLDB_H_
#define _MYSQLDB_H_

#include "MySqlField.h"

//#define MAX_WAIT_CONN_TIME 1000000

//const int MAX_LOCK_TIME =  30 * CLOCKS_PER_SEC;		//һ�������������30����

//#ifdef min
//#undef min
//#endif
//
//#ifdef max
//#undef max
//#endif

#ifdef WIN32
int vsscanf(
			const char  *buffer,
			const char  *format,
			va_list     argPtr
			);
#endif

namespace IODDB
{
	extern MYSQL* common_mysql_connection;

	bool InitCommonMysqlConnection(const char* address, unsigned short port, const char* user, const char* pass, const char* dbname);

	//����ֵд��szRet�ַ������ö��Ÿ���
	const char* FreeQuery(MYSQL* pConn, const char* pszSql, char* szRet = NULL);

	//����sscanf��ȡ������õ��ַ���
	const char* FreeQuery(MYSQL* pConn, const char* pszSql, const char* pszRetValueFormat, ...);

	//���ص�һ���ṹ�壨���飩�У���Ҫͨ��__out_field����ָ���������Ӧ���ֶ�
	//__out_field(fieldName, className, memberName, fieldValueType)
	template<typename returnType>
	const char* FreeQuery(MYSQL* pConn, const char* pszSql, returnType* pRecords, unsigned long* pulResultCount, unsigned long ulResultMaxCount, 
		const STOutFieldInfo* pOutField, unsigned int outputFieldCount);

	const char* GetValueFromSzFieldIntoRecord( void* pRecord, const STOutFieldInfo& field, const char* szValue, unsigned long ulLength );

	//���Դ���
	void TestFreeQuery(MYSQL* pConn);

	struct STAutoTiming {
		STAutoTiming(const char, int){}
	};
	////�Զ���ʱ��΢�뾫�ȣ�
	//struct STAutoTiming 
	//{
	//	STAutoTiming(const char* pszName, iod_time_t_64 timeoutTime = 20000) : m_pszName(pszName), m_nTimeout(timeoutTime) 
	//	{
	//		m_nTiming = Utility::GetUTickCount();
	//	}

	//	~STAutoTiming()
	//	{
	//		iod_time_t_64 n = Utility::GetUTickCount() - m_nTiming;
	//		if (n > m_nTimeout)
	//		{
	//			if (strlen(m_pszName) > 500)
	//			{
	//				char szBuff[128] = {0};
	//				memcpy(szBuff, m_pszName, sizeof(szBuff) - 1);
	//				if (n > QUERY_OVER_TIME_2)
	//				{
	//					IOD_SRV_CRIT("statement: %s ... (total length %d); process time %d us", szBuff, strlen(m_pszName) , n);
	//				}
	//				else if (n > 30000)
	//				{
	//					IOD_SRV_SYS_INFO("statement: %s ... (total length %d); process time %d us", szBuff, strlen(m_pszName) , n);
	//				}
	//				else
	//				{
	//					IOD_SRV_INFO("statement: %s ... (total length %d); process time %d us", szBuff, strlen(m_pszName) , n);
	//				}
	//			}
	//			else
	//			{
	//				if (n > QUERY_OVER_TIME_2)
	//				{
	//					IOD_SRV_CRIT("statement: %s; process time %d us", m_pszName, n);
	//				}
	//				else if (n > 30000)
	//				{
	//					IOD_SRV_SYS_INFO("statement: %s; process time %d us", m_pszName, n);
	//				}
	//				else
	//				{
	//					IOD_SRV_INFO("statement: %s; process time %d us", m_pszName, n);
	//				}
	//			}				
	//		}
	//		IOD::on_query_return_statistics((unsigned int)n);
	//	}
	//	iod_time_t_64 m_nTiming;
	//	iod_time_t_64 m_nTimeout;
	//	const char* m_pszName;
	//};
}

template<typename returnType>
const char* IODDB::FreeQuery( MYSQL* pConn, const char* pszSql, returnType* pRecords, unsigned long* pulResultCount, unsigned long ulResultMaxCount, const STOutFieldInfo* pOutField, unsigned int outputFieldCount)
{
	{
		//IODDB::STAutoTiming stAutoTiming(pszSql, 1);
		if (int iError = mysql_real_query(pConn, pszSql, (unsigned long)strlen(pszSql)))
		{
			IOD_SRV_ERROR("query error code %d", iError);
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
				if (const char* pszResult = GetValueFromSzFieldIntoRecord(pRecords + ulIdx, fieldInfo[ui], row[ui], lengths[ui]))
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


//
////���ӳ�
//class CMySqlDB
//{
//public:
//	static CMySqlDB& GetInstance()
//	{
//		static CMySqlDB db;
//		return db;
//	}
//
//	bool Connect(const char* pszServerAddr, const char* pszUser, const char* pszPassword, const char* pszDBName, unsigned short usConnCount = 0);
//	void Disconnect();
//	bool IsConnected();
//
//	//---------------------------------------------------------------------------------------------
//	//����Ϊ���̺߳���
//	int GetAndLockConn(MYSQL** ppConn, int maxTryTimes = 3000);
//
//	inline void UnlockConn(int idx)
//	{
//#ifdef MULTI_THREAD
//		WAIT_MUTEX(m_hPoolMutex, INFINITE);
//		SetUnLockIdx(idx);
//		RELEASE_MUTEX(m_hPoolMutex);
//#endif
//	}
//
//	const char* Real_Query(const char* pszSql, size_t sLength, MYSQL_RES** pRes);
//	//---------------------------------------------------------------------------------------------
//
//	inline char* GetStmtBuffer(int idx) {	m_szStmtBuffer[idx][0] = 0; return m_szStmtBuffer[idx];	}
//	inline char* GetValueBuffer(int idx) {	m_szValueBuffer[idx][0] = 0; return m_szValueBuffer[idx];	}
//	inline char* GetCommonBuffer(int idx) {	m_szCommonBuffer[idx][0] = 0; return m_szCommonBuffer[idx];	}
//	inline char* GetCommonBuffer1(int idx) {	m_szCommonBuffer1[idx][0] = 0; return m_szCommonBuffer1[idx];	}
//	inline MYSQL* GetConnByIdx(int idx)	{ return m_ConnPool[idx]; }
//
//private:
//	CMySqlDB(void);
//	~CMySqlDB(void);
//
//	MYSQL* m_ConnPool[MAX_SQL_CONN_COUNT];
//	bool  m_bLocked[MAX_SQL_CONN_COUNT];
//	clock_t m_LockTime[MAX_SQL_CONN_COUNT];
//
//	char m_szStmtBuffer[MAX_SQL_CONN_COUNT][SQL_STMT_LENGTH];
//	char m_szValueBuffer[MAX_SQL_CONN_COUNT][SQL_VALUE_LENGTH];
//	char m_szCommonBuffer[MAX_SQL_CONN_COUNT][SQL_STMT_LENGTH];
//	char m_szCommonBuffer1[MAX_SQL_CONN_COUNT][SQL_STMT_LENGTH];
//
//	inline void SetLockIdx(int idx)
//	{
//		m_bLocked[idx] = true;
//		m_LockTime[idx] = clock();
//		m_uiLastConnIndex = idx;
//	}
//	inline void SetUnLockIdx(int idx)
//	{
//		m_bLocked[idx] = false;
//		m_LockTime[idx] = 0;
//	}
//
//	unsigned short m_usConnCount;
//
//	unsigned int m_uiLastConnIndex;
//
//#ifdef MULTI_THREAD
//
//#ifdef WINDOWS
//	HANDLE m_hPoolMutex;
//#else
//	pthread_mutex_t* m_hPoolMutex;
//#endif
//
//#endif
//};

#endif
