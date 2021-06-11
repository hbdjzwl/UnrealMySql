// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleMysqlLinkType.generated.h"

//Mysql所有的变量类型
UENUM(BlueprintType)
enum class EMysqlVariableType :uint8
{
	MYSQL_DECIMAL							 UMETA(DisplayName = "Decimal"),	//DECIMAL(M,D)/NUMERIC  M > D ? M+ 2 : D+ 2
	MYSQL_TINY								 UMETA(DisplayName = "Small Int"),	//SMALLINT		2 //s
	MYSQL_SHORT								 UMETA(DisplayName = "Short"),		//SHORT			2 //s
	MYSQL_LONG								 UMETA(DisplayName = "integer"),	//INTEGER		4 //s
	MYSQL_FLOAT								 UMETA(DisplayName = "Float"),		//FLOAT			4 //s
	MYSQL_DOUBLE							 UMETA(DisplayName = "Double"),		//DOUBLE/REAL	8 //s
	MYSQL_NULL								 UMETA(DisplayName = "Null"),		//NULL
	MYSQL_TIMESTAMP							 UMETA(DisplayName = "Time Stamp"), //TIMESTAMP		8
	MYSQL_LONGLONG							 UMETA(DisplayName = "Big Int"),	//BIGINT		8 //s
	MYSQL_INT24								 UMETA(DisplayName = "Medium Int"),	//MEDIUMINT		3 //ns
	MYSQL_DATE								 UMETA(DisplayName = "Date"),		//DATE			3
	MYSQL_TIME								 UMETA(DisplayName = "Time"),		//TIME			3
	MYSQL_DATETIME							 UMETA(DisplayName = "Date Time"),	//DATETIME		8
	MYSQL_YEAR								 UMETA(DisplayName = "Year"),		//YEAR			1
	MYSQL_NEWDATE							 UMETA(DisplayName = "New Date"),	//NEWDATE
	MYSQL_VARCHAR							 UMETA(DisplayName = "Varchar"),	//VARCHAR
	MYSQL_BIT								 UMETA(DisplayName = "Bit"),		//BIT(M)			
	MYSQL_TIMESTAMP2						 UMETA(DisplayName = "Time Stamp2"),
	MYSQL_DATETIME2							 UMETA(DisplayName = "Date Time2"),
	MYSQL_TIME2								 UMETA(DisplayName = "Time2"),
	MYSQL_JSON = 245				 UMETA(DisplayName = "Json"),		//@@
	MYSQL_NEWDECIMAL = 246				 UMETA(DisplayName = "New Decimal"),//
	MYSQL_ENUM = 247				 UMETA(DisplayName = "Enum"),		//				1 or 2   65535个
	MYSQL_SET = 248				 UMETA(DisplayName = "Set"),		//				1,2,4,8
	MYSQL_TINY_BLOB = 249				 UMETA(DisplayName = "Tiny Blob"),  //@@				//s
	MYSQL_MEDIUM_BLOB = 250				 UMETA(DisplayName = "Medium Blob"),//@@				//s
	MYSQL_LONG_BLOB = 251				 UMETA(DisplayName = "Long Blob"),	//@@				//s
	MYSQL_BLOB = 252				 UMETA(DisplayName = "Blob"),		//@@ 				//s
	MYSQL_VAR_STRING = 253				 UMETA(DisplayName = "VarString"),	//@@ //VARCHAR
	MYSQL_STRING = 254				 UMETA(DisplayName = "String"),		//@@ //CHAR/VARCHAR 
	MYSQL_GEOMETRY = 255				 UMETA(DisplayName = "Geometry"),	//   Geometry(PINT(经度 维度)) 
};

//UENUM(BlueprintType)
enum EModificationVariableType
{
	Mysql_NONE		UMETA(DisplayName = "None"),
	Mysql_unsigned	UMETA(DisplayName = "unsigned")
};

//存储引擎类型
UENUM(BlueprintType)
enum class EMysqlSaveEngine :uint8
{
	//___________________________________________________________________________________________________________________________________
	//Engine			//|Comment														 |Support	| Transactions  |XA		|Savepoints	|			
	//____________________|_______________________________________________________________________________________________________________
	InnoDB,				//|Supports transactions, row-level locking, and foreign keys	 |	YES		|	YES			|YES	|	YES		|
	MyISAM,				//|MyISAM storage engine										 |	DEFAULT	|	NO			|NO		|	NO		|
	MEMORY,				//|Hash based, stored in memory, useful for temporary tables	 |	YES		|	NO			|NO		|	NO		|
	ARCHIVE,			//|Archive storage engine										 |	YES		|	NO			|NO		|	NO		|
	CSV,				//|CSV storage engine											 |	YES		|	NO			|NO		|	NO		|
	PERFORMANCE_SCHEMA,	//|Performance Schema											 |	YES		|	NO			|NO		|	NO		|
	MRG_MYISAM,			//|Collection of identical MyISAM tables						 |	YES		|	NO			|NO		|	NO		|
	BLACKHOLE,			//|/dev/null storage engine (anything you write to it disappears)|	YES		|	NO			|NO		|	NO		|
	FEDERATED,			//|Federated MySQL storage engine								 |	NO		|	NULL		|NULL	|	NULL	|
	//___________________________________________________________________________________________________________________________________
};

//字符集
UENUM(BlueprintType)
enum class EMysqlCharset :uint8
{
	None,
	armscii8,
	ascii,
	big5,
	binary,
	cp1250,
	cp1251,
	cp1256,
	cp1257,
	cp850,
	cp852,
	cp866,
	cp932,
	dec8,
	eucjpms,
	euckr,
	gb2312,
	gbk,
	geostd8,
	greek,
	bebrew,
	hp8,
	keybcs2,
	koi8r,
	koi8u,
	latin1,
	latin2,
	latin5,
	latin7,
	macce,
	macroman,
	sjis,
	swe7,
	tis620,
	ucs2,
	ujis,
	utf16,
	utf32,
	utf8,
	utf8mb4
};

//字段的类型
USTRUCT(BlueprintType)
struct SIMPLEMYSQL_API FMysqlFieldType
{
	GENERATED_USTRUCT_BODY()

		FMysqlFieldType();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|FieldType")
		bool bUnsignedVariable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|FieldType")
		EMysqlVariableType VariableType;	//变量类型

	//UPROPERTY()
		EModificationVariableType ModificationVariableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|FieldType")
		int64 VariableLen;		//变量长度 



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|FieldType")
		int64 DecimalPoint;		//小数(2，3)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|FieldType")
		bool bNULL;				//是否为空

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|FieldType")
		FString DefaultValue;	//默认值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|FieldType")
		bool bAutoIncrement;	//是否自增

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|FieldType")
		FString Comment;

	FString ToString() const;	//转换为String
};



USTRUCT(BlueprintType)
struct SIMPLEMYSQL_API FMysqlCreateTableParam
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|CreateTableParam")
	EMysqlSaveEngine SaveEngine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|CreateTableParam")
	EMysqlCharset Charset;

	FString ToString() const;
};