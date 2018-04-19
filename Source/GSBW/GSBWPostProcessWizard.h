// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GSBWPostProcessWizard.generated.h"

UCLASS()
class GSBW_API AGSBWPostProcessWizard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGSBWPostProcessWizard();
  
  // Called every frame
  virtual void Tick(float DeltaTime) override;
  
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
  void OnAsteroidHit();
  
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
  void OnAsteroidDown();
  
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
  void OnEarthHit();
  
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
  void OnEarthDown();

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=CPP_Rendering)
  APostProcessVolume* PostProcessVolume;
  
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
  
  FScriptDelegate AsteroidHitDelegate;
  FScriptDelegate AsteroidDownDelegate;
  FScriptDelegate EarthHitDelegate;
  FScriptDelegate EarthDownDelegate;
};
