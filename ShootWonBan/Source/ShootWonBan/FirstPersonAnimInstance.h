// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootWonBanCharacter.h"
#include "Animation/AnimInstance.h"
#include "FirstPersonAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTWONBAN_API UFirstPersonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInAir;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AShootWonBanCharacter* FirstPersonCharacter;
	
};
