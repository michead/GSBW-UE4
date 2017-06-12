// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "Earth.h"
#include "GSBWHUD.h"

DEFINE_LOG_CATEGORY(GSBWHUD);

// Sets default values
AGSBWHUD::AGSBWHUD() {
  
}

// Called when the game starts or when spawned
void AGSBWHUD::BeginPlay() {
  Super::BeginPlay();

  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEarth::StaticClass(), actors);
  PlayerController = Cast<APlayerController>(Cast<AEarth>(actors[0])->GetController());

  HUD = CreateWidget<UEarthHUD>(PlayerController, EarthHUDClass);
  HUD->AddToViewport();
  HUD->Init();

  MainMenu = CreateWidget<UUserWidget>(PlayerController, MainMenuClass);
  MainMenu->AddToViewport();

  PauseMenu = CreateWidget<UUserWidget>(PlayerController, PauseMenuClass);
  PauseMenu->AddToViewport();
}

void AGSBWHUD::SetPauseMenuVisibility(bool NewVisiblity) {
  PauseMenu->SetVisibility(NewVisiblity ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
