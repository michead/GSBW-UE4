// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWCommon.h"
#include "GSBWUtils.h"
#include "Rocket.h"
#include "Earth.h"


// Sets default values
AEarth::AEarth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Attach Destructible Mesh as Root Component
    DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("RootComponent"));
    RootComponent = DestructibleComponent;
    
    // Reference to lower-case alphabet
    Alphabet = IL_ALPHABET_LC;

    // Reference(s) to rocket's BP class(es)
    static ConstructorHelpers::FObjectFinder<UBlueprint> BaseRocketBP(TEXT("Blueprint'/Game/Blueprints/BP_BaseRocket.BP_BaseRocket'"));
    BaseRocketBPClass = (UClass*)BaseRocketBP.Object->GeneratedClass;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEarth::OnConstruction(const FTransform& Transform) {
  DestructibleComponent->SetDestructibleMesh(DestructibleMesh);
}

void AEarth::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
  // Handle letters typed by player
  for (FName axis : IL_ALPHABET_UC) {
    PlayerInputComponent->BindAxis(axis, this, &AEarth::HandleInput);
  }
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

void AEarth::HandleInput(float AxisScale) {
  // No button has been pressed
  if (!AxisScale) {
    return;
  }

  FString letter = Alphabet[AxisScale - 1];
  
  // Target currently locked and not destroyed
  if (target) {
  SHOOT_TARGET:
    ShootTarget(letter);
  } else if (AcquireTarget(letter)) {
    goto SHOOT_TARGET;
  }
}

bool AEarth::AcquireTarget(FString& InputLetters) {
  AAsteroid* tentativeTarget = nullptr;
  float sqrdDistance = MAX_FLT;

  TArray<AActor*> asteroids;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAsteroid::StaticClass(), asteroids);
  
  for (AActor* actor : asteroids) {
    AAsteroid* asteroid = Cast<AAsteroid>(actor);
    
    // Maybe we could compute this only once we know that 'StartsWith' condition is satisfied
    FVector distVec = GetActorLocation() - asteroid->GetActorLocation();
    float tmpSqrdDist = FVector::DotProduct(distVec, distVec);

    if (GSBWUtils::ContainsAnyOf(asteroid->GetWord(), InputLetters) && tmpSqrdDist < sqrdDistance) {
      tentativeTarget = asteroid;
      sqrdDistance = tmpSqrdDist;
    }
  }

  target = tentativeTarget;

  // Coerce to bool
  return !!target;
}

bool AEarth::ShootTarget(FString& Letters) {
  GSBWUtils::KeepContainedChars(target->GetWord(), Letters);
  bool ret = !Letters.IsEmpty();
  short wIndex = 0;

  while (!Letters.IsEmpty()) {
    FString letter = GSBWUtils::GetFirstChar(Letters);
    if (target->GetWord().StartsWith(letter)) {
      LaunchRocket(target, letter);
      Letters.RemoveAt(0);
    }
  }

  return ret;
}

void AEarth::LaunchRocket(AAsteroid* _target, const FString& letter) {
  FTransform transform;
  FVector targetDir = _target->GetActorLocation() - GetActorLocation();
  targetDir.Normalize();
  transform.SetLocation(GetActorLocation() + 30 * targetDir);
  ARocket* rocket = GetWorld()->SpawnActor<ARocket>(BaseRocketBPClass, transform);
  FRocketInitProps props;
  props.target = _target;
  rocket->Init(props);
}

void AEarth::OnTargetHit(AAsteroid& Asteroid) {

}