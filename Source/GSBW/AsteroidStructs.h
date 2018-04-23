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
  SLOW,
  FREEZE,
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
  UPROPERTY()
  FVector torque;
};

USTRUCT(BlueprintType)
struct FAsteroidExplosionInitProps {
  GENERATED_BODY()

  UPROPERTY()
  UDestructibleMesh* mesh;
  UPROPERTY()
  FHitResult hit;
};

USTRUCT(BlueprintType)
struct FAsteroidTextComponentInitProps {
  GENERATED_BODY()

  UPROPERTY()
  USceneComponent* rootComponent;
  UPROPERTY()
  FString word;
  UPROPERTY()
  float radius;
  UPROPERTY()
  float charSpacing;
  UPROPERTY()
  FRotator baseRotation;
  UPROPERTY()
  TSubclassOf<UTextRenderComponent> textRenderComponentClass;
  UPROPERTY()
  float fontScalingFactor;
  UPROPERTY()
  FColor textColor;
};
