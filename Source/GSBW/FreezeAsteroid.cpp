// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "FreezeAsteroid.h"

void AFreezeAsteroid::OnDestruction() {
  AAsteroid::OnDestruction();

  UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
}
