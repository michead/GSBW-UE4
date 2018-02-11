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
  StaticMeshComponent->SetEnableGravity(false);
  StaticMeshComponent->SetCollisionProfileName("Rocket");
  StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ARocket::OnOverlapBegin);
  StaticMeshComponent->SetMobility(EComponentMobility::Movable);
  RootComponent = StaticMeshComponent;
}

void ARocket::OnConstruction(const FTransform& Transform) {
  Super::OnConstruction(Transform);

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

  FVector direction = (Target->GetActorLocation() - GetActorLocation());
  direction.Normalize();

  AlignWithVector(direction);
  ApplyImpulse(direction);
}

void ARocket::ApplyImpulse(const FVector& Direction) {
  // Enable physics simulation
  StaticMeshComponent->SetSimulatePhysics(true);
  // Self-apply impulse
  StaticMeshComponent->AddImpulse(Direction * Speed);
}

void ARocket::AlignWithVector(const FVector& Vector) {
  // Disable physics simulation
  StaticMeshComponent->SetSimulatePhysics(false);
  FVector origin = GetActorLocation();
  FVector axisX = ((origin + GetActorForwardVector()) - origin);
  FVector axisY = (Target->GetActorLocation()) - origin;
  FVector axisZ = FVector::CrossProduct(axisX, axisY);
  axisX.Normalize();
  axisY.Normalize();
  axisZ.Normalize();
  float angle = FMath::Acos(FVector::DotProduct(axisX, axisY));
  FRotator rotator = UKismetMathLibrary::RotatorFromAxisAndAngle(axisZ, angle);
  SetActorRotation(rotator);
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
