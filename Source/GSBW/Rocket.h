// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RocketStructs.h"
#include "Rocket.generated.h"

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
  virtual void Tick( float DeltaSeconds ) override;

  virtual void OnConstruction(const FTransform& Transform) override;

  // Asteroid virtual methods
  virtual void Init(const FRocketInitProps& props);
	
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  UStaticMesh* StaticMesh;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  FString Letter;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  ERocketType Type;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  float Speed;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CPP_Gameplay)
  AAsteroid* Target;

protected:
  void ApplyImpulse();

  UStaticMeshComponent* StaticMeshComponent;
};
