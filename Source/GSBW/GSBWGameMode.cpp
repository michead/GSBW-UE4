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

  OnGamePausedDelegate.BindUFunction(this, "OnGamePaused");
  OnGameUnpausedDelegate.BindUFunction(this, "OnGameUnpaused");

  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_PAUSED, OnGamePausedDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_UNPAUSED, OnGameUnpausedDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::EARTH_DOWN, OnEarthDownDelegate);

  PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  PlayerController->bShowMouseCursor = false;
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
  if (static_cast<uint8>(CurrentDifficulty) <
      static_cast<uint8>(EDifficulty::NUM_DIFFICULTIES) - 1) {
    CurrentDifficulty = static_cast<EDifficulty>(static_cast<uint8>(CurrentDifficulty) + 1);
  }
}

float AGSBWGameMode::GetCurrentDifficultyDuration() {
  return 5.f;
}

void AGSBWGamemode::OnEarthDown() {

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

