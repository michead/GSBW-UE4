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
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CPP_Gameplay)
  int32 AsteroidDamage;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CPP_Gameplay)
  int32 RocketDamage;
};
