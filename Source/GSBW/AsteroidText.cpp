// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "AsteroidText.h"


// Sets default values for this component's properties
AAsteroidText::AAsteroidText() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts
void AAsteroidText::BeginPlay() {
  Super::BeginPlay();
}

// Called every frame
void AAsteroidText::Tick(float DeltaSeconds) {
  Super::Tick(DeltaSeconds);

  // ...
}

void AAsteroidText::Init(FString Word) {
  this->Word = Word;
  
  AttachTextComponents();
}

void AAsteroidText::OnConstruction(const FTransform & Transform) {
  Super::OnConstruction(Transform);

  AttachTextComponents();
}

void AAsteroidText::DestroyLastChar() {
  Word.RemoveAt(Word.Len() - 1);
  TextRenderComponents[Word.Len() - 1]->DestroyComponent();
}

void AAsteroidText::AttachTextComponents() {
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
