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
  AsteroidTimeScaleChangeDelegate.BindUFunction(this, "OnAsteroidTimeScaleChange");
  GamePausedDelegate.BindUFunction(this, "OnGamePaused");
  GameUnpausedDelegate.BindUFunction(this, "OnGameUnpaused");
  EarthDownDelegate.BindUFunction(this, "OnEarthDown");
  DifficultyBumpDelegate.BindUFunction(this, "OnDifficultyBump");
  
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_HIT, AsteroidHitDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_DOWN, AsteroidDownDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_TIME_SCALE_CHANGE, AsteroidTimeScaleChangeDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::EARTH_DOWN, EarthDownDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_PAUSED, GamePausedDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_UNPAUSED, GameUnpausedDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::DIFFICULTY_BUMP, DifficultyBumpDelegate);

  // Cache world settings
  WorldSettings = Cast<AGSBWWorldSettings>(GetWorldSettings());

  // Game is not paused when started
  IsPaused = false;
  
  // Start off easy
  CurrentDifficulty = EDifficulty::EASY;
  
  // Start with normal asteroid movement speed
  AsteroidTimeScale = 1.f;
  
  // Let all components know game has started
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::GAME_STARTED);
}

void AGSBWGameState::OnAsteroidHit() {
  Score += WorldSettings->AsteroidHitScore;
}

void AGSBWGameState::OnAsteroidDown() {
  Score += WorldSettings->AsteroidDownScore;
}

void AGSBWGameState::OnAsteroidTimeScaleChange() {

}

void AGSBWGameState::OnGamePaused() {
  UE_LOG(GSBWGameState, Log, TEXT("Pausing game"));
  IsPaused = true;
}

void AGSBWGameState::OnGameUnpaused() {
  UE_LOG(GSBWGameState, Log, TEXT("Unpausing game"));
  IsPaused = false;
}

void AGSBWGameState::OnDifficultyBump() {
  if (static_cast<uint8>(CurrentDifficulty) <
      static_cast<uint8>(EDifficulty::NUM_DIFFICULTIES) - 1) {
    CurrentDifficulty = static_cast<EDifficulty>(static_cast<uint8>(CurrentDifficulty) + 1);
    UE_LOG(GSBWGameState, Log, TEXT("Bumping difficulty index to %d"), CurrentDifficulty);
  }
}

EDifficulty AGSBWGameState::GetCurrentDifficulty() const {
  return CurrentDifficulty;
}

bool AGSBWGameState::IsGamePaused() {
  return IsPaused;
}

void AGSBWGameState::OnEarthDown() {
  // Let game state class decide that, when earth goes down, game is over
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::GAME_OVER);
}

void AGSBWGameState::RequestPauseToggle() {
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(IsPaused ? EGSBWEvent::GAME_UNPAUSED : EGSBWEvent::GAME_PAUSED);
}

void AGSBWGameState::RequestAsteroidTimeScaleChange(float NewTimeScale) {
  AsteroidTimeScale = NewTimeScale;
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::ASTEROID_TIME_SCALE_CHANGE);
}
