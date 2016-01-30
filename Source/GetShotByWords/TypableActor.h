// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TypableActor.generated.h"

UCLASS()
class GETSHOTBYWORDS_API ATypableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATypableActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    virtual void OnCharTyped() PURE_VIRTUAL(ATypableActor::OnCharTyped,;);
    virtual void OnWordTyped() PURE_VIRTUAL(ATypableActor::OnWordTyped,;);
    
    virtual FString GetWord();
    
private:
    FString word;

	
	
};
