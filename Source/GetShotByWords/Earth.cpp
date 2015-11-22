// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "Earth.h"


// Sets default values
AEarth::AEarth()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Dummy root component for easing mesh switch
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	camera->SetRelativeLocation(cameraOffset);
	camera->SetRelativeRotation(cameraRotation);

	camera->AttachTo(RootComponent);
	mesh->AttachTo(RootComponent);
}

void AEarth::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	camera->SetRelativeLocation(cameraOffset);
	camera->SetRelativeRotation(cameraRotation);
}

// Called when the game starts or when spawned
void AEarth::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEarth::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AEarth::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

