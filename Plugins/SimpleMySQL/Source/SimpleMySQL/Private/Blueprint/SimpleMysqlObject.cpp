// Copyright (C) RenZhai.2020.All Rights Reserved.


#include "Blueprint/SimpleMysqlObject.h"

USimpleMysqlObject::USimpleMysqlObject()
{

}

void USimpleMysqlObject::InitMysql(
	const FString &InUser,
	const FString &InHost, 
	const FString &InPawd, 
	const FString &InDB,
	const uint32 InPort, 
	const FString &Unix_Socket /* =TEXT("")*/,
	const TArray<ESimpleClientFlags>& InClientFlag /* = ()*/)
{
	Link = MakeShareable(new FSimpleMysqlLink(InUser, InHost, InPawd, InDB, InPort, Unix_Socket, InClientFlag));
}

TSharedRef<FSimpleMysqlLink> USimpleMysqlObject::GetLink()
{
	return Link.ToSharedRef();
}
