// Fill out your copyright notice in the Description page of Project Settings.


#include "Wonban.h"

#include "BrokenPiece.h"
#include "ShootWonBanPlayerController.h"
#include "ShootWonBanProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AWonban::AWonban()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WonbanSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WonbanSceneComponent"));
	SetRootComponent(WonbanSceneComponent);

	WonbanMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WonbanMeshComponent"));
	WonbanMeshComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("/Script/Engine.StaticMesh'/Game/WonbanMesh.WonbanMesh'"));

	if(ObjectFinder.Succeeded())
	{
		WonbanMeshComponent->SetStaticMesh(ObjectFinder.Object);
	}

	WonbanMeshComponent->SetSimulatePhysics(false);

	WonbanMeshComponent->OnComponentHit.AddDynamic(this, &AWonban::OnCollision);
}

// Called when the game starts or when spawned
void AWonban::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWonban::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ThrowTimeline.TickTimeline(DeltaTime);
}

void AWonban::InitializeThrow(UCurveFloat* Curve)
{
	InitialLocation = GetActorLocation();
	TargetLocation +=  FVector(InitialLocation.X, InitialLocation.Y, 0 );
	SetupThrowTimeline(Curve);
}

void AWonban::SetupThrowTimeline(UCurveFloat* Curve)
{
	if (Curve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleThrowProgress"));
		ThrowTimeline.AddInterpFloat(Curve, ProgressFunction);
		ThrowTimeline.SetLooping(false);

		FOnTimelineEvent FinishedFunction;
		FinishedFunction.BindUFunction(this, FName("OnThrowTimelinFinished"));
		ThrowTimeline.SetTimelineFinishedFunc(FinishedFunction);

		ThrowTimeline.PlayFromStart();
	}
}

void AWonban::HandleThrowProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(InitialLocation, TargetLocation, Value);
	NewLocation.Z += FMath::Sin(Value * PI) * ParabolaHeight;  // 포물선 운동 추가
	SetActorLocation(NewLocation);
	
	FRotator NewRotation = FRotator(FMath::Sin(Value * PI * RotationFrequency) * RotationPower, GetActorRotation().Yaw, GetActorRotation().Roll);
	SetActorRotation(NewRotation);
}

void AWonban::OnThrowTimelinFinished()
{
	WonbanMeshComponent->SetSimulatePhysics(true);
}

void AWonban::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->IsA<AShootWonBanProjectile>())
	{
		SpawnBrokenPieces();
		Destroy();

		if(WonbanDestroySound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), WonbanDestroySound, GetActorLocation());
		}

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if(PlayerController)
		{
			AShootWonBanPlayerController* ShootWonBanPlayerController = Cast<AShootWonBanPlayerController>(PlayerController);
			if(ShootWonBanPlayerController)
			{
				ShootWonBanPlayerController->CurrentScore++;
			}
		}
	}
}

void AWonban::SpawnBrokenPieces()
{
	for (int i = 0; i < PeiceCount; i++)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = FRotator::ZeroRotator;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ABrokenPiece::StaticClass(), SpawnLocation, SpawnRotation);
		if(SpawnedActor)
		{
			ABrokenPiece* BrokenPiece = Cast<ABrokenPiece>(SpawnedActor);
			if (BrokenPiece)
			{
				UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(BrokenPiece->GetComponentByClass(UStaticMeshComponent::StaticClass()));
				if (MeshComponent)
				{
					FVector ImpulseDirection = FVector(FMath::FRandRange(-1.0f, 1.0f), FMath::FRandRange(-1.0f, 1.0f), FMath::FRandRange(0.5f, 1.5f));
					MeshComponent->SetWorldScale3D(GetActorScale3D()/4);
					MeshComponent->AddImpulse(ImpulseDirection * PeicePower);
				}
				BrokenPiece->SetLifeSpan(5.0f);
			}
		}
	}
}
