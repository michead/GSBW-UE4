// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "GameUtils.h"
#include "Rocket.h"


// Sets default values
ARocket::ARocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->AttachTo(RootComponent);
	mesh->SetSimulatePhysics(true);
	mesh->SetEnableGravity(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> RocketAsset(TEXT("/Game/Meshes/Shape_Sphere"));
	if (RocketAsset.Succeeded())
	{
		mesh->SetWorldScale3D(FVector(.25f));
		mesh->SetStaticMesh(RocketAsset.Object);
	}
	
	mesh->bGenerateOverlapEvents = true;
	mesh->SetCollisionProfileName("OverlapAll");
}

// Sets default values
ARocket::ARocket(AAsteroid* asteroid) : target(asteroid)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARocket::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ARocket::Fire()
{

}

void ARocket::NotifyActorBeginOverlap(AActor* OtherActor)
{
	check(GEngine);

	if (OtherActor == target && target->word.GetCharArray()[0] == letter)
	{
		target->NotifyRocketHit();
		Destroy();
	}
}