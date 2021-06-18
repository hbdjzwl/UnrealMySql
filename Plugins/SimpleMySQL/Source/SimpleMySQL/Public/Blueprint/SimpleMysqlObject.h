// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/SimpleMysqlLink.h"
#include "SimpleMysqlObject.generated.h"


/**
 * UE4的C++类封装了原生的Mysql类(FSimpleMysqlLink)，方便蓝图调用。
 */
UCLASS(Blueprintable,BlueprintType)
class SIMPLEMYSQL_API USimpleMysqlObject : public UObject
{
	GENERATED_BODY()

public:
	USimpleMysqlObject();

	void InitMysql(const FString &InUser,
		const FString &InHost,
		const FString &InPawd,
		const FString &InDB,
		const uint32  InPort,
		const FString &Unix_Socket = TEXT(""),
		const TArray<ESimpleClientFlags>& InClientFlag = TArray<ESimpleClientFlags>());

	TSharedRef<FSimpleMysqlLink> GetLink();
private:
	TSharedPtr<FSimpleMysqlLink> Link;
};
