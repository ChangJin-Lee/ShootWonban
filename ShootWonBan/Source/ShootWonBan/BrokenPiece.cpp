// Fill out your copyright notice in the Description page of Project Settings.


#include "BrokenPiece.h"

// Sets default values
ABrokenPiece::ABrokenPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PieceSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PieceSceneComponent"));
	SetRootComponent(PieceSceneComponent);

	BrokenPieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrokenPieceMesh"));
	BrokenPieceMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("/Script/Engine.StaticMesh'/Game/WonbanMesh.WonbanMesh'"));

	if(ObjectFinder.Succeeded())
	{
		BrokenPieceMesh->SetStaticMesh(ObjectFinder.Object);
	}

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

