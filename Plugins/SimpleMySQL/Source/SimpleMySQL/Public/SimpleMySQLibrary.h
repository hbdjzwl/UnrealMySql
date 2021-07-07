// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Core/SimpleMysqlLink.h"
#include "SimpleMySQLibrary.generated.h"

class USimpleMysqlObject;

UCLASS(meta = (BlueprintThreadSafe, ScriptName = "MySQLLibrary"))
class SIMPLEMYSQL_API USimpleMySQLLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (Keywords = "SimpleMySQL sample test testing"), Category = "SimpleMySQLTesting")
		static void MySqlMain();

	//Mysql对象操作
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "SimpleMySQL"))
		static USimpleMysqlObject* CreateMysqlObject(
			UObject* WorldContextObject,
			const FString &InUser,
			const FString &InHost,
			const FString &InPawd,
			const FString &InDB,
			const int32  InPort,
			const TArray<ESimpleClientFlags>& InClientFlag,
			const FString &Unix_Socket = TEXT("")
			);

	/////////////////////////////////////////数据库操作//////////////////////////////////////////////
	//创建数据库DB
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
	static bool CreateDataBase(USimpleMysqlObject* Object, const FString& DataBaseName, EMysqlCharset Charset, FString& ErrorMsg);
	//创建并选择数据库DB
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
	static bool CreateAndSelectDataBase(USimpleMysqlObject* Object, const FString& DataBaseName, EMysqlCharset Charset, FString& ErrorMsg);
	//选择数据库DB
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
	static bool SelectNewDB(USimpleMysqlObject* Object, const FString& NewDB, FString& ErrMesg);
	//删除数据库DB
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
	static bool DropDataBase(USimpleMysqlObject* Object, const FString& DataBaseName, FString& ErrorMsg);


	/////////////////////////////////////////表操作//////////////////////////////////////////////
	//创建表
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
		static bool CreateTable(USimpleMysqlObject* Object, const FString& TableName, const TMap<FString, FMysqlFieldType>& InFields, const TArray<FString>& InPrimaryKeys, const FMysqlCreateTableParam& Param, FString& ErrorMsg);
	//将表全部删除 释放内存 不支持回滚 Innodb 和 MyISAM 全部清除
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
		static bool DropTable(USimpleMysqlObject* Object, const FString& TableName, FString& ErrorMsg);
	//清除表 释放内存 不支持回滚 Innodb 和 MyISAM 全部清除
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
		static bool TruncateTable(USimpleMysqlObject* Object, const FString& TableName, FString& ErrorMsg);
	//可回滚，并没有真正的释放掉内存
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
		static bool DeleteFromTable(USimpleMysqlObject* Object, const FString& TableName, FString& ErrorMsg);
	//搭配 DeleteFromTable 用于删除和释放内存
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
		static bool OptimiseTable(USimpleMysqlObject* Object, const FString& TableName, FString& ErrorMsg);
	//条件删除表
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
		static bool DeleteFromTableWhereData(USimpleMysqlObject* Object, const FString& TableName, const TArray<FSimpleMysqlComparisonOperator>& Condition, FString& ErrorMsg);



	/////////////////////////////////////////查询打印//////////////////////////////////////////////
	
	//快速查询传入的SQL语句
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
	static bool GetSelectTableData(USimpleMysqlObject* Object,EMysqlQuerySaveType SaveType, const FString& TableName, const TArray<FString>& InFields, const FSimpleMysqlQueryParameters& QueryParam, TArray<FSimpleMysqlResult>& Results, FString& ErrorMes, const FSimpleMysqlDebugResult& Debug);

	//
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
	static bool GetSelectTableDataSQL(USimpleMysqlObject* Object, FString& SQL, const FString& TableName, const TArray<FString>& InFields, const FSimpleMysqlQueryParameters& QueryParam);

	//快速查询
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
	static bool QueryLink(USimpleMysqlObject *Object, const FString &SQL, FString &ErrMesg);
	
	//打印结果集
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
	static bool PrintResult(USimpleMysqlObject *Object, const TArray<FSimpleMysqlResult>& Results, bool bPrintToScreen = true, bool bPrintToLog = true);






	/////////////////////////////////////////更新//////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
	static bool UpdateTableData(USimpleMysqlObject* Object, const FString& TableName, const TArray<FSimpleMysqlAssignment>& InFields, const TArray<FSimpleMysqlComparisonOperator>& Condition, FString& ErrorMsg);

	UFUNCTION(BlueprintCallable, meta = (Category = "SimpleMySQL"))
	static bool ReplaceTableData(USimpleMysqlObject* Object, const FString& TableName, const TArray<FSimpleMysqlReplaceParameters>& InReplaces, const TArray<FSimpleMysqlComparisonOperator>& Condition, FString& ErrorMsg);




	//////////////////////////////////////// 返回NULL值 ////////////////////////////////////////
	//返回空值
	UFUNCTION(BlueprintCallable, BlueprintPure ,meta = (Category = "SimpleMySQL|NULL"))
	static TArray<FString> GetStringNULLArray();
	//
	UFUNCTION(BlueprintCallable, BlueprintPure , meta = (Category = "SimpleMySQL|NULL"))
	static TArray<FSimpleMysqlQueryOrderBy> GetOrderByNULLArray();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "SimpleMySQL|NULL"))
	static TArray<FSimpleMysqlJoinParameters> GetJoinParamNULLArray();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "SimpleMySQL|NULL"))
	static TArray<FSimpleMysqlComparisonOperator> GetComparisonOperatorNULLArray();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "SimpleMySQL|NULL"))
	static TArray<FSimpleMysqlReplaceParameters> GetReplaceParametersNULLArray();
};