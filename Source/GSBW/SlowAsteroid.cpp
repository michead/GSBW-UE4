// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "SlowAsteroid.h"

void ASlowAsteroid::OnDestruction() {
  AAsteroid::OnDestruction();
  
  GSBWUtils::GetGameState(GetWorld())->RequestAsteroidTimeScaleChange(TimeScale);
  // TODO: Restore time scale
}
