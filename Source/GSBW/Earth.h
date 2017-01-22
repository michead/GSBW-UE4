// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Earth.generated.h"

UCLASS()
class GSBW_API AEarth : public AActor
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

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=CPP_Rendering)
  UDestructibleMesh* Mesh;

private:
  UDestructibleComponent* DestructibleComponent;
};
