// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "Rocket.h"


// Sets default values
ARocket::ARocket() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
  StaticMeshComponent->SetEnableGravity(false);
  StaticMeshComponent->SetSimulatePhysics(true);
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
