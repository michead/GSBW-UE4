// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "Earth.h"
#include "EarthController.h"
#include "GetShotByWordsGameMode.h"

AGetShotByWordsGameMode::AGetShotByWordsGameMode()
{
	DefaultPawnClass = AEarth::StaticClass();
	PlayerControllerClass = AEarthController::StaticClass();
}