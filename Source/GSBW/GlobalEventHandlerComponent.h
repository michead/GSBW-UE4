// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GlobalEventHandlerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventDelegate_OnAsteroidHit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventDelegate_OnAsteroidDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventDelegate_OnAsteroidTimeScaleChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventDelegate_OnEarthHit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventDelegate_OnEarthDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventDelegate_OnGamePaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventDelegate_OnGameUnpaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventDelegate_OnGameStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventDelegate_OnGameOver);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelEventDelegate_OnDifficultyBump);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GSBW_API UGlobalEventHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
  // Sets default values for this component's properties
  UGlobalEventHandlerComponent();

  // Called when the game starts
  virtual void BeginPlay() override;
	
  // Called every frame
  virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    
  FLevelEventDelegate_OnAsteroidHit OnAsteroidHit;
  FLevelEventDelegate_OnAsteroidDown OnAsteroidDown;
  FLevelEventDelegate_OnAsteroidTimeScaleChange OnAsteroidTimeScaleChange;
  FLevelEventDelegate_OnEarthHit OnEarthHit;
  FLevelEventDelegate_OnEarthDown OnEarthDown;
  FLevelEventDelegate_OnGamePaused OnGamePaused;
  FLevelEventDelegate_OnGameUnpaused OnGameUnpaused;
  FLevelEventDelegate_OnGameStarted OnGameStarted;
  FLevelEventDelegate_OnGameOver OnGameOver;
  FLevelEventDelegate_OnDifficultyBump OnDifficultyBump;
};
