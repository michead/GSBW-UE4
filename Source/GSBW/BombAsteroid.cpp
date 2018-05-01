// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "BombAsteroid.h"

void ABombAsteroid::OnDestruction() {
  AAsteroid::OnDestruction();
  
  uint32 actorId = GetUniqueID();
  
  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAsteroid::StaticClass(), actors);
  for (AActor* actor : actors) {
    if (actor->GetUniqueID() == actorId) {
      // Ignore this actor as it is already bound to explode
      continue;
    }
    FHitResult hitResult{};
    hitResult.Location = actor->GetActorLocation();
    Cast<AAsteroid>(actor)->Explode(hitResult, false);
  }
}
