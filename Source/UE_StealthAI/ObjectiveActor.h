// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveActor.generated.h"

UCLASS()
class UE_STEALTHAI_API AObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// 플레이어 감지용 콜리전 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Objective")
	class USphereComponent* CollisionSphere;

	// 플레이어가 감지됐을때 호출
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
