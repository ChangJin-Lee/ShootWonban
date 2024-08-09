// Fill out your copyright notice in the Description page of Project Settings.


#include "WonbanSpawner.h"

#include "TimerManager.h"
#include "Wonban.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWonbanSpawner::AWonbanSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundBase> ObjectFinder(TEXT("/Script/Engine.SoundWave'/Game/Sounds/WonbanDriveClose.WonbanDriveClose'"));

	if(ObjectFinder.Succeeded())
	{
		WonbanCreatingSound = ObjectFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> ObjectFinder2(TEXT("/Script/Engine.SoundWave'/Game/Sounds/WonbanShooting.WonbanShooting'"));

	if(ObjectFinder2.Succeeded())
	{
		WonbanShootingSound = ObjectFinder2.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<USoundBase> ObjectFinder3(TEXT("/Script/Engine.SoundWave'/Game/Sounds/WonbanBrokenSound.WonbanBrokenSound'"));

	if(ObjectFinder3.Succeeded())
	{
		WonbanDestroySound = ObjectFinder3.Object;
	}

}

// Called when the game starts or when spawned
void AWonbanSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AWonbanSpawner::SpawnWonban, 3.0f, true);

	FTimerHandle SoundTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(SoundTimerHandle, [this]()
	{
		PlaySound(WonbanCreatingSound);  // 사운드를 재생
	}, 3.0f, true, 2.0f);

	FTimerHandle SoundTimerHandle2;
	GetWorld()->GetTimerManager().SetTimer(SoundTimerHandle2, [this]()
	{
		PlaySound(WonbanShootingSound);  // 사운드를 재생
	}, 3.0f, true, 2.7f);
}

void AWonbanSpawner::SpawnWonban()
{
	SpawnLocation = GetActorLocation() + FVector(20,0,0);
	SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParameters;
	
	AWonban* SpawnedWonban = GetWorld()->SpawnActor<AWonban>(AWonban::StaticClass(), SpawnLocation, SpawnRotation, SpawnParameters);

	if(SpawnedWonban)
	{
		SpawnedWonban->SetActorScale3D(FVector(WonbanScale, WonbanScale, WonbanScale/5));
		SpawnedWonban->RotationFrequency = FMath::RandRange(WonbanRotationFrequency * 0.8, WonbanRotationFrequency * 1.2);
		SpawnedWonban->RotationPower = FMath::RandRange(WonbanRotationPower * 0.8, WonbanRotationPower * 1.2);
		SpawnedWonban->ParabolaHeight = FMath::RandRange(WonbanParabolaHeight * 0.8, WonbanParabolaHeight * 1.2);
		SpawnedWonban->ThrowDirection = FVector(FMath::RandRange(WonbanThrowDirectionX.X, WonbanThrowDirectionX.Y),FMath::RandRange(WonbanThrowDirectionY.X, WonbanThrowDirectionY.Y),0.0f).GetSafeNormal();
		SpawnedWonban->TargetLocation = SpawnedWonban->ThrowDirection * WonbanTargetLocationDistance;
		SpawnedWonban->WonbanDestroySound = WonbanDestroySound;
		ChangeSpeed(10.0f / WonbanSpeed);
		SpawnedWonban->InitializeThrow(ThrowCurve);
		SpawnedWonban->SetLifeSpan(60);
	}
}

// Called every frame
void AWonbanSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWonbanSpawner::PlaySound(USoundBase* Sound)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), 0.8f);
}

void AWonbanSpawner::ChangeSpeed(float time)
{
	if(ThrowCurve)
	{
		FRichCurve& RichCurve = ThrowCurve->FloatCurve;

		int32 KeyIndexToRemove = INDEX_NONE;

		for (int32 KeyIndex = 0; KeyIndex < RichCurve.Keys.Num(); ++KeyIndex)
		{
			FRichCurveKey& Key = RichCurve.Keys[KeyIndex];
			if (Key.Value == 1.0f)
			{
				KeyIndexToRemove = KeyIndex;
				break; 
			}
		}

		// 해당 키프레임이 발견되면
		if (KeyIndexToRemove != INDEX_NONE)
		{
			// 키프레임 제거
			RichCurve.Keys.RemoveAt(KeyIndexToRemove);

			// 새로운 키프레임 추가 (NewTime 시간에 값은 1.0f로 설정)
			RichCurve.AddKey(time, 1.0f);
		}
	}
}

