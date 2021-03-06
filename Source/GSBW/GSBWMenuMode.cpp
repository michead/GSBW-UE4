// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWMenuMode.h"
#include "GSBWMenu.h"

AGSBWMenuMode::AGSBWMenuMode() {
  HUDClass = AGSBWMenu::StaticClass();
}

void AGSBWMenuMode::HandleMatchHasStarted() {
  Super::HandleMatchHasStarted();

  PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  PlayerController->bShowMouseCursor = true;
}

