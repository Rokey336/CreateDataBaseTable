
/********************************************************************************
*
* Name:	DB_SqlConnect
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlConnect(PCHAR DataBase,PCHAR UserName,PCHAR PassWord)
{
	SQLRETURN SqlRet = 0;

	SqlRet = SQLAllocHandle(SQL_HANDLE_ENV,NULL,&DB_SqlHandleEnv);
	if(SqlRet != SQL_SUCCESS && SqlRet != SQL_SUCCESS_WITH_INFO) return FALSE;

	SqlRet = SQLSetEnvAttr(DB_SqlHandleEnv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
	if(SqlRet != SQL_SUCCESS && SqlRet != SQL_SUCCESS_WITH_INFO) return FALSE;

	SqlRet = SQLAllocHandle(SQL_HANDLE_DBC,DB_SqlHandleEnv,&DB_SqlHandleDbc);
	if(SqlRet != SQL_SUCCESS && SqlRet != SQL_SUCCESS_WITH_INFO) return FALSE;

	SqlRet = SQLConnect(DB_SqlHandleDbc,(PUCHAR)DataBase,strlen(DataBase),(PUCHAR)UserName,strlen(UserName),(PUCHAR)PassWord,strlen(PassWord));
	if(SqlRet != SQL_SUCCESS && SqlRet != SQL_SUCCESS_WITH_INFO) return FALSE;

	return TRUE;
}

/********************************************************************************
*
* Name:	DB_SqlDisConnect
*
* Return:	VOID
*
********************************************************************************/
VOID DB_SqlDisConnect(VOID)
{
	if(DB_SqlHandleEnv != NULL) 
	{
		SQLFreeHandle(SQL_HANDLE_ENV,DB_SqlHandleEnv);
		DB_SqlHandleEnv = NULL;
	}

	if(DB_SqlHandleDbc != NULL) 
	{
		SQLFreeHandle(SQL_HANDLE_DBC,DB_SqlHandleDbc);
		DB_SqlHandleDbc = NULL;
	}
}

/********************************************************************************
*
* Name:	DB_SqlReConnect
*
* Return:	VOID
*
********************************************************************************/
VOID DB_SqlReConnect(VOID)
{
    printf("\n # Connect Database ...");

	do
	{
		DB_SqlDisConnect();

	}while(!DB_SqlConnect(DB_ODBC_DSN,DB_USERNAME,DB_PASSWORD));

	printf(" # Database reconnection successful ! ");
}

