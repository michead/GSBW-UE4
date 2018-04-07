// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "BombAsteroid.h"

void ABombAsteroid::OnDestruction() {
  AAsteroid::OnDestruction();
  
  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAsteroid::StaticClass(), actors);
  for (AActor* actor : actors) {
    FHitResult hitResult{};
    hitResult.Location = actor->GetActorLocation();
    Cast<AAsteroid>(actor)->Explode(hitResult);
  }
}
