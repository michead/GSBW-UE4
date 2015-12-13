// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class GETSHOTBYWORDS_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SpawnAsteroid();

	const FTransform GetAsteroidInitialTransform();
	const FVector GetAsteroidInitialLoc();
	const FRotator GetAsteroidInitialRot();
	const FVector GetAsteroidInitialScale();

	FVector GetRandLocFromBounds(FVector a, FVector b);

	float GetSpawnTimeout();
	float GetForceMagnitude();

	FTimerHandle timerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TArray<FVector> spawnBounds;
};
