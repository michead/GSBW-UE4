// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "Earth.h"
#include "GSBWHUD.h"

// Sets default values
AGSBWHUD::AGSBWHUD() {
  
}

// Called when the game starts or when spawned
void AGSBWHUD::BeginPlay() {
  Super::BeginPlay();

  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEarth::StaticClass(), actors);
  PlayerController = Cast<APlayerController>(Cast<AEarth>(actors[0])->GetController());

  HUD = CreateWidget<UUserWidget>(PlayerController, EarthHUDClass);
  HUD->AddToViewport();

  MainMenu = CreateWidget<UUserWidget>(PlayerController, MainMenuClass);
  MainMenu->AddToViewport();

  PauseMenu = CreateWidget<UUserWidget>(PlayerController, PauseMenuClass);
  PauseMenu->AddToViewport();
}