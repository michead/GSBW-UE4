// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "Earth.h"
#include "Rocket.h"
#include "GSBWCommon.h"
#include "GSBWUtils.h"
#include "AsteroidExplosion.h"
#include "Asteroid.h"


// Sets default values
AAsteroid::AAsteroid() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Default value for AsteroidTextComponent class
  AsteroidTextComponentClass = UAsteroidTextComponent::StaticClass();

  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
  StaticMeshComponent->SetEnableGravity(false);
  StaticMeshComponent->SetSimulatePhysics(true);
  StaticMeshComponent->SetCollisionProfileName("Asteroid");
  StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlapBegin);
  SetRootComponent(StaticMeshComponent);

  RocketCount = 0;
}

void AAsteroid::OnConstruction(const FTransform& Transform) {
  Super::OnConstruction(Transform);

  StaticMeshComponent->SetStaticMesh(StaticMesh);
  AsteroidTextComponent = NewObject<UAsteroidTextComponent>(this, AsteroidTextComponentClass);

  // Set default value mostly for debugging purposes
  WordToDisplay = Word;

  AttachFloatingText();
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay() {
  Super::BeginPlay();
}

// Called every frame
void AAsteroid::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
}

void AAsteroid::Init(const FAsteroidInitProps& props) {
  Type = props.type;
  Word = props.word;
  Speed = props.speed;

  WordToDisplay = Word;

  AttachFloatingText();
  ApplyImpulse();
}

void AAsteroid::AttachFloatingText() {
  FAsteroidTextComponentInitProps props = {};
  props.rootComponent = RootComponent;
  props.word = WordToDisplay;
  AsteroidTextComponent->Init(props);
  check(AsteroidTextComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform));
}

void AAsteroid::ApplyImpulse() {
  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEarth::StaticClass(), actors);

  FVector direction = (actors[0]->GetActorLocation() - GetActorLocation());
  direction.Normalize();

  // Self-apply impulse
  StaticMeshComponent->AddImpulse(direction * Speed);
}

void AAsteroid::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                               class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<AEarth>(OtherActor)) {
		OnEarthHit(OtherActor, SweepResult);
	} else if (Cast<ARocket>(OtherActor)
          && Cast<ARocket>(OtherActor)->GetTargetID() == GetUniqueID()) {
		OnRocketHit(OtherActor, SweepResult);
	}
}

void AAsteroid::OnEarthHit(class AActor* Actor, const FHitResult& Hit) {
  // Let Earth broadcast the event, just explode
  Explode(Hit);
}

void AAsteroid::OnRocketHit(class AActor* Actor, const FHitResult& Hit) {
  uint32 rocketLetterIndex = Cast<ARocket>(Actor)->LetterIndex;
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::ASTEROID_HIT);
  
  RocketCount++;

  AsteroidTextComponent->DestroyLetterAt(rocketLetterIndex);
  if (WordToDisplay.Len() == RocketCount) {
    Explode(Hit);
  }
}

void AAsteroid::Explode(const FHitResult& Hit) {
  // Notify other actors about event
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::ASTEROID_DOWN);

  // Spawn explosion
  AAsteroidExplosion* explosion = GetWorld()->SpawnActor<AAsteroidExplosion>(GetActorLocation(), GetActorRotation());
  explosion->Init({ DestructibleMesh, Hit });

  // Destroy static mesh
  Disappear();
}

FString AAsteroid::GetWord() const {
  return WordToDisplay;
}

void AAsteroid::Disappear() {
  Destroy();
}