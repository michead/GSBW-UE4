// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Asteroid.h"
#include "AsteroidStructs.h"
#include "Spawner.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Spawner, Log, All);

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
  float GetSpawnInterval();
  FVector GetNextAsteroidLocation();
  FString GetNextAsteroidWord();
  EAsteroidType GetNextAsteroidType();
  float GetNextAsteroidSpeed();
  void ComputeSpawnerBounds();
  void InitAsteroidProps(FAsteroidInitProps& Props, EAsteroidType Type);

  FVector2D ViewportSize;
  FTimerHandle TimerHandle;
  TSubclassOf<class AAsteroid> BaseAsteroidBPClass;
  TSubclassOf<class AAsteroid> SlowAsteroidBPClass;
  TSubclassOf<class AAsteroid> FreezeAsteroidBPClass;
  TSubclassOf<class AAsteroid> BombAsteroidBPClass;
  TMap<uint8_t, TArray<FString>> WordMap;
};
