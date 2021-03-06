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

  // Start the game with spawner enabled
  ShouldSpawn = true;

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
  
  check(AsteroidSpawnIntervalRanges.Num() == static_cast<int>(EDifficulty::NUM_DIFFICULTIES) * 2);
  check(AsteroidSpeedRanges.Num() == static_cast<int>(EDifficulty::NUM_DIFFICULTIES) * 2);
  check(AsteroidTypeProbabilities.Num() == static_cast<int>(EDifficulty::NUM_DIFFICULTIES) * static_cast<int>(EAsteroidType::NUM_TYPES));
  
  GameState = GetWorld()->GetGameState<AGSBWGameState>();
  
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::EARTH_DOWN, EarthDownDelegate);
  
  StartSpawnCoroutine();
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
  if (ShouldSpawn) {
    Spawn(GetNextAsteroidType());
  }
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
  Props.torque = GetNextAsteroidTorque();
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
  FInt32Interval bounds = WordLens[static_cast<int>(GameState->GetCurrentDifficulty())];
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
    word = PickWordFromMap(wordLen, index++ % 26);
    if (SomeStartWithLetter(Asteroids, word)) {
      continue;
    }
    break;
  }
  if (word.IsEmpty()) {
    word = PickWordFromMap(wordLen, FMath::RandRange(0, 25));
  }
  return word;
}

FString ASpawner::GetNextAsteroidWord() {
  TArray<AActor*> asteroids;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAsteroid::StaticClass(), asteroids);
  return GetNextFirstLetter(asteroids);
}

float ASpawner::GetNextAsteroidSpeed() {
  int difficultyIndex = static_cast<int>(GameState->GetCurrentDifficulty());
  float a = AsteroidSpeedRanges[2 * difficultyIndex];
  float b = AsteroidSpeedRanges[2 * difficultyIndex + 1];
  return FMath::FRandRange(a, b);
}

FVector ASpawner::GetNextAsteroidTorque() {
  int difficultyIndex = static_cast<int>(GameState->GetCurrentDifficulty());
  float a = AsteroidTorqueSpeedRanges[2 * difficultyIndex];
  float b = AsteroidTorqueSpeedRanges[2 * difficultyIndex + 1];
  return FMath::FRandRange(a, b) * FMath::VRand();
}

float ASpawner::GetSpawnInterval() {
  int difficultyIndex = static_cast<int>(GameState->GetCurrentDifficulty());
  float a = AsteroidSpawnIntervalRanges[2 * difficultyIndex];
  float b = AsteroidSpawnIntervalRanges[2 * difficultyIndex + 1];
  return FMath::FRandRange(a, b);
}

EAsteroidType ASpawner::GetNextAsteroidType() {
  int difficultyIndex = static_cast<int>(GameState->GetCurrentDifficulty());
  int numAsteroidTypes = static_cast<int>(EAsteroidType::NUM_TYPES);
  
  float probA = AsteroidTypeProbabilities[difficultyIndex * numAsteroidTypes];
  float probB = AsteroidTypeProbabilities[difficultyIndex * numAsteroidTypes + 1] + probA;
  float probC = AsteroidTypeProbabilities[difficultyIndex * numAsteroidTypes + 2] + probB;
  
  float randNum = FMath::FRand();
  EAsteroidType type;
  
  if (randNum <= probA) {
    type = EAsteroidType::BASE;
  } else if (randNum <= probB) {
    type = EAsteroidType::SLOW;
  } else if (randNum <= probC) {
    type = EAsteroidType::FREEZE;
  } else {
    type = EAsteroidType::BOMB;
  }
  
  return type;
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

FString ASpawner::PickWordFromMap(uint8_t WordLen, uint8_t PrefixCharIndex) {
  FString ret = "";
  uint8_t i = 0;
  while (i < 26) {
    FString prefix = Alphabet.Mid((PrefixCharIndex + i) % 26, 1);
    if (WordMap[WordLen].Num() > 0 &&
      WordMap[WordLen][prefix].Num() > 0) {
      ret = WordMap[WordLen][prefix][FMath::RandRange(0, WordMap[WordLen][prefix].Num() - 1)];
      break;
    }
    i++;
  }
  check(ret.Len());
  return ret;
}

void ASpawner::OnEarthDown() {
  // Stop Spawn() routine
  ShouldSpawn = false;
  TimerHandle.Invalidate();
}

