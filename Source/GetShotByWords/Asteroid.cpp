// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "Earth.h"
#include "GameUtils.h"
#include "Asteroid.h"


// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RocketAsset(TEXT("/Game/Meshes/Shape_Sphere"));
	if (RocketAsset.Succeeded())
	{
		mesh->SetStaticMesh(RocketAsset.Object);
	}
	mesh->AttachTo(RootComponent);

	mesh->SetSimulatePhysics(true);
	mesh->SetEnableGravity(false);

	// TODO To be removed
	word = "ciao";
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(ASTEROID_LIFESPAN);
}

// Called every frame
void AAsteroid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAsteroid::NotifyRocketHit()
{
	word.RemoveAt(0);
	Cast<AEarth>(GetWorld()->GetFirstPlayerController()->GetPawn())->NotifyEnemyHit();

	if (!word.Len()) NotifyDestroy();
}

void AAsteroid::NotifyDestroy()
{
	Cast<AEarth>(GetWorld()->GetFirstPlayerController()->GetPawn())->NotifyEnemyDown();
	Destroy();
}

