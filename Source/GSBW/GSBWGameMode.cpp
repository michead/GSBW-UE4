// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
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

  OnGamePauseDelegate.BindUFunction(this, "OnGamePause");
  OnGameUnpauseDelegate.BindUFunction(this, "OnGameUnpause");
  OnEarthDownDelegate.BindUFunction(this, "OnEarthDown");

  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_PAUSE, OnGamePauseDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_UNPAUSE, OnGameUnpauseDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::EARTH_DOWN, OnEarthDownDelegate);

  PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  PlayerController->bShowMouseCursor = false;
  
  check(DifficultyDurations.Num() == static_cast<int>(EDifficulty::NUM_DIFFICULTIES) - 1);
}

void AGSBWGameMode::StartBumpDifficultyCoroutine() {
  GetWorld()->GetTimerManager().SetTimer(
    TimerHandle,
    this,
    &AGSBWGameMode::BumpDifficulty,
    GetCurrentDifficultyDuration(),
    true);
}

float AGSBWGameMode::GetCurrentDifficultyDuration() const {
  EDifficulty currentDifficulty = GetWorld()->GetGameState<AGSBWGameState>()->GetCurrentDifficulty();
  if (currentDifficulty == EDifficulty::BARUCH) {
    return MAX_FLT;
  }
  return DifficultyDurations[static_cast<int>(currentDifficulty)];
}

void AGSBWGameMode::BumpDifficulty() {
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::DIFFICULTY_BUMP);
}

void AGSBWGameMode::OnEarthDown() {
  // Probably nothing to do on behalf of GameMode
}

void AGSBWGameMode::OnGamePaused() {
  UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
  PlayerController->bShowMouseCursor = true;
  IsGamePaused = true;
}

void AGSBWGameMode::OnGameUnpaused() {
  UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
  PlayerController->bShowMouseCursor = false;
  IsGamePaused = false;
}

