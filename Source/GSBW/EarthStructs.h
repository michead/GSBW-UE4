// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Asteroid.h"
#include "EarthStructs.generated.h"

/**
*
*/
USTRUCT(BlueprintType)
struct FTarget {
  GENERATED_BODY()

  UPROPERTY()
  AAsteroid* ref;
  UPROPERTY()
  FString originalWord;
  UPROPERTY()
  uint32 rocketCount;
};
