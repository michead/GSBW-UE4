// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "RocketStructs.generated.h"

/**
*
*/
UENUM()
enum class ERocketType : uint8 {
  BASE,
  NUM_TYPES
};

USTRUCT(BlueprintType)
struct FRocketInitProps {
  GENERATED_BODY()

  UPROPERTY()
  ERocketType type;
  UPROPERTY()
  FString letter;
  UPROPERTY()
  float speed;
};
