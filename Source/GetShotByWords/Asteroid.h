// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class GETSHOTBYWORDS_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Hit(class AActor* SelfActor, class AActor* OtherActor, FVector NormalImpulse, struct FHitResult Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rendering)
	UStaticMeshComponent* mesh;

	FString word;
};
