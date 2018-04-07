// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "SlowAsteroid.h"

void ASlowAsteroid::OnDestruction() {
  AAsteroid::OnDestruction();
  
  UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeScale);
}
