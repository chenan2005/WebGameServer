#include "IODMyDb.h"

using namespace IODMyDb;

MYSQL* IODMyDb::common_mysql_connection = NULL;

bool IODMyDb::initCommonConnection(const char* address, unsigned short port, const char* user, const char* pass, const char* dbname)
{
	if (IODMyDb::common_mysql_connection != 0)
		return false;

	mysql_library_init(0, NULL, NULL);

	bool enable_auto_reconnect = true;
	unsigned int timeout_seconds = 3600 * 24 * 30;	//连接超时时间设为1个月
	const char* charactset = "utf8";
	common_mysql_connection = mysql_init(NULL);

	mysql_options(common_mysql_connection, MYSQL_SET_CHARSET_NAME, charactset);
	mysql_options(common_mysql_connection, MYSQL_OPT_RECONNECT, &enable_auto_reconnect);
	mysql_options(common_mysql_connection, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_seconds);

	if (!mysql_real_connect(common_mysql_connection, address, user, pass, dbname, port, 0, CLIENT_MULTI_STATEMENTS))
	{
		//TRACE("%s", mysql_error(common_mysql_connection));
		return false;
	}

	//5.1.6版本之前 MYSQL_OPT_RECONNECT 在 mysql_real_connect之后需要重新设置
	mysql_options(common_mysql_connection, MYSQL_OPT_RECONNECT, &enable_auto_reconnect);

	//IOD_SRV_SYS_INFO("common mysql connection set to %s@%s:%d", user, address, (int)port);

	return true;
}

