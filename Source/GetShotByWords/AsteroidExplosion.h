// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AsteroidExplosion.generated.h"

UCLASS()
class GETSHOTBYWORDS_API AAsteroidExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidExplosion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnConstruction(const FTransform& transform) override;

	void AAsteroidExplosion::SetDestructibleMeshProps();

	void Explode();

	void FadeOut(float DeltaTime);

	FVector GetImpactLocation();
	FVector GetImpulseDirection();

	UStaticMeshComponent* staticMesh;
	UDestructibleComponent* destructMesh;
	UMaterialInstanceDynamic* dynamicMaterial;
};
