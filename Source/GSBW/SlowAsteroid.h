// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Asteroid.h"
#include "SlowAsteroid.generated.h"

/**
 * 
 */
UCLASS()
class GSBW_API ASlowAsteroid : public AAsteroid {
  GENERATED_BODY()
  
  UPROPERTY(EditAnywhere, Category=CPP_Gameplay)
  float TimeScale;
  
protected:
  virtual void OnDestruction() override;
};
