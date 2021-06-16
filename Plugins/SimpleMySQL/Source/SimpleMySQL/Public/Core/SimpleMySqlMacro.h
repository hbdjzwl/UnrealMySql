#pragma once
// Copyright (C) RenZhai.2020.All Rights Reserved.

#define Mysql_Printf(String,bPrintToSrceen,bPrintToLog,Color,Time) \
if (bPrintToSrceen) \
{GEngine->AddOnScreenDebugMessage(-1, Time, Color, String,false);} \
if (bPrintToLog) \
{UE_LOG(LogTemp, Log,TEXT("%s"),String);}

#define Mysql_Simple_Printf_all(Str) \
Mysql_Printf(Str, true, true, FColor::Red, 100.f);

//#define MysqlFuntionParam TArray<FSimpleMysqlResult>& Results, FString& ErrMesg, EMysqlQuerySaveType SaveType = EMysqlQuerySaveType::STORE_RESULT, const FSimpleMysqlDebugResult& Debug = FSimpleMysqlDebugResult() 
