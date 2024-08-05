// Fill out your copyright notice in the Description page of Project Settings.


#include "WonbanSpawner.h"

#include "TimerManager.h"
#include "Wonban.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWonbanSpawner::AWonbanSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWonbanSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AWonbanSpawner::SpawnWonban, 3.0f, true);
}

void AWonbanSpawner::SpawnWonban()
{
	SpawnLocation = GetActorLocation() + FVector(20,0,0);
	SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParameters;
	
	AWonban* SpawnedWonban = GetWorld()->SpawnActor<AWonban>(AWonban::StaticClass(), SpawnLocation, SpawnRotation, SpawnParameters);

	if(SpawnedWonban)
	{
		SpawnedWonban->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
	}
}

// Called every frame
void AWonbanSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

