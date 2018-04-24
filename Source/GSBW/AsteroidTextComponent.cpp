// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "AsteroidTextComponent.h"


// Sets default values for this component's properties
UAsteroidTextComponent::UAsteroidTextComponent() {
  PrimaryComponentTick.bCanEverTick = false;

  Radius = 10;
  CharSpacing = 10;
  RadiusMultiplier = 1.1f;
}

void UAsteroidTextComponent::Init(const FAsteroidTextComponentInitProps& Props) {
  RootComponent = Props.rootComponent;
  Word = Props.word;
  BaseRotation = Props.baseRotation;
  CharSpacing = Props.charSpacing;
  FontScalingFactor = Props.fontScalingFactor;
  Radius = Props.radius;
  TextColor = Props.textColor;
  TextRenderComponentClass = Props.textRenderComponentClass;

  InitAsteroidLetterComponents();
}

void UAsteroidTextComponent::DestroyAllLetters() {
  for (auto i = 0; i < TextRenderComponents.Num(); i++) {
    DestroyLetterAt(i);
  }
  
  TextRenderComponents.Empty();
}

void UAsteroidTextComponent::DestroyLetterAt(uint32 LetterIndex) {
  if (LetterIndex < 0 || LetterIndex >= TextRenderComponents.Num() || !TextRenderComponents[LetterIndex]) {
    return;
  }
  
  TextRenderComponents[LetterIndex]->UnregisterComponent();
  TextRenderComponents[LetterIndex]->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
  TextRenderComponents[LetterIndex]->DestroyComponent();
}

void UAsteroidTextComponent::InitAsteroidLetterComponents() {
  DestroyAllLetters();

  uint8_t i = 0;
  for (TCHAR c : Word) {
    auto component = NewObject<UTextRenderComponent>(this, TextRenderComponentClass);
    
    component->RegisterComponent();
    component->SetWorldRotation(BaseRotation);
    component->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    component->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
    component->SetWorldScale3D(FVector(FontScalingFactor));
    component->SetText(FText::FromString(FString("").AppendChar(c)));
    component->SetTextRenderColor(TextColor);
    component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
      
    TextRenderComponents.Push(component);
    i += 1;
  }
  
  i = 0;
  float angle = FMath::DegreesToRadians<float>(20.f);
  float totalAngle = angle * (TextRenderComponents.Num() - 1);
  FVector forward = FVector(0, 0, -1);
  FVector2D sphericalLoc = forward.UnitCartesianToSpherical();
  FVector2D baseLoc = sphericalLoc + FVector2D(totalAngle / 2.f, 0.f);
  for (auto component : TextRenderComponents) {
    FVector dir = baseLoc.SphericalToUnitCartesian();
    float alpha = FMath::RadiansToDegrees<float>(FMath::Acos(FVector::DotProduct(dir, forward)));
    float bPlus = FVector::DotProduct(FVector::CrossProduct(dir, forward), FVector(0, 1, 0)) > 0;
    FRotator deltaRotation = FRotator(bPlus ? alpha : -alpha, 0, 0);
    component->SetRelativeLocation(dir * Radius * RadiusMultiplier);
    component->AddWorldRotation(deltaRotation);
    baseLoc -= FVector2D(angle, 0.f);
    i++;
  }
};
