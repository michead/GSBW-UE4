// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "GSBWGameMode.generated.h"


/**
 *
 */
UENUM()
enum class EGSBWDifficulty : uint8 {
  EASY,
  NORMAL,
  HARD,
  BARUCH,
  NUM_DIFFICULTIES
};

/**
 * 
 */
UCLASS()
class GSBW_API AGSBWGameMode : public AGameMode
{
  GENERATED_BODY()

  virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

  UPROPERTY(EditAnywhere, Category=CPP_Gameplay)
  TArray<float> DifficultyDurations;

private:
  void StartChangeDifficultyCoroutine();
  void BumpDifficulty();
  float GetCurrentDifficultyDuration();

  FTimerHandle TimerHandle;
  EGSBWDifficulty currentDifficulty;
};
