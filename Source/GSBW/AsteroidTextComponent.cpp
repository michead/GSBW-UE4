// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "AsteroidTextComponent.h"


// Sets default values for this component's properties
UAsteroidTextComponent::UAsteroidTextComponent() {
  PrimaryComponentTick.bCanEverTick = false;

  Radius = 10;
  CharSpacing = 10;
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
  
  float width = CharSpacing * float(TextRenderComponents.Num() - 1);
  for (auto component : TextRenderComponents) {
    width += component->Bounds.BoxExtent.X;
  }
  
  float x = -width / 2.f;
  for (auto component : TextRenderComponents) {
    component->SetRelativeLocation(FVector(x, 0, -Radius));
    x += component->Bounds.BoxExtent.X + CharSpacing;
  }
};
