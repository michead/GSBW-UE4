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
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_HIT, AsteroidHitDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_DOWN, AsteroidDownDelegate);

  // Cache world settings
  WorldSettings = Cast<AGSBWWorldSettings>(GetWorldSettings());
}

void AGSBWGameState::OnAsteroidHit() {
  UE_LOG(GSBWGameState, Log, TEXT("OnAsteroidHit()"));
  Score += WorldSettings->AsteroidHitScore;
}

void AGSBWGameState::OnAsteroidDown() {
  UE_LOG(GSBWGameState, Log, TEXT("OnAsteroidDown()"));
  Score += WorldSettings->AsteroidDownScore;
}

