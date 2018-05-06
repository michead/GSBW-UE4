// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "GameFramework/HUD.h"
#include "GSBWHUD.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(GSBWHUD, Log, All);

UCLASS()
class GSBW_API AGSBWHUD : public AHUD
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AGSBWHUD();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_UI)
  TSubclassOf<class UEarthHUD> EarthHUDClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_UI)
  TSubclassOf<class UPauseMenu> PauseMenuClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_UI)
  TSubclassOf<class UGameOverMenu> GameOverMenuClass;
  
  UFUNCTION()
  void OnGamePaused();
  
  UFUNCTION()
  void OnGameUnpaused();
  
  UFUNCTION()
  void OnGameStarted();
  
  UFUNCTION()
  void OnGameOver();

private:
  void SetWidgetVisibility(UUserWidget* Widget, bool NewVisiblity);
  void SetPauseMenuVisibility(bool NewVisibilty);
  void SetGameOverMenuVisibility(bool NewVisibility);

  APlayerController* PlayerController;
  UEarthHUD* HUD;
  UPauseMenu* PauseMenu;
  UGameOverMenu* GameOverMenu;
  FScriptDelegate OnGamePausedDelegate;
  FScriptDelegate OnGameUnpausedDelegate;
  FScriptDelegate OnGameStartedDelegate;
  FScriptDelegate OnGameOverDelegate;
};
