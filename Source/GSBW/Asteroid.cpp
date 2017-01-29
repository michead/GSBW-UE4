// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "Asteroid.h"


// Sets default values
AAsteroid::AAsteroid() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

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

}

void AAsteroid::Explode(const FHitResult& hit) {

}

FString AAsteroid::GetWord() const {
  return WordToDisplay;
}
