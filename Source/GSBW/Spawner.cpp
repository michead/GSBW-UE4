// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWUtils.h"
#include "Asteroid.h"
#include "Earth.h"
#include "Spawner.h"

DEFINE_LOG_CATEGORY(Spawner);

// Sets default values
ASpawner::ASpawner()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  Alphabet = FString(STR_ALPHABET_LC);

  FString wordsPath = FPaths::Combine(*FPaths::GameContentDir(), *FString("Data/Words.json"));
  UE_LOG(Spawner, Log, TEXT("Loading words from %s"), *wordsPath);
  WordMap = GSBWUtils::LoadWordsFromFileIntoLenMap(wordsPath, MIN_WORD_LEN, MAX_WORD_LEN);

  WordLens.Add(FInt32Interval(MIN_WORD_LEN +  0, MIN_WORD_LEN + 1));
  WordLens.Add(FInt32Interval(MIN_WORD_LEN +  2, MIN_WORD_LEN + 5));
  WordLens.Add(FInt32Interval(MIN_WORD_LEN +  6, MIN_WORD_LEN + 9));
  WordLens.Add(FInt32Interval(MIN_WORD_LEN +  9, MIN_WORD_LEN + 10));

  EarthDownDelegate.BindUFunction(this, "OnEarthDown");
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay() {
	Super::BeginPlay();
  StartSpawnCoroutine();
  GameMode = Cast<AGSBWGameMode>(GetWorld()->GetAuthGameMode());
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::EARTH_DOWN, EarthDownDelegate);
}

// Called every frame
void ASpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
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
  transform.SetLocation(GetNextAsteroidLocation(AsteroidType));
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

FVector ASpawner::GetNextAsteroidLocation(EAsteroidType AsteroidType) {
  float r = FMath::FRand() * 4, r2 = FMath::FRand();
  float asteroidRadius = 100;
  if (r <= 1) {
    return FMath::Lerp(Bounds[0], Bounds[1], r2) + FVector(-asteroidRadius, 0, 0);
  } else if (r <= 2) {
    return FMath::Lerp(Bounds[1], Bounds[2], r2) + FVector(0, -asteroidRadius, 0);
  } else if (r <= 3) {
    return FMath::Lerp(Bounds[2], Bounds[3], r2) + FVector(asteroidRadius, 0, 0);
  } else {
    return FMath::Lerp(Bounds[3], Bounds[0], r2) + FVector(0, asteroidRadius, 0);
  }
}

int32_t ASpawner::GetNextWordLen() {
  FInt32Interval bounds = WordLens[(uint8_t) GameMode->GetCurrentDifficulty()];
  return FMath::RandRange(bounds.Min, bounds.Max);
}

FString ASpawner::GetNextFirstLetter(TArray<AActor*> Asteroids) {
  FString word;
  uint8_t index = FMath::RandRange(0, 25);
  int32_t wordLen = GetNextWordLen();
  for (uint8_t i = 0; i < 26; i++) {
    TArray<FString> wordArray = WordMap[wordLen][Alphabet.Mid(index++ % 26, 1)];
    if (wordArray.Num() < 1) {
      continue;
    }
    word = PickWordFromMap(wordLen, Alphabet.Mid(index++ % 26, 1));
    if (SomeStartWithLetter(Asteroids, word)) {
      continue;
    }
    break;
  }
  if (word.IsEmpty()) {
    word = PickWordFromMap(wordLen, Alphabet.Mid(FMath::RandRange(0, 25), 1));
  }
  return word;
}

FString ASpawner::GetNextAsteroidWord() {
  TArray<AActor*> asteroids;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAsteroid::StaticClass(), asteroids);
  return GetNextFirstLetter(asteroids);
}

float ASpawner::GetNextAsteroidSpeed() {
  // TODO: This is just a stub
  return 5000.f;
}

float ASpawner::GetSpawnInterval() {
  // TODO: This is just a stub
  return 3.f;
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

bool ASpawner::SomeStartWithLetter(const TArray<AActor*>& Asteroids, const FString& Letter) {
  for (const AActor* asteroid : Asteroids) {
    AAsteroid* _asteroid = Cast<AAsteroid>((AAsteroid*)asteroid);
    if (_asteroid && _asteroid->GetWord().StartsWith(Letter)) {
      return true;
    }
  }
  return false;
}

FString ASpawner::PickWordFromMap(uint8_t WordLen, const FString& Prefix) {
  if (WordMap[WordLen].Num() < 1 ||
      WordMap[WordLen][Prefix].Num() < 1) {
    return "";
  }
  return WordMap[WordLen][Prefix][FMath::RandRange(0, WordMap[WordLen][Prefix].Num() - 1)];
}

void ASpawner::OnEarthDown() {
  // Stop Spawn() routine
  TimerHandle.Invalidate();
}

