// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWGameMode.h"
#include "Spawner.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UBlueprint> BaseAsteroidBP(TEXT("Blueprint'/Game/Blueprints/BP_BaseAsteroid.BP_BaseAsteroid'"));
    static ConstructorHelpers::FObjectFinder<UBlueprint> SlowAsteroidBP(TEXT("Blueprint'/Game/Blueprints/BP_SlowAsteroid.BP_SlowAsteroid'"));
    static ConstructorHelpers::FObjectFinder<UBlueprint> FreezeAsteroidBP(TEXT("Blueprint'/Game/Blueprints/BP_FreezeAsteroid.BP_FreezeAsteroid'"));
    static ConstructorHelpers::FObjectFinder<UBlueprint> BombAsteroidBP(TEXT("Blueprint'/Game/Blueprints/BP_BombAsteroid.BP_BombAsteroid'"));

    BaseAsteroidBPClass = BaseAsteroidBP.Object->GetClass();
    SlowAsteroidBPClass = SlowAsteroidBP.Object->GetClass();
    FreezeAsteroidBPClass = FreezeAsteroidBP.Object->GetClass();
    BombAsteroidBPClass = BombAsteroidBP.Object->GetClass();
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
    asteroidClass = SlowAsteroidBPClass;
    break;
  case EAsteroidType::FREEZE:
    asteroidClass = FreezeAsteroidBPClass;
    break;
  case EAsteroidType::BOMB:
    asteroidClass = BombAsteroidBPClass;
    break;
  case EAsteroidType::BASE:
  default:
    asteroidClass = BaseAsteroidBPClass;
    break;
  }
  GetWorld()->SpawnActor(asteroidClass);
}

void ASpawner::ComputeSpawnerBounds() {
  const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), 0, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), viewportSize.Y, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), viewportSize.X, viewportSize.Y));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), viewportSize.X, 0));
}

float ASpawner::GetCurrentDifficultySpawnInterval() {
  return 2.f;
}

EAsteroidType ASpawner::GetRandomAsteroidTypeForCurrentDifficulty() {
  return EAsteroidType::BASE;
}