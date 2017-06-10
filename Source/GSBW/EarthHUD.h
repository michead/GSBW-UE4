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

private:
  void OnAsteroidHit();
  void OnAsteroidDown();
  void OnEarthHit();
  void OnEarthDown();

  TScriptDelegate<FWeakObjectPtr> OnAsteroidHitDelegate;
  TScriptDelegate<FWeakObjectPtr> OnAsteroidDownDelegate;
  TScriptDelegate<FWeakObjectPtr> OnEarthHitDelegate;
  TScriptDelegate<FWeakObjectPtr> OnEarthDownDelegate;
};
