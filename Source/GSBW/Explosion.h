// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RandomizedAudioComponent.h"
#include "Explosion.generated.h"

/**
*
*/
UCLASS()
class GSBW_API AExplosion : public AActor {
  GENERATED_BODY()
  
public:
  AExplosion();
  
  virtual void OnConstruction(const FTransform& Transform) override;
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Audio)
  URandomizedAudioComponent* AudioComponent;
    
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Audio)
  USoundBase* ExplosionSound;
  
protected:
  virtual void Explode();
};
