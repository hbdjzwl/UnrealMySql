// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MySQL/mysql.h"

struct  FSimpleMysqlLink
{
	FSimpleMysqlLink(const FString& InUser,
		const FString& InHost,
		const FString& InPawd,
		const FString& InDB,
		const uint32   InPort,
		const FString& InUnix_Socket = "\0",
		uint16 InClientFlag = 0);
	~FSimpleMysqlLink();

	bool QueryLink(const FString& SQL,FString& ErrMesg);

private:
	const FString User;			//用户
	const FString Host;			//localhoust
	const FString Pawd;			//密码
	const FString DB;			//数据库db
	const FString Unix_Socket;//
	const uint32  Port;			//端口
	uint16 ClientFlag;


	MYSQL Mysql;
};


