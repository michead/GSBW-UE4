// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "GSBWMenuMode.generated.h"

/**
 * 
 */
UCLASS()
class GSBW_API AGSBWMenuMode : public AGameMode {
  GENERATED_BODY()

  AGSBWMenuMode();
	
  virtual void HandleMatchHasStarted() override;

private:
  APlayerController* PlayerController;
};
