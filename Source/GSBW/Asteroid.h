// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GSBWCommon.h"
#include "AsteroidStructs.h"
#include "AsteroidText.h"
#include "Asteroid.generated.h"

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
  virtual void OnExplodeAction() {} // PURE_VIRTUAL

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  UStaticMeshComponent* StaticMeshComponent;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  UStaticMesh* StaticMesh;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  UDestructibleMesh* DestructibleMesh;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Gameplay)
  TSubclassOf<AAsteroidText> AsteroidTextClass;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=CPP_Gameplay)
  AAsteroidText* AsteroidText;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Gameplay)
  FString Word;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Gameplay)
  EAsteroidType Type;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Gameplay)
  float Speed;

  // Returns current asteroid word (which might be truncated wrt the original one)
  FString GetWord() const;

protected:
  void AttachFloatingText();
  void ApplyImpulse();

  // Asteroid protected virtual methods
  virtual void Disappear();
  virtual void Explode(const FHitResult& hit);
  virtual void OnEarthHit(class AActor* Actor, const FHitResult& hit);
  virtual void OnRocketHit(class AActor* Actor, const FHitResult& hit);

  UFUNCTION()
  void OnOverlapBegin(
    class UPrimitiveComponent* OverlappedComp,
    class AActor* OtherActor,
    class UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult);

  FString WordToDisplay;
};
