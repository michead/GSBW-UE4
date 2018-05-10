// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GSBWCommon.h"
#include "AsteroidStructs.h"
#include "AsteroidTextComponent.h"
#include "Asteroid.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Asteroid, Log, All);

UCLASS()
class GSBW_API AAsteroid : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AAsteroid();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

  virtual void OnConstruction(const FTransform& Transform) override;

  // Asteroid public virtual methods
  virtual void Init(const FAsteroidInitProps& props);
  
  // Asteroid special actions
  virtual void OnEarthHitAction() {}
  virtual void OnRocketHitAction() {}
  virtual void OnExplodeAction() {}
  
  UFUNCTION()
  void OnAsteroidTimeScaleChange();

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  UStaticMeshComponent* StaticMeshComponent;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  UStaticMesh* StaticMesh;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  UDestructibleMesh* DestructibleMesh;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Gameplay)
  TSubclassOf<UAsteroidTextComponent> AsteroidTextComponentClass;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=CPP_Gameplay)
  UAsteroidTextComponent* AsteroidTextComponent;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Gameplay)
  FString Word;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Gameplay)
  EAsteroidType Type;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Gameplay)
  float EffectDuration;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Gameplay)
  float Speed;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Gameplay)
  FVector Torque;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  int32 RocketCount;
  
  // UAsteroidTextComponent Props
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FRotator BaseTextRotation;
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Rendering)
  TSubclassOf<UTextRenderComponent> TextRenderComponentClass;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float FontScalingFactor;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FColor TextColor;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float CharSpacing;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float MinRadius;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float MaxRadius;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  float WordLenRadiusConstantFactor;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FVector2D TextSphericalPositionOffset;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  FVector TextWorldRotationAxis;

  // Returns current asteroid word (which might be truncated wrt the original one)
  UFUNCTION()
  FString GetWord() const;
  
  UFUNCTION()
  virtual void Explode(const FHitResult& hit, bool TriggerEffect = true);
  
  UFUNCTION()
  virtual void SetIsTarget(bool IsTarget);

protected:
  void InitTextComponent();
  void ApplyImpulse();
  void ScaleAccordingToWordLen();

  // Asteroid protected virtual methods
  virtual void Disappear();
  virtual void OnEarthHit(class AActor* Actor, const FHitResult& hit);
  virtual void OnRocketHit(class AActor* Actor, const FHitResult& hit);
  virtual void OnDestruction();
  virtual void RestoreAsteroidTimeScale();

  UFUNCTION()
  void OnOverlapBegin(
    class UPrimitiveComponent* OverlappedComp,
    class AActor* OtherActor,
    class UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult);

  FString WordToDisplay;
  FScriptDelegate AsteroidTimeScaleChangeDelegate;
  FTimerHandle DisableEffectTimerHandle;
  FTimerHandle DestroyTimerHandle;
};
