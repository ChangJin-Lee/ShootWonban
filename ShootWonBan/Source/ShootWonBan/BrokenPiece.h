// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrokenPiece.generated.h"

UCLASS()
class SHOOTWONBAN_API ABrokenPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrokenPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Wonban")
	USceneComponent* PieceSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Piece")
	UStaticMeshComponent* BrokenPieceMesh;
};
