// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "EarthController.h"
#include "Earth.h"
#include "EngineUtils.h"
#include "GameUtils.h"

AEarthController::AEarthController()
{	

}

void AEarthController::SetupInputComponent()
{
	check(InputComponent);

	InputComponent->BindAxis("Alphabet", this, &AEarthController::HandleAlphaInput);
}

void AEarthController::HandleAlphaInput(float value)
{
	check(value);

	if (IsPaused()) return; // TODO Handle paused case
	else ShootWord(ConvertAlphaInputToLetter(value));
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
	// TODO
}