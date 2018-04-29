// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "Explosion.h"


AExplosion::AExplosion() {
  AudioComponent = CreateDefaultSubobject<URandomizedAudioComponent>(TEXT("AudioComponent"));
}

void AExplosion::OnConstruction(const FTransform& Transform) {
  Super::OnConstruction(Transform);
  
  AudioComponent->SetAutoActivate(false);
  AudioComponent->SetSounds(ExplosionSounds);
}

void AExplosion::BeginPlay() {
  Super::BeginPlay();
  
  // Trigger explosion in next tick
  GetWorld()->GetTimerManager().SetTimerForNextTick<AExplosion>(this, &AExplosion::Explode);
}

void AExplosion::Explode() {
  AudioComponent->PlayOneAtRand();
  const FTimerDelegate DisappearDelegate = FTimerDelegate::CreateUObject(this, &AExplosion::Disappear);
  GetWorldTimerManager().SetTimer(TimerHandle, DisappearDelegate, Duration, false);
}

void AExplosion::Disappear() {
  Destroy();
}
