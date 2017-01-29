// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWGameMode.h"
#include "Spawner.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UBlueprint> BaseAsteroidBP(TEXT("Blueprints/BP_BasicAsteroid"));
    static ConstructorHelpers::FObjectFinder<UBlueprint> SlowAsteroidBP(TEXT("Blueprints/BP_SlowAsteroid"));
    static ConstructorHelpers::FObjectFinder<UBlueprint> FreezeAsteroidBP(TEXT("Blueprints/BP_FreezeAsteroid"));
    static ConstructorHelpers::FObjectFinder<UBlueprint> BombAsteroidBP(TEXT("Blueprints/BP_BombAsteroid"));

    BPBaseAsteroid = BaseAsteroidBP.Object;
    BPSlowAsteroid = SlowAsteroidBP.Object;
    BPFreezeAsteroid = FreezeAsteroidBP.Object;
    BPBombAsteroid = BombAsteroidBP.Object;
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
  UClass* asteroidClass;
  switch (AsteroidType) {
  case EAsteroidType::SLOW:
    asteroidClass = BPSlowAsteroid->GetClass();
    break;
  case EAsteroidType::FREEZE:
    asteroidClass = BPFreezeAsteroid->GetClass();
    break;
  case EAsteroidType::BOMB:
    asteroidClass = BPBombAsteroid->GetClass();
    break;
  case EAsteroidType::BASE:
  default:
    asteroidClass = BPBaseAsteroid->GetClass();
    break;
  }
  GetWorld()->SpawnActor(asteroidClass);
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