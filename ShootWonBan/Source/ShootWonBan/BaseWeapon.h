// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class AShootWonBanCharacter;
class UTP_WeaponComponent;
class UTP_PickUpComponent;

UCLASS()
class SHOOTWONBAN_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	UFUNCTION()
	void Fire(int32 AmmoCount);
	
protected:

	UFUNCTION()
	void AttachWeapon(AShootWonBanCharacter* ShootWonBanCharacter);
	
	/** The Character holding this weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapon, meta = (AllowPrivateAccess = "true"))
	AShootWonBanCharacter* Character;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapon, meta = (AllowPrivateAccess = "true"))
	UTP_PickUpComponent* PickUpComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapon, meta = (AllowPrivateAccess = "true"))
	UTP_WeaponComponent* WeaponComponent;
	
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Sound, meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound;

	// 총알이 없을 때 사운드
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Sound, meta = (AllowPrivateAccess = "true"))
	USoundBase* EmptyAmmoSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapon, meta=(AllowPrivateAccess = "true"))
	float WeaponRange = 1000.f;
	
	void PlaySound(USoundBase* SetSoundBase) const;
	void PlayAnimation(UAnimMontage* SetAnimation, float PlayRate) const;
};
