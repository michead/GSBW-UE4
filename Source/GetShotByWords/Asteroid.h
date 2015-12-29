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

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rendering)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rendering)
	UTextRenderComponent* textComp;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void NotifyRocketHit();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void NotifyDestroy();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	float GetAsteroidRadius();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void SetWord(FString w);

	FString word;
	int initialWordLen;
};
