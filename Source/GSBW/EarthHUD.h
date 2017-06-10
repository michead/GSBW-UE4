// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Earth.h"
#include "EarthHUD.generated.h"

/**
 * 
 */
UCLASS()
class GSBW_API UEarthHUD : public UUserWidget
{
	GENERATED_BODY()

public:
  virtual void Init();

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Gameplay_CPP)
  AEarth* Earth;

  UFUNCTION()
  void OnAsteroidHit();
  UFUNCTION()
  void OnAsteroidDown();
  UFUNCTION()
  void OnEarthHit();
  UFUNCTION()
  void OnEarthDown();

private:
  FScriptDelegate OnAsteroidHitDelegate;
  FScriptDelegate OnAsteroidDownDelegate;
  FScriptDelegate OnEarthHitDelegate;
  FScriptDelegate OnEarthDownDelegate;
};
