// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "RandomizedAudioComponent.generated.h"

/**
 * 
 */
UCLASS()
class GSBW_API URandomizedAudioComponent : public UAudioComponent {
  GENERATED_BODY()
  
public:
  virtual void SetSounds(TArray<USoundBase*> SoundBases);
  virtual void PlayOneAtRand();
  
private:
  TArray<USoundBase*> Sounds;
};
