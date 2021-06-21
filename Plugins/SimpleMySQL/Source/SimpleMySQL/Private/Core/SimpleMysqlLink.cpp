#include "Core/SimpleMysqlLink.h"
#include "Core/SimpleMySqlMacro.h"


FSimpleMysqlLink::FSimpleMysqlLink(const FString& InUser, const FString& InHost, const FString& InPawd, const FString& InDB, const uint32 InPort, const FString& InUnix_Socket /*= "\0"*/, const TArray<ESimpleClientFlags> InClientFlag /*= 0*/)
	:User(InUser),
	Host(InHost),
	Pawd(InPawd),
	DB(InDB),
	Unix_Socket(InUnix_Socket),
	Port(InPort),
	ClientFlag(0)
{
	for (auto& Tmp : InClientFlag)
	{
		ClientFlag |= ToMySqlClientFlag(Tmp);
	}

	mysql_library_init(NULL, NULL, NULL);//保证线程安全
	mysql_init(&Mysql);

}

FSimpleMysqlLink::~FSimpleMysqlLink()
{
	mysql_close(&Mysql);
	mysql_library_end();
}


bool FSimpleMysqlLink::GetStoreResult(TArray<FSimpleMysqlResult> &Results, FString &ErrMesg, const FSimpleMysqlDebugResult &Debug /*= FSimpleMysqlDebugResult()*/)
{
	if (MYSQL_RES *Result = mysql_store_result(&Mysql))	//传查询语句给服务器。存到本地缓存里在去读？ 
	{
		GetResult(Result, Results);	//获取查询结果

		if (Debug.bPrintToScreen || Debug.bPrintToLog)
		{
			PrintResult(Results, Debug.bPrintToScreen, Debug.bPrintToLog);	//打印结果集
		}
	}

	ErrMesg = UTF8_TO_TCHAR(mysql_error(&Mysql));

	return ErrMesg.IsEmpty();
}

bool FSimpleMysqlLink::GetUseResult(TArray<FSimpleMysqlResult> &Results, FString &ErrMesg, const FSimpleMysqlDebugResult &Debug /*= FSimpleMysqlDebugResult()*/)
{
	if (MYSQL_RES *Result = mysql_use_result(&Mysql))	//通过服务器去查询然后返回结果，会浪费服务器资源
	{
		GetResult(Result, Results);//获取查询结果

		if (Debug.bPrintToScreen || Debug.bPrintToLog)
		{
			PrintResult(Results, Debug.bPrintToScreen, Debug.bPrintToLog);	//打印结果集
		}
	}

	ErrMesg = UTF8_TO_TCHAR(mysql_error(&Mysql));

	return ErrMesg.IsEmpty();
}


bool FSimpleMysqlLink::QueryLink(const FString& SQL,FString& ErrMesg)
{
	int32 Ret = mysql_ping(&Mysql);
	if (Ret == 0)
	{
		if ((Ret = mysql_query(&Mysql,TCHAR_TO_UTF8(*SQL)))!= 0)
		{
			ErrMesg = UTF8_TO_TCHAR(mysql_error(&Mysql));
			return false;
		}
	}
	else
	{
		if (mysql_real_connect(
			&Mysql,
			TCHAR_TO_UTF8(*Host),
			TCHAR_TO_UTF8(*User),
			TCHAR_TO_UTF8(*Pawd),
			TCHAR_TO_UTF8(*DB),
			Port,
			Unix_Socket == TEXT("") ? 0 : TCHAR_TO_UTF8(*Unix_Socket),
			ClientFlag))//链接
		{
			if ((Ret = mysql_query(&Mysql, TCHAR_TO_UTF8(*SQL))) != 0)
			{
				ErrMesg = UTF8_TO_TCHAR(mysql_error(&Mysql));
				return false;
			}
		}
		else
		{
			ErrMesg = UTF8_TO_TCHAR(mysql_error(&Mysql));
			return false;
		}

	}
	return true;
}

bool FSimpleMysqlLink::QueryLinkStoreResult(const FString& SQL, TArray<FSimpleMysqlResult> &Results, FString& ErrMesg, const FSimpleMysqlDebugResult& Debug)
{
	FString ErrMsgQuery;
	if (QueryLink(SQL, ErrMsgQuery))
	{
		GetStoreResult(Results, ErrMesg, Debug);
	}

	ErrMesg += ErrMsgQuery;

	return ErrMesg.IsEmpty();
}

