// Fill out your copyright notice in the Description page of Project Settings.


#include "Wonban.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AWonban::AWonban()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WonbanMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WonbanMeshComponent"));
	WonbanMeshComponent->SetupAttachment(RootComponent);

	MovementDirection = FVector(1.0f, 1.0f, 0.0f);
	MovementSpeed = 150.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("/Script/Engine.StaticMesh'/Game/FPWeapon/Mesh/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));

	if(ObjectFinder.Succeeded())
	{
		WonbanMeshComponent->SetStaticMesh(ObjectFinder.Object);
	}
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

	// Move the actor forward
	FVector NewLocation = GetActorLocation() + (MovementDirection * MovementSpeed * DeltaTime);
	SetActorLocation(NewLocation);

}

