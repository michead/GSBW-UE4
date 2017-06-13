// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "GSBWCommon.h"
#include "GSBWGameMode.generated.h"


UCLASS()
class GSBW_API AGSBWGameMode : public AGameMode
{
  GENERATED_BODY()

  AGSBWGameMode();

  virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
  virtual void HandleMatchHasStarted() override;

  UPROPERTY(EditAnywhere, Category=CPP_Gameplay)
  TArray<float> DifficultyDurations;

public:
  UFUNCTION()
  EDifficulty GetCurrentDifficulty() const { return CurrentDifficulty; }

private:
  void StartBumpDifficultyCoroutine();
  void BumpDifficulty();
  float GetCurrentDifficultyDuration();

  FTimerHandle TimerHandle;
  EDifficulty CurrentDifficulty;
};
