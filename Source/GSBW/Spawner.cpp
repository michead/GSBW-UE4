// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWGameMode.h"
#include "Earth.h"
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

    BaseAsteroidBPClass = (UClass*)BaseAsteroidBP.Object->GeneratedClass;
    SlowAsteroidBPClass = (UClass*)SlowAsteroidBP.Object->GeneratedClass;
    FreezeAsteroidBPClass = (UClass*)FreezeAsteroidBP.Object->GeneratedClass;
    BombAsteroidBPClass = (UClass*)BombAsteroidBP.Object->GeneratedClass;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
    StartSpawnCoroutine();
    ComputeSpawnerBounds();
}

// Called every frame
void ASpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
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

  FTransform transform;
  transform.SetLocation(GetRandomAsteroidLocation());
  AAsteroid* asteroid = GetWorld()->SpawnActor<AAsteroid>(asteroidClass, transform);
  FAsteroidInitProps props;
  InitAsteroidProps(props, AsteroidType);
  asteroid->Init(props);
}

void ASpawner::InitAsteroidProps(FAsteroidInitProps& Props, EAsteroidType Type) {
  Props.type = Type;
  Props.word = PickAsteroidWord();
  Props.speed = PickAsteroidSpeed();
}

FVector ASpawner::GetRandomAsteroidLocation() {
  float r = FMath::FRand() * 4, r2 = FMath::FRand();
  if (r <= 1) return FMath::Lerp(Bounds[0], Bounds[1], r2);
  else if (r <= 2) return FMath::Lerp(Bounds[1], Bounds[2], r2);
  else if (r <= 3) return FMath::Lerp(Bounds[2], Bounds[3], r2);
  else return FMath::Lerp(Bounds[3], Bounds[0], r2);
}

FString ASpawner::PickAsteroidWord() {
  // TODO: This is just a stub
  return "test";
}

float ASpawner::PickAsteroidSpeed() {
  // TODO: This is just a stub
  return 100.f;
}

void ASpawner::ComputeSpawnerBounds() {
  const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
  Bounds.Empty();
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), 0, 0, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), viewportSize.Y, 0, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), viewportSize.X, viewportSize.Y, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), viewportSize.X, 0, 0));
}

float ASpawner::GetCurrentDifficultySpawnInterval() {
  return 2.f;
}

EAsteroidType ASpawner::GetRandomAsteroidTypeForCurrentDifficulty() {
  return EAsteroidType::BASE;
}