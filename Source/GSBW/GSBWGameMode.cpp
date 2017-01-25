// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWGameMode.h"


void AGSBWGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
  StartBumpDifficultyCoroutine();
}

void AGSBWGameMode::StartBumpDifficultyCoroutine() {
  currentDifficulty = EDifficulty::EASY;
  GetWorld()->GetTimerManager().SetTimer(
    TimerHandle,
    this,
    &AGSBWGameMode::BumpDifficulty,
    GetCurrentDifficultyDuration(),
    true);
}

void AGSBWGameMode::BumpDifficulty() {
  currentDifficulty = static_cast<EDifficulty>(static_cast<uint8>(currentDifficulty) + 1);
}

float AGSBWGameMode::GetCurrentDifficultyDuration() {
  return 2.f;
}

