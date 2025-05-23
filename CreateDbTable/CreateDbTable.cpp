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
		printf("Failed to connect to the database\n");
		Sleep(5000);
		return 0;
	}

	/*
	if(!DB_SqlCreateDbAllocInfos(200) && !DB_SqlCreateDbClientInfos(200) && !DB_SqlCreateDbLoginInfos(200)) 
	{
		printf("Failed to create multiple tables\n");
	}	
	else
	{
		printf("Create multiple tables complete\n");
	}

	
	if(!DB_SqlDeleteTableDbAllocInfo(200) && !DB_SqlDeleteTableDbAllocInfo(200) && !DB_SqlDeleteTableDbAllocInfo(200)) 
	{
		printf("Failed to delete multiple tables\n");
	}
	else
	{
		printf("Deleting multiple tables completed\n");
	}
	*/
	time(&Time); 
	TimeInfo = localtime(&Time);
	printf(" # Start Time:%2d-%02d-%02d %02d:%02d:%02d\n",1900 + TimeInfo->tm_year,1 + TimeInfo->tm_mon,TimeInfo->tm_mday,TimeInfo->tm_hour,TimeInfo->tm_min,TimeInfo->tm_sec);

	if(DB_SqlInsertDbClientInfo(120000000))
	{
		printf("Insert record successfully!\n");
	}
	else
	{
		printf("Failed to insert record!\n");
	}

	time(&Time); 
	TimeInfo = localtime(&Time);
	printf(" # End Time:%2d-%02d-%02d %02d:%02d:%02d\n",1900 + TimeInfo->tm_year,1 + TimeInfo->tm_mon,TimeInfo->tm_mday,TimeInfo->tm_hour,TimeInfo->tm_min,TimeInfo->tm_sec);

	Sleep(100000);
	return 0;
}
