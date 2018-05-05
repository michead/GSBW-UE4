// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AsteroidStructs.h"
#include "AsteroidTextComponent.generated.h"


UCLASS(Blueprintable)
class GSBW_API UAsteroidTextComponent : public USceneComponent {
  GENERATED_BODY()
  
  // Workaround for TickComponent not firing in AsteroidTextComponent
  friend class AAsteroid;

public:
  // Sets default values for this component's properties
  UAsteroidTextComponent();
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FRotator BaseRotation;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Rendering)
  TSubclassOf<UTextRenderComponent> TextRenderComponentClass;
    
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
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float DistanceFromSurface;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float AngleBetweenLetters;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float RotationSpeed;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FVector WorldRotationAxis;

  // Initialize component with passed word
  UFUNCTION()
  void Init(const FAsteroidTextComponentInitProps& Props);

  UFUNCTION()
  void DestroyLetterAt(uint32 LetterIndex);
  
  UFUNCTION()
  void DestroyAllLetters();

protected:
  void InitAsteroidLetterComponents();
  void UpdatePosition(float DeltaTime);
  FVector2D GetTextForwardVector() const;
  FVector2D GetBaseTextLocation() const;
  
  FVector2D SphericalPositionOffset;
};
