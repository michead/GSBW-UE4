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

  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
  StaticMeshComponent->SetEnableGravity(false);
  StaticMeshComponent->SetSimulatePhysics(true);
  StaticMeshComponent->SetCollisionProfileName("Asteroid");
  StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlapBegin);
  SetRootComponent(StaticMeshComponent);

  TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
}

void AAsteroid::OnConstruction(const FTransform& Transform) {
  StaticMeshComponent->SetStaticMesh(StaticMesh);
  TextRenderComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay() {
  Super::BeginPlay();
}

// Called every frame
void AAsteroid::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  // Update word
  TextRenderComponent->SetText(WordToDisplay);
}

void AAsteroid::Init(const FAsteroidInitProps& props) {
  Type = props.type;
  Word = props.word;
  Speed = props.speed;

  WordToDisplay = Word;

  ApplyImpulse();
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
	} else if (Cast<ARocket>(OtherActor)) {
		OnRocketHit(OtherActor, SweepResult);
	}
}

void AAsteroid::OnEarthHit(class AActor* Actor, const FHitResult& Hit) {
  // Let Earth broadcast the event, just explode
  Explode(Hit);
}

void AAsteroid::OnRocketHit(class AActor* Actor, const FHitResult& Hit) {
  FString rocketLetter = Cast<ARocket>(Actor)->Letter;
  if (!rocketLetter.Equals(GSBWUtils::GetFirstChar(WordToDisplay))) {
    // Letter field in rocket object does not match asteroid's first letter, do nothing
    return;
  }

  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::ASTEROID_HIT);
  WordToDisplay.RemoveAt(0);
  
  if (WordToDisplay.IsEmpty()) {
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