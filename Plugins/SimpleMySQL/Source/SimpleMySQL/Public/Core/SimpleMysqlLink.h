// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "SimpleMysqlLinkType.h"
#include "MySQL/mysql.h"

struct  FSimpleMysqlLink :public TSharedFromThis<FSimpleMysqlLink>
{
	//构造函数初始化 MYSQL 对象
	FSimpleMysqlLink(const FString& InUser,
		const FString& InHost,
		const FString& InPawd,
		const FString& InDB,
		const uint32   InPort,
		const FString& InUnix_Socket = TEXT(""),
		const TArray<ESimpleClientFlags> InClientFlag = TArray<ESimpleClientFlags>());

	~FSimpleMysqlLink();	//析构函数关闭 MYSQL对象




	void InitMysqlOptions() {}


	//创建DB数据库
	bool CreateDataBase(const FString& DataBaseName, EMysqlCharset Charset, FString& ErrorMsg);
	//创建DB数据库并选择
	bool CreateAndSelectDataBase(const FString& DataBaseName, EMysqlCharset Charset, FString& ErrorMsg);
	//删除DB数据库
	bool DropDataBase(const FString& DataBaseName, FString& ErrorMsg);
	//选择数据库
	bool SelectNewDB(const FString& NewDB, FString& ErrMesg);


	//创建表
	bool CreateTable(const FString& TableName, const TMap<FString, FMysqlFieldType>& InFields, const TArray<FString>& InPrimaryKeys, const FMysqlCreateTableParam& Param, FString& ErrorMsg);
	//将表全部删除 释放内存 不支持回滚 Innodb 和 MyISAM 全部清除
	bool DropTable(const FString& TableName, FString& ErrorMsg);
	//清除表 释放内存 不支持回滚 Innodb 和 MyISAM 全部清除
	bool TruncateTable(const FString& TableName, FString& ErrorMsg);
	//可回滚，并没有真正的释放掉内存
	bool DeleteFromTable(const FString& TableName, FString& ErrorMsg);
	//优化表:搭配 DeleteFromTable 用于删除和释放内存
	bool OptimiseTable(const FString& TableName, FString& ErrorMsg);
	//条件删除表
	bool DeleteFromTableWhereData(const FString& TableName, const TArray<FSimpleMysqlComparisonOperator>& Condition, FString& ErrorMsg);


	
	//更新表数据
	bool UpdateTableData(const FString& TableName, const TArray<FSimpleMysqlAssignment>& InFields, const TArray<FSimpleMysqlComparisonOperator>& Condition, FString& ErrorMsg);


	

	//获取数据库里的数据
	bool GetSelectTableData(EMysqlQuerySaveType SaveType, const FString& TableName, const TArray<FString>& InFields, const FSimpleMysqlQueryParameters& QueryParam, TArray<FSimpleMysqlResult>& Results, FString& ErrorMes, const FSimpleMysqlDebugResult& Debug = FSimpleMysqlDebugResult());
	//快速查询传入的SQL语句
	bool QueryLink(const FString& SQL, FString& ErrMesg);
	//
	bool GetSelectTableDataSQL(FString& SQL, const FString& TableName, const TArray<FString>& InFields, const FSimpleMysqlQueryParameters& QueryParam);
	//打印结果集
	bool PrintResult(const TArray<FSimpleMysqlResult>& Results, bool bPrintToScreen = true, bool bPrintToLog = true);

protected:
	uint32 ToMySqlClientFlag(ESimpleClientFlags ClientFlags) const;
	//获取查询所有行结果
	void GetResult(MYSQL_RES* RES, TArray<FSimpleMysqlResult>& Results);
	bool GetSelectTableDataUR(const FString& TableName, const TArray<FString>& InFields, const FSimpleMysqlQueryParameters& QueryParam, TArray<FSimpleMysqlResult>& Results, FString& ErrorMes, const FSimpleMysqlDebugResult& Debug = FSimpleMysqlDebugResult());
	bool GetSelectTableDataSR(const FString& TableName, const TArray<FString>& InFields, const FSimpleMysqlQueryParameters& QueryParam, TArray<FSimpleMysqlResult>& Results, FString& ErrorMes, const FSimpleMysqlDebugResult& Debug = FSimpleMysqlDebugResult());
private:
	//获取结果集
	bool GetStoreResult(TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, const FSimpleMysqlDebugResult& Debug = FSimpleMysqlDebugResult());
	//获取结果集
	bool GetUseResult(TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, const FSimpleMysqlDebugResult& Debug = FSimpleMysqlDebugResult());
	//查询并获取结果
	bool QueryLinkStoreResult(const FString& SQL, TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, const FSimpleMysqlDebugResult& Debug);
	//查询并获取结果
	bool QueryLinkUseResult(const FString& SQL, TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, const FSimpleMysqlDebugResult& Debug);
private:
	const FString User;			//用户
	const FString Host;			//localhoust
	const FString Pawd;			//密码
		  FString DB;			//数据库db
	const FString Unix_Socket;//
	const uint32  Port;			//端口
	uint16 ClientFlag;


	MYSQL Mysql;				//MySQL官方封装的对象
};