/********************************************************************************
*
* Name:	DB_SqlInsert
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlInsert(PCHAR TableName,PCHAR StrValues)
{
	SQLRETURN SqlRet       = 0;
	CHAR SqlCmd[512]       = {0};
	SQLHSTMT SqlHandleStmt = NULL;

	if(TableName == NULL || StrValues == NULL) return FALSE;		

	__try
	{
		SqlRet = SQLAllocHandle(SQL_HANDLE_STMT,DB_SqlHandleDbc,&SqlHandleStmt);
		if(SqlRet != SQL_SUCCESS && SqlRet != SQL_SUCCESS_WITH_INFO) return FALSE;

		strcpy(SqlCmd,"insert into ");
		strcat(SqlCmd,TableName);
		strcat(SqlCmd," values (");
		strcat(SqlCmd,StrValues);
		strcat(SqlCmd,")");

		SqlRet = SQLExecDirect(SqlHandleStmt,(PUCHAR)SqlCmd,strlen(SqlCmd));
		return SqlRet == SQL_SUCCESS || SqlRet == SQL_SUCCESS_WITH_INFO;
	}
	__finally
	{
		if(SqlHandleStmt != NULL)
		{
			SQLCloseCursor(SqlHandleStmt);
			SQLFreeHandle(SQL_HANDLE_STMT,SqlHandleStmt);
		}
	}
}

/********************************************************************************
*
* Name:	DB_SqlUpdate
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlUpdate(PCHAR TableName,PCHAR Condition)
{
	SQLRETURN SqlRet       = 0;
	CHAR SqlCmd[512]       = {0};
	SQLHSTMT SqlHandleStmt = NULL;

	if(TableName == NULL || Condition == NULL) return FALSE;

	__try
	{
		SqlRet = SQLAllocHandle(SQL_HANDLE_STMT,DB_SqlHandleDbc,&SqlHandleStmt);
		if(SqlRet != SQL_SUCCESS && SqlRet != SQL_SUCCESS_WITH_INFO) return FALSE;

		strcpy(SqlCmd,"update ");
		strcat(SqlCmd,TableName);
		strcat(SqlCmd," set ");
		strcat(SqlCmd,Condition);

		SqlRet = SQLExecDirect(SqlHandleStmt,(PUCHAR)SqlCmd,strlen(SqlCmd));
		return SqlRet == SQL_SUCCESS || SqlRet == SQL_SUCCESS_WITH_INFO;
	}
	__finally
	{
		if(SqlHandleStmt != NULL)
		{
			SQLCloseCursor(SqlHandleStmt);
			SQLFreeHandle(SQL_HANDLE_STMT,SqlHandleStmt);
		}
	}
}

/********************************************************************************
*
* Name:	DB_SqlDelete
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlDelete(PCHAR TableName,PCHAR Condition)
{
	SQLRETURN SqlRet       = 0;
	CHAR SqlCmd[512]       = {0};
	SQLHSTMT SqlHandleStmt = NULL;

	if(TableName == NULL || Condition == NULL) return FALSE;

	__try
	{
		SqlRet = SQLAllocHandle(SQL_HANDLE_STMT,DB_SqlHandleDbc,&SqlHandleStmt);
		if(SqlRet != SQL_SUCCESS && SqlRet != SQL_SUCCESS_WITH_INFO) return FALSE;

		strcpy(SqlCmd, "delete from ");
		strcat(SqlCmd, TableName);
		strcat(SqlCmd, " where ");
		strcat(SqlCmd, Condition);

		SqlRet = SQLExecDirect(SqlHandleStmt,(PUCHAR)SqlCmd,strlen(SqlCmd));
		return SqlRet == SQL_SUCCESS || SqlRet == SQL_SUCCESS_WITH_INFO;
	}
	__finally
	{
		if(SqlHandleStmt != NULL)
		{
			SQLCloseCursor(SqlHandleStmt);
			SQLFreeHandle(SQL_HANDLE_STMT,SqlHandleStmt);
		}
	}
}

/********************************************************************************
*
* Name:	DB_SqlTableExec
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlTableExec(PCHAR TableStr)
{
	SQLRETURN SqlRet       = 0;
	CHAR SqlCmd[512]       = {0};
	SQLHSTMT SqlHandleStmt = NULL;

	if(TableStr == NULL) return FALSE;

	__try
	{
		SqlRet = SQLAllocHandle(SQL_HANDLE_STMT,DB_SqlHandleDbc,&SqlHandleStmt);
		if(SqlRet != SQL_SUCCESS && SqlRet != SQL_SUCCESS_WITH_INFO) return FALSE;

		strcpy(SqlCmd, TableStr);

		SqlRet = SQLExecDirect(SqlHandleStmt,(PUCHAR)SqlCmd,strlen(SqlCmd));
		return SqlRet == SQL_SUCCESS || SqlRet == SQL_SUCCESS_WITH_INFO;
	}
	__finally
	{
		if(SqlHandleStmt != NULL)
		{
			SQLCloseCursor(SqlHandleStmt);
			SQLFreeHandle(SQL_HANDLE_STMT,SqlHandleStmt);
		}
	}
}

/*================================================================================
*
* Name:	DB_MakeInsertDbClientInfoStmt
*
* Return:	VOID
*
================================================================================*/
VOID DB_MakeInsertDbClientInfoStmt(PCHAR SqlStr, PDB_CLIENT_INFO ClientInfo)
{	
	strcpy(SqlStr,"call InsertSglDbClientInfo(");
	sprintf(&SqlStr[strlen(SqlStr)],"%d",ClientInfo->StateFlag);// StateFlag

	strcat(SqlStr,",");
	sprintf(&SqlStr[strlen(SqlStr)],"%d",ClientInfo->AreaCode);	// AreaCode

	strcat(SqlStr,",");
	sprintf(&SqlStr[strlen(SqlStr)],"%d",ClientInfo->AppVer);	// AppVer	

	strcat(SqlStr,",'");
	strcat(SqlStr,ClientInfo->OsVer);		// OsVer

	strcat(SqlStr,"','");
	strcat(SqlStr,ClientInfo->MacAddr);		// MacAddr

	strcat(SqlStr,"','");
	strcat(SqlStr,ClientInfo->LgnAddr);		// LgnAddr

	strcat(SqlStr,"','");
	strcat(SqlStr,ClientInfo->CnlAddr);		// CnlAddr	

	strcat(SqlStr,"','");
	strcat(SqlStr,ClientInfo->Channel);		// Channel	

	strcat(SqlStr,"','");
	strcat(SqlStr,ClientInfo->OnLnTime);	// OnLnTime	

	strcat(SqlStr,"','");
	strcat(SqlStr,ClientInfo->OfLnTime);	// OfLnTime		

	strcat(SqlStr,"','");
	strcat(SqlStr,ClientInfo->InstTime);	// InstTime			
	strcat(SqlStr,"');");

	return;
}

