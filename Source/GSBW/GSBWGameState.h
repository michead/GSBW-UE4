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
  UFUNCTION()
  void OnAsteroidHit();
  
  UFUNCTION()
  void OnAsteroidDown();
  
  UFUNCTION()
  void OnGamePaused();
  
  UFUNCTION()
  void OnGameUnpaused();
  
  UFUNCTION(BlueprintCallable, Category=CPP_Gameplay)
  bool IsGamePaused();
  
  UFUNCTION()
  void OnEarthDown();
  
  UFUNCTION()
  void OnDifficultyBump();
  
  UFUNCTION()
  EDifficulty GetCurrentDifficulty() const;
  
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Score)
  int32 Score;

  void RequestPauseToggle();

private:
  AGSBWWorldSettings* WorldSettings;
  
  EDifficulty CurrentDifficulty;
  
  FScriptDelegate AsteroidHitDelegate;
  FScriptDelegate AsteroidDownDelegate;
  FScriptDelegate GamePausedDelegate;
  FScriptDelegate GameUnpausedDelegate;
  FScriptDelegate EarthDownDelegate;
  FScriptDelegate DifficultyBumpDelegate;
  
  bool IsPaused;
};
