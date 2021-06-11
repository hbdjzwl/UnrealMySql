// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MySQL/mysql.h"
#include "SimpleMysqlLinkType.h"

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

	void InitMysqlOptions() {}

	bool QueryLink(const FString& SQL,FString& ErrMesg);


	bool CreateDataBase(const FString& DataBaseName, EMysqlCharset Charset, FString& ErrorMsg);
	bool DropDataBase(const FString& DataBaseName, FString& ErrorMsg);

	//������
	bool CreateTable(const FString& TableName, const TMap<FString, FMysqlFieldType>& InFields, const TMap<FString, FMysqlFieldType>& InPrimaryKeys, const FMysqlCreateTableParam& Param, FString& ErrorMsg);

private:
	const FString User;			//�û�
	const FString Host;			//localhoust
	const FString Pawd;			//����
	const FString DB;			//���ݿ�db
	const FString Unix_Socket;//
	const uint32  Port;			//�˿�
	uint16 ClientFlag;


	MYSQL Mysql;
};

