// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMenuWidget.h"
#include "GameOverWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SHOOTWONBAN_API UGameOverWidget : public UMainMenuWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;


protected:
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* NextStageButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;


private:
	UFUNCTION()
	void OnMainMenuButtonClick();

	UFUNCTION()
	void OnNextStageButtonClick();
	
	UFUNCTION()
	void OnQuitGameButtonClick();
	
	FTimerHandle TimerHandle;

	void OnQuitGame();
};
