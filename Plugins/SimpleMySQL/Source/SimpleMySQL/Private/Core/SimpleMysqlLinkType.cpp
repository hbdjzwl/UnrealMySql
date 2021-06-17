#include "Core/SimpleMysqlLinkType.h"

FMysqlFieldType::FMysqlFieldType()
	: bUnsignedVariable(false)
	, VariableType(EMysqlVariableType::MYSQL_int)
	, VariableLen(0)
	, DecimalPoint(0)
	, bNULL(true)
	, bAutoIncrement(false)
{

}

FString FMysqlFieldType::ToString() const
{ 
	//Name INT NOT NULL AUTO_INCREMENT
	UEnum *MysqlVariableEnum = StaticEnum<EMysqlVariableType>();
	FString FieldTypeString = MysqlVariableEnum->GetNameStringByIndex((int32)VariableType);

	FieldTypeString.RemoveFromStart(TEXT("MYSQL_"));
	if (VariableLen > 0 || DecimalPoint > 0)	//变量长度和小数点
	{
		FieldTypeString += TEXT("(") + FString::Printf(TEXT("%lld"), VariableLen) +	
			(DecimalPoint > 0 ? FString::Printf(TEXT(",%lld"), DecimalPoint) : FString("")) + TEXT(")");
	}

	if (bUnsignedVariable)
	{
		FieldTypeString += TEXT(" UNSIGNED");
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
