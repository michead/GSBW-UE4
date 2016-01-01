// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "Asteroid.h"
#include "GameUtils.h"
#include "Spawner.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetBounds();
	LoadWords();
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(timerHandle, this, &ASpawner::SpawnAsteroid, GetSpawnTimeout());
}

// Called every frame
void ASpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASpawner::SpawnAsteroid()
{
	const FTransform transform = GetAsteroidInitialTransform();
	AAsteroid* asteroid = GetWorld()->SpawnActor<AAsteroid>(AAsteroid::StaticClass(), transform);

	FVector direction = (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - asteroid->GetActorLocation());
	direction.Normalize();

	UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(asteroid->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	meshComp->AddForce(direction * GetForceMagnitude());

	asteroid->SetWord(GetWord());

	GetWorldTimerManager().ClearTimer(timerHandle);
	GetWorldTimerManager().SetTimer(timerHandle, this, &ASpawner::SpawnAsteroid, GetSpawnTimeout());
}

const FTransform ASpawner::GetAsteroidInitialTransform()
{
	const FTransform transform = FTransform(GetAsteroidInitialRot(), GetAsteroidInitialLoc(), GetAsteroidInitialScale());
	return transform;
}

const FVector ASpawner::GetAsteroidInitialLoc()
{
	int side = FMath::RandRange(0, 4);
	FVector loc;

	if (!side)  loc = GetRandLocFromBounds(spawnBounds[0], spawnBounds[1]);
	else if (side == 1) loc = GetRandLocFromBounds(spawnBounds[2], spawnBounds[3]);
	else if (side == 2) loc = GetRandLocFromBounds(spawnBounds[0], spawnBounds[2]);
	else loc = GetRandLocFromBounds(spawnBounds[1], spawnBounds[3]);

	return loc;
}

const FRotator ASpawner::GetAsteroidInitialRot()
{
	return FRotator::ZeroRotator;
}

const FVector ASpawner::GetAsteroidInitialScale()
{
	const FVector scale = FVector(1);
	return scale;
}

float ASpawner::GetSpawnTimeout()
{
	return DEFAULT_SPAWN_TIMEOUT;
}

float ASpawner::GetForceMagnitude()
{
	return DEFAULT_SPAWNER_FORCE_MAGNITUDE;
}

FVector ASpawner::GetRandLocFromBounds(FVector a, FVector b)
{
	float r = FMath::FRand();
	return r * a + (1 - r) * b;
}

FString ASpawner::GetWord()
{
	check(words.Num())

	int index = FMath::RandRange(0, words.Num() - 1);
	return words[index];
}

void ASpawner::LoadWords()
{
	wordFile = FPaths::GameContentDir() + WORDS_FILE_RELATIVE_PATH;
	wordsStr = "";
	FFileHelper::LoadFileToString(wordsStr, *wordFile);
	wordsStr.ParseIntoArray(words, TEXT("\r\n"), true);
}

void ASpawner::SetBounds()
{
	spawnBounds.Empty();

	spawnBounds.Add(DEFAULT_UPPER_LEFT_BOUND);
	spawnBounds.Add(DEFAULT_UPPER_RIGHT_BOUND);
	spawnBounds.Add(DEFAULT_LOWER_LEFT_BOUND);
	spawnBounds.Add(DEFAULT_LOWER_RIGHT_BOUND);
}

