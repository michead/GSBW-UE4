// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "EarthHUD.h"
#include "PauseMenu.h"
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

  OnGamePausedDelegate.BindUFunction(this, "OnGamePaused");
  OnGameUnpausedDelegate.BindUFunction(this, "OnGameUnpaused");

  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_PAUSED, OnGamePausedDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::GAME_UNPAUSED, OnGameUnpausedDelegate);

  // Pause Menu Widget should start hidden
  SetPauseMenuVisibility(false);
}

void AGSBWHUD::SetPauseMenuVisibility(bool NewVisiblity) {
  PauseMenu->SetVisibility(NewVisiblity ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void AGSBWHUD::OnGamePaused() {
  SetPauseMenuVisibility(true);
}

void AGSBWHUD::OnGameUnpaused() {
  SetPauseMenuVisibility(false);
}
