// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWGameMode.h"
#include "Spawner.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
    StartSpawnCoroutine();
}

// Called every frame
void ASpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    ComputeSpawnerBounds();
}

void ASpawner::StartSpawnCoroutine() {
  GetWorld()->GetTimerManager().SetTimer(
    TimerHandle,
    this,
    &ASpawner::Spawn,
    GetCurrentDifficultySpawnInterval(),
    true);
}

void ASpawner::Spawn() {
  Spawn(GetRandomAsteroidTypeForCurrentDifficulty());
}

void ASpawner::Spawn(EAsteroidType AsteroidType) {
  switch (AsteroidType) {
  case EAsteroidType::BASE:
  default:
    break;
  }
}

void ASpawner::ComputeSpawnerBounds() {
  const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
  Bounds.Add(ScreenSpaceToWorldSpace(GetWorld(), 0, 0));
  Bounds.Add(ScreenSpaceToWorldSpace(GetWorld(), viewportSize.Y, 0));
  Bounds.Add(ScreenSpaceToWorldSpace(GetWorld(), viewportSize.X, viewportSize.Y));
  Bounds.Add(ScreenSpaceToWorldSpace(GetWorld(), viewportSize.X, 0));
}

float ASpawner::GetCurrentDifficultySpawnInterval() {
  return 2.f;
}

EAsteroidType ASpawner::GetRandomAsteroidTypeForCurrentDifficulty() {
  return EAsteroidType::BASE;
}