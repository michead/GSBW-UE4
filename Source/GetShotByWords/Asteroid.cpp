// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "Asteroid.h"


// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->AttachTo(RootComponent);
	
	FScriptDelegate hitDelegate;
	hitDelegate.BindUFunction(this, TEXT("Hit"));
	this->OnActorHit.AddUnique(hitDelegate);

	// TODO To be removed
	word = "ciao";
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsteroid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAsteroid::Hit(class AActor* SelfActor, class AActor* OtherActor, FVector NormalImpulse, struct FHitResult Hit)
{
	check(GEngine);

	GEngine->AddOnScreenDebugMessage(0, 0, FColor::Red, TEXT("Asteroid hit!"));
}

