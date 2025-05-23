// 定义 SQL 源、用户名及密码
#define DB_ODBC_DSN     "DarkBlue_101"
#define DB_USERNAME		"darkblue"
#define DB_PASSWORD		"darkblue"


// 定义任务信息结构体
typedef struct _DB_TASK_INFO              
{
	LIST_ENTRY ListEntry;
	ULONG StateFlag;              
	ULONG MajorNum;               
	ULONG MinorNum;               
	ULONG TotalCnt;               
	ULONG AllocCnt;               
	ULONG CntFlag;                
	ULONG TaskType;               
	ULONG AreaCode;               
	ULONG Priority;               
	ULONG StartTime;              
	ULONG EndTime;                
	ULONG AppVer;                 
	CHAR OsVer[16];               
	CHAR Account[64];             
	CHAR Channel[MAX_PATH];        
	CHAR Descript[MAX_PATH];      
	CHAR FilePath[MAX_PATH];      
	CHAR AddTime[20];             
	CHAR UpdTime[20];             
	CHAR DelTime[20];             

	// ...        

} DB_TASK_INFO, *PDB_TASK_INFO;

// 定义 ALLOC 结构体
typedef struct _DB_ALLOC_INFO
{
	CHAR MacAddr[18];          
	ULONG MajorNum;           
	ULONG MinorNum;           
	ULONG TaskType;           
	CHAR Account[64];         
	CHAR Descript[MAX_PATH];  
	CHAR Channel[MAX_PATH];    
	CHAR AllocTime[20];       

	// ...

} DB_ALLOC_INFO, *PDB_ALLOC_INFO;

// 定义 ALLOC 结构体缓存
typedef struct _DB_ALLC_CAHE
{
	LIST_ENTRY ListEntry;
	CHAR MacAddr[18];          
	ULONG MajorNum[100];      

	// ...

} DB_ALLC_CAHE, *PDB_ALLC_CAHE;

// 定义客户端信息结构体
typedef struct _DB_CLINET_INFO              
{
	ULONG StateFlag;           
	ULONG AreaCode;           
	ULONG AppVer;              
	CHAR OsVer[16];            
	CHAR MacAddr[18];          
	CHAR LgnAddr[16];           
	CHAR CnlAddr[16];          
	CHAR Channel[MAX_PATH];    
	CHAR OnLnTime[20];          
	CHAR OfLnTime[20];          
	CHAR InstTime[20];        

	// ...    

} DB_CLIENT_INFO, *PDB_CLIENT_INFO;

// 定义渠道信息结构体
typedef struct _DB_CHNL_INFO              
{
	LIST_ENTRY ListEntry;
	ULONG StateFlag;           
	CHAR ChnlName[260];        
	CHAR MacAddr1[18];         
	CHAR MacAddr2[18];         
	CHAR MacAddr3[18];         
	CHAR MacAddr4[18];         
	CHAR MacAddr5[18];         
	CHAR MacAddr6[18];         
	CHAR MacAddr7[18];         
	CHAR MacAddr8[18];        
	CHAR MacAddr9[18];         
	CHAR AddTime[20];         

	// ...    

} DB_CHNL_INFO, *PDB_CHNL_INFO;


SQLHENV DB_SqlHandleEnv = NULL;	   
SQLHDBC DB_SqlHandleDbc = NULL;	   