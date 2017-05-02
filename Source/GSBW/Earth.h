// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GSBWGameMode.h"
#include "Asteroid.h"
#include "Rocket.h"
#include "EarthStructs.h"
#include "Earth.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Earth, Log, All);

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

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rocket)
  TSubclassOf<ARocket> BaseRocketClass;

private:
  // Binding for player input
  void HandleInput(float AxisScale);
  // Returns true if target has been acquired
  bool AcquireTarget(FString& InputLetters);
  // Returns true if rocket has been shot to target
  void ShootTarget(FString& InputLetters);
  // Spawn rocket
  void LaunchRocket();
  // Returns the initial speed next rocket should have
  float GetNextRocketSpeed();
  // Clear reference to current target
  void ClearTarget();

  UDestructibleComponent* DestructibleComponent;
  TArray<FString> Alphabet;
  FTarget Target;
  float OldAlphaKey;
};
