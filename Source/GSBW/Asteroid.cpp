// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "Rocket.h"
#include "GSBWCommon.h"
#include "GSBWUtils.h"
#include "Asteroid.h"


// Sets default values
AAsteroid::AAsteroid() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Attach Destructible Mesh as Root Component
  DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("RootComponent"));
  RootComponent = DestructibleComponent;
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
}

void AAsteroid::OnEarthHit(const FHitResult& hit) {

}

void AAsteroid::OnRocketHit(const FHitResult& hit) {
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::ASTEROID_HIT);

  ARocket* rocket = Cast<ARocket>(hit.GetActor());
  check(rocket->Letter.Equals(GSBWUtils::GetFirstChar(Word)));
  
  Word.RemoveAt(0);
  
  if (Word.IsEmpty()) {
    Explode(hit);
  }
}

void AAsteroid::Explode(const FHitResult& hit) {
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::ASTEROID_DOWN);
  DestructibleComponent->ApplyDamage(ROCKET_HIT_DAMAGE_AMOUNT, hit.ImpactPoint, -hit.ImpactNormal, ROCKET_HIT_IMPULSE_STRENGTH);

  const FTimerDelegate DisappearDelegate = FTimerDelegate::CreateUObject(this, &AAsteroid::Disappear);
  GetWorldTimerManager().SetTimer(TimerHandle, DisappearDelegate, ASTEROID_EXPLOSION_DURATION, false);
}

FString AAsteroid::GetWord() const {
  return WordToDisplay;
}

void AAsteroid::Disappear() {
  Destroy();
}