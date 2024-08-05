// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../../EpicGames/UE_5.4/Engine/Source/Runtime/Engine/Classes/Engine/StaticMesh.h"
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
	UStaticMeshComponent* WonbanMeshComponent;

private:
	FVector MovementDirection;
	float MovementSpeed;
};
