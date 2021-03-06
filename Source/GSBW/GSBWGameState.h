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
  void OnAsteroidTimeScaleChange();
  
  UFUNCTION()
  void OnGamePause();
  
  UFUNCTION()
  void OnGameUnpause();
  
  UFUNCTION(BlueprintCallable, Category=CPP_Gameplay)
  bool IsGamePaused();
  
  UFUNCTION()
  void OnEarthDown();
  
  UFUNCTION()
  void OnDifficultyBump();
  
  UFUNCTION()
  EDifficulty GetCurrentDifficulty() const;
  
  UFUNCTION()
  void RequestPauseToggle();
  
  UFUNCTION()
  void RequestAsteroidTimeScaleChange(float NewTimeScale);
  
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  float AsteroidTimeScale;
  
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Score)
  int32 Score;

private:
  AGSBWWorldSettings* WorldSettings;
  
  EDifficulty CurrentDifficulty;
  
  FScriptDelegate AsteroidHitDelegate;
  FScriptDelegate AsteroidDownDelegate;
  FScriptDelegate AsteroidTimeScaleChangeDelegate;
  FScriptDelegate GamePauseDelegate;
  FScriptDelegate GameUnpauseDelegate;
  FScriptDelegate EarthDownDelegate;
  FScriptDelegate DifficultyBumpDelegate;
  
  bool IsPaused;
};
