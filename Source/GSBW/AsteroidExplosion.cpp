// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "AsteroidExplosion.h"


// Sets default values
AAsteroidExplosion::AAsteroidExplosion() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleComponent"));
  DestructibleComponent->SetEnableGravity(false);
  DestructibleComponent->SetSimulatePhysics(true);
  DestructibleComponent->SetCollisionProfileName(FName("OverlapAll"));
  SetRootComponent(DestructibleComponent);
}

void AAsteroidExplosion::Init(const FAsteroidExplosionInitProps& props) {
  Hit = props.hit;
  Mesh = props.mesh;

  DestructibleComponent->SetDestructibleMesh(Mesh);

  ApplyDamage();
}

void AAsteroidExplosion::ApplyDamage() {
  DestructibleComponent->ApplyDamage(ROCKET_HIT_DAMAGE_AMOUNT, Hit.ImpactPoint, -Hit.ImpactNormal, ROCKET_HIT_IMPULSE_STRENGTH);
  const FTimerDelegate DisappearDelegate = FTimerDelegate::CreateUObject(this, &AAsteroidExplosion::Disappear);
  GetWorldTimerManager().SetTimer(TimerHandle, DisappearDelegate, ASTEROID_EXPLOSION_DURATION, false);
}

void AAsteroidExplosion::Disappear() {
  Destroy();
}
