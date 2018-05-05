// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWCommon.h"
#include "AsteroidTextComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UAsteroidTextComponent::UAsteroidTextComponent() {
  PrimaryComponentTick.bCanEverTick = false;
  
  Radius = 10;
  CharSpacing = 10;
  DistanceFromSurface = 2.f;
  AngleBetweenLetters = 20.f;
  RotationSpeed = .8f;
  SphericalPositionOffset = { 0.f, 0.f };
  WorldRotationAxis = { 1.f, 0.f, 0.f };
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
  WorldRotationAxis = Props.textWorldRotationAxis;
  SphericalPositionOffset = Props.sphericalPositionOffset;

  InitAsteroidLetterComponents();
}

FVector2D UAsteroidTextComponent::GetTextForwardVector() const {
  float angle = FMath::DegreesToRadians<float>(AngleBetweenLetters);
  float totalAngle = angle * (TextRenderComponents.Num() - 1);
  
  return FVector(0, 0, -1).UnitCartesianToSpherical() + SphericalPositionOffset;
}

FVector2D UAsteroidTextComponent::GetBaseTextLocation() const {
  float angle = FMath::DegreesToRadians<float>(AngleBetweenLetters);
  float totalAngle = angle * (TextRenderComponents.Num() - 1);
  
  return GetTextForwardVector() + FVector2D(totalAngle / 2.f, 0.f);
}

void UAsteroidTextComponent::UpdatePosition(float DeltaTime) {
  WorldRotationAxis.Normalize();
  SphericalPositionOffset += RotationSpeed * DeltaTime * FVector2D(1.f, 0.f);
  
  float angle = FMath::DegreesToRadians<float>(AngleBetweenLetters);
  FVector worldForward = FVector(0, 0, -1);
  FVector2D forward = GetTextForwardVector();
  FVector2D baseLoc = GetBaseTextLocation();
  
  for (auto component : TextRenderComponents) {
    FVector dir = baseLoc.SphericalToUnitCartesian();
    component->SetWorldLocation(RootComponent->GetComponentLocation() + dir * (Radius + DistanceFromSurface));
    
    float alpha = FMath::RadiansToDegrees<float>(FMath::Acos(FVector::DotProduct(dir, worldForward)));
    bool bPlus = FVector::DotProduct(FVector::CrossProduct(dir, worldForward), FVector(0, 1, 0)) > 0;
    float rotAngle = bPlus ? alpha : -alpha;
    FRotator deltaRotation = FRotator(WorldRotationAxis.X, WorldRotationAxis.Y, WorldRotationAxis.Z) * rotAngle;
    component->SetWorldRotation(UKismetMathLibrary::ComposeRotators(BaseRotation, deltaRotation));
    
    baseLoc -= FVector2D(angle, 0.f);
  }
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

  for (TCHAR c : Word) {
    auto component = NewObject<UTextRenderComponent>(this, TextRenderComponentClass);
    
    component->RegisterComponent();
    component->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    component->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
    component->SetWorldScale3D(FVector(FontScalingFactor));
    component->SetText(FText::FromString(FString("").AppendChar(c)));
    component->SetTextRenderColor(TextColor);
    component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    
    UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(component->GetMaterial(0), this);
    component->SetMaterial(0, material);
    material->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(TextColor));
      
    TextRenderComponents.Push(component);
  }
  
  UpdatePosition(0);
};
