// Fill out your copyright notice in the Description page of Project Settings.


#include "BrokenPiece.h"

// Sets default values
ABrokenPiece::ABrokenPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BrokenPieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrokenPieceMesh"));
	BrokenPieceMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("/Script/Engine.StaticMesh'/Game/FPWeapon/Mesh/FirstPersonProjectileMesh.FirstPersonProjectileMesh'"));

	if(ObjectFinder.Succeeded())
	{
		BrokenPieceMesh->SetStaticMesh(ObjectFinder.Object);
	}
	
	BrokenPieceMesh->SetWorldScale3D(FVector(0.2f,0.2f,0.04f));

	BrokenPieceMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ABrokenPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrokenPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

