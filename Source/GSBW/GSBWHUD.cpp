// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWHUD.h"

// Sets default values
AGSBWHUD::AGSBWHUD() {
  
}

// Called when the game starts or when spawned
void AGSBWHUD::BeginPlay() {
  Super::BeginPlay();

  HUD = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), EarthHUDClass);
  HUD->AddToViewport();

  MainMenu = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), MainMenuClass);
  MainMenu->AddToViewport();

  PauseMenu = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), PauseMenuClass);
  PauseMenu->AddToViewport();
}