/*================================================================================
*
* Name:	DB_MakeCreateDbClientInfoStmt
*
* Return:	VOID
*
================================================================================*/
VOID DB_MakeCreateDbClientInfoStmt(PCHAR TablePartStr, ULONG TablePartNum, PCHAR SqlStr)
{	
	strcpy(SqlStr,"create table ");
	strcat(SqlStr,TablePartStr);
	sprintf(&SqlStr[strlen(SqlStr)],"%.3d",TablePartNum);

	strcat(SqlStr,"(StateFlag int, AreaCode int, AppVer int, OsVer varchar(16), MacAddr varchar(18), LgnAddr varchar(16), CnlAddr varchar(16), Channel varchar(260), OnLnTime varchar(20), OfLnTime varchar(20), InstTime varchar(20), constraint PK_");

	strcat(SqlStr,TablePartStr);
	sprintf(&SqlStr[strlen(SqlStr)],"%.3d",TablePartNum);

	strcat(SqlStr, " primary key clustered (MacAddr asc))");

	return;
}

/*================================================================================
*
* Name:	DB_MakeCreateDbAllocInfoStmt
*
* Return:	VOID
*
================================================================================*/
VOID DB_MakeCreateDbAllocInfoStmt(PCHAR TablePartStr, ULONG TablePartNum, PCHAR SqlStr)
{	
	strcpy(SqlStr,"create table ");
	strcat(SqlStr,TablePartStr);
	sprintf(&SqlStr[strlen(SqlStr)],"%.3d",TablePartNum);

	strcat(SqlStr,"(MacAddr varchar(18),MajorNum int, MinorNum int,TaskType int, Account varchar(64), Descript varchar(260), Channel varchar(260), AllocTime  varchar(20), constraint PK_");

	strcat(SqlStr,TablePartStr);
	sprintf(&SqlStr[strlen(SqlStr)],"%.3d",TablePartNum);

	strcat(SqlStr, " PRIMARY KEY CLUSTERED (MacAddr asc,MajorNum ASC,MinorNum ASC))");

	return;
}

/*================================================================================
*
* Name:	DB_MakeDeleteTableStmt
*
* Return:	VOID
*
================================================================================*/
VOID DB_MakeDeleteTableStmt(PCHAR TablePartStr, ULONG TablePartNum, PCHAR SqlStr)
{
	strcpy(SqlStr,"drop table ");
	strcat(SqlStr,TablePartStr);
	sprintf(&SqlStr[strlen(SqlStr)],"%.3d",TablePartNum);

	return;
}

