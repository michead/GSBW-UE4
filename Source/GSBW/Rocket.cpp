// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "Rocket.h"
#include "Earth.h"

DEFINE_LOG_CATEGORY(Rocket);

// Sets default values
ARocket::ARocket() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
  StaticMeshComponent->SetEnableGravity(false);
  StaticMeshComponent->SetSimulatePhysics(true);
  StaticMeshComponent->SetCollisionProfileName("Rocket");
  StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ARocket::OnOverlapBegin);
  RootComponent = StaticMeshComponent;
}

void ARocket::OnConstruction(const FTransform& Transform) {
  StaticMeshComponent->SetStaticMesh(StaticMesh);
}

// Called when the game starts or when spawned
void ARocket::BeginPlay() {
  Super::BeginPlay();
}

// Called every frame
void ARocket::Tick( float DeltaTime ) {
  Super::Tick( DeltaTime );
}

void ARocket::Init(const FRocketInitProps& props) {
  Letter = props.letter;
  Type = props.type;
  Speed = props.speed;
  Target = props.target;

  ApplyImpulse();
}

void ARocket::ApplyImpulse() {
  FVector direction = (Target->GetActorLocation() - GetActorLocation());
  direction.Normalize();

  // Self-apply impulse
  StaticMeshComponent->AddImpulse(direction * Speed);
}

void ARocket::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                             class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
  UE_LOG(Rocket, Log, TEXT("OnOverlapBegin() called."));
  if (Cast<AAsteroid>(OtherActor)) {
    Explode(SweepResult);
  }
}

void ARocket::Explode(const FHitResult& hit) {
  UE_LOG(Rocket, Log, TEXT("Explode() called."));
  if (ExplosionClass) {
    // Spawn explosion actor
    GetWorld()->SpawnActor<AExplosion>(ExplosionClass);
  }
  // Destroy actor on next tick in order to allow overlap events to be sent to both sides
  GSBWUtils::DestroyOnNextTick<ARocket>(GetWorld(), this, &ARocket::Disappear);
}

void ARocket::Disappear() {
  Destroy();
}
