// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../../EpicGames/UE_5.4/Engine/Source/Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Wonban.generated.h"

UCLASS()
class SHOOTWONBAN_API AWonban : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWonban();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Wonban")
	USceneComponent* WonbanSceneComponent;

	UPROPERTY(EditAnywhere, Category="Wonban")
	UStaticMeshComponent* WonbanMeshComponent;

	void InitializeThrow(UCurveFloat* Curve);

	// wonban 특성
	float RotationFrequency;
	float RotationPower;
	float ParabolaHeight;
	FVector ThrowDirection;
	FVector TargetLocation;
	int32 PeiceCount;
	float PeicePower;

	//Sound
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* WonbanDestroySound;
	
private:
	FVector InitialLocation;
	FVector MovementDirection;
	
	FTimeline ThrowTimeline;

	UFUNCTION()
	void HandleThrowProgress(float Value);

	UFUNCTION()
	void OnThrowTimelinFinished();

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	
	void SetupThrowTimeline(UCurveFloat* Curve);

	void SpawnBrokenPieces();
};
