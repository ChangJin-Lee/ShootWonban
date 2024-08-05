// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootWonBanGameMode.h"
#include "ShootWonBanCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootWonBanGameMode::AShootWonBanGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
