// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "FreezeAsteroid.h"

void AFreezeAsteroid::OnDestruction() {
  AAsteroid::OnDestruction();

  GSBWUtils::GetGameState(GetWorld())->RequestAsteroidTimeScaleChange(0);
  // TODO: Restore time scale
}
