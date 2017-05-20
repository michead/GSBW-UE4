// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/WorldSettings.h"
#include "GSBWWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class GSBW_API AGSBWWorldSettings : public AWorldSettings
{
  GENERATED_BODY()

public:
  // Health
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Gameplay)
  int32 AsteroidDamage;
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Gameplay)
  int32 RocketDamage;
  // Score
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Gameplay)
  int32 AsteroidHitScore;
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Gameplay)
  int32 AsteroidDownScore;
};
