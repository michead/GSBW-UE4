// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "AsteroidStructs.generated.h"

/**
 * 
 */
UENUM()
enum class EAsteroidType : uint8 {
  BASE,
  FREEZE,
  SLOW,
  BOMB,
  NUM_TYPES
};

USTRUCT(BlueprintType)
struct FAsteroidInitProps {
  GENERATED_BODY()

  UPROPERTY()
  EAsteroidType type;
  UPROPERTY()
  FString word;
  UPROPERTY()
  float speed;
};

USTRUCT(BlueprintType)
struct FAsteroidExplosionInitProps {
  GENERATED_BODY()

  UPROPERTY()
  UDestructibleMesh* mesh;
  UPROPERTY()
  FHitResult hit;
};
