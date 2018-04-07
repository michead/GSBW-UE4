// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "GameFramework/HUD.h"
#include "GSBWMenu.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(GSBWMenu, Log, All);

UCLASS()
class GSBW_API AGSBWMenu : public AHUD {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AGSBWMenu();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_UI)
  TSubclassOf<class UMainMenu> MainMenuClass;

private:
  APlayerController * PlayerController;
  UMainMenu* MainMenu;
};
