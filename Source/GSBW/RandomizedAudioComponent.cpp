// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "RandomizedAudioComponent.h"


void URandomizedAudioComponent::SetSounds(TArray<USoundBase*> SoundBases) {
  Sounds = SoundBases;
}

void URandomizedAudioComponent::PlayOneAtRand() {
  if (!Sounds.Num()) {
    // No sound bases have been assigned
    return;
  }
  int index = FMath::RandRange(0, Sounds.Num() - 1);
  SetSound(Sounds[index]);
  Play(0);
}
