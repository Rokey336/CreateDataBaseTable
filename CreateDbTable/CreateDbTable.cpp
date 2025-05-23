#include <time.h>
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>

#include "DbHeader.h"
#include "CreateDbTable.h"

int main()
{
	time_t Time            = 0; 
	struct tm *TimeInfo    = NULL;

	if(!DB_SqlConnect(DB_ODBC_DSN, DB_USERNAME, DB_PASSWORD))
	{
		printf("连接数据库失败\n");
		Sleep(5000);
		return 0;
	}

	/*
	if(!DB_SqlCreateDbAllocInfos(200) && !DB_SqlCreateDbClientInfos(200) && !DB_SqlCreateDbLoginInfos(200)) 
	{
		printf("创建多表失败\n");
	}	
	else
	{
		printf("创建多表完成\n");
	}

	
	if(!DB_SqlDeleteTableDbAllocInfo(200) && !DB_SqlDeleteTableDbAllocInfo(200) && !DB_SqlDeleteTableDbAllocInfo(200)) 
	{
		printf("删除多表失败\n");
	}
	else
	{
		printf("删除多表完成\n");
	}
	*/
	time(&Time); 
	TimeInfo = localtime(&Time);
	printf(" # 开始时间:%2d-%02d-%02d %02d:%02d:%02d\n",1900 + TimeInfo->tm_year,1 + TimeInfo->tm_mon,TimeInfo->tm_mday,TimeInfo->tm_hour,TimeInfo->tm_min,TimeInfo->tm_sec);

	if(DB_SqlInsertDbClientInfo(120000000))
	{
		printf("插入记录成功!\n");
	}
	else
	{
		printf("插入记录失败!\n");
	}

	time(&Time); 
	TimeInfo = localtime(&Time);
	printf(" # 结束时间:%2d-%02d-%02d %02d:%02d:%02d\n",1900 + TimeInfo->tm_year,1 + TimeInfo->tm_mon,TimeInfo->tm_mday,TimeInfo->tm_hour,TimeInfo->tm_min,TimeInfo->tm_sec);

	Sleep(100000);
	return 0;
}