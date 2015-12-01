// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "EarthController.h"
#include "Earth.h"
#include "Asteroid.h"
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
	if (!target) LockTarget(letter);
	check(target);
	
	// TODO Shoot rocket
}

void AEarthController::LockTarget(TCHAR letter)
{

}

TCHAR AEarthController::ConvertAlphaInputToLetter(float value)
{
	check(value);

	return ALPHABET[value - 1];
}