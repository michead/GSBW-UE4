// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Asteroid.h"
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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Gameplay)
    TArray<FVector> Bounds;

private:
  void StartSpawnCoroutine();
  void Spawn();
  void Spawn(EAsteroidType AsteroidType);
  float GetCurrentDifficultySpawnInterval();
  FVector GetRandomAsteroidLocation();
  EAsteroidType GetRandomAsteroidTypeForCurrentDifficulty();
  void ComputeSpawnerBounds();
  void InitAsteroidProps(FAsteroidInitProps& Props, EAsteroidType Type);
  FString PickAsteroidWord();
  float PickAsteroidSpeed();

  FTimerHandle TimerHandle_0, TimerHandle_1;
  TSubclassOf<class AAsteroid> BaseAsteroidBPClass;
  TSubclassOf<class AAsteroid> SlowAsteroidBPClass;
  TSubclassOf<class AAsteroid> FreezeAsteroidBPClass;
  TSubclassOf<class AAsteroid> BombAsteroidBPClass;
};
