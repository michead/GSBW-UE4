// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "Explosion.h"


AExplosion::AExplosion() {
  AudioComponent = CreateDefaultSubobject<URandomizedAudioComponent>(TEXT("AudioComponent"));
}

void AExplosion::OnConstruction(const FTransform& Transform) {
  Super::OnConstruction(Transform);
}

void AExplosion::BeginPlay() {
  Super::BeginPlay();
  
  AudioComponent->SetAutoActivate(false);
  AudioComponent->SetSounds(ExplosionSounds);
}

void AExplosion::Explode() {
  AudioComponent->PlayOneAtRand();
}
