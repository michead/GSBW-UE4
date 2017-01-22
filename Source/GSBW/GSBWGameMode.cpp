// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWGameMode.h"


void AGSBWGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
  StartChangeDifficultyCoroutine();
}

void AGSBWGameMode::StartChangeDifficultyCoroutine() {
  GetWorld()->GetTimerManager().SetTimer(
    TimerHandle,
    this,
    &AGSBWGameMode::ChangeDifficulty,
    GetCurrentDifficultyDuration(),
    true);
}

void AGSBWGameMode::ChangeDifficulty() {

}

float AGSBWGameMode::GetCurrentDifficultyDuration() {
  return 2.f;
}

