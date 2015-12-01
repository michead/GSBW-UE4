// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "EarthController.generated.h"

/**
 * 
 */
UCLASS()
class GETSHOTBYWORDS_API AEarthController : public APlayerController
{
	GENERATED_BODY()

	AEarthController();

	virtual void SetupInputComponent() override;

	inline TCHAR ConvertAlphaInputToLetter(float value);

	void HandleAlphaInput(float value);

	void ShootWord(TCHAR letter);

	void LockTarget(TCHAR letter);
};
