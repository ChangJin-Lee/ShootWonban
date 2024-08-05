// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wonban.h"
#include "GameFramework/Actor.h"
#include "WonbanSpawner.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wonban")
	FRotator SpawnRotation;
	
private:
	FTimerHandle TimerHandle;

	void SpawnWonban();

	TSubclassOf<AWonban> WonbanActor;
};
