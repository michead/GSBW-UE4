// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWCommon.h"
#include "GSBWUtils.h"
#include "GlobalEventHandler.h"
#include "GSBWGameState.h"

DEFINE_LOG_CATEGORY(GSBWGameState);

void AGSBWGameState::HandleMatchHasStarted() {
  Super::HandleMatchHasStarted();

  // Register event listeners
  AsteroidHitDelegate.BindUFunction(this,"OnAsteroidHit");
  AsteroidDownDelegate.BindUFunction(this, "OnAsteroidDown");
  GamePausedDelegate.BindUFunction(this, "OnGamePaused");
  GameUnpausedDelegate.BindUFunction(this, "OnGameUnpaused");
  EarthDownDelegate.BindUFunction(this, "OnEarthDown");
  DifficultyBumpDelegate.BindUFunction(this, "OnDifficultyBump");
  
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_HIT, AsteroidHitDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_DOWN, AsteroidDownDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_PAUSED, GamePausedDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_UNPAUSED, GameUnpausedDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::DIFFICULTY_BUMP, DifficultyBumpDelegate);

  // Cache world settings
  WorldSettings = Cast<AGSBWWorldSettings>(GetWorldSettings());

  // Game is not paused when started
  IsPaused = false;
  
  // Start off easy
  CurrentDifficulty = EDifficulty::EASY;
}

void AGSBWGameState::OnAsteroidHit() {
  UE_LOG(GSBWGameState, Log, TEXT("OnAsteroidHit()"));
  Score += WorldSettings->AsteroidHitScore;
}

void AGSBWGameState::OnAsteroidDown() {
  UE_LOG(GSBWGameState, Log, TEXT("OnAsteroidDown()"));
  Score += WorldSettings->AsteroidDownScore;
}

void AGSBWGameState::OnGamePaused() {
  UE_LOG(GSBWGameState, Log, TEXT("OnGamePaused()"));
  IsPaused = true;
}

void AGSBWGameState::OnGameUnpaused() {
  UE_LOG(GSBWGameState, Log, TEXT("OnGameUnpaused()"));
  IsPaused = false;
}

void AGSBWGameState::OnDifficultyBump() {
  UE_LOG(GSBWGameState, Log, TEXT("OnDifficultyBump()"));
  if (static_cast<uint8>(CurrentDifficulty) <
      static_cast<uint8>(EDifficulty::NUM_DIFFICULTIES) - 1) {
    CurrentDifficulty = static_cast<EDifficulty>(static_cast<uint8>(CurrentDifficulty) + 1);
  }
}

EDifficulty AGSBWGameState::GetCurrentDifficulty() const {
  return CurrentDifficulty;
}

bool AGSBWGameState::IsGamePaused() {
  return IsPaused;
}

void AGSBWGameState::OnEarthDown() {
  UE_LOG(GSBWGameState, Log, TEXT("OnEarthDown()"));
}

void AGSBWGameState::RequestPauseToggle() {
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(IsPaused ? EGSBWEvent::GAME_UNPAUSED : EGSBWEvent::GAME_PAUSED);
}
