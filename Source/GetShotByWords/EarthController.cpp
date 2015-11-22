// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "EarthController.h"
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

}

TCHAR AEarthController::ConvertAlphaInputToLetter(float value)
{
	check(value);

	return ALPHABET[value - 1];
}
