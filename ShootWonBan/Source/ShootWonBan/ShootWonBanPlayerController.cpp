// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootWonBanPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "ShootWonbanSaveGame.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

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
			UWorld* World = GetWorld();
			if(World)
			{
				FString FullMapName = World->GetMapName();
				FString ShortMapName = FullMapName;

				// 접두사 제거
				const FString Prefix = World->StreamingLevelsPrefix;
				if (FullMapName.StartsWith(Prefix))
				{
					ShortMapName = FullMapName.RightChop(Prefix.Len());
				}
				
				if(ShortMapName != FString("MainMenu"))
				{
					HUDWidget -> AddToViewport();
				}
			}
		}
	}

	if (!UGameplayStatics::DoesSaveGameExist(TEXT("WonbanStageScoreSlot"), 0))
	{
		UShootWonbanSaveGame* SaveGameInstance = Cast<UShootWonbanSaveGame>(UGameplayStatics::CreateSaveGameObject(UShootWonbanSaveGame::StaticClass()));

		if (SaveGameInstance)
		{
			SaveGameInstance->StageClearScore = {10, 15, 20};
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("WonbanStageScoreSlot"), 0);
		}
	}
}

void AShootWonBanPlayerController::SaveHighScore(int32 Score)
{
	UShootWonbanSaveGame* SaveGame = Cast<UShootWonbanSaveGame>(UGameplayStatics::CreateSaveGameObject(UShootWonbanSaveGame::StaticClass()));

	if(SaveGame)
	{
		SaveGame->HighScore = Score;
		UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("WonbanScoreSlot"), 0);
	}
}


int32 AShootWonBanPlayerController::LoadHighScore()
{
	if(UGameplayStatics::DoesSaveGameExist(TEXT("WonbanScoreSlot"), 0))
	{
		UShootWonbanSaveGame* LoadGame = Cast<UShootWonbanSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("WonbanScoreSlot"), 0));

		if(LoadGame)
		{
			return LoadGame->HighScore;
		}
	}

	return -1;
}


void AShootWonBanPlayerController::SetCurrentStageWonbanCount()
{
	
	if(UGameplayStatics::DoesSaveGameExist(TEXT("WonbanStageScoreSlot"), 0))
	{
		UShootWonbanSaveGame* WonbanSaveGame = Cast<UShootWonbanSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("WonbanStageScoreSlot"), 0));

		if(WonbanSaveGame)
		{

			UWorld* World = GetWorld();
			if(World)
			{
				FString FullMapName = World->GetMapName();
				FString ShortMapName = FullMapName;

				// 접두사 제거
				const FString Prefix = World->StreamingLevelsPrefix;
				if (FullMapName.StartsWith(Prefix))
				{
					ShortMapName = FullMapName.RightChop(Prefix.Len());
				}
				
				if(ShortMapName == FString("Stage1"))
				{
					StageClearScore = WonbanSaveGame->StageClearScore[0];
				}
				else if(ShortMapName == FString("Stage2"))
				{
					StageClearScore = WonbanSaveGame->StageClearScore[1];
				}
				else if(ShortMapName == FString("Stage3"))
				{
					StageClearScore = WonbanSaveGame->StageClearScore[2];
				}
				
				UE_LOG(LogTemp, Warning, TEXT("StageClearScore %d"), StageClearScore);

			}
		}
	}
}
