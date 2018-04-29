// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "SlowAsteroid.h"


ASlowAsteroid::ASlowAsteroid() {
  EffectDuration = 8.f;
}

void ASlowAsteroid::OnDestruction() {
  AAsteroid::OnDestruction();
  
  GSBWUtils::GetGameState(GetWorld())->RequestAsteroidTimeScaleChange(TimeScale);

  const FTimerDelegate RestoreAsteroidTimeScaleDelegate = FTimerDelegate::CreateUObject(this, &ASlowAsteroid::RestoreAsteroidTimeScale);
  GetWorldTimerManager().SetTimer(TimerHandle, RestoreAsteroidTimeScaleDelegate, EffectDuration, false);
}
