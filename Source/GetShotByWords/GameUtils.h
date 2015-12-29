// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Asteroid.h"
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
const float ROCKET_SPAWN_LOCATION_OFFSET = 20.f;
const float DEFAULT_FORCE_MAGNITUDE_TO_ROCKET = 50000.f;
const float DEFAULT_SPAWN_TIMEOUT = 4.f;
const FVector DEFAULT_UPPER_LEFT_BOUND = FVector(600.f, -1000.f, 0);
const FVector DEFAULT_UPPER_RIGHT_BOUND = FVector(600.f, 1000.f, 0);
const FVector DEFAULT_LOWER_LEFT_BOUND = FVector(-600.f, -1000.f, 0);
const FVector DEFAULT_LOWER_RIGHT_BOUND = FVector(-600.f, 1000.f, 0);
const float DEFAULT_SPAWNER_FORCE_MAGNITUDE = 10000.f;
const float ASTEROID_LIFESPAN = 30.f;
const FString WORDS_FILE_RELATIVE_PATH = "Data\\words.txt";
const float EXPLOSION_DURATION = 4.f;
const int ROCKET_DAMAGE_AMOUNT = 1000000000;
const int ROCKET_IMPULSE_STRENGTH = 500;
const float EXPLOSION_FADEOUT_SPEED = 0.5f;
const int INITIAL_PLAYER_HEALTH = 100;

void SpawnExplosion(UWorld* world, FTransform tranform, UStaticMeshComponent* mesh);

enum GSBWState
{
	EASY,
	NORMAL,
	HARD,
	BARUCH,
	NUM_STATES
};