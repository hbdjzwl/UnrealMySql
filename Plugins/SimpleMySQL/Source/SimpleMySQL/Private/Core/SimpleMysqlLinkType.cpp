#include "Core/SimpleMysqlLinkType.h"
#include "SimpleMySqlAssist.h"

FMysqlFieldType::FMysqlFieldType()
	: bUnsignedVariable(false)
	, VariableType(EMysqlVariableType::MYSQL_int)
	, VariableLen(0)
	, DecimalPoint(0)
	, bNULL(true)
	, bAutoIncrement(false)
{

}

//将表的所有字段的参数返回为String
FString FMysqlFieldType::ToString() const
{ 
	//Name INT NOT NULL AUTO_INCREMENT
	UEnum *MysqlVariableEnum = StaticEnum<EMysqlVariableType>();
	FString FieldTypeString = MysqlVariableEnum->GetNameStringByIndex((int32)VariableType);

	FieldTypeString.RemoveFromStart(TEXT("MYSQL_")); //获取枚举字段对应的mysql数据类型

	if (VariableLen > 0 || DecimalPoint > 0)	//字段变量长度和小数点
	{
		// "... float(15.3)"  MySql类型的长度
		FieldTypeString += TEXT("(") + FString::Printf(TEXT("%lld"), VariableLen) +	
			(DecimalPoint > 0 ? FString::Printf(TEXT(",%lld"), DecimalPoint) : FString("")) + TEXT(")");
	}

	if (bUnsignedVariable)	//是否是无符号
	{
		FieldTypeString += TEXT(" UNSIGNED");
	}

	if (bNULL)	
	{
		FieldTypeString += TEXT(" NULL");	//值为空
	}
	else
	{	
		FieldTypeString += TEXT(" NOT NULL");	//值不为空

		if (!DefaultValue.IsEmpty())
		{
			FieldTypeString += TEXT(" DEFAULT ") + DefaultValue;	//默认值
		}

		if (bAutoIncrement)
		{
			FieldTypeString += TEXT(" AUTO_INCREMENT");	//自增
		}
	}

	if (!Comment.IsEmpty())
	{
		FieldTypeString += TEXT(" COMMENT '") + Comment + ("'");	//提示
	}


	return FieldTypeString;
}

FString FMysqlCreateTableParam::ToString()const
{
	FString Param;
	UEnum *SaveEngineEnum = StaticEnum<EMysqlSaveEngine>();
	FString SaveEngineString = SaveEngineEnum->GetNameStringByIndex((int32)SaveEngine);
	Param += (TEXT(" ENGINE=") + SaveEngineString);

	UEnum *CharsetEnum = StaticEnum<EMysqlCharset>();
	FString CharsetString = CharsetEnum->GetNameStringByIndex((int32)Charset);
	Param += (TEXT(" DEFAULT CHARSET=") + CharsetString);

	return Param;
}

FSimpleMysqlDebugResult::FSimpleMysqlDebugResult()
	:bPrintToScreen(false)
	,bPrintToLog(false)
{

}

FSimpleMysqlQueryParameters::FSimpleMysqlQueryParameters()
	:bDistinct(false)
	,Limit(FVector2D::ZeroVector)
	,bWithRollup(false)

{

}

FSimpleMysqlQueryOrderBy::FSimpleMysqlQueryOrderBy()
	:bDesc(false)
{

}

FSimpleMysqlJoinParameters::FSimpleMysqlJoinParameters()
	: JoinType(EMysqlJoinType::NONE)
{

}

FString FSimpleMysqlJoinParameters::ToString() const
{
	FString SQL;
	if (JoinType != EMysqlJoinType::NONE)
	{
		UEnum* MysqlJoinTypeEnum = StaticEnum<EMysqlJoinType>();
		SQL += MysqlJoinTypeEnum->GetNameStringByIndex((int32)JoinType) + TEXT(" JOIN ");

		SQL += TableName + TEXT(" ON ") + Condition;//hp.id = eee.age
	}

	return SQL;
}

FSimpleMysqlAssignment::FSimpleMysqlAssignment()
	:ComparisonOperator(EMysqlComparisonOperator::EQUAL)
{

}

FString FSimpleMysqlAssignment::ToString() const
{
	FString SQL;
	if (!InFieldName.IsEmpty())
	{
		SQL += InFieldName + TEXT(" ") + SimpleMysqlAssist::ComparisonOperatorToString(ComparisonOperator) + TEXT(" '") + Value + TEXT("'");
	}

	return SQL;
}
