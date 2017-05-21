// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GSBWCommon.h"
#include "GlobalEventHandlerComponent.h"
#include "GlobalEventHandler.generated.h"

DECLARE_DELEGATE(EventDelegate);

UCLASS()
class GSBW_API AGlobalEventHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlobalEventHandler();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  // Wraps delegates of GSBW events
  UGlobalEventHandlerComponent* EventHandler;

  void BroadcastEvent(EGSBWEvent Ev, GSBWEventPayload* Payload = nullptr);
  void SubscribeToEvent(EGSBWEvent Ev, TScriptDelegate<FWeakObjectPtr>& DelegateFunc);
};
