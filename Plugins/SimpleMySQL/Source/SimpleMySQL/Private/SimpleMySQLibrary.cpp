// Copyright (C) RenZhai.2020.All Rights Reserved.
#include "SimpleMySQLibrary.h"
#include "MySQL/mysql.h"
//---------------------------------------------------链接测试 查询
// void USimpleMySQLLibrary::MySqlMain()
// {
// 	const char* user = "root";		//用户
// 	const char* host = "127.0.0.1";	//localhoust
// 	const char* pawd = "root";		//密码
// 	const char* table = "hello";	//数据库db
// 	const char* db = "Mysql";		//数据库起名
// 	const uint32 port = 3306;		//端口
// 
// 	MYSQL mysql;
// 	MYSQL_RES* result = NULL;		//查询结果
// 
// 	int32 result_int = INDEX_NONE;	//返回结果成功失败
// 
// 	mysql_init(&mysql);
// 	if (mysql_real_connect(&mysql, host, user, pawd, table/*db*/, port, 0, 0))	//链接数据库
// 	{
// 		//SELECT * FROM 表
// 		if ((result_int = mysql_query(&mysql,"SELECT * FROM W"/*语句*/)) == 0)
// 		{
// 				//存储到本地磁盘默认大小64MB;
// 			if ((result = mysql_store_result(&mysql)) != NULL)
// 			{;
// 				while(MYSQL_ROW sql_row = mysql_fetch_row(result))//以某种方式读出来
// 				{
// 					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red,*FString::Printf(TEXT("name:%s"), ANSI_TO_TCHAR(sql_row[0])));
// 					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("age:%s"), ANSI_TO_TCHAR(sql_row[1])));
// 					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("size:%s"), ANSI_TO_TCHAR(sql_row[2])));
// 					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("height:%s"), ANSI_TO_TCHAR(sql_row[3])));
// 				}
// 			}
// 		}
// 		else
// 		{
// 			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "query sql failed!");
// 			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
// 		}
// 	}
// 	else
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "query sql failed!");
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
// 	}
// 
// 	if(result != NULL)
// 	{
// 		mysql_free_result(result);
// 	}
// 
// 	mysql_close(&mysql);
// }

//--------------------------------------------------------
// void USimpleMySQLLibrary::MySqlMain()
// {
// 	const char* user = "root";		//用户
// 	const char* host = "127.0.0.1";	//localhoust
// 	const char* pawd = "root";		//密码
// 	const char* table = "hello";	//数据库db
// 	const char* db = "Mysql";		//数据库起名
// 	const uint32 port = 3306;		//端口
// 
// 	MYSQL mysql;
// 
// 	mysql_library_init(NULL, NULL, NULL);	//保证线程安全，对应mysql_library_end
// 	mysql_init(&mysql);	//分配内存(如果牵扯多线程可能会存在内存泄露，搭配mysql_library_init可以线程安全)
// 	
// 
// 	mysql_close(&mysql);
// 	mysql_library_end();	//对应mysql_library_init
// }

//--------------------------------------------------------------------链接
//void USimpleMySQLLibrary::MySqlMain()
//{
//	const char *user = "root";
//	const char *host = "127.0.0.1";//localhost
//	const char *pawd = "root";
//	const char *table = "hello";
//	const uint32 port = 3306;
//
//	MYSQL mysql;
//	mysql_library_init(NULL, NULL, NULL);//保证线程安全
//	mysql_init(&mysql);//分配内存
//
//	/*CLIENT_COMPRESS 
//	CLIENT_FOUND_ROWS
//	CLIENT_IGNORE_SPACE
//	CLIENT_INTERACTIVE
//	CLIENT_LOCAL_FILES
//	CLIENT_MULTI_STATEMENTS
//	CLIENT_MULTI_RESULTS  
//	CLIENT_NO_SCHEMA db_name.tbl_name.col_name ODBC
//	CLIENT_ODBC  
//	CLIENT_SSL*/ //openSSL
//	if (mysql_real_connect(&mysql, host, user, pawd, table, port, 0, 0))//链接
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "connect success !");
//	}
//	else
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "connect failed!");
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
//	}
//	
//	int ret = mysql_ping(&mysql);
//	if (ret == 0)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "mysql_ping success!");
//	}
//	else
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "mysql_ping failed!");
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
//	}
//
//
//	mysql_close(&mysql);
//	mysql_library_end();
//}

