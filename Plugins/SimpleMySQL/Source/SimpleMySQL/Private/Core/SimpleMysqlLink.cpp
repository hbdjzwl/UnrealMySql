#include "Core/SimpleMysqlLink.h"
FSimpleMysqlLink::FSimpleMysqlLink(const FString& InUser, const FString& InHost, const FString& InPawd, const FString& InDB, const uint32 InPort, const FString& InUnix_Socket /*= "\0"*/, uint16 InClientFlag /*= 0*/)
	:User(InUser),
	Host(InHost),
	Pawd(InPawd),
	DB(InDB),
	Unix_Socket(InUnix_Socket),
	Port(InPort),
	ClientFlag(InClientFlag)
{
	
	mysql_library_init(NULL, NULL, NULL);//保证线程安全
	mysql_init(&Mysql);

	
}

FSimpleMysqlLink::~FSimpleMysqlLink()
{
	mysql_close(&Mysql);
	mysql_library_end();
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

