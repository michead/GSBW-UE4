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
const float ROCKET_SPAWN_LOCATION_OFFSET = 30.f;