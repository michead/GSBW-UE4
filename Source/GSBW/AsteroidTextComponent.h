// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AsteroidStructs.h"
#include "AsteroidTextComponent.generated.h"


UCLASS(Blueprintable)
class GSBW_API UAsteroidTextComponent : public USceneComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UAsteroidTextComponent();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FRotator BaseRotation;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  TArray<UTextRenderComponent*> TextRenderComponents;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  USceneComponent* RootComponent;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float FontScalingFactor;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FColor TextColor;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FString Word;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float CharSpacing;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float Radius;

  // Initialize component with passed word
  UFUNCTION()
  void Init(const FAsteroidTextComponentInitProps& Props);

  // Make the first char explode
  UFUNCTION()
  void DestroyLetterAt(uint32 LetterIndex);

private:
  void AttachTextComponents();

  FString InitialWord;
};
