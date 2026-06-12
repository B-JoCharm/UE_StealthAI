// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "StealthCharacter.h"
#include "StealthGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObjectiveActor::AObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 콜리전 컴포넌트 생성
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(100.f);
	CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));

}

// Called when the game starts or when spawned
void AObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	// 콜리전 이벤트 바인딩
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AObjectiveActor::OnOverlapBegin);
}

void AObjectiveActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어 캐릭터와 충돌했는지 확인
	if (Cast<AStealthCharacter>(OtherActor))
	{
		AStealthCharacter* StealthCharacter = Cast<AStealthCharacter>(OtherActor);
		if (StealthCharacter)
		{
			AStealthGameModeBase* GameMode = Cast<AStealthGameModeBase>(UGameplayStatics::GetGameMode(this));
			if (GameMode)
			{
				GameMode->OnGameWin();
			}
		}
	}
}
