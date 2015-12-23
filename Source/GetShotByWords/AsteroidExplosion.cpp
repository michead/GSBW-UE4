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

	destructMesh = CreateDefaultSubobject <UDestructibleComponent>("DestructibleMesh");

	FString meshPath = "/Game/Meshes/D_Shape_Sphere";
	static ConstructorHelpers::FObjectFinder<UDestructibleMesh> AsteroidAsset(*meshPath);
	if (AsteroidAsset.Succeeded())
	{
		destructMesh->SetDestructibleMesh(AsteroidAsset.Object);
	}

	RootComponent = destructMesh;
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

	FadeOut(DeltaTime);
}

void AAsteroidExplosion::OnConstruction(const FTransform& transform)
{
	SetDestructibleMeshProps();



	destructMesh->SetSimulatePhysics(true);
	destructMesh->SetEnableGravity(false);

	destructMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AAsteroidExplosion::SetDestructibleMeshProps()
{
	float radius = staticMesh->GetCollisionShape().GetSphereRadius();
	
	// TODO Set scale
	// destructMesh->SetWorldScale3D(FVector(radius));

	dynamicMaterial = UMaterialInstanceDynamic::Create(staticMesh->GetMaterial(0)->GetMaterial(), this);
	destructMesh->SetMaterial(0, dynamicMaterial);
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

void AAsteroidExplosion::FadeOut(float DeltaTime)
{
	float currentOpacity;
	dynamicMaterial->GetScalarParameterValue("Opacity", currentOpacity);
	dynamicMaterial->SetScalarParameterValue("Opacity", currentOpacity - DeltaTime * EXPLOSION_FADEOUT_SPEED);
}

