// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootWonBanProjectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class ABaseWeapon;
class AShootWonBanCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTWONBAN_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	// void SetBaseWeapon(ABaseWeapon* Value) { BaseWeapon = Value; }
	void SetOwnerController(APlayerController* Value) { OwnerController = Value; }
	
protected:
	// /** Ends gameplay for this component. */
	// UFUNCTION()
	// virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	APlayerController* OwnerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AShootWonBanProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Aim, meta=(AllowPrivateAccess = "true"))
	float WeaponRange = 1000.f;
	
	FVector MuzzleLocation;
	FRotator MuzzleRotation;

	FVector CrosshairWorldLocation;
	FVector CrosshairDirection;

	void GetMuzzleLocation();
	bool GetCrossHairLocation(const APlayerController* OwnerController, FVector& WorldLocation, FVector& WorldDirection) const;
};