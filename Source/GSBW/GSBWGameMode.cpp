// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWGameMode.h"


void AGSBWGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
  StartChangeDifficultyCoroutine();
}

void AGSBWGameMode::StartChangeDifficultyCoroutine() {
  currentDifficulty = EGSBWDifficulty::EASY;
  GetWorld()->GetTimerManager().SetTimer(
    TimerHandle,
    this,
    &AGSBWGameMode::BumpDifficulty,
    GetCurrentDifficultyDuration(),
    true);
}

void AGSBWGameMode::BumpDifficulty() {
  check(static_cast<uint8>(currentDifficulty) < (static_cast<uint8>(EGSBWDifficulty::NUM_DIFFICULTIES) - 1));
  currentDifficulty = static_cast<EGSBWDifficulty>(static_cast<uint8>(currentDifficulty) + 1);
}

float AGSBWGameMode::GetCurrentDifficultyDuration() {
  return 2.f;
}

