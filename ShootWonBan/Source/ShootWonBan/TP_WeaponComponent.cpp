// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "ShootWonBanProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"

void UTP_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UTP_WeaponComponent::Fire()
{
	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		GetMuzzleLocation();
		
		UWorld* const World = GetWorld();
		
		if (World != nullptr && OwnerController != nullptr)
		{
			if(GetCrossHairLocation(OwnerController, CrosshairWorldLocation, CrosshairDirection))
			{	
				FVector EndTrace = CrosshairWorldLocation + (CrosshairDirection * WeaponRange);

				FVector FireDirection = (EndTrace - MuzzleLocation).GetSafeNormal();
				FRotator ProjectileRotation = FireDirection.Rotation();
				
				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		
				// Spawn the projectile at the muzzle
				World->SpawnActor<AShootWonBanProjectile>(ProjectileClass, MuzzleLocation, ProjectileRotation, ActorSpawnParams);
			}
		}
	}
}

void UTP_WeaponComponent::GetMuzzleLocation()
{
	if(const USkeletalMesh* MySkeletalMesh = GetSkeletalMeshAsset())
	{
		if(MySkeletalMesh->FindSocket(TEXT("Muzzle")))
		{
			MuzzleLocation =	GetSocketLocation(TEXT("Muzzle"));
		}
	}
}

// 화면의 중앙의 월드 좌표와 방향을 가져온다 
bool UTP_WeaponComponent::GetCrossHairLocation(const APlayerController* PlayerController, FVector& WorldLocation, FVector& WorldDirection) const
{	
	if(PlayerController != nullptr)
	{
		FVector2D Viewport;
		GetWorld()->GetGameViewport()->GetViewportSize(Viewport);
		PlayerController->DeprojectScreenPositionToWorld(Viewport.X * 0.5f, Viewport.Y * 0.5f, WorldLocation, WorldDirection);
		return true;
	}
	return false;
}

// void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
// {
// 	if (Character == nullptr)
// 	{
// 		return;
// 	}
//
// 	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
// 	{
// 		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
// 		{
// 			Subsystem->RemoveMappingContext(FireMappingContext);
// 		}
// 	}
// }

