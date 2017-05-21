// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWCommon.h"
#include "GSBWUtils.h"
#include "GlobalEventHandler.h"
#include "GSBWGameState.h"

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

}

void AGSBWGameState::OnAsteroidDown() {

}

