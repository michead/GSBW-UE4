// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Asteroid.h"
#include "BombAsteroid.generated.h"

/**
 * 
 */
UCLASS()
class GSBW_API ABombAsteroid : public AAsteroid {
  GENERATED_BODY()

protected:
  virtual void OnDestruction() override;
};
