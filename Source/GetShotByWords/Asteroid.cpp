// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "Earth.h"
#include "AsteroidExplosion.h"
#include "GameUtils.h"
#include "Asteroid.h"


// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RocketAsset(TEXT("/Game/Meshes/Shape_Sphere"));
	if (RocketAsset.Succeeded())
	{
		mesh->SetStaticMesh(RocketAsset.Object);
	}
	mesh->SetRelativeLocation(FVector(0));
	mesh->SetRelativeRotation(FRotator::ZeroRotator);
	mesh->SetSimulatePhysics(true);
	mesh->SetEnableGravity(false);
	mesh->SetCollisionProfileName("OverlapAll");
	mesh->bGenerateOverlapEvents = true;

	RootComponent = mesh;

	textComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	textComp->AttachTo(RootComponent);
	textComp->SetRelativeLocation(FVector(0, 0, 2 * GetAsteroidRadius()));
	textComp->SetRelativeRotation(FRotator(90, 0, 180));
	textComp->SetTextRenderColor(FColor::Blue);
	textComp->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
	textComp->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	textComp->SetXScale(2);
	textComp->SetYScale(2);
	textComp->SetMobility(EComponentMobility::Movable);
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
	textComp->SetText(word);

	Cast<AEarth>(GetWorld()->GetFirstPlayerController()->GetPawn())->NotifyEnemyHit();

	if (word.IsEmpty()) NotifyDestroy();
}

void AAsteroid::NotifyDestroy()
{
	Cast<AEarth>(GetWorld()->GetFirstPlayerController()->GetPawn())->NotifyEnemyDown();
	SpawnExplosion(GetWorld(), GetTransform(), mesh);
	Destroy();
}

float AAsteroid::GetAsteroidRadius()
{
	return mesh->GetCollisionShape().GetSphereRadius();
}

void AAsteroid::SetWord(FString w)
{
	word = w;
	textComp->SetText(word);
	initialWordLen = word.Len();
}

void AAsteroid::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AEarth* earth = Cast<AEarth>(OtherActor);

	if (earth)
	{
		earth->NotifyAsteroidHit(initialWordLen);
		SpawnExplosion(GetWorld(), GetTransform(), mesh);
		Destroy();
	}
}