// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootWonBanPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"

void AShootWonBanPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	
	if(HUDWidgetClass != nullptr)
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	
		if(HUDWidget != nullptr)
		{
			HUDWidget -> AddToViewport();
		}
	}
}