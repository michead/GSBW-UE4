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

  WordLens.Add(FInt32Interval(MIN_WORD_LEN    , MIN_WORD_LEN + 1));
  WordLens.Add(FInt32Interval(MIN_WORD_LEN + 2, MIN_WORD_LEN + 4));
  WordLens.Add(FInt32Interval(MIN_WORD_LEN + 5, MIN_WORD_LEN + 5));
  WordLens.Add(FInt32Interval(MIN_WORD_LEN + 6, MIN_WORD_LEN + 8));
  WordLens.Add(FInt32Interval(MIN_WORD_LEN + 9, MAX_int32));

  GameMode = Cast<AGSBWGameMode>(GetWorld()->GetAuthGameMode());
  check(GameMode);
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
  GEngine->GameViewport->GetViewportSize(ViewportSize);
  UE_LOG(Spawner, Log, TEXT("Computing spawner bounds... Viewport size: %.1fx%.1f"), ViewportSize.X, ViewportSize.Y);
  // If viewport size has not been computed yet
  if (ViewportSize.IsNearlyZero() ||
    // If viewport size changed
    !(PrevViewportSize - ViewportSize).IsNearlyZero()) {
    ComputeSpawnerBounds();
  }
  PrevViewportSize = ViewportSize;

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
  EDifficulty currentDifficulty = GameMode->GetCurrentDifficulty();
  FInt32Interval bounds = WordLens[static_cast<uint8_t>(currentDifficulty)];
  int32_t randLen = FMath::RandRange(bounds.Min, bounds.Max);
  return WordMap[randLen][FMath::RandRange(0, WordMap[randLen].Num() - 1)];
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
  Bounds.Empty();
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), 0, 0, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), 0, ViewportSize.Y, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), ViewportSize.X, ViewportSize.Y, 0));
  Bounds.Add(GSBWUtils::ScreenSpaceToWorldSpace(GetWorld(), ViewportSize.X, 0, 0));
  UE_LOG(Spawner, Log, TEXT("Bounds[0] (TL): { %.1f,  %.1f, %.1f }"), Bounds[0].X, Bounds[0].Y, Bounds[0].Z);
  UE_LOG(Spawner, Log, TEXT("Bounds[1] (BL): { %.1f,  %.1f, %.1f }"), Bounds[1].X, Bounds[1].Y, Bounds[1].Z);
  UE_LOG(Spawner, Log, TEXT("Bounds[2] (BR): { %.1f,  %.1f, %.1f }"), Bounds[2].X, Bounds[2].Y, Bounds[2].Z);
  UE_LOG(Spawner, Log, TEXT("Bounds[3] (TR): { %.1f,  %.1f, %.1f }"), Bounds[3].X, Bounds[3].Y, Bounds[3].Z);
}
