// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWCommon.h"
#include "GlobalEventHandler.h"


// Sets default values
AGlobalEventHandler::AGlobalEventHandler() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  EventHandler = CreateDefaultSubobject<UGlobalEventHandlerComponent>(TEXT("GlobalEventHandlerComponent"));
}

// Called when the game starts or when spawned
void AGlobalEventHandler::BeginPlay() {
  Super::BeginPlay();
}

// Called every frame
void AGlobalEventHandler::Tick( float DeltaTime ) {
  Super::Tick(DeltaTime);
}

void AGlobalEventHandler::BroadcastEvent(EGSBWEvent Ev) {
  switch (Ev) {
    case EGSBWEvent::ASTEROID_HIT:
      EventHandler->OnAsteroidHit.Broadcast(); break;
    case EGSBWEvent::ASTEROID_DOWN:
      EventHandler->OnAsteroidDown.Broadcast(); break;
    case EGSBWEvent::ASTEROID_TIME_SCALE_CHANGE:
      EventHandler->OnAsteroidTimeScaleChange.Broadcast(); break;
    case EGSBWEvent::EARTH_HIT:
      EventHandler->OnEarthHit.Broadcast(); break;
    case EGSBWEvent::EARTH_DOWN:
      EventHandler->OnEarthDown.Broadcast(); break;
    case EGSBWEvent::TARGET_CHANGE:
      EventHandler->OnTargetChange.Broadcast(); break;
    case EGSBWEvent::GAME_PAUSE:
      EventHandler->OnGamePause.Broadcast(); break;
    case EGSBWEvent::GAME_UNPAUSE:
      EventHandler->OnGameUnpause.Broadcast(); break;
    case EGSBWEvent::GAME_START:
      EventHandler->OnGameStart.Broadcast(); break;
    case EGSBWEvent::GAME_OVER:
      EventHandler->OnGameOver.Broadcast(); break;
    case EGSBWEvent::DIFFICULTY_BUMP:
      EventHandler->OnDifficultyBump.Broadcast(); break;
    default:
      break;
  }
}

template<typename T>
void AGlobalEventHandler::BroadcastEvent(EGSBWEvent Ev, T& Payload) {
  switch (Ev) {
  case EGSBWEvent::ASTEROID_HIT:
    EventHandler->OnAsteroidHit.Broadcast(Payload); break;
  case EGSBWEvent::ASTEROID_DOWN:
    EventHandler->OnAsteroidDown.Broadcast(Payload); break;
  case EGSBWEvent::ASTEROID_TIME_SCALE_CHANGE:
    EventHandler->OnAsteroidTimeScaleChange.Broadcast(Payload); break;
  case EGSBWEvent::EARTH_HIT:
    EventHandler->OnEarthHit.Broadcast(Payload); break;
  case EGSBWEvent::EARTH_DOWN:
    EventHandler->OnEarthDown.Broadcast(Payload); break;
  case EGSBWEvent::TARGET_CHANGE:
    EventHandler->OnTargetChange.Broadcast(Payload); break;
  case EGSBWEvent::GAME_PAUSE:
    EventHandler->OnGamePause.Broadcast(Payload); break;
  case EGSBWEvent::GAME_UNPAUSE:
    EventHandler->OnGameUnpause.Broadcast(Payload); break;
  case EGSBWEvent::GAME_START:
    EventHandler->OnGameStart.Broadcast(Payload); break;
  case EGSBWEvent::GAME_OVER:
    EventHandler->OnGameOver.Broadcast(Payload); break;
  case EGSBWEvent::DIFFICULTY_BUMP:
    EventHandler->OnDifficultyBump.Broadcast(Payload); break;
  default:
    break;
  }
}

void AGlobalEventHandler::SubscribeToEvent(EGSBWEvent Ev, const FScriptDelegate& DelegateFunc) {
  switch (Ev) {
  case EGSBWEvent::ASTEROID_HIT:
    EventHandler->OnAsteroidHit.Add(DelegateFunc); break;
  case EGSBWEvent::ASTEROID_DOWN:
    EventHandler->OnAsteroidDown.Add(DelegateFunc); break;
  case EGSBWEvent::ASTEROID_TIME_SCALE_CHANGE:
    EventHandler->OnAsteroidTimeScaleChange.Add(DelegateFunc); break;
  case EGSBWEvent::EARTH_HIT:
    EventHandler->OnEarthHit.Add(DelegateFunc); break;
  case EGSBWEvent::EARTH_DOWN:
    EventHandler->OnEarthDown.Add(DelegateFunc); break;
  case EGSBWEvent::TARGET_CHANGE:
    EventHandler->OnTargetChange.Add(DelegateFunc); break;
  case EGSBWEvent::GAME_PAUSE:
    EventHandler->OnGamePause.Add(DelegateFunc); break;
  case EGSBWEvent::GAME_UNPAUSE:
    EventHandler->OnGameUnpause.Add(DelegateFunc); break;
  case EGSBWEvent::GAME_START:
    EventHandler->OnGameStart.Add(DelegateFunc); break;
  case EGSBWEvent::GAME_OVER:
    EventHandler->OnGameOver.Add(DelegateFunc); break;
  case EGSBWEvent::DIFFICULTY_BUMP:
    EventHandler->OnDifficultyBump.Add(DelegateFunc); break;
  default:
    break;
  }
}
