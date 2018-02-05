// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GSBWGameMode.h"
#include "GSBWWorldSettings.h"
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

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Camera)
  UCameraComponent* Camera;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CPP_Camera)
  float DistanceFromCamera;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rendering)
  UDestructibleMesh* DestructibleMesh;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=CPP_Rocket)
  TSubclassOf<ARocket> BaseRocketClass;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Gameplay)
  int32 Health;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Gameplay)
  int32 MaxHealth;

private:
  // Binding for player input
  void HandleInput(FString letter);
#pragma region Input Delegates
  void HandleA() { HandleInput("A"); }
  void HandleB() { HandleInput("B"); }
  void HandleC() { HandleInput("C"); }
  void HandleD() { HandleInput("D"); }
  void HandleE() { HandleInput("E"); }
  void HandleF() { HandleInput("F"); }
  void HandleG() { HandleInput("G"); }
  void HandleH() { HandleInput("H"); }
  void HandleI() { HandleInput("I"); }
  void HandleJ() { HandleInput("J"); }
  void HandleK() { HandleInput("K"); }
  void HandleL() { HandleInput("L"); }
  void HandleM() { HandleInput("M"); }
  void HandleN() { HandleInput("N"); }
  void HandleO() { HandleInput("O"); }
  void HandleP() { HandleInput("P"); }
  void HandleQ() { HandleInput("Q"); }
  void HandleR() { HandleInput("R"); }
  void HandleS() { HandleInput("S"); }
  void HandleT() { HandleInput("T"); }
  void HandleU() { HandleInput("U"); }
  void HandleV() { HandleInput("V"); }
  void HandleW() { HandleInput("W"); }
  void HandleX() { HandleInput("X"); }
  void HandleY() { HandleInput("Y"); }
  void HandleZ() { HandleInput("Z"); }
#pragma endregion
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
  // Toggle pause menu
  void TogglePause();
  // Explode once health reaches 0
  void Explode();
  // Destroy actor
  void Disappear();

  UFUNCTION()
  void OnOverlapBegin(
    class UPrimitiveComponent* OverlappedComp,
    class AActor* OtherActor,
    class UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult);

  UDestructibleComponent* DestructibleComponent;
  FTimerHandle TimerHandle;
  TArray<FString> Alphabet;
  AGSBWWorldSettings* WorldSettings;
  FTarget Target;
  float OldAlphaKey;
};
