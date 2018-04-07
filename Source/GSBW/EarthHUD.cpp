// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "EarthHUD.h"

void UEarthHUD::Init() {
  OnAsteroidHitDelegate.BindUFunction(this, "OnAsteroidHit");
  OnAsteroidDownDelegate.BindUFunction(this, "OnAsteroidDown");
  OnEarthHitDelegate.BindUFunction(this, "OnEarthHit");
  OnEarthDownDelegate.BindUFunction(this, "OnEarthDown");

  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_HIT, OnAsteroidHitDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_DOWN, OnAsteroidDownDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::EARTH_HIT, OnEarthHitDelegate);
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::EARTH_DOWN, OnEarthDownDelegate);

  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEarth::StaticClass(), actors);
  Earth = Cast<AEarth>(actors[0]);
}

void UEarthHUD::OnAsteroidHit() {

}

void UEarthHUD::OnAsteroidDown() {

}

void UEarthHUD::OnEarthHit() {

}

void UEarthHUD::OnEarthDown() {

}
