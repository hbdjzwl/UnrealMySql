#include "Core/SimpleMysqlLinkType.h"

FMysqlFieldType::FMysqlFieldType()
	: ModificationVariableType(EModificationVariableType::Mysql_NONE)
	, VariableType(EMysqlVariableType::MYSQL_LONG)
	, VariableLen(0)
	, DecimalPoint(0)
	, bNULL(true)
	, bAutoIncrement(false)
{

}

FString FMysqlFieldType::ToString() const
{ 
	FString FieldTypeString;

	if (VariableLen > 0 || DecimalPoint > 0)	//变量长度和小数点
	{
		FieldTypeString += TEXT("(") + FString::Printf(TEXT("%lld"), VariableLen) +	
			(DecimalPoint > 0 ? FString::Printf(TEXT(",%lld"), DecimalPoint) : FString("")) + TEXT(")");
	}
	if (bNULL)
	{
		FieldTypeString += TEXT(" NULL");
	}
	else
	{
		FieldTypeString += TEXT(" NOT NULL");
		if (!DefaultValue.IsEmpty())
		{
			FieldTypeString += TEXT(" DEFAULT ") + DefaultValue;
		}

		if (bAutoIncrement)
		{
			FieldTypeString += TEXT(" AUTO_INCREMENT");
		}
	}

	if (!Comment.IsEmpty())
	{
		FieldTypeString += TEXT(" COMMENT '") + Comment + ("'");
	}


	return FieldTypeString;
}

FString FMysqlCreateTableParam::ToString()const
{
	FString Param;

	return Param;
}
