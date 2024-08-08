// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "ShootWonBanCharacter.h"
#include "TP_WeaponComponent.h"
#include "TP_PickUpComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Component 초기화
	WeaponComponent = CreateDefaultSubobject<UTP_WeaponComponent>(TEXT("WeaponComponent"));
	RootComponent = WeaponComponent;

	PickUpComponent = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("PickUpComponent"));
	PickUpComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	PickUpComponent->OnPickUp.AddDynamic(this, &ABaseWeapon::AttachWeapon);
}

void ABaseWeapon::AttachWeapon(AShootWonBanCharacter* ShootWonBanCharacter)
{
	Character = ShootWonBanCharacter;
	
	if (Character == nullptr)
	{
		return;
	}
	
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	
	if(APlayerController* PlayerController = Cast<APlayerController>(ShootWonBanCharacter->GetController()))
	{
		WeaponComponent->SetOwnerController(PlayerController);
	}

	Character->PickUpWeapon(this);
}

void ABaseWeapon::Fire(const int32 AmmoCount)
{
	if(AmmoCount < 1)
	{
		// play empty ammo sound
		PlaySound(EmptyAmmoSound);
		PlayAnimation(FireAnimation, 1.f);
		return; 
	}

	WeaponComponent->Fire();
	
	PlaySound(FireSound);
	PlayAnimation(FireAnimation, 1.f);
}

void ABaseWeapon::PlaySound(USoundBase* SetSoundBase) const
{
	if(SetSoundBase != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SetSoundBase, GetActorLocation());
	}
}

void ABaseWeapon::PlayAnimation(UAnimMontage* SetAnimation, float PlayRate) const
{
	if (SetAnimation != nullptr)
	{
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(SetAnimation, PlayRate);
		}
	}
}
