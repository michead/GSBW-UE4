// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWCommon.h"
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

void AGlobalEventHandler::BroadcastEvent(EGSBWEvent Ev, GSBWEventPayload* Payload) {
  switch (Ev) {
  case EGSBWEvent::ASTEROID_HIT:
    EventHandler->OnAsteroidHit.Broadcast(); break;
  case EGSBWEvent::ASTEROID_DOWN:
    EventHandler->OnAsteroidDown.Broadcast(); break;
  default:
    break;
  }
}

void AGlobalEventHandler::SubscribeToEvent(EGSBWEvent Ev, AActor* Subscriber, GSBWEventCallback DelegateFunc) {
  switch (Ev) {
  case EGSBWEvent::ASTEROID_HIT:
    EventHandler->OnAsteroidHit.AddDynamic(Subscriber, DelegateFunc); break;
  case EGSBWEvent::ASTEROID_DOWN:
    EventHandler->OnAsteroidDown.AddDynamic(Subscriber, DelegateFunc); break;
  default:
    break;
  }
}