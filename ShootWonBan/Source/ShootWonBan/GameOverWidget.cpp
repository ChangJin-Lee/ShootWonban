// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include "ShootWonBanPlayerController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnMainMenuButtonClick);
	}
	
	if(NextStageButton)
	{
		NextStageButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnNextStageButtonClick);
	}
	
	if(QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnQuitGameButtonClick);
	}


	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if(AShootWonBanPlayerController* WonBanPlayerController = Cast<AShootWonBanPlayerController>(PlayerController))
		{
			if(WonBanPlayerController->OpenNextStage() == "")
			{
				NextStageButton->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UGameOverWidget::OnMainMenuButtonClick()
{
	PlayButtonClickSound();
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void UGameOverWidget::OnNextStageButtonClick()
{
	PlayButtonClickSound();
	
	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if(AShootWonBanPlayerController* WonBanPlayerController = Cast<AShootWonBanPlayerController>(PlayerController))
		{
			FString NextLevel = WonBanPlayerController->OpenNextStage();
			UGameplayStatics::OpenLevel(this, FName(*NextLevel));
			
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false; 
		}
	}
}

void UGameOverWidget::OnQuitGameButtonClick()
{
	PlayButtonClickSound();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UGameOverWidget::OnQuitGame, 0.4f, false);
}

void UGameOverWidget::OnQuitGame()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
	}
}