//-----------------------------------------------------------------------------------------

// void USimpleMySQLLibrary::MySqlMain()
// {
// 	const char *user = "root";
// 	const char *host = "127.0.0.1";//localhost
// 	const char *pawd = "root";
// 	const char *table = "hello";
// 	const uint32 port = 3306;
// 
// 	MYSQL mysql;
// 	mysql_library_init(NULL, NULL, NULL);//保证线程安全
// 	mysql_init(&mysql);//分配内存
// 
// 	int time = 4;
// 	//MYSQL_OPT_RECONNECT 重新链接
// 	//MYSQL_OPT_CONNECT_TIMEOUT 超时的时间 “ ”
// 	int ret = mysql_options(&mysql, MYSQL_OPT_RECONNECT,&time);
// 
// 	if (mysql_real_connect(&mysql, host, user, pawd, table, port, 0, 0))//链接
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "connect success !");
// 	}
// 	else
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "connect failed!");
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
// 	}
// 
// 	 ret = mysql_ping(&mysql);
// 	if (ret == 0)
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "mysql_ping success!");
// 	}
// 	else
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "mysql_ping failed!");
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
// 	}
// 
// 	mysql_close(&mysql);
// 	mysql_library_end();
// 
// }

//---------------------------------------------Mysql查询---------------------------------------------------

//
// void USimpleMySQLLibrary::MySqlMain()
// {
// 	const char *user = "root";
// 	const char *host = "127.0.0.1";//localhost
// 	const char *pawd = "root";
// 	const char *table = "hello";
// 	const uint32 port = 3306;
// 
// 	MYSQL mysql;
// 	mysql_library_init(NULL, NULL, NULL);//保证线程安全
// 	mysql_init(&mysql);//分配内存
// 
// 	my_bool reconnect = 1;
// 	int ret = mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconnect);
// 	int BufSize = 1024 * 1024 * 64 ;//1MB
// 	//MYSQL_OPT_MAX_ALLOWED_PACKET 64MB
// 	ret = mysql_options(&mysql, MYSQL_OPT_MAX_ALLOWED_PACKET, &BufSize);
// 
// 	char select[] = "SELECT name FROM W";
// 	if (mysql_real_connect(&mysql, host, user, pawd, table, port, 0, 0))//链接
// 	{
// 		//mysql_real_query(&mysql, select, strlen(select));
// 		if ((ret = mysql_query(&mysql, select)) == 0)
// 		{
// 			if (MYSQL_RES *result = mysql_store_result(&mysql))
// 			{
// 				while (MYSQL_ROW sql_row = mysql_fetch_row(result))
// 				{
// 					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name [%s]"), ANSI_TO_TCHAR(sql_row[0])));
// 				}
// 			}
// 		}
// 	}
// 	else
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "connect failed!");
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
// 	}
// 
// 	ret = mysql_ping(&mysql);
// 	if (ret == 0)
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "mysql_ping success!");
// 	}
// 	else
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "mysql_ping failed!");
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
// 	}
// 
// 	mysql_close(&mysql);
// 	mysql_library_end();
// }

//---------------------------------------对查询结果进行服务器读取或者本地缓存读取-------------------

//void USimpleMySQLLibrary::MySqlMain()
//{
//	const char *user = "root";
//	const char *host = "127.0.0.1";//localhost
//	const char *pawd = "root";
//	const char *table = "hello";
//	const uint32 port = 3306;
//
//	MYSQL mysql;
//	mysql_library_init(NULL, NULL, NULL);//保证线程安全
//	mysql_init(&mysql);//分配内存
//
//	my_bool reconnect = 1;
//	int ret = mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconnect);
//	int BufSize = 1024 * 1024 * 64;//1MB
//	//MYSQL_OPT_MAX_ALLOWED_PACKET 64MB
//	ret = mysql_options(&mysql, MYSQL_OPT_MAX_ALLOWED_PACKET, &BufSize);
//
//	char select[] = "SELECT name FROM W";
//	if (mysql_real_connect(&mysql, host, user, pawd, table, port, 0, 0))//链接
//	{
//		//mysql_real_query(&mysql, select, strlen(select));
//		if ((ret = mysql_query(&mysql, select)) == 0)
//		{
//			//mysql_use_result();		//通过服务器去查询然后返回结果，会浪费服务器资源
//			//mysql_store_result();		//传查询语句给服务器。存到本地缓存里在去读？ 
//			if (MYSQL_RES *result = mysql_use_result(&mysql))	
//			{
//				while (MYSQL_ROW sql_row = mysql_fetch_row(result))
//				{
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name [%s]"), ANSI_TO_TCHAR(sql_row[0])));
//				}
//			}
//		}
//	}
//	else
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "connect failed!");
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
//	}
//
//	ret = mysql_ping(&mysql);
//	if (ret == 0)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "mysql_ping success!");
//	}
//	else
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "mysql_ping failed!");
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
//	}
//
//	mysql_close(&mysql);
//	mysql_library_end();
//}

