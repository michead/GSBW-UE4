// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "FreezeAsteroid.h"

AFreezeAsteroid::AFreezeAsteroid() {
  EffectDuration = 3.f;
}

void AFreezeAsteroid::OnDestruction() {
  Super::OnDestruction();

  // Do not completely freeze (set dilation to 0) as other components rely on dividing by this value
  GSBWUtils::GetGameState(GetWorld())->RequestAsteroidTimeScaleChange(0.0001f);
  
  const FTimerDelegate RestoreAsteroidTimeScaleDelegate = FTimerDelegate::CreateUObject(this, &AFreezeAsteroid::RestoreAsteroidTimeScale);
  GetWorldTimerManager().SetTimer(DisableEffectTimerHandle, RestoreAsteroidTimeScaleDelegate, EffectDuration, false);
}
