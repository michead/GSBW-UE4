// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWGameState.h"
#include "GSBWHUD.h"
#include "Earth.h"
#include "GSBWGameMode.h"


AGSBWGameMode::AGSBWGameMode() {
  DefaultPawnClass = AEarth::StaticClass();
  HUDClass = AGSBWHUD::StaticClass();
}

void AGSBWGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
  Super::InitGame(MapName, Options, ErrorMessage);
}

void AGSBWGameMode::HandleMatchHasStarted() {
  Super::HandleMatchHasStarted();
  StartBumpDifficultyCoroutine();
}

void AGSBWGameMode::StartBumpDifficultyCoroutine() {
  CurrentDifficulty = EDifficulty::EASY;
  GetWorld()->GetTimerManager().SetTimer(
    TimerHandle,
    this,
    &AGSBWGameMode::BumpDifficulty,
    GetCurrentDifficultyDuration(),
    true);
}

void AGSBWGameMode::BumpDifficulty() {
  CurrentDifficulty = static_cast<EDifficulty>(static_cast<uint8>(CurrentDifficulty) + 1);
}

float AGSBWGameMode::GetCurrentDifficultyDuration() {
  return 2.f;
}

