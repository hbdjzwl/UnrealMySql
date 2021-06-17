// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "SimpleMysqlLinkType.h"
#include "MySQL/mysql.h"

struct  FSimpleMysqlLink :public TSharedFromThis<FSimpleMysqlLink>
{
	FSimpleMysqlLink(const FString& InUser,
		const FString& InHost,
		const FString& InPawd,
		const FString& InDB,
		const uint32   InPort,
		const FString& InUnix_Socket = TEXT(""),
		const TArray<ESimpleClientFlags> InClientFlag = TArray<ESimpleClientFlags>());

	~FSimpleMysqlLink();

	void InitMysqlOptions() {}

	bool GetStoreResult(TArray<FSimpleMysqlResult> &Results, FString &ErrMesg, const FSimpleMysqlDebugResult &Debug = FSimpleMysqlDebugResult());

	bool GetUseResult(TArray<FSimpleMysqlResult> &Results, FString &ErrMesg, const FSimpleMysqlDebugResult &Debug = FSimpleMysqlDebugResult());

	//立马查询
	bool QueryLink(const FString& SQL,FString& ErrMesg);

	//
	bool QueryLinkStoreResult(const FString& SQL, TArray<FSimpleMysqlResult> &Results, FString& ErrMesg, const FSimpleMysqlDebugResult& Debug);

	bool QueryLinkUseResult(const FString& SQL, TArray<FSimpleMysqlResult> &Results, FString& ErrMesg, const FSimpleMysqlDebugResult& Debug);

	bool CreateDataBase(const FString& DataBaseName, EMysqlCharset Charset, FString& ErrorMsg);

	bool CreateAndSelectDataBase(const FString &DataBaseName, EMysqlCharset Charset, FString &ErrorMsg);

	bool DropDataBase(const FString& DataBaseName, FString& ErrorMsg);

	//创建表
	bool CreateTable(const FString& TableName, const TMap<FString, FMysqlFieldType>& InFields, const TArray<FString>& InPrimaryKeys, const FMysqlCreateTableParam& Param, FString& ErrorMsg);
	
	//设置选择表
	bool SelectNewDB(const FString &NewDB, FString &ErrMesg);

	//打印结果集
	bool PrintResult(const TArray<FSimpleMysqlResult>& Results, bool bPrintToScreen = true, bool bPrintToLog = true);

protected:
	uint32 ToMySqlClientFlag(ESimpleClientFlags ClientFlags) const;

	//获取查询结果
	void GetResult(MYSQL_RES *RES, TArray<FSimpleMysqlResult> &Results);
private:
	const FString User;			//用户
	const FString Host;			//localhoust
	const FString Pawd;			//密码
		  FString DB;			//数据库db
	const FString Unix_Socket;//
	const uint32  Port;			//端口
	uint16 ClientFlag;


	MYSQL Mysql;
};


