// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Asteroid.h"
#include "GameFramework/Actor.h"
#include "Rocket.generated.h"

UCLASS()
class GETSHOTBYWORDS_API ARocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARocket();

	ARocket(AAsteroid* asteroid);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Fire();

	AAsteroid* target;
};
