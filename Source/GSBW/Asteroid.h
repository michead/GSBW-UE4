// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AsteroidStructs.h"
#include "Asteroid.generated.h"

UCLASS()
class GSBW_API AAsteroid : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AAsteroid();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

  // Asteroid virtual methods
  virtual void Init(const FAsteroidInitProps& props);
  virtual void OnEarthHit(const FHitResult& hit);
  virtual void OnRocketHit(const FHitResult& hit);
  virtual void Explode(const FHitResult& hit);

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  FString word;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  EAsteroidType type;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  float speed;
};
