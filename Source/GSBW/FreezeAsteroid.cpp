// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "FreezeAsteroid.h"

AFreezeAsteroid::AFreezeAsteroid() {
  EffectDuration = 3.f;
}

void AFreezeAsteroid::OnDestruction() {
  Super::OnDestruction();

  GSBWUtils::GetGameState(GetWorld())->RequestAsteroidTimeScaleChange(0);
  
  const FTimerDelegate RestoreAsteroidTimeScaleDelegate = FTimerDelegate::CreateUObject(this, &AFreezeAsteroid::RestoreAsteroidTimeScale);
  GetWorldTimerManager().SetTimer(DisableEffectTimerHandle, RestoreAsteroidTimeScaleDelegate, EffectDuration, false);
}
