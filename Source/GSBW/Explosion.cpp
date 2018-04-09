// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "Explosion.h"


AExplosion::AExplosion() {
  AudioComponent = CreateDefaultSubobject<URandomizedAudioComponent>(TEXT("AudioComponent"));
}

void AExplosion::OnConstruction(const FTransform& Transform) {
  AudioComponent->SetAutoActivate(false);
  AudioComponent->SetSound(ExplosionSound);
}

void AExplosion::Explode() {
  AudioComponent->Play(0);
}
