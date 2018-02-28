// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Asteroid.h"
#include "AsteroidStructs.h"
#include "GSBWGameMode.h"
#include "GSBWCommon.h"
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

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Gameplay)
  TSubclassOf<class AAsteroid> BaseAsteroidBPClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Gameplay)
  TSubclassOf<class AAsteroid> SlowAsteroidBPClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Gameplay)
  TSubclassOf<class AAsteroid> FreezeAsteroidBPClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Gameplay)
  TSubclassOf<class AAsteroid> BombAsteroidBPClass;

  UFUNCTION()
  void OnEarthDown();

private:
  void StartSpawnCoroutine();
  void Spawn();
  void Spawn(EAsteroidType AsteroidType);
  float GetSpawnInterval();
  FVector GetNextAsteroidLocation(EAsteroidType AsteroidType);
  FString GetNextAsteroidWord();
  EAsteroidType GetNextAsteroidType();
  float GetNextAsteroidSpeed();
  void ComputeSpawnerBounds();
  void InitAsteroidProps(FAsteroidInitProps& Props, EAsteroidType Type);
  FString PickWordFromMap(uint8_t WordLen, uint8_t PrefixCharIndex);
  FString GetNextFirstLetter(TArray<AActor*> Asteroids);
  int32_t GetNextWordLen();

  // Static methods
  static bool SomeStartWithLetter(const TArray<AActor*>& Asteroids, const FString& Letter);

  AGSBWGameMode* GameMode;
  FVector2D ViewportSize;
  FVector2D PrevViewportSize;
  FScriptDelegate EarthDownDelegate;
  FTimerHandle TimerHandle;
  bool ShouldSpawn;
  FString Alphabet;
  GSBWWordMap WordMap;
  TArray<FInt32Interval> WordLens;
};
