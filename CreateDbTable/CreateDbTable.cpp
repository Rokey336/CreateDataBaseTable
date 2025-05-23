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
		printf("�������ݿ�ʧ��\n");
		Sleep(5000);
		return 0;
	}

	/*
	if(!DB_SqlCreateDbAllocInfos(200) && !DB_SqlCreateDbClientInfos(200) && !DB_SqlCreateDbLoginInfos(200)) 
	{
		printf("�������ʧ��\n");
	}	
	else
	{
		printf("����������\n");
	}

	
	if(!DB_SqlDeleteTableDbAllocInfo(200) && !DB_SqlDeleteTableDbAllocInfo(200) && !DB_SqlDeleteTableDbAllocInfo(200)) 
	{
		printf("ɾ�����ʧ��\n");
	}
	else
	{
		printf("ɾ��������\n");
	}
	*/
	time(&Time); 
	TimeInfo = localtime(&Time);
	printf(" # ��ʼʱ��:%2d-%02d-%02d %02d:%02d:%02d\n",1900 + TimeInfo->tm_year,1 + TimeInfo->tm_mon,TimeInfo->tm_mday,TimeInfo->tm_hour,TimeInfo->tm_min,TimeInfo->tm_sec);

	if(DB_SqlInsertDbClientInfo(120000000))
	{
		printf("�����¼�ɹ�!\n");
	}
	else
	{
		printf("�����¼ʧ��!\n");
	}

	time(&Time); 
	TimeInfo = localtime(&Time);
	printf(" # ����ʱ��:%2d-%02d-%02d %02d:%02d:%02d\n",1900 + TimeInfo->tm_year,1 + TimeInfo->tm_mon,TimeInfo->tm_mday,TimeInfo->tm_hour,TimeInfo->tm_min,TimeInfo->tm_sec);

	Sleep(100000);
	return 0;
}