//------------------------------------------------------------------------------------------------
// void USimpleMySQLLibrary::MySqlMain()
// {
// 	const char *user = "root";
// 	const char *host = "127.0.0.1";//localhost
// 	const char *pawd = "root";
// 	const char *table = "hello";
// 	const uint32 port = 3306;
// 
// 	MYSQL mysql;
// 	mysql_library_init(NULL, NULL, NULL);//保证线程安全
// 	mysql_init(&mysql);//分配内存
// 
// 	my_bool reconnect = 1;
// 	int ret = mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconnect);
// 	int BufSize = 1024 * 1024 * 64;//1MB
// 	//MYSQL_OPT_MAX_ALLOWED_PACKET 64MB
// 	ret = mysql_options(&mysql, MYSQL_OPT_MAX_ALLOWED_PACKET, &BufSize);
// 
// 	char select[] = "SELECT * FROM W";
// 	if (mysql_real_connect(&mysql, host, user, pawd, table, port, 0, 0))//链接
// 	{
// 		
// 		if ((ret = mysql_query(&mysql, select)) == 0)
// 		{
// 			//mysql_field_count(mysql)	//链接成功后connect:获取字段的数量。"SELECT * FROM W"  *里有几个字段
// 			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("fields num: %u"), mysql_field_count(mysql)));
// 
// 			mysql_errno(&mysql);
// 			{
// 				//  1005 : 创建表失败
// 				//	1006 : 创建数据库失败
// 				//	1007 : 数据库已存在，创建数据库失败
// 				//	1008 : 数据库不存在，删除数据库失败
// 				//	1009 : 不能删除数据库文件导致删除数据库失败
// 				//	1010 : 不能删除数据目录导致删除数据库失败
// 				//	1011 : 删除数据库文件失败
// 				//	1012 : 不能读取系统表中的记录
// 				//	1016 : 无法打开文件
// 				//	1020 : 记录已被其他用户修改
// 				//	1021 : 硬盘剩余空间不足，请加大硬盘可用空间
// 				//	1022 : 关键字重复，更改记录失败
// 				//	1023 : 关闭时发生错误
// 				//	1024 : 读文件错误
// 				//	1025 : 更改名字时发生错误
// 				//	1026 : 写文件错误
// 				//	1032 : 记录不存在
// 				//	1036 : 数据表是只读的，不能对它进行修改
// 				//	1037 : 系统内存不足，请重启数据库或重启服务器
// 				//	1038 : 用于排序的内存不足，请增大排序缓冲区
// 				//	1040 : 已到达数据库的最大连接数，请加大数据库可用连接数
// 				//	1041 : 系统内存不足
// 				//	1042 : 无效的主机名
// 				//	1043 : 无效连接
// 				//	1044 : 当前用户没有访问数据库的权限
// 				//	1045 : 不能连接数据库，用户名或密码错误
// 				//	1040 : 最大连接数
// 				//	1048 : 字段不能为空
// 				//	1049 : 数据库不存在
// 				//	1050 : 数据表已存在
// 				//	1051 : 数据表不存在
// 				//	1054 : 字段不存在
// 				//	1065 : 无效的SQL语句，SQL语句为空
// 				//	1081 : 不能建立Socket连接
// 				//	1114 : 数据表已满，不能容纳任何记录
// 				//	1116 : 打开的数据表太多
// 				//	1129 : 数据库出现异常，请重启数据库
// 				//	1130 : 连接数据库失败，没有连接数据库的权限
// 				//	1133 : 数据库用户不存在
// 				//	1141 : 当前用户无权访问数据库
// 				//	1142 : 当前用户无权访问数据表
// 				//	1143 : 当前用户无权访问数据表中的字段
// 				//	1146 : 数据表不存在
// 				//	1147 : 未定义用户对数据表的访问权限
// 				//	1149 : SQL语句语法错误
// 				//	1158 : 网络错误，出现读错误，请检查网络连接状况
// 				//	1159 : 网络错误，读超时，请检查网络连接状况
// 				//	1160 : 网络错误，出现写错误，请检查网络连接状况
// 				//	1161 : 网络错误，写超时，请检查网络连接状况
// 				//	1062 : 字段值重复，入库失败
// 			}
// 			if (MYSQL_RES *result = mysql_use_result(&mysql))	
// 			{
// 				//mysql_num_fields(result)	//获取结果集成功后:获取字段的数量。"SELECT * FROM W"  *里有几个字段
// 				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("fields num: %u"),mysql_num_fields(result)));
// 
// 				while (MYSQL_ROW sql_row = mysql_fetch_row(result))
// 				{
// 					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name [%s]"), ANSI_TO_TCHAR(sql_row[0])));
// 				}
// 			}
// 		}
// 	}
// 	else
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "connect failed!");
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
// 	}
// 
// 	ret = mysql_ping(&mysql);
// 	if (ret == 0)
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "mysql_ping success!");
// 	}
// 	else
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "mysql_ping failed!");
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
// 	}
// 
// 	mysql_close(&mysql);
// 	mysql_library_end();
// }

