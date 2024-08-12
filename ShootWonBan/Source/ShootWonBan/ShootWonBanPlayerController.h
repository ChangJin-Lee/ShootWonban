// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootWonBanPlayerController.generated.h"

class UInputMappingContext;
/**
 *
 */
UCLASS()
class SHOOTWONBAN_API AShootWonBanPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDWidgetClass;
	
	UPROPERTY()
	UUserWidget* HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	
	UPROPERTY()
	UUserWidget* GameOverWidget;

public:

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentScore;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentWonbanCount;
	
	UPROPERTY(BlueprintReadWrite)
	int32 StageClearScore = 1000;
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentStageWonbanCount();
	
	UFUNCTION(BlueprintCallable)
	void SaveHighScore(int32 Score);
	
	UFUNCTION(BlueprintCallable)
	int32 LoadHighScore();

	UFUNCTION(BlueprintCallable)
	void DestoryHUD();

	UFUNCTION(BlueprintCallable)
	FString GetCurrentStageName();

	UUserWidget* CreateUIWidget(TSubclassOf<UUserWidget> WidgetClass);
	void CreateGameOverWidget();

	UFUNCTION(BlueprintCallable)
	FString OpenNextStage();
};
