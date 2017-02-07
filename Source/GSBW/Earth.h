// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Asteroid.h"
#include "Earth.generated.h"

UCLASS()
class GSBW_API AEarth : public APawn
{
	GENERATED_BODY()
	
public:	
  // Sets default values for this actor's properties
  AEarth();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
	
  // Called every frame
  virtual void Tick( float DeltaSeconds ) override;

  virtual void OnConstruction(const FTransform& Transform) override;
  virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

  // Called when rocket hits target
  void OnTargetHit(AAsteroid& Asteroid);

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Camera)
  UCameraComponent* Camera;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  UDestructibleMesh* DestructibleMesh;

private:
  // Binding for player input
  void HandleInput(float AxisScale);
  // Returns true if target has been acquired
  bool AcquireTarget(FString& InputLetters);
  // Returns true if rocket has been shot to target
  bool ShootTarget(FString& InputLetters);
  void LaunchRocket(AAsteroid* Target, const FString& letter);

  UDestructibleComponent* DestructibleComponent;
  TArray<FString> Alphabet;
  AAsteroid* target;
  UClass* BaseRocketBPClass;
};
