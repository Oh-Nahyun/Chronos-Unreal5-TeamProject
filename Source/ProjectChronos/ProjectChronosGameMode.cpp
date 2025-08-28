// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectChronosGameMode.h"
#include "ProjectChronosCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectChronosGameMode::AProjectChronosGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
