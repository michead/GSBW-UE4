// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Asteroid.h"
#include "AsteroidStructs.h"
#include "Explosion.h"
#include "AsteroidExplosion.generated.h"

/**
*
*/
UCLASS()
class GSBW_API AAsteroidExplosion : public AExplosion
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AAsteroidExplosion();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // AsteroidExplosion public virtual methods
  virtual void Init(const FAsteroidExplosionInitProps& Props);
  virtual void ApplyDamage();
  virtual void Disappear();

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  UDestructibleComponent* DestructibleComponent;

protected:
  virtual void Explode() override;
    
  FHitResult Hit;
  UDestructibleMesh* Mesh;
  FTimerHandle TimerHandle;
};
