// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GlobalEventHandler.h"


// Sets default values
AGlobalEventHandler::AGlobalEventHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    EventHandler = ConstructObject<UGlobalEventHandlerComponent>(UGlobalEventHandlerComponent::StaticClass(), this);
}

// Called when the game starts or when spawned
void AGlobalEventHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGlobalEventHandler::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AGlobalEventHandler::BroadcastEvent(EGSBWEvent ev, GSBWEventPayload* payload) {
  switch (ev) {
  case EGSBWEvent::ASTEROID_HIT:
    EventHandler->OnAsteroidHit.Broadcast(); break;
  case EGSBWEvent::ASTEROID_DOWN:
    EventHandler->OnAsteroidDown.Broadcast(); break;
  default:
    break;
  }
}

void AGlobalEventHandler::SubscribeToEvent(EGSBWEvent ev, AActor* subscriber, GSBWEventCallback callback) {
  switch (ev) {
  case EGSBWEvent::ASTEROID_HIT:
    EventHandler->OnAsteroidHit.AddDynamic(subscriber, callback); break;
  case EGSBWEvent::ASTEROID_DOWN:
    EventHandler->OnAsteroidDown.AddDynamic(subscriber, callback); break;
  default:
    break;
  }
}