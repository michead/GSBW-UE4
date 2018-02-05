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
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_HIT, AsteroidHitDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_DOWN, AsteroidDownDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_PAUSED, GamePausedDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_UNPAUSED, GameUnpausedDelegate);

  // Cache world settings
  WorldSettings = Cast<AGSBWWorldSettings>(GetWorldSettings());

  // Game is not paused when started
  Paused = false;
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
  Paused = true;
}

void AGSBWGameState::OnGameUnpaused() {
  UE_LOG(GSBWGameState, Log, TEXT("OnGameUnpaused()"));
  Paused = false;
}

bool AGSBWGameState::IsPaused() {
  return Paused;
}

void AGSBWGameState::OnEarthDown() {
  UE_LOG(GSBWGameState, Log, TEXT("OnEarthDown()"));
}
