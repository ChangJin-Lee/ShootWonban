// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ShootWonBanCharacter.generated.h"

class ABaseWeapon;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UCurveFloat;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AShootWonBanCharacter : public ACharacter
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AShootWonBanCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
	//
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	/** Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	/** Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	/** WeaponSlot1 Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* WeaponSlot1;
	
	/** WeaponSlot2 Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* WeaponSlot2;

	/** WeaponSwitching1 Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SwitchWeaponAction1;
	
	/** WeaponSwitching2 Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SwitchWeaponAction2;
	
	UPROPERTY()
	TArray<ABaseWeapon*> Weapons;
	
	UPROPERTY()
	ABaseWeapon* CurrentWeapon;
	

	UPROPERTY(EditAnywhere, Category = Aim, meta = (AllowPrivateAccess = "true"))
	float ZoomedFOV = 60.f;
	
	float DefaultFOV;
	
	UPROPERTY(EditAnywhere, Category = Aim, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* AimCurve = nullptr;
	
	FTimeline AimTimeline;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ammo")
	int32 AmmoCount = 0;

	bool bHasWeapon;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Aim();
	void CancelAim();
	void FireWeapon();
	void GetWeaponSlot1();
	void GetWeaponSlot2();
	void SwitchWeapon1();
	void SwitchWeapon2();
	void ChangeWeaponState(int32 CurrentWeapon, int32 NewWeapon);
	
	int32 CurrentWeaponIndex = 0;
	
public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION()
	void PickUpWeapon(ABaseWeapon* InWeapon);

	UFUNCTION()
	void UpdateZoom(float Value);
	
	void SetAmmo(int32 Value) { AmmoCount = Value; };
	int32 GetAmmo() const { return AmmoCount; }


	// Sound
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* PickUpSound;

	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* ChangeWeaponSound;

	void PlaySound(USoundBase* Sound);
};

