// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AShootWonBanCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTWONBAN_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();
	
public:
	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AShootWonBanProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	// 총알이 없을 때 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* EmptyAmmoSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(AShootWonBanCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	void SetWeaponAmmo(int32 value);
	int32 GetWeaponAmmo();
	
protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this weapon*/
	AShootWonBanCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Aim, meta=(AllowPrivateAccess = "true"))
	float WeaponRange = 1000.f;

	// Muzzle
	FVector MuzzleLocation;
	FRotator MuzzleRotation;

	// Ammo Count 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Ammo, meta=(AllowPrivateAccess = "true"))
	int32 AmmoCount = 0; 

	void PlaySound(USoundBase* SetSoundBase);
	void PlayAnimation(UAnimMontage* SetAnimation, float PlayRate);
	
	void GetMuzzleLocation(FVector& OutMuzzleLocation);
	bool GetCrossHairLocation(APlayerController* MyPlayerController, FVector& WorldLocation, FVector& WorldDirection) const;
};
