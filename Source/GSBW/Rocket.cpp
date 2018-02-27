// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "Rocket.h"
#include "Earth.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY(Rocket);

// Sets default values
ARocket::ARocket() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
  StaticMeshComponent->SetCollisionProfileName("Rocket");
  StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ARocket::OnOverlapBegin);

  RootComponent = StaticMeshComponent;

  ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

  // Previous location is using for aligning the rocket with the movement direction
  PrevLocation = { 0, 0, 0 };
}

void ARocket::OnConstruction(const FTransform& Transform) {
  Super::OnConstruction(Transform);

  StaticMeshComponent->SetStaticMesh(StaticMesh);
}

// Called when the game starts or when spawned
void ARocket::BeginPlay() {
  Super::BeginPlay();

  SmokeEmitter = GetWorld()->SpawnActor<AEmitter>(SmokeEmitterClass);
  SmokeEmitter->SetActorRelativeRotation(FRotator(0, 0, 0));
  SmokeEmitter->SetActorRelativeLocation(-RootComponent->Bounds.SphereRadius * GetActorUpVector());
  SmokeEmitter->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

  // Aim target
  ProjectileMovementComponent->bIsHomingProjectile = true;
}

// Called every frame
void ARocket::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  if (Target) {
    IncreaseHomingAcceleration(DeltaTime);
  }
}

void ARocket::IncreaseHomingAcceleration(float DeltaTime) {
  float newAccelerationMagnitude = ProjectileMovementComponent->HomingAccelerationMagnitude += DeltaHomingAcceleration * DeltaTime;
  ProjectileMovementComponent->HomingAccelerationMagnitude = FMath::Min(MaxHomingAcceleration, newAccelerationMagnitude);
}

void ARocket::Init(const FRocketInitProps& props) {
  Letter = props.letter;
  Type = props.type;
  Target = props.target;
  // Currently ignored
  Speed = props.speed;

  ProjectileMovementComponent->UpdatedComponent = RootComponent;
  ProjectileMovementComponent->ProjectileGravityScale = 0;
  ProjectileMovementComponent->HomingTargetComponent = Target->GetRootComponent();
  ProjectileMovementComponent->HomingAccelerationMagnitude = 0;
  ProjectileMovementComponent->bRotationFollowsVelocity = true;
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
