// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "Earth.h"
#include "EarthController.h"
#include "EarthState.h"
#include "GetShotByWordsGameMode.h"

AGetShotByWordsGameMode::AGetShotByWordsGameMode()
{
	DefaultPawnClass = AEarth::StaticClass();
	PlayerControllerClass = AEarthController::StaticClass();
}

void AGetShotByWordsGameMode::SetGamePause(bool isGamePaused)
{
	check(GEngine);

	AEarthController* const earth = Cast<AEarthController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (earth) earth->SetPause(isGamePaused);
}