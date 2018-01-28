// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AsteroidText.generated.h"


UCLASS()
class GSBW_API AAsteroidText : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  AAsteroidText();

  // Called when the game starts
  virtual void BeginPlay() override;

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

  virtual void OnConstruction(const FTransform & Transform) override;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FRotator BaseRotation;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  TArray<UTextRenderComponent*> TextRenderComponents;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FString Word;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float CharSpacing;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float Radius;

  // Initialize component with passed word
  void Init(FString Word);

  // Make the last char explode
  void DestroyLastChar();

private:
  void AttachTextComponents();

  FString InitialWord;
};
