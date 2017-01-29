// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AsteroidStructs.h"
#include "GSBWUtils.h"
#include "Spawner.generated.h"

UCLASS()
class GSBW_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
    TArray<FVector> Bounds;

private:
  void StartSpawnCoroutine();
  void Spawn();
  void Spawn(EAsteroidType AsteroidType);
  float GetCurrentDifficultySpawnInterval();
  EAsteroidType GetRandomAsteroidTypeForCurrentDifficulty();
  void ComputeSpawnerBounds();

  FTimerHandle TimerHandle;
  UClass* BaseAsteroidBPClass;
  UClass* SlowAsteroidBPClass;
  UClass* FreezeAsteroidBPClass;
  UClass* BombAsteroidBPClass;
};