//------------------------------------mysql_fetch_lengths 获取字段信息的长度--------------------------------------- 

//void USimpleMySQLLibrary::MySqlMain()
//{
//	const char *user = "root";
//	const char *host = "127.0.0.1";//localhost
//	const char *pawd = "root";
//	const char *table = "hello";
//	const uint32 port = 3306;
//
//	MYSQL mysql;
//	mysql_library_init(NULL, NULL, NULL);//保证线程安全
//	mysql_init(&mysql);//分配内存
//
//	my_bool reconnect = 1;
//	int ret = mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconnect);
//	int BufSize = 1024 * 1024 * 64;//1MB
//	//MYSQL_OPT_MAX_ALLOWED_PACKET 64MB
//	ret = mysql_options(&mysql, MYSQL_OPT_MAX_ALLOWED_PACKET, &BufSize);
//
//	char select[] = "SELECT name FROM W";
//	if (mysql_real_connect(&mysql, host, user, pawd, table, port, 0, 0))//链接
//	{
//		if ((ret = mysql_query(&mysql, select)) == 0)
//		{
//			if (MYSQL_RES *result = mysql_use_result(&mysql))
//			{
//				while (MYSQL_ROW sql_row = mysql_fetch_row(result))
//				{
//					unsigned long *len = mysql_fetch_lengths(result);// \0 "renzhai" strlen()
//
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name len [%i]"), *len));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name [%s]"), ANSI_TO_TCHAR(sql_row[0])));
//				}
//			}
//		}
//	}
//	else
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "connect failed!");
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
//	}
//
//	mysql_close(&mysql);
//	mysql_library_end();
//}

