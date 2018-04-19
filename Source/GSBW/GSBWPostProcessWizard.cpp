// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "GSBWPostProcessWizard.h"


// Sets default values
AGSBWPostProcessWizard::AGSBWPostProcessWizard() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  
  AsteroidHitDelegate.BindUFunction(this, "OnAsteroidHit");
  AsteroidDownDelegate.BindUFunction(this, "OnAsteroidDown");
  EarthHitDelegate.BindUFunction(this, "OnEarthHit");
  EarthDownDelegate.BindUFunction(this, "OnEarthDown");
}

// Called when the game starts or when spawned
void AGSBWPostProcessWizard::BeginPlay() {
	Super::BeginPlay();
  
  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), APostProcessVolume::StaticClass(), actors);
  PostProcessVolume = Cast<APostProcessVolume>(actors[0]);
  
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_HIT, AsteroidHitDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_DOWN, AsteroidDownDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::EARTH_HIT, EarthHitDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::EARTH_DOWN, EarthDownDelegate);
}

// Called every frame
void AGSBWPostProcessWizard::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AGSBWPostProcessWizard::OnAsteroidHit_Implementation() {
  
}

void AGSBWPostProcessWizard::OnAsteroidDown_Implementation() {
  
}

void AGSBWPostProcessWizard::OnEarthHit_Implementation() {
  
}

void AGSBWPostProcessWizard::OnEarthDown_Implementation() {
  
}

