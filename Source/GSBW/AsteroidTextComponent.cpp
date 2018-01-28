// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "AsteroidTextComponent.h"


// Sets default values for this component's properties
UAsteroidTextComponent::UAsteroidTextComponent() {
  PrimaryComponentTick.bCanEverTick = false;
}

void UAsteroidTextComponent::Init(const FAsteroidTextComponentInitProps& Props) {
  Word = Props.word;
  RootComponent = Props.rootComponent;

  AttachTextComponents();
}

void UAsteroidTextComponent::DestroyLastChar() {
  Word.RemoveAt(Word.Len() - 1);
  TextRenderComponents[Word.Len() - 1]->DestroyComponent();
}

void UAsteroidTextComponent::AttachTextComponents() {
  bool bWordChanged = InitialWord != Word;

  InitialWord = Word;

  if (bWordChanged) {
    for (auto component : TextRenderComponents) {
      if (component) {
        component->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
        component->DestroyComponent();
      }
    }

    TextRenderComponents.Empty();

    for (TCHAR c : Word) {
      TextRenderComponents.Push(NewObject<UTextRenderComponent>(this, UTextRenderComponent::StaticClass()));
    }
  }

  uint8_t i = 0;
  float x = -((TextRenderComponents.Num() - (TextRenderComponents.Num() % 2 == 0 ? 1 : 0)) / 2) * CharSpacing;
  for (auto component : TextRenderComponents) {
    component->SetWorldRotation(BaseRotation);
    component->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    component->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
    component->SetRelativeLocation(FVector(x, 0, -Radius));
    component->SetText(FString("").AppendChar(Word[i]));
    component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    x += CharSpacing;
    i += 1;
  }
};