//---------------------------------------------------------------------------------------------------------
// void USimpleMySQLLibrary::MySqlMain()
// {
// 	const char *user = "root";
// 	const char *host = "127.0.0.1";//localhost
// 	const char *pawd = "root";
// 	const char *table = "hello";
// 	const uint32 port = 3306;
// 
// 	MYSQL mysql;
// 	mysql_library_init(NULL, NULL, NULL);//保证线程安全
// 	mysql_init(&mysql);//分配内存
// 
// 	my_bool reconnect = 1;
// 	int ret = mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconnect);
// 	int BufSize = 1024 * 1024 * 64;//1MB
// 	//MYSQL_OPT_MAX_ALLOWED_PACKET 64MB
// 	ret = mysql_options(&mysql, MYSQL_OPT_MAX_ALLOWED_PACKET, &BufSize);
// 
// 	char select[] = "SELECT name FROM W";
// 	if (mysql_real_connect(&mysql, host, user, pawd, table, port, 0, 0))//链接
// 	{
// 		if ((ret = mysql_query(&mysql, select)) == 0)
// 		{
// 			if (MYSQL_RES *result = mysql_use_result(&mysql))
// 			{
// 				int num_fields = mysql_num_fields(result);
// 				while (MYSQL_ROW sql_row = mysql_fetch_row(result))
// 				{
// 					for (int i = 0 ;i < num_fields; i++)
// 					{
// 						MYSQL_FIELD *find_sql = mysql_fetch_field_direct(result, i);
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name [%s]"), find_sql->name));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("org_name [%s]"), find_sql->org_name));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("table [%s]"), find_sql->table));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("org_table [%s]"), find_sql->org_table));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("db [%s]"), find_sql->db));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("catalog [%s]"), find_sql->catalog));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("def [%s]]"), find_sql->def));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("length [%i]"), find_sql->length));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("max_length [%i]"), find_sql->max_length));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name_length [%i]"), find_sql->name_length));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("org_name_length [%i]"), find_sql->org_name_length));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("db_length [%i]"), find_sql->db_length));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("catalog_length [%i]"), find_sql->catalog_length));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("flags [%i]"), find_sql->flags));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("def_length [%i]"), find_sql->def_length));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("decimals [%i]"), find_sql->decimals));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("charsetnr [%i]"), find_sql->charsetnr));
// 						GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("enum_field_types [%i]"), find_sql->type));
// 						//enum enum_field_types type; /* Type of field. See mysql_com.h for types */
// 						//void *extension;
// 					}
// 					
// 					unsigned long *len = mysql_fetch_lengths(result);// \0 "renzhai" strlen()
// 
// 					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name len [%i]"), *len));
// 					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name [%s]"), ANSI_TO_TCHAR(sql_row[0])));
// 				}
// 			}
// 		}
// 	}
// 	else
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "connect failed!");
// 		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
// 	}
// 
// 	mysql_close(&mysql);
// 	mysql_library_end();
// }

//------------------------------------与上面一样---------------------------------------------------------------
//
//void USimpleMySQLLibrary::MySqlMain()
//{
//	const char *user = "root";
//	const char *host = "127.0.0.1";//localhost
//	const char *pawd = "root";
//	const char *table = "hello";
//	const uint32 port = 3306;
//
//	MYSQL mysql;
//	mysql_library_init(NULL, NULL, NULL);//保证线程安全
//	mysql_init(&mysql);//分配内存
//
//	my_bool reconnect = 1;
//	int ret = mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconnect);
//	int BufSize = 1024 * 1024 * 64;//1MB
//	//MYSQL_OPT_MAX_ALLOWED_PACKET 64MB
//	ret = mysql_options(&mysql, MYSQL_OPT_MAX_ALLOWED_PACKET, &BufSize);
//
//	char select[] = "SELECT * FROM W";
//	if (mysql_real_connect(&mysql, host, user, pawd, table, port, 0, 0))//链接
//	{
//		if ((ret = mysql_query(&mysql, select)) == 0)
//		{
//			if (MYSQL_RES *result = mysql_use_result(&mysql))
//			{
//				int num_fields = mysql_num_fields(result);
//				MYSQL_FIELD *find_sql_org = mysql_fetch_field(result);
//				for (int i = 0; i < num_fields; i++)
//				{
//					MYSQL_FIELD *find_sql = &find_sql_org[i];
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name [%s]"), find_sql->name));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("org_name [%s]"), find_sql->org_name));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("table [%s]"), find_sql->table));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("org_table [%s]"), find_sql->org_table));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("db [%s]"), find_sql->db));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("catalog [%s]"), find_sql->catalog));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("def [%s]]"), find_sql->def));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("length [%i]"), find_sql->length));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("max_length [%i]"), find_sql->max_length));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("name_length [%i]"), find_sql->name_length));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("org_name_length [%i]"), find_sql->org_name_length));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("db_length [%i]"), find_sql->db_length));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("catalog_length [%i]"), find_sql->catalog_length));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("flags [%i]"), find_sql->flags));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("def_length [%i]"), find_sql->def_length));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("decimals [%i]"), find_sql->decimals));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("charsetnr [%i]"), find_sql->charsetnr));
//					GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, *FString::Printf(TEXT("enum_field_types [%i]"), find_sql->type));
//					//enum enum_field_types type; /* Type of field. See mysql_com.h for types */
//					//void *extension;
//				}
//			}		
//		}
//	}
//	else
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "connect failed!");
//		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mysql_error(&mysql));
//	}
//
//	mysql_close(&mysql);
//	mysql_library_end();
//}
//

