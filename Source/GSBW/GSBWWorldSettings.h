// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/WorldSettings.h"
#include "GSBWCommon.h"
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
  int32 EarthMaxHealth;
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Gameplay)
  int32 AsteroidDamage;
  // Score
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Gameplay)
  int32 AsteroidHitScore;
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Gameplay)
  int32 AsteroidDownScore;
  // Gameplay
  UPROPERTY(EditDefaultsOnly, Category=CPP_Gameplay)
  int32 DufficultyDurations[EDifficulty::NUM_DIFFICULTIES];
  UPROPERTY(EditDefaultsOnly, Category=CPP_Gameplay)
  int32 AsteroidSpeeds[EDifficulty::NUM_DIFFICULTIES];
  UPROPERTY(EditDefaultsOnly, Category=CPP_Gameplay)
  FInt32Interval AsteroidWordLens[EDifficulty::NUM_DIFFICULTIES];
};
