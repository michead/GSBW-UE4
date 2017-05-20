// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWCommon.h"
#include "GSBWUtils.h"
#include "GSBWGameState.h"

void AGSBWGameState::HandleMatchHasStarted() {
  Super::HandleMatchHasStarted();

  // Register event listeners
  // GSBWEventCallback cbHit = &AGSBWGameState::OnAsteroidHit;
  // GSBWEventCallback cbDown = &AGSBWGameState::OnAsteroidDown;
  // GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_HIT, this, cbHit);
  // GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_DOWN, this, cbDown);

  // Cache world settings
  WorldSettings = Cast<AGSBWWorldSettings>(GetWorldSettings());
}

void AGSBWGameState::OnAsteroidHit() {

}

void AGSBWGameState::OnAsteroidDown() {

}

