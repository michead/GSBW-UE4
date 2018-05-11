// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "EarthHUD.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"
#include "GSBWHUD.h"

DEFINE_LOG_CATEGORY(GSBWHUD);

// Sets default values
AGSBWHUD::AGSBWHUD() {
  
}

// Called when the game starts or when spawned
void AGSBWHUD::BeginPlay() {
  Super::BeginPlay();

  PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

  HUD = CreateWidget<UEarthHUD>(PlayerController, EarthHUDClass);
  HUD->AddToViewport();
  HUD->Init();

  PauseMenu = CreateWidget<UPauseMenu>(PlayerController, PauseMenuClass);
  PauseMenu->AddToViewport();
  
  GameOverMenu = CreateWidget<UGameOverMenu>(PlayerController, GameOverMenuClass);
  GameOverMenu->AddToViewport();

  OnGamePauseDelegate.BindUFunction(this, "OnGamePause");
  OnGameUnpauseDelegate.BindUFunction(this, "OnGameUnpause");
  OnGameStartDelegate.BindUFunction(this, "OnGameStart");
  OnGameOverDelegate.BindUFunction(this, "OnGameOver");

  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_PAUSE, OnGamePauseDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_UNPAUSE, OnGameUnpauseDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_START, OnGameStartDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_OVER, OnGameOverDelegate);

  // Pause and game over menus should start hidden
  SetPauseMenuVisibility(false);
  SetGameOverMenuVisibility(false);
}

void AGSBWHUD::SetWidgetVisibility(UUserWidget* Widget, bool NewVisibility) {
  check(Widget);
  Widget->SetVisibility(NewVisibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void AGSBWHUD::SetPauseMenuVisibility(bool NewVisiblity) {
  SetWidgetVisibility(PauseMenu, NewVisiblity);
}

void AGSBWHUD::SetGameOverMenuVisibility(bool NewVisibility) {
  SetWidgetVisibility(GameOverMenu, NewVisibility);
}

void AGSBWHUD::OnGamePause() {
  SetPauseMenuVisibility(true);
  PlayerController->bShowMouseCursor = true;
}

void AGSBWHUD::OnGameUnpause() {
  SetPauseMenuVisibility(false);
  PlayerController->bShowMouseCursor = false;
}

void AGSBWHUD::OnGameStart() {
  PlayerController->bShowMouseCursor = false;
}

void AGSBWHUD::OnGameOver() {
  SetGameOverMenuVisibility(true);
  PlayerController->bShowMouseCursor = true;
}
