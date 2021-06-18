// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "SimpleMysqlLinkType.generated.h"

//Mysql所有的变量类型
UENUM(BlueprintType)
enum class EMysqlVariableType :uint8
{
	MYSQL_tinyint								UMETA(DisplayName = "tinyint"),
	MYSQL_smallint								UMETA(DisplayName = "smallint"),
	MYSQL_mediumint								UMETA(DisplayName = "mediumint"),
	MYSQL_int									UMETA(DisplayName = "int"),
	MYSQL_integer								UMETA(DisplayName = "integer"),
	MYSQL_bigint								UMETA(DisplayName = "bigint"),
	MYSQL_bit									UMETA(DisplayName = "bit"),
	MYSQL_real									UMETA(DisplayName = "real"),
	MYSQL_double								UMETA(DisplayName = "double"),	
	MYSQL_float									UMETA(DisplayName = "float"),	
	MYSQL_decimal								UMETA(DisplayName = "decimal"),
	MYSQL_numeric								UMETA(DisplayName = "numeric"),
	MYSQL_char									UMETA(DisplayName = "char"),
	MYSQL_varchar								UMETA(DisplayName = "varchar"),
	MYSQL_date									UMETA(DisplayName = "date"),
	MYSQL_time									UMETA(DisplayName = "time"),
	MYSQL_year									UMETA(DisplayName = "year"),
	MYSQL_timestamp								UMETA(DisplayName = "timestamp"),
	MYSQL_datetime								UMETA(DisplayName = "datetime"),
	MYSQL_tinyblob								UMETA(DisplayName = "tinyblob"),
	MYSQL_blob									UMETA(DisplayName = "blob"),
	MYSQL_mediumblob							UMETA(DisplayName = "mediumblob"),
	MYSQL_longblob								UMETA(DisplayName = "longblob"),
	MYSQL_tinytext								UMETA(DisplayName = "tinytext"),
	MYSQL_text									UMETA(DisplayName = "text"),
	MYSQL_mediumtext							UMETA(DisplayName = "mediumtext"),
	MYSQL_longtext								UMETA(DisplayName = "longtext"),
	MYSQL_enum									UMETA(DisplayName = "enum"),
	MYSQL_set									UMETA(DisplayName = "set"),
	MYSQL_binary								UMETA(DisplayName = "binary"),
	MYSQL_varbinary								UMETA(DisplayName = "varbinary"),
	MYSQL_point									UMETA(DisplayName = "point"),
	MYSQL_linestring							UMETA(DisplayName = "linestring"),
	MYSQL_polygon								UMETA(DisplayName = "polygon"),
	MYSQL_geometry								UMETA(DisplayName = "geometry"),
	MYSQL_multipoint							UMETA(DisplayName = "multipoint"),
	MYSQL_multilinestring						UMETA(DisplayName = "multilinestring"),
	MYSQL_multipolygon							UMETA(DisplayName = "multipolygon"),
	MYSQL_geometrycollection					UMETA(DisplayName = "geometrycollection"),
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


UENUM(BlueprintType)
enum class ESimpleClientFlags :uint8
{
	Client_None,
	Client_Long_Password,			/* new more secure passwords */
	Client_Found_Rows,				/* Found instead of affected rows */
	Client_Long_Flag,				/* Get all column flags */
	Client_Connect_With_db,			/* One can specify db on connect */
	Client_No_Schema,				/* Don't allow database.table.column */
	Client_Compress,				/* Can use compression protocol */
	Client_ODBC,					/* Odbc client */
	Client_Local_Files,				/* Can use LOAD DATA LOCAL */
	Client_Ignore_Space,			/* Ignore spaces before '(' */
	Client_Protocol_41,				/* New 4.1 protocol */
	Client_Interactive,				/* This is an interactive client */
	Client_SSL,						/* Switch to SSL after handshake */
	Client_Ignore_Sigpipe,			/* IGNORE sigpipes */
	Client_Transactions,			/* Client knows about transactions */
	Client_Reserved,				/* Old flag for 4.1 protocol  */
	Client_Reserved2,				/* Old flag for 4.1 authentication */
	Client_Multi_Statements,		/* Enable/disable multi-stmt support */
	Client_Multi_Results,			/* Enable/disable multi-results */
	Client_PS_Multi_Results,		/* Multi-results in PS-protocol */
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


//引擎和字符集
USTRUCT(BlueprintType)
struct SIMPLEMYSQL_API FMysqlCreateTableParam
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|CreateTableParam")
	EMysqlSaveEngine SaveEngine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|CreateTableParam")
	EMysqlCharset Charset;

	FString ToString() const;	////创建表时:设置存储引擎和字符集
};

//获取查询的所有行信息
USTRUCT(BlueprintType)
struct SIMPLEMYSQL_API FSimpleMysqlResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|MysqlResult")
	TArray<FString> Rows;
};

//打印调试
USTRUCT(BlueprintType)
struct SIMPLEMYSQL_API FSimpleMysqlDebugResult
{
	GENERATED_USTRUCT_BODY()
		 
		FSimpleMysqlDebugResult();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|DebugResult", meta = (EditCondition = "bDebug"))
		bool bPrintToScreen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimpleMySQL|DebugResult", meta = (EditCondition = "bDebug"))
		bool bPrintToLog;
};
