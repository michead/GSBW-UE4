// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "Earth.h"
#include "Spawner.h"

DEFINE_LOG_CATEGORY(Spawner);

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

  WordMap = GSBWUtils::LoadWordsFromFileIntoLenMap(FPaths::GameContentDir() + "Data/Words.json", MIN_WORD_LEN, MAX_WORD_LEN);
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
}

void ASpawner::StartSpawnCoroutine() {
  GetWorld()->GetTimerManager().SetTimer(
    TimerHandle,
    this,
    &ASpawner::Spawn,
    GetSpawnInterval(),
    true);
}

void ASpawner::Spawn() {
  Spawn(GetNextAsteroidType());
}

void ASpawner::Spawn(EAsteroidType AsteroidType) {
  // TODO: Handle the case viewport size has changed
  if (ViewportSize.IsNearlyZero()) {
    ComputeSpawnerBounds();
  }
  
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
  transform.SetLocation(GetNextAsteroidLocation());
  AAsteroid* asteroid = GetWorld()->SpawnActor<AAsteroid>(asteroidClass, transform);
  FAsteroidInitProps props;
  InitAsteroidProps(props, AsteroidType);
  asteroid->Init(props);
}

void ASpawner::InitAsteroidProps(FAsteroidInitProps& Props, EAsteroidType Type) {
  Props.type = Type;
  Props.word = GetNextAsteroidWord();
  Props.speed = GetNextAsteroidSpeed();
}

FVector ASpawner::GetNextAsteroidLocation() {
  float r = FMath::FRand() * 4, r2 = FMath::FRand();
  if (r <= 1) return FMath::Lerp(Bounds[0], Bounds[1], r2);
  else if (r <= 2) return FMath::Lerp(Bounds[1], Bounds[2], r2);
  else if (r <= 3) return FMath::Lerp(Bounds[2], Bounds[3], r2);
  else return FMath::Lerp(Bounds[3], Bounds[0], r2);
}

FString ASpawner::GetNextAsteroidWord() {
  // TODO: This is just a stub
  return WordMap[MIN_WORD_LEN][0];
}

float ASpawner::GetNextAsteroidSpeed() {
  // TODO: This is just a stub
  return 5000.f;
}

float ASpawner::GetSpawnInterval() {
  // TODO: This is just a stub
  return 2.f;
}

EAsteroidType ASpawner::GetNextAsteroidType() {
  // TODO: This is just a stub
  return EAsteroidType::BASE;
}

void ASpawner::ComputeSpawnerBounds() {
  GEngine->GameViewport->GetViewportSize(ViewportSize);
  UE_LOG(Spawner, Log, TEXT("Computing spawner bounds... Viewport size: %f %f"), ViewportSize.X, ViewportSize.Y);
  Bounds.Empty();
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), 0, 0, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), 0, ViewportSize.Y, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), ViewportSize.X, ViewportSize.Y, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), ViewportSize.X, 0, 0));
}
