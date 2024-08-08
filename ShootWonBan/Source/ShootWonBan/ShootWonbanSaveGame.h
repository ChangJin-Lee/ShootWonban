// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ShootWonbanSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTWONBAN_API UShootWonbanSaveGame : public USaveGame
{
	GENERATED_BODY()

	UShootWonbanSaveGame();

public:
	UPROPERTY(VisibleAnywhere, Category="Score")
	int32 HighScore;

	UPROPERTY(VisibleAnywhere, Category="StageClearCondition")
	TArray<int32> StageClearScore;
};
