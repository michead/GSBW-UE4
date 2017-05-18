// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "GameFramework/HUD.h"
#include "GSBWHUD.generated.h"

/**
 * 
 */
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
  TSubclassOf<class UUserWidget> EarthHUDClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_UI)
  TSubclassOf<class UUserWidget> MainMenuClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_UI)
  TSubclassOf<class UUserWidget> PauseMenuClass;

private:
  UUserWidget* HUD;
  UUserWidget* MainMenu;
  UUserWidget* PauseMenu;
};
