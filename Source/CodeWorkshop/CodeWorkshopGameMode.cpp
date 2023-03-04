// Copyright Epic Games, Inc. All Rights Reserved.

#include "CodeWorkshopGameMode.h"
#include "CodeWorkshopCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACodeWorkshopGameMode::ACodeWorkshopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