/********************************************************************************
*
* Name:	DB_SqlCreateDbAllocInfos
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlCreateDbAllocInfos(ULONG TableNum)
{
	BOOL    bRet = TRUE;
	CHAR	SqlStr[1024] = {0};
	USHORT  Index = 0;

	for (Index = 0; Index < TableNum; Index++)
	{
		DB_MakeCreateDbAllocInfoStmt("DbAllocInfo",Index, SqlStr);
		if(!DB_SqlTableExec(SqlStr)) 
		{
			bRet = FALSE;
			break;
		}
	}

	return bRet;
}

/********************************************************************************
*
* Name:	DB_SqlCreateDbClientInfos
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlCreateDbClientInfos(ULONG TableNum)
{
	BOOL    bRet = TRUE;
	CHAR	SqlStr[1024] = {0};
	USHORT  Index = 0;

	for (Index = 0; Index < TableNum; Index++)
	{
		DB_MakeCreateDbClientInfoStmt("DbClientInfo",Index, SqlStr);
		if(!DB_SqlTableExec(SqlStr)) 
		{
			bRet = FALSE;
			break;
		}
	}

	return bRet;
}


/********************************************************************************
*
* Name:	DB_SqlCreateDbLoginInfos
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlCreateDbLoginInfos(ULONG TableNum)
{
	BOOL    bRet = TRUE;
	CHAR	SqlStr[1024] = {0};
	USHORT  Index = 0;

	for (Index = 0; Index < TableNum; Index++)
	{
		DB_MakeCreateDbClientInfoStmt("DbLoginInfo",Index, SqlStr);
		if(!DB_SqlTableExec(SqlStr)) 
		{
			bRet = FALSE;
			break;
		}
	}

	return bRet;
}


/********************************************************************************
*
* Name:	DB_SqlDeleteTableDbAllocInfo
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlDeleteTableDbAllocInfo(ULONG TableNum)
{
	BOOL    bRet = TRUE;
	CHAR	SqlStr[1024] = {0};
	USHORT  Index = 0;

	for (Index = 0; Index < TableNum; Index++)
	{
		DB_MakeDeleteTableStmt("DbAllocInfo",Index, SqlStr);
		if(!DB_SqlTableExec(SqlStr)) 
		{
			bRet = FALSE;
			break;
		}
	}

	return bRet;
}

/********************************************************************************
*
* Name:	DB_SqlDeleteTableDbClientInfo
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlDeleteTableDbClientInfo(ULONG TableNum)
{
	BOOL    bRet = TRUE;
	CHAR	SqlStr[1024] = {0};
	USHORT  Index = 0;

	for (Index = 0; Index < TableNum; Index++)
	{
		DB_MakeDeleteTableStmt("DbClientInfo",Index, SqlStr);
		if(!DB_SqlTableExec(SqlStr)) 
		{
			bRet = FALSE;
			break;
		}
	}

	return bRet;
}

/********************************************************************************
*
* Name:	DB_SqlDeleteTableDbLoginInfo
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlDeleteTableDbLoginInfo(ULONG TableNum)
{
	BOOL    bRet = TRUE;
	CHAR	SqlStr[1024] = {0};
	USHORT  Index = 0;

	for (Index = 0; Index < TableNum; Index++)
	{
		DB_MakeDeleteTableStmt("DbLoginInfo",Index, SqlStr);
		if(!DB_SqlTableExec(SqlStr)) 
		{
			bRet = FALSE;
			break;
		}
	}

	return bRet;
}


/********************************************************************************
*
* Name:	DB_SqlInsertDbClientInfo
*
* Return:	BOOL
*
********************************************************************************/
BOOL DB_SqlInsertDbClientInfo(ULONG RecordNum)
{
	time_t Time            = 0; 
	struct tm *TimeInfo    = NULL;

	BOOL    bRet = TRUE;
	CHAR	SqlStr[1024] = {0};
	ULONG   Index = 0;
	DB_CLIENT_INFO ClientInfo = {0};

	ClientInfo.AppVer = 1;
	ClientInfo.AreaCode = 1;
	
	strcat(ClientInfo.OsVer, "WinXP_Test");
	strcat(ClientInfo.LgnAddr, "127.0.0.1");
	strcat(ClientInfo.CnlAddr, "127.0.0.1");
	strcat(ClientInfo.Channel, "DarkBlue_Test");
	strcat(ClientInfo.OnLnTime, "17:50:00 2016/02/14");
	strcat(ClientInfo.OfLnTime, "17:50:00 2016/02/14");
	strcat(ClientInfo.InstTime, "17:50:00 2016/02/14");

	for (Index = 110000001; Index < RecordNum; Index++)
	{
		ClientInfo.StateFlag = Index;
		sprintf(ClientInfo.MacAddr,"%d", Index);	// MacAddr
		
		DB_MakeInsertDbClientInfoStmt(SqlStr, &ClientInfo);
		if(!DB_SqlTableExec(SqlStr)) 
		{
			bRet = FALSE;
			break;
		}

		if (Index % 10000 == 0)
		{
			time(&Time); 
			TimeInfo = localtime(&Time);
			printf(" #%dW, Time:%2d-%02d-%02d %02d:%02d:%02d\n",Index / 10000, 1900 + TimeInfo->tm_year,1 + TimeInfo->tm_mon,TimeInfo->tm_mday,TimeInfo->tm_hour,TimeInfo->tm_min,TimeInfo->tm_sec);
		}
	}

	return bRet;
}
