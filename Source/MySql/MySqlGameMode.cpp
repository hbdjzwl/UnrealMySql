// Copyright Epic Games, Inc. All Rights Reserved.

#include "MySqlGameMode.h"
#include "MySqlCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMySqlGameMode::AMySqlGameMode()
{
	// set default pawn class to our Blueprinted character
// 	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
// 	if (PlayerPawnBPClass.Class != NULL)
// 	{
// 		DefaultPawnClass = PlayerPawnBPClass.Class;
// 	}
}
