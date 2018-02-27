// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Explosion.h"
#include "RocketStructs.h"
#include "Rocket.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Rocket, Log, All);

UCLASS()
class GSBW_API ARocket : public AActor
{
  GENERATED_BODY()
	
public:	
  // Sets default values for this actor's properties
  ARocket();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
	
  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

  virtual void OnConstruction(const FTransform& Transform) override;

  // Asteroid virtual methods
  virtual void Init(const FRocketInitProps& props);
	
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  UStaticMesh* StaticMesh;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  UStaticMeshComponent* StaticMeshComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  FString Letter;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  ERocketType Type;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  UProjectileMovementComponent* ProjectileMovementComponent;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CPP_Rendering)
  TSubclassOf<AEmitter> SmokeEmitterClass;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  AAsteroid* Target;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  TSubclassOf<AExplosion> ExplosionClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Gameplay)
  float DeltaHomingAcceleration;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Gameplay)
  float MaxHomingAcceleration;

protected:
  void IncreaseHomingAcceleration(float DeltaTime);
  void Explode(const FHitResult& hit);
  void Disappear();

  UFUNCTION()
  void OnOverlapBegin(
    class UPrimitiveComponent* OverlappedComp,
    class AActor* OtherActor,
    class UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult);

  AEmitter* SmokeEmitter;
  FVector PrevLocation;
  float Speed;
};
