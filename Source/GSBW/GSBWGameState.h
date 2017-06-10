// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "GSBWWorldSettings.h"
#include "GSBWGameState.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(GSBWGameState, Log, All);

UCLASS()
class GSBW_API AGSBWGameState : public AGameState
{
  GENERATED_BODY()

  virtual void HandleMatchHasStarted() override;

public:
  // Event delegates
  void OnAsteroidHit();
  void OnAsteroidDown();

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Score)
  int32 Score;

private:
  AGSBWWorldSettings* WorldSettings;
  TScriptDelegate<FWeakObjectPtr> AsteroidHitDelegate;
  TScriptDelegate<FWeakObjectPtr> AsteroidDownDelegate;
};