bool FSimpleMysqlLink::QueryLinkUseResult(const FString& SQL, TArray<FSimpleMysqlResult> &Results, FString& ErrMesg, const FSimpleMysqlDebugResult& Debug)
{
	FString ErrMsgQuery;
	if (QueryLink(SQL, ErrMsgQuery))
	{
		GetUseResult(Results, ErrMesg, Debug);
	}

	ErrMesg += ErrMsgQuery;

	return ErrMesg.IsEmpty();
}

bool FSimpleMysqlLink::CreateDataBase(const FString& DataBaseName, EMysqlCharset Charset, FString& ErrorMsg)
{
	FString SQL = TEXT("CREATE DATABASE ") + DataBaseName + TEXT(";");
	return QueryLink(SQL, ErrorMsg);
}


bool FSimpleMysqlLink::CreateAndSelectDataBase(const FString &DataBaseName, EMysqlCharset Charset, FString &ErrorMsg)
{
	FString CreateDataBaseError;
	if (CreateDataBase(DataBaseName, Charset, CreateDataBaseError))
	{
		SelectNewDB(DataBaseName, ErrorMsg);
	}

	ErrorMsg += CreateDataBaseError;

	return ErrorMsg.IsEmpty();
}

bool FSimpleMysqlLink::DropDataBase(const FString& DataBaseName, FString& ErrorMsg)
{
	FString SQL = TEXT("DROP DATABASE ") + DataBaseName + TEXT(";");
	return QueryLink(SQL, ErrorMsg);
}

//创建表
bool FSimpleMysqlLink::CreateTable(const FString& TableName, const TMap<FString, FMysqlFieldType>& InFields, const TArray<FString>& InPrimaryKeys,const FMysqlCreateTableParam& Param, FString& ErrorMsg)
{
	FString SQL = TEXT("CREATE TABLE `");
	SQL += (TableName + TEXT("`("));

	auto SpawnFieldsString = [&](const TMap<FString, FMysqlFieldType>& InNewFields)
	{
		for (auto& Tmp : InNewFields)
		{
			SQL += TEXT("`") + Tmp.Key + TEXT("` "); //定义字段名字
			SQL += Tmp.Value.ToString() + TEXT(","); //将表的所有字段的参数返回为String
		}
	};

	SpawnFieldsString(InFields);		//创建字段

	//创建主键
	//PRIMARY KEY(1,2,3,4,5,6),
	if (InPrimaryKeys.Num())
	{
		SQL += TEXT("PRIMARY KEY(`");
		for (auto &Tmp : InPrimaryKeys)
		{
			SQL += (Tmp + TEXT(","));
		}

		SQL.RemoveFromEnd(TEXT(","));
		SQL += TEXT("`),");
	}



	SQL.RemoveFromEnd(",");				//删除循环末尾的,符号
	SQL += TEXT(")");

	SQL += Param.ToString();			//设置引擎与字符集

	SQL += ";";


	
	return QueryLink(SQL,ErrorMsg);
}



bool FSimpleMysqlLink::DropTable(const FString& TableName, FString& ErrorMsg)
{
	FString SQL = TEXT("DROP TABLE IF EXISTS ") + TableName + TEXT(";");
	return QueryLink(SQL, ErrorMsg);
}

bool FSimpleMysqlLink::TruncateTable(const FString& TableName, FString& ErrorMsg)
{
	FString SQL = TEXT("TRUNCATE TABLE ") + TableName + TEXT(";");
	return QueryLink(SQL, ErrorMsg);
}

bool FSimpleMysqlLink::DeleteFromTable(const FString& TableName, FString& ErrorMsg)
{
	FString SQL = TEXT("DELETE FROM ") + TableName + TEXT(";");
	return QueryLink(SQL, ErrorMsg);
}

bool FSimpleMysqlLink::OptimiseTable(const FString& TableName, FString& ErrorMsg)
{
	FString SQL = TEXT("OPTIMISE TABLE ") + TableName + TEXT(";");
	return QueryLink(SQL, ErrorMsg);
}

bool FSimpleMysqlLink::DeleteFromTableWhereData(const FString& TableName, const FString& Condition, FString& ErrorMsg)
{
		FString SQL = TEXT("DELETE FROM ") + TableName + TEXT("WHERE ") + Condition + TEXT(";");
		return QueryLink(SQL, ErrorMsg);
}

