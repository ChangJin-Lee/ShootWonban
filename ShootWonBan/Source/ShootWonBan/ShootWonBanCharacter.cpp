// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootWonBanCharacter.h"

#include "BaseWeapon.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FirstPersonAnimInstance.h"
#include "InputActionValue.h"
#include "ShootWonBanPlayerController.h"
#include "Components/TimelineComponent.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "FirstPersonAnimInstance.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AShootWonBanCharacter

AShootWonBanCharacter::AShootWonBanCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	// Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AShootWonBanCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	
	
	// set Default FOV
	DefaultFOV = FirstPersonCameraComponent->FieldOfView;

	if(AimCurve)
	{
		FOnTimelineFloat OnTimelineFloat;
		OnTimelineFloat.BindUFunction(this, FName("UpdateZoom"));
		AimTimeline.AddInterpFloat(AimCurve, OnTimelineFloat);
		AimTimeline.SetLooping(false);
	}
	
	bHasWeapon = false;
	
	if(APlayerController* PlayerController =  UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if(AShootWonBanPlayerController* ShootWonBanPlayerController = Cast<AShootWonBanPlayerController>(PlayerController))
		{
			ShootWonBanPlayerController->SetCurrentStageWonbanCount();
			AmmoCount = ShootWonBanPlayerController->StageClearScore;
		}
	}
}

void AShootWonBanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTimeline.TickTimeline(DeltaTime);
}

//////////////////////////////////////////////////////////////////////////// Input

void AShootWonBanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShootWonBanCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShootWonBanCharacter::Look);

		// Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AShootWonBanCharacter::FireWeapon);

		// Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AShootWonBanCharacter::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AShootWonBanCharacter::CancelAim);

		// Change Weapon Slot 
		EnhancedInputComponent->BindAction(WeaponSlot1, ETriggerEvent::Started, this, &AShootWonBanCharacter::GetWeaponSlot1);
		EnhancedInputComponent->BindAction(WeaponSlot2, ETriggerEvent::Started, this, &AShootWonBanCharacter::GetWeaponSlot2);
		
		// Switching Weapon 
		EnhancedInputComponent->BindAction(SwitchWeaponAction1, ETriggerEvent::Started, this, &AShootWonBanCharacter::SwitchWeapon1);
		EnhancedInputComponent->BindAction(SwitchWeaponAction2, ETriggerEvent::Started, this, &AShootWonBanCharacter::SwitchWeapon2);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AShootWonBanCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AShootWonBanCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AShootWonBanCharacter::Aim()
{
	AimTimeline.Play();
}

void AShootWonBanCharacter::CancelAim()
{
	AimTimeline.Reverse();
}

void AShootWonBanCharacter::UpdateZoom(float Value)
{
	float TargetFOV = FMath::Lerp(DefaultFOV, ZoomedFOV, Value);
	FirstPersonCameraComponent->SetFieldOfView(TargetFOV);
}

void AShootWonBanCharacter::FireWeapon()
{
	if(CurrentWeapon == nullptr)
	{
		return;
	}

	CurrentWeapon->Fire(AmmoCount);
	
	if(AmmoCount > 0)
	{
		AmmoCount--;
	}
}

void AShootWonBanCharacter::GetWeaponSlot1()
{
	if(CurrentWeaponIndex == 0)
	{
		return;	
	}	
	
	int32 NewWeaponSlotIndex = 0;
	ChangeWeaponState(CurrentWeaponIndex, NewWeaponSlotIndex);
}

void AShootWonBanCharacter::GetWeaponSlot2()
{
	if(CurrentWeaponIndex == 1 || Weapons.Num() < 2)
	{
		return;	
	}
	
	int32 NewWeaponSlotIndex = 1;
	ChangeWeaponState(CurrentWeaponIndex, NewWeaponSlotIndex);
}

void AShootWonBanCharacter::SwitchWeapon1()
{
	if(CurrentWeapon == nullptr)
	{
		return;
	}
	
	int32 NewWeaponIndex = (CurrentWeaponIndex - 1 + Weapons.Num()) % Weapons.Num();
	ChangeWeaponState(CurrentWeaponIndex, NewWeaponIndex);
}

void AShootWonBanCharacter::SwitchWeapon2()
{
	if(CurrentWeapon == nullptr)
	{
		return;
	}
	
	int32 NewWeaponIndex = (CurrentWeaponIndex + 1) %  Weapons.Num(); 
	ChangeWeaponState(CurrentWeaponIndex, NewWeaponIndex);
}

void AShootWonBanCharacter::ChangeWeaponState(int32 CurrentIndex, int32 NewIndex)
{
	if(CurrentWeapon == nullptr)
	{
		return;
	}
	
	Weapons[CurrentIndex]->SetActorHiddenInGame(true);
	Weapons[NewIndex]->SetActorHiddenInGame(false);
	CurrentWeapon = Weapons[NewIndex];
	CurrentWeaponIndex = NewIndex;
}


void AShootWonBanCharacter::PickUpWeapon(ABaseWeapon* Weapon)
{
	if(Weapon)
	{
		Weapons.Add(Weapon);

		PlaySound(PickUpSound);
		
		if(bHasWeapon)
		{
			Weapon->SetActorHiddenInGame(true);
		}
		else
		{
			bHasWeapon = true;
			CurrentWeaponIndex = 0;
			CurrentWeapon = Weapon;

			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if(UFirstPersonAnimInstance* FirstPersonAnimInstance = Cast<UFirstPersonAnimInstance>(AnimInstance))
			{
				FirstPersonAnimInstance->HasRifle = true;
			}
		}
	}
}

void AShootWonBanCharacter::PlaySound(USoundBase* Sound)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), 0.7f);
}
