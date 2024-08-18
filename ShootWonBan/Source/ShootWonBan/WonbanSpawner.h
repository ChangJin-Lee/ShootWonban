// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wonban.h"
#include "GameFramework/Actor.h"
#include "WonbanSpawner.generated.h"

class AShootWonBanPlayerController;

UCLASS()
class SHOOTWONBAN_API AWonbanSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWonbanSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	FRotator SpawnRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	UCurveFloat* ThrowCurve;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	float WonbanScale = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	float WonbanSpeed = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	float WonbanRotationFrequency = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	float WonbanRotationPower = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	float WonbanParabolaHeight = 250.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	FVector WonbanThrowDirectionX = FVector(-1.0f, 1.0f, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	FVector WonbanThrowDirectionY = FVector(-1.0f, 1.0f, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	float WonbanTargetLocationDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	int32 PeiceCount = 7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	float PeicePower = 2000;
	
	
	void ChangeSpeed(float time);

	//Sound
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* WonbanCreatingSound;
	
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* WonbanShootingSound;

	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* WonbanDestroySound;

	void PlaySound(USoundBase* Sound);
	
private:
	FTimerHandle TimerHandle;
	FTimerHandle SoundTimerHandle;
	FTimerHandle SoundTimerHandle2;
	
	void SpawnWonban();

	TSubclassOf<AWonban> WonbanActor;

	UPROPERTY()
	AShootWonBanPlayerController* ShootWonBanPlayerController;
};
