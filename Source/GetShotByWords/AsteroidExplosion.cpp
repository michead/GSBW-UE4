// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "GameUtils.h"
#include "AsteroidExplosion.h"
#include "Engine/DestructibleMesh.h"

// Sets default values
AAsteroidExplosion::AAsteroidExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
}

// Called when the game starts or when spawned
void AAsteroidExplosion::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(EXPLOSION_DURATION);
	Explode();
}

// Called every frame
void AAsteroidExplosion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAsteroidExplosion::OnConstruction(const FTransform& transform)
{
	GetAndSetDestructibleMesh();

	destructMesh->SetRelativeLocation(FVector::ZeroVector);
	destructMesh->AttachTo(RootComponent);

	destructMesh->SetSimulatePhysics(true);
	destructMesh->SetEnableGravity(false);

	destructMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AAsteroidExplosion::GetAndSetDestructibleMesh()
{
	float radius = staticMesh->GetCollisionShape().GetSphereRadius();
	FString meshPath = "/Game/Meshes/D_Shape_Sphere_";
	// meshPath.AppendInt((int)radius);

	static ConstructorHelpers::FObjectFinder<UDestructibleMesh> AsteroidAsset(*meshPath);
	if (AsteroidAsset.Succeeded())
	{
		destructMesh->SetDestructibleMesh(AsteroidAsset.Object);
	}

	destructMesh->SetMaterial(0, staticMesh->GetMaterial(0)->GetMaterial());
}

void AAsteroidExplosion::Explode()
{
	destructMesh->ApplyDamage(ROCKET_DAMAGE_AMOUNT, GetImpactLocation(), GetImpulseDirection(), ROCKET_IMPULSE_STRENGTH);
}

FVector AAsteroidExplosion::GetImpactLocation()
{
	return GetActorLocation() - GetImpulseDirection() * destructMesh->GetCollisionShape().GetSphereRadius() * 0.5f;
}

FVector AAsteroidExplosion::GetImpulseDirection()
{
	FVector earthLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector direction = GetActorLocation() - earthLocation;
	direction.Normalize();

	return direction;
}

