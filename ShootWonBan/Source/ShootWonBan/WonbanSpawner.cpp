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
		SpawnedWonban->SetActorScale3D(FVector(WonbanScale, WonbanScale, WonbanScale/5));
		SpawnedWonban->RotationFrequency = FMath::RandRange(WonbanRotationFrequency * 0.8, WonbanRotationFrequency * 1.2);
		SpawnedWonban->RotationPower = FMath::RandRange(WonbanRotationPower * 0.8, WonbanRotationPower * 1.2);
		SpawnedWonban->ParabolaHeight = FMath::RandRange(WonbanParabolaHeight * 0.8, WonbanParabolaHeight * 1.2);
		SpawnedWonban->ThrowDirection = FVector(FMath::RandRange(WonbanThrowDirectionX.X, WonbanThrowDirectionX.Y),FMath::RandRange(WonbanThrowDirectionY.X, WonbanThrowDirectionY.Y),0.0f).GetSafeNormal();
		SpawnedWonban->TargetLocation = SpawnedWonban->ThrowDirection * WonbanTargetLocationDistance;
		SpawnedWonban->InitializeThrow(ThrowCurve);
		SpawnedWonban->SetLifeSpan(60);
	}
}

// Called every frame
void AWonbanSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

