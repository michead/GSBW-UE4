// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "GSBWMenu.h"

DEFINE_LOG_CATEGORY(GSBWMenu);

// Sets default values
AGSBWMenu::AGSBWMenu() {

}

// Called when the game starts or when spawned
void AGSBWMenu::BeginPlay() {
  Super::BeginPlay();

  PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  MainMenu = CreateWidget<UMainMenu>(PlayerController, MainMenuClass);
  SettingsMenu = CreateWidget<USettingsMenu>(PlayerController, SettingsMenuClass);

  ShowMainMenu();
}

void AGSBWMenu::ShowMainMenu() {
  if (SettingsMenu->IsVisible()) {
    SettingsMenu->RemoveFromParent();
  }

  MainMenu->AddToViewport();
}

void AGSBWMenu::ShowSettingsMenu() {
  MainMenu->RemoveFromParent();

  SettingsMenu->AddToViewport();
}
