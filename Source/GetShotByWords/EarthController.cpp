// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "EarthController.h"
#include "Earth.h"
#include "Rocket.h"
#include "EngineUtils.h"
#include "GameUtils.h"

AEarthController::AEarthController()
{	
	lastVal = -1.f;
}

void AEarthController::SetupInputComponent()
{
	if (!InputComponent)
	{
		InputComponent = ConstructObject<UInputComponent>(UInputComponent::StaticClass(), this, TEXT("InputComponent"));
	}

	InputComponent->BindAxis("Alphabet", this, &AEarthController::HandleAlphaInput);
}

void AEarthController::HandleAlphaInput(float value)
{
	if (!value || value == lastVal) return;

	if (IsPaused()) return; // TODO Handle paused case
	else ShootWord(ConvertAlphaInputToLetter(value));

	lastVal = value;
}

void AEarthController::ShootWord(TCHAR letter)
{
	AAsteroid* target = Cast<AEarth>(GetPawn())->target;
	
	if (!target)
		if (!LockTarget(letter)) return;
	
	FireRocket(Cast<AEarth>(GetPawn())->target);
}

bool AEarthController::LockTarget(TCHAR letter)
{
	for (TActorIterator<AAsteroid> iter(GetWorld()); iter; ++iter)
	{
		if ((*iter)->word.GetCharArray()[0] == letter)
		{
			Cast<AEarth>(GetPawn())->target = *iter;
			return true;
		}
	}

	return false;
}

TCHAR AEarthController::ConvertAlphaInputToLetter(float value)
{
	check(value);

	return ALPHABET[value - 1];
}

void AEarthController::FireRocket(AAsteroid* target)
{
	check(target);

	FVector earthLocation = GetPawn()->GetActorLocation();
	FRotator earthRotation = GetPawn()->GetActorRotation();

	FVector direction = target->GetActorLocation() - earthLocation;
	direction.Normalize();
	FVector spawnLocation = earthLocation + direction * ROCKET_SPAWN_LOCATION_OFFSET;

	ARocket* rocket = Cast<ARocket>(GetWorld()->SpawnActor(ARocket::StaticClass(), &spawnLocation, &earthRotation));
	rocket->target = target;
	rocket->SetLifeSpan(ROCKET_LIFESPAN);

	UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(rocket->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	meshComp->AddForce(direction * Cast<AEarth>(GetPawn())->forceMagnitude);
}