const char* IODMyDb::getValueFromSzIntoField( void* pRecord, const STOutFieldInfo& field, const char* szValue, unsigned long ulLength )
{
	switch (field.m_eVType)
	{
	case IOD_FIELD_TYPE_BOOL:
		{
			//sscanf_s(szValue, "%s", (bool*)((char*)(&record) + field.m_nOffset));	
			if (szValue[0] == '0')
			{
				*(bool*)((char*)(pRecord) + field.m_nOffset) = false;
			}
			else
			{
				*(bool*)((char*)(pRecord) + field.m_nOffset) = true;
			}
		}
		break;
	case IOD_FIELD_TYPE_UINT1:
		{
			//sscanf_s(szValue, "%d", (uint8*)((char*)(&record) + field.m_nOffset));
			*(uint8*)((char*)(pRecord) + field.m_nOffset) = (uint8)strtoul(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_UINT2:
		{
			//sscanf_s(szValue, "%h", (uint16*)((char*)(&record) + field.m_nOffset));
			*(uint16*)((char*)(pRecord) + field.m_nOffset) = (uint16)strtoul(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_UINT4:
		{
			//sscanf_s(szValue, "%d", (uint32*)((char*)(&record) + field.m_nOffset));
			*(uint32*)((char*)(pRecord) + field.m_nOffset) = (uint32)strtoul(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_UINT8:
		{
			//sscanf_s(szValue, "%L", (uint64*)((char*)(&record) + field.m_nOffset));
			*(uint64*)((char*)(pRecord) + field.m_nOffset) = (uint64)strtoull(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_INT1:
		{
			//sscanf_s(szValue, "%d", (int8*)((char*)(&record) + field.m_nOffset));
			*(int8*)((char*)(pRecord) + field.m_nOffset) = (int8)strtol(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_INT2:
		{
			//sscanf_s(szValue, "%d", (int16*)((char*)(&record) + field.m_nOffset));
			*(int16*)((char*)(pRecord) + field.m_nOffset) = (int16)strtol(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_INT4:
		{
			//sscanf_s(szValue, "%d", (int32*)((char*)(&record) + field.m_nOffset));
			*(int32*)((char*)(pRecord) + field.m_nOffset) = (int32)strtol(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_INT8:
		{
			//sscanf_s(szValue, "%d", (int64*)((char*)(&record) + field.m_nOffset));
			*(int64*)((char*)(pRecord) + field.m_nOffset) = (int64)strtoll(szValue, NULL, 10);
		}
		break;
	case IOD_FIELD_TYPE_REAL4:
		{
			//sscanf_s(szValue, "%f", (float*)((char*)(&record) + field.m_nOffset));
			*(float*)((char*)(pRecord) + field.m_nOffset) = (float)strtod(szValue, NULL);
		}
		break;
	case IOD_FIELD_TYPE_REAL8:
		{
			//sscanf_s(szValue, "%f", (double*)((char*)(&record) + field.m_nOffset));
			*(double*)((char*)(pRecord) + field.m_nOffset) = (double)strtod(szValue, NULL);
		}
		break;
	case IOD_FIELD_TYPE_STRING:
		{	
			if (ulLength > field.m_nSize)
			{
				printf("%s\n", field.m_pszFieldName);
				return "mysql error: field value length overflow!\n";
			}
			memcpy((char*)(pRecord) + field.m_nOffset, szValue, ulLength);
			((char*)(pRecord) + field.m_nOffset)[ulLength] = 0;
		}
		break;
	case IOD_FIELD_TYPE_BLOB:
		{
			if (ulLength > field.m_nSize)
			{
				printf("%s\n", field.m_pszFieldName);
				return "mysql error: field value length overflow!\n";
			}			
			memcpy((char*)(pRecord) + field.m_nOffset, szValue, ulLength);
			((char*)(pRecord) + field.m_nOffset)[ulLength] = 0;

			//紧跟的下一个字段是blob长度
			*(uint16*)((char*)(pRecord) + field.m_nOffset + field.m_iSizeMemberOffset) = (uint16)ulLength;
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
				*(time_t*)((char*)(pRecord) + field.m_nOffset) = 0;
			}
			else
			{
				tm tm1 = {0};
				strptime(szValue, "%Y-%m-%d %H:%M:%S", &tm1);
				if (tm1.tm_year < 0)
				{
					*(time_t*)((char*)(pRecord) + field.m_nOffset) = 0;
				}
				else
				{
					*(time_t*)((char*)(pRecord) + field.m_nOffset) = IODUtility::mktimeDaylyTimeFlag(&tm1);
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
			memcpy((char*)(pRecord) + field.m_nOffset, szValue, ulLength);
		}
		break;
	}

	return NULL;
}
//
//CMySqlDB::CMySqlDB(void) : m_usConnCount(MAX_SQL_CONN_COUNT)
//{
//	memset(m_ConnPool, 0 ,sizeof(m_ConnPool));
//	memset(m_bLocked, 0 ,sizeof(m_bLocked));
//	memset(m_LockTime, 0, sizeof(m_LockTime));
//
//#ifdef MULTI_THREAD
//
////创建多线程互斥锁
//#ifdef WINDOWS
//	m_hPoolMutex = CreateMutex(NULL, NULL, NULL);  
//#else
//	m_hPoolMutex = new pthread_mutex_t;
//	pthread_mutex_init(m_hPoolMutex, NULL);
//#endif
//
//#endif
//}
//
//CMySqlDB::~CMySqlDB(void)
//{
//	Disconnect();
//
//#ifdef MULTI_THREAD
//
//#ifdef WINDOWS
//#else
//	delete m_hPoolMutex;
//#endif
//
//#endif
//}
//
//bool CMySqlDB::Connect( const char* pszServerAddr, const char* pszUser, const char* pszPassword, const char* pszDBName, unsigned short usConnCount )
//{
//	if (mysql_library_init(0, NULL, NULL))
//	{
//		return false;
//	}
//	
//	if (usConnCount == 0 || usConnCount > MAX_SQL_CONN_COUNT)
//	{
//		m_usConnCount = MAX_SQL_CONN_COUNT;
//	}
//	else
//	{
//		m_usConnCount = usConnCount;
//	}
//
//	bool bAutoReconnect = true;
//	unsigned int uiTimeoutSeconds = 3600 * 24 * 30;	//连接超时时间设为1个月
//	const char* pcsCharacterSetName = "gbk";	 
//	for (unsigned short us = 0; us < m_usConnCount; us++)
//	{
//		m_ConnPool[us] = mysql_init(NULL);
//		mysql_options(m_ConnPool[us], MYSQL_SET_CHARSET_NAME, pcsCharacterSetName);
//		mysql_options(m_ConnPool[us], MYSQL_OPT_RECONNECT, &bAutoReconnect);
//		mysql_options(m_ConnPool[us], MYSQL_OPT_CONNECT_TIMEOUT, &uiTimeoutSeconds);
//		m_ConnPool[us] = mysql_real_connect(m_ConnPool[us], pszServerAddr, pszUser, pszPassword, pszDBName, 0, 0, 0);
//		if (!m_ConnPool[us])
//		{
//			return false;
//		}
//
//		//5.1.6版本之前 MYSQL_OPT_RECONNECT 在 mysql_real_connect之后需要重新设置
//		mysql_options(m_ConnPool[us], MYSQL_OPT_RECONNECT, &bAutoReconnect);
//	}
//
//	return true;
//}
//
//void CMySqlDB::Disconnect()
//{
//	if (IsConnected())
//	{
//		for (unsigned int ui = 0; ui < m_usConnCount; ui++)
//		{
//			mysql_close(m_ConnPool[ui]);
//			m_ConnPool[ui] = 0;
//		}
//
//		mysql_library_end();
//	}
//}
//
//bool CMySqlDB::IsConnected()
//{
//	return (m_ConnPool[0] && !mysql_ping(m_ConnPool[0]));
//}
//
//const char* CMySqlDB::Real_Query(const char* pszSql, size_t sLength, MYSQL_RES** pRes)
//{
//	MYSQL* pConn;
//	int idx;
//	if ((idx = GetAndLockConn(&pConn)) < 0 || !pConn)
//	{
//		return "connection get failed";
//	}
//	
//
//	if (mysql_real_query(pConn, pszSql, (unsigned long)sLength))
//	{
//		UnlockConn(idx);
//		return mysql_error(pConn);
//	}
//	
//	*pRes = mysql_store_result(pConn);
//
//	UnlockConn(idx);
//	return NULL;
//}
//
////const char*  CMySqlDB::BeginQuery(const char* pszQuery)
////{
////	if (!m_pConn || m_pRes)
////	{
////		return false;
////	}
////
////	mysql_query(m_pConn, pszQuery);
////
////	m_pRes = mysql_store_result(m_pConn);
////
////	return mysql_error(m_pConn);
////}
////
////const char*  CMySqlDB::BeginRealQuery(const char* pszQuery, size_t uiQueryLength)
////{
////	if (!m_pConn || m_pRes)
////	{
////		return false;
////	}
////
////	mysql_real_query(m_pConn, pszQuery, (unsigned long)uiQueryLength);
////
////	m_pRes = mysql_store_result(m_pConn);
////
////	return mysql_error(m_pConn);
////}
////
////void CMySqlDB::EndQuery()
////{
////	mysql_free_result(m_pRes);
////	m_pRes = NULL;
////}
////
////int CMySqlDB::GetResCount()
////{
////	if (!m_pRes)
////	{
////		return -1;
////	}
////
////	return (int)mysql_num_rows(m_pRes);
////}
//
////const char* CMySqlDB::Test()
////{
////	//MYSQL_BIND* insertbind = new MYSQL_BIND[2];
////
////	//char insertSQL[SQL_STMT_LENGTH];
////	//strcpy_s(insertSQL, SQL_STMT_LENGTH, "insert into test1(id, name) values(?, ?)");
////
////	////MYSQL_STMT* stmt = mysql_stmt_init(m_pConn);
////
////	////mysql_stmt_prepare(stmt, insertSQL, (unsigned long)strlen(insertSQL));
////	//MYSQL_STMT* stmt = PrepareStmt(insertSQL);
////
////	//int param_count= mysql_stmt_param_count(stmt);
////
////	//MYSQL_BIND bind[3];
////	//memset(bind, 0, sizeof(bind));
////
////	//char str_data[64];
////	//strcpy_s(str_data, 64, "xxxxxx");
////	//unsigned long str_length = (unsigned long)strlen(str_data);
////	//unsigned int ui_data = 0;
////	//float float_data = 111.11f;
////
////	//bind[0].buffer_type = MYSQL_TYPE_LONG;
////	//bind[0].buffer = &ui_data;
////
////	//bind[1].buffer_type = MYSQL_TYPE_STRING;
////	//bind[1].buffer = str_data;
////	//bind[1].buffer_length = 64;
////	////bind[1].length = &str_length;
////
////	//bind[2].buffer_type = MYSQL_TYPE_FLOAT;
////	//bind[2].buffer = &float_data;
////	//
////	//if (mysql_stmt_bind_param(stmt, bind))
////	//{
////	//	fprintf(stderr, "bind error!\n");
////	//}
////
////	//if (mysql_stmt_execute(stmt))
////	//{
////	//	fprintf(stderr, "execute error!\n");
////	//}
////
////	//return NULL;
////
////
//////#define STRING_SIZE 50
//////
//////#define DROP_SAMPLE_TABLE "DROP TABLE IF EXISTS test_table"
//////#define CREATE_SAMPLE_TABLE "CREATE TABLE test_table(col1 INT,\
//	col2 VARCHAR(40),\
//	col3 SMALLINT,\
//	col4 TIMESTAMP)"
//////#define INSERT_SAMPLE "INSERT INTO \
//	test_table(col1,col2,col3) \
//	VALUES(?,?,?)"
//////
//////	MYSQL_STMT    *stmt;
//////	MYSQL_BIND    bind[3];
//////	my_ulonglong  affected_rows;
//////	int           param_count;
//////	short         small_data;
//////	int           int_data;
//////	char          str_data[STRING_SIZE];
//////	unsigned long str_length;
//////	my_bool       is_null;
//////
//////	if (mysql_query(m_pConn, DROP_SAMPLE_TABLE))
//////	{
//////		fprintf(stderr, " DROP TABLE failed\n");
//////		fprintf(stderr, " %s\n", mysql_error(m_pConn));
//////		exit(0);
//////	}
//////
//////	if (mysql_query(m_pConn, CREATE_SAMPLE_TABLE))
//////	{
//////		fprintf(stderr, " CREATE TABLE failed\n");
//////		fprintf(stderr, " %s\n", mysql_error(m_pConn));
//////		exit(0);
//////	}
//////
//////	/* Prepare an INSERT query with 3 parameters */
//////	/* (the TIMESTAMP column is not named; the server */
//////	/*  sets it to the current date and time) */
//////	stmt = mysql_stmt_init(m_pConn);
//////	if (!stmt)
//////	{
//////		fprintf(stderr, " mysql_stmt_init(), out of memory\n");
//////		exit(0);
//////	}
//////	if (mysql_stmt_prepare(stmt, INSERT_SAMPLE, (unsigned long)strlen(INSERT_SAMPLE)))
//////	{
//////		fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
//////		fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
//////		exit(0);
//////	}
//////	fprintf(stdout, " prepare, INSERT successful\n");
//////
//////	/* Get the parameter count from the statement */
//////	param_count= mysql_stmt_param_count(stmt);
//////	fprintf(stdout, " total parameters in INSERT: %d\n", param_count);
//////
//////	if (param_count != 3) /* validate parameter count */
//////	{
//////		fprintf(stderr, " invalid parameter count returned by MySQL\n");
//////		exit(0);
//////	}
//////
//////	/* Bind the data for all 3 parameters */
//////
//////	memset(bind, 0, sizeof(bind));
//////
//////	/* INTEGER PARAM */
//////	/* This is a number type, so there is no need
//////	to specify buffer_length */
//////	bind[0].buffer_type= MYSQL_TYPE_LONG;
//////	bind[0].buffer= (char *)&int_data;
//////	bind[0].is_null= 0;
//////	bind[0].length= 0;
//////
//////	/* STRING PARAM */
//////	bind[1].buffer_type= MYSQL_TYPE_STRING;
//////	bind[1].buffer= (char *)str_data;
//////	bind[1].buffer_length= STRING_SIZE;
//////	bind[1].is_null= 0;
//////	bind[1].length= &str_length;
//////
//////	/* SMALLINT PARAM */
//////	bind[2].buffer_type= MYSQL_TYPE_SHORT;
//////	bind[2].buffer= (char *)&small_data;
//////	bind[2].is_null= &is_null;
//////	bind[2].length= 0;
//////
//////	/* Bind the buffers */
//////	if (mysql_stmt_bind_param(stmt, bind))
//////	{
//////		fprintf(stderr, " mysql_stmt_bind_param() failed\n");
//////		fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
//////		return NULL;
//////	}
//////
//////	/* Specify the data values for the first row */
//////	int_data= 10;             /* integer */
//////	strncpy(str_data, "MySQL", STRING_SIZE); /* string  */
//////	str_length= (unsigned long)strlen(str_data);
//////
//////	/* INSERT SMALLINT data as NULL */
//////	is_null= 1;
//////
//////	/* Execute the INSERT statement - 1*/
//////	if (mysql_stmt_execute(stmt))
//////	{
//////		fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
//////		fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
//////		exit(0);
//////	}
//////
//////	/* Get the number of affected rows */
//////	affected_rows= mysql_stmt_affected_rows(stmt);
//////	fprintf(stdout, " total affected rows(insert 1): %lu\n",
//////		(unsigned long) affected_rows);
//////
//////	if (affected_rows != 1) /* validate affected rows */
//////	{
//////		fprintf(stderr, " invalid affected rows by MySQL\n");
//////		exit(0);
//////	}
//////
//////	/* Specify data values for second row,
//////	then re-execute the statement */
//////	int_data= 1000;
//////	strncpy(str_data, "The most popular Open Source database",
//////		STRING_SIZE);
//////	str_length= (unsigned long)strlen(str_data);
//////	small_data= 1000;         /* smallint */
//////	is_null= 0;               /* reset */
//////
//////	/* Execute the INSERT statement - 2*/
//////	if (mysql_stmt_execute(stmt))
//////	{
//////		fprintf(stderr, " mysql_stmt_execute, 2 failed\n");
//////		fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
//////		exit(0);
//////	}
//////
//////	/* Get the total rows affected */
//////	affected_rows= mysql_stmt_affected_rows(stmt);
//////	fprintf(stdout, " total affected rows(insert 2): %lu\n",
//////		(unsigned long) affected_rows);
//////
//////	if (affected_rows != 1) /* validate affected rows */
//////	{
//////		fprintf(stderr, " invalid affected rows by MySQL\n");
//////		exit(0);
//////	}
//////
//////	/* Close the statement */
//////	if (mysql_stmt_close(stmt))
//////	{
//////		fprintf(stderr, " failed while closing the statement\n");
//////		fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
//////		exit(0);
//////	}
////
////	return NULL;
////}
//
////MYSQL_STMT* CMySqlDB::PrepareStmt( const char* szStmt )
////{
////	//MYSQL_STMT* pstmt = mysql_stmt_init(m_pConn);
////	MYSQL_STMT* pstmt = mysql_stmt_init(GetCurrentConn());
////
////	if (!pstmt)
////	{
////		fprintf(stderr, " mysql_stmt_init(), out of memory\n");
////		return NULL;
////	}
////
////	if (mysql_stmt_prepare(pstmt, szStmt, (unsigned long)strlen(szStmt)))
////	{
////		fprintf(stderr, " mysql_stmt_prepare() failed\n");
////		fprintf(stderr, " %s\n", mysql_stmt_error(pstmt));
////		return NULL;
////	}
////
////	unsigned int uiParamCount = mysql_stmt_param_count(pstmt);
////
////	return pstmt;
////}
////
////MYSQL* CMySqlDB::GetCurrentConn()
////{
////	return m_ConnPool[m_uiCurrentConn == SQL_CONN_COUNT ? (m_uiCurrentConn = 0) : m_uiCurrentConn++];
////}
//
////bool CMySqlDB::LockConn(MYSQL* pConn)
////{
////	unsigned int uiIdx = 0xffffffff;
////	for (unsigned int ui = 0; ui < SQL_CONN_COUNT; ui++)
////	{
////		if (m_ConnPool[ui] == pConn)
////		{
////			uiIdx = ui;
////			break;
////		}
////	}
////
////	if (uiIdx >= SQL_CONN_COUNT)
////	{
////		return false;
////	}
////
////	unsigned long ulWaitTime = 0;
////	while (m_bLocked[uiIdx])
////	{
////		sleep(1);
////
////		ulWaitTime++;
////		if (ulWaitTime > MAX_WAIT_CONN_TIME)
////		{
////			return false;
////		}
////	}
////
////	m_bLocked[uiIdx] = true;
////	
////	return true;
////}
////
////void CMySqlDB::UnLockConn(MYSQL* pConn)
////{
////	for (unsigned int ui = 0; ui < SQL_CONN_COUNT; ui++)
////	{
////		if (m_ConnPool[ui] == pConn)
////		{
////			m_bLocked[ui] = false;
////			return;
////		}
////	}
////}
////
////MYSQL_ROW CMySqlDB::FetchRow()
////{
////	return mysql_fetch_row(m_pRes);
////}
//
//int CMySqlDB::GetAndLockConn( MYSQL** ppConn, int maxTryTimes )
//{
//#ifdef MULTI_THREAD
//	int iTryTimes = 0;
//	int iFoundIdx = -1;
//	while (iTryTimes < maxTryTimes && iFoundIdx == -1)
//	{
//		iTryTimes++;
//
//		//锁定连接池资源
//		WAIT_MUTEX(m_hPoolMutex, INFINITE);
//
//		//查找未被锁定的连接
//		int idx = m_uiLastConnIndex;
//		bool bFound = true;
//		while (m_bLocked[idx])
//		{
//			idx = (((idx + 1) == m_usConnCount) ? 0 : (idx + 1));
//
//			if (idx == m_uiLastConnIndex)
//			{
//				bFound = false;
//				break;
//			}
//		}
//
//		if (bFound)
//		{
//			*ppConn = m_ConnPool[idx];
//			SetLockIdx(idx);	
//			iFoundIdx = idx;
//
//			RELEASE_MUTEX(m_hPoolMutex);
//		}
//		else
//		{
//			RELEASE_MUTEX(m_hPoolMutex);
//
//#ifdef WINDOWS
//			Sleep(3);
//#else
//			timespec ts;
//			ts.tv_sec = 0;
//			ts.tv_nsec = 3000000;
//			::nanosleep(&ts, 0);
//#endif
//		}
//	}
//
//	return iFoundIdx;
//#else
//	*ppConn = m_ConnPool[0];
//	return 0;
//#endif
//	
//}

const char* IODMyDb::freeQuery( MYSQL* pConn, const char* pszSql, const char* pszRetValueFormat, ... )
{
	char szRetBuff[1024] = {0};

	if (const char* pszErr = freeQuery(pConn, pszSql, szRetBuff))
	{
		return pszErr;
	}

	va_list va;
	va_start(va, pszRetValueFormat);
	vsscanf(szRetBuff, pszRetValueFormat, va);
	va_end(va);

	return NULL;
}

const char* IODMyDb::freeQuery( MYSQL* pConn, const char* pszSql, char* szRet /* = NULL*/ )
{
	{
		//IODDB::STAutoTiming stAutoTiming(pszSql, 1);
		if (int iError = mysql_real_query(pConn, pszSql, (unsigned long)strlen(pszSql)))
		{
			//IOD_SRV_ERROR("query error code %d", iError);
			//IOD::on_query_failed_statistics();
			return mysql_error(pConn);
		}
		//if (mysql_real_query(pConn, pszSql, (unsigned long)strlen(pszSql)))
		//{
		//	return mysql_error(pConn);
		//}
	}
	
	if (szRet == NULL)
	{
		return NULL;
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
	if (num_rows != 1)
	{
		mysql_free_result(pRes);
		return "invalid result count!!!";
	}

	MYSQL_ROW row = 0;
	if (!(row = mysql_fetch_row(pRes)))
	{
		mysql_free_result(pRes);
		return "fetch result failed\n";
	}

	unsigned int uiFieldCount = mysql_num_fields(pRes);

	szRet[0] = 0;
	for (unsigned int i = 0; i < uiFieldCount; i++)
	{
		if (strlen(szRet) > 0)
		{
			sprintf(szRet + strlen(szRet), ",%s", row[i]);
		}
		else
		{
			sprintf(szRet + strlen(szRet), row[i]);
		}
	}

	mysql_free_result(pRes);

	return NULL;
}

struct STQueryResult
{
	uint64 id;
	char szName[100];
};

void IODMyDb::TestFreeQuery( MYSQL* pConn )
{
	STQueryResult oQueryResult[12];

	STOutFieldInfo outFileInfo[] = {
		__out_field("outId", STQueryResult, id, IOD_FIELD_TYPE_UINT8), 
		__out_field("outName", STQueryResult, szName, IOD_FIELD_TYPE_STRING)
	};
	unsigned long ulResultCount;
	const char* pszErr1 = IODMyDb::freeQuery(pConn, "select RoleId as outId, RoleName as outName from TRoleInfo limit 1, 10", 
		oQueryResult /*query result pointer*/, &ulResultCount, 
		sizeof(oQueryResult)/sizeof(STQueryResult) /*max count of query result*/, 
		outFileInfo, 2 /*out field count*/);

	char szQueryResult[100];
	const char* pszErr2 = IODMyDb::freeQuery(pConn, "select RoleId as outId, RoleName as outName from TRoleInfo limit 1", szQueryResult);

	uint64 nRetId;
	char szRetName[64];
	const char* pszErr3 = IODMyDb::freeQuery(pConn, "select RoleId as outId, RoleName as outName from TRoleInfo limit 1", "%llu,%s", &nRetId, szRetName);
}
