// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "GameUtils.generated.h"

/**
 * 
 */
UCLASS()
class GETSHOTBYWORDS_API UGameUtils : public UObject
{
	GENERATED_BODY()

};

const TArray<TCHAR> ALPHABET = FString(TEXT("abcdefghijklmnopqrstuvwxyz")).GetCharArray();
const float ROCKET_LIFESPAN = 10.f;
const float ROCKET_SPAWN_LOCATION_OFFSET = 50.f;
const float DEFAULT_FORCE_MAGNITUDE_TO_ROCKET = 50000.f;
const float DEFAULT_SPAWN_TIMEOUT = 4.f;
const FVector DEFAULT_UPPER_LEFT_BOUND = FVector(600.f, -1000.f, 0);
const FVector DEFAULT_UPPER_RIGHT_BOUND = FVector(600.f, 1000.f, 0);
const FVector DEFAULT_LOWER_LEFT_BOUND = FVector(-600.f, -1000.f, 0);
const FVector DEFAULT_LOWER_RIGHT_BOUND = FVector(-600.f, 1000.f, 0);
const float DEFAULT_SPAWNER_FORCE_MAGNITUDE = 1000000.f;
const float ASTEROID_LIFESPAN = 30.f;