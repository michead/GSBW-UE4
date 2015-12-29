// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Asteroid.h"
#include "GameplayHUD.h"
#include "GameFramework/Pawn.h"
#include "Earth.generated.h"

UCLASS()
class GETSHOTBYWORDS_API AEarth : public APawn
{
	GENERATED_BODY()

	bool isInputEnabled;

public:
	// Sets default values for this pawn's properties
	AEarth();

	virtual void OnConstruction(const FTransform& transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rendering)
	UStaticMeshComponent* mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FVector cameraOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FRotator cameraRotation;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	float GetEarthRadius();

	void NotifyEnemyHit();
	void NotifyEnemyDown();
	void SwitchTarget();
	void NotifyAsteroidHit(int damage);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void EndGame();

	AAsteroid* target;
	int8 currentIndex;
	float forceMagnitude;

	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
	int32 health;

	UPROPERTY(BlueprintReadWrite, Category = Gameplay)
	int32 initialHealth;

	int32 score;
};
