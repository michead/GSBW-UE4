// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "TypableActor.h"


// Sets default values
ATypableActor::ATypableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATypableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATypableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATypableActor::OnCharTyped()
{
    
}

void ATypableActor::OnWordTyped()
{
    
}

FString ATypableActor::GetWord()
{
    return word;
}