bool FSimpleMysqlLink::SelectNewDB(const FString &NewDB, FString &ErrMesg)
{
	int32 Ret = mysql_ping(&Mysql);
	if (Ret == 0)
	{
		if (mysql_select_db(&Mysql, TCHAR_TO_UTF8(*NewDB)) == 0)
		{
			DB = NewDB;
			return true;
		}
	}
	else
	{
		if (mysql_real_connect(
			&Mysql,
			TCHAR_TO_UTF8(*Host),
			TCHAR_TO_UTF8(*User),
			TCHAR_TO_UTF8(*Pawd),
			TCHAR_TO_UTF8(*DB),
			Port,
			Unix_Socket == TEXT("") ? 0 : TCHAR_TO_UTF8(*Unix_Socket),
			ClientFlag))//链接
		{
			if (mysql_select_db(&Mysql, TCHAR_TO_UTF8(*NewDB)) == 0)
			{
				DB = NewDB;

				return true;
			}

			ErrMesg = UTF8_TO_TCHAR(mysql_error(&Mysql));
		}
		else
		{
			ErrMesg = UTF8_TO_TCHAR(mysql_error(&Mysql));
		}
	}

	return false;
}

bool FSimpleMysqlLink::PrintResult(const TArray<FSimpleMysqlResult>& Results, bool bPrintToScreen /*= true*/, bool bPrintToLog /*= true*/)
{
	for (auto& Tmp : Results)
	{
		FString RowString;
		for (int i = 0; i < Tmp.Rows.Num(); i++)
		{
			int32 Len = Tmp.Rows[i].Len() / 2;
			int32 AddLen = 10 - Len; //剩余空间的 长度
			RowString += "|";
			for (int j = 0; j < AddLen; j++)
			{
				RowString += " ";
			}

			RowString += Tmp.Rows[i];

			for (int j = 0; j < AddLen; j++)
			{
				RowString += " ";
			}

			Mysql_Printf(*RowString, bPrintToScreen, bPrintToLog, FColor::Red, 100.f);
		}
	}

	return Results.Num() != 0;
}

uint32 FSimpleMysqlLink::ToMySqlClientFlag(ESimpleClientFlags ClientFlags) const
{
	switch (ClientFlags)
	{
	case ESimpleClientFlags::Client_Long_Password:
		return 1;
	case ESimpleClientFlags::Client_Found_Rows:
		return 2;
	case ESimpleClientFlags::Client_Long_Flag:
		return 4;
	case ESimpleClientFlags::Client_Connect_With_db:
		return 8;
	case ESimpleClientFlags::Client_No_Schema:
		return 16;
	case ESimpleClientFlags::Client_Compress:
		return 32;
	case ESimpleClientFlags::Client_ODBC:
		return 64;
	case ESimpleClientFlags::Client_Local_Files:
		return 128;
	case ESimpleClientFlags::Client_Ignore_Space:
		return 256;
	case ESimpleClientFlags::Client_Protocol_41:
		return 512;
	case ESimpleClientFlags::Client_Interactive:
		return 1024;
	case ESimpleClientFlags::Client_SSL:
		return 2048;
	case ESimpleClientFlags::Client_Ignore_Sigpipe:
		return 4096;
	case ESimpleClientFlags::Client_Transactions:
		return 8192;
	case ESimpleClientFlags::Client_Reserved:
		return 16384;
	case ESimpleClientFlags::Client_Reserved2:
		return 32768;
	case ESimpleClientFlags::Client_Multi_Statements:
		return (1UL << 16);
	case ESimpleClientFlags::Client_Multi_Results:
		return (1UL << 17);
	case ESimpleClientFlags::Client_PS_Multi_Results:
		return (1UL << 18);
	}

	return 0;
}


void FSimpleMysqlLink::GetResult(MYSQL_RES *Result, TArray<FSimpleMysqlResult> &Results)
{
	int32 NumRow = mysql_num_fields(Result);
	while (MYSQL_ROW SQLRow = mysql_fetch_row(Result))
	{
		Results.Add(FSimpleMysqlResult());
		FSimpleMysqlResult *R = &Results[Results.Num() - 1];

		FString RowString;
		for (int i = 0; i < NumRow; i++)
		{
			if (SQLRow[i] != NULL)
			{
				R->Rows.Add(ANSI_TO_TCHAR(SQLRow[i]));
			}
			else
			{
				R->Rows.Add(TEXT("NULL"));

			}
		}
	}
}

