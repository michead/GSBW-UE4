// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWCommon.h"
#include "GSBWUtils.h"
#include "Rocket.h"
#include "Earth.h"

DEFINE_LOG_CATEGORY(Earth);

// Sets default values
AEarth::AEarth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Attach Destructible Mesh as Root Component
    DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("RootComponent"));
    DestructibleComponent->SetCollisionProfileName("Earth");
    DestructibleComponent->OnComponentBeginOverlap.AddDynamic(this, &AEarth::OnOverlapBegin);
    RootComponent = DestructibleComponent;
    
    // Reference to lower-case alphabet
    Alphabet = IL_ALPHABET_LC;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEarth::OnConstruction(const FTransform& Transform) {
  DestructibleComponent->SetDestructibleMesh(DestructibleMesh);
}

void AEarth::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
  // Handle letters typed by player
#pragma region Input Delegates
  PlayerInputComponent->BindKey(EKeys::A, EInputEvent::IE_Pressed, this, &AEarth::HandleA);
  PlayerInputComponent->BindKey(EKeys::B, EInputEvent::IE_Pressed, this, &AEarth::HandleB);
  PlayerInputComponent->BindKey(EKeys::C, EInputEvent::IE_Pressed, this, &AEarth::HandleC);
  PlayerInputComponent->BindKey(EKeys::D, EInputEvent::IE_Pressed, this, &AEarth::HandleD);
  PlayerInputComponent->BindKey(EKeys::E, EInputEvent::IE_Pressed, this, &AEarth::HandleE);
  PlayerInputComponent->BindKey(EKeys::F, EInputEvent::IE_Pressed, this, &AEarth::HandleF);
  PlayerInputComponent->BindKey(EKeys::G, EInputEvent::IE_Pressed, this, &AEarth::HandleG);
  PlayerInputComponent->BindKey(EKeys::H, EInputEvent::IE_Pressed, this, &AEarth::HandleH);
  PlayerInputComponent->BindKey(EKeys::I, EInputEvent::IE_Pressed, this, &AEarth::HandleI);
  PlayerInputComponent->BindKey(EKeys::J, EInputEvent::IE_Pressed, this, &AEarth::HandleJ);
  PlayerInputComponent->BindKey(EKeys::K, EInputEvent::IE_Pressed, this, &AEarth::HandleK);
  PlayerInputComponent->BindKey(EKeys::L, EInputEvent::IE_Pressed, this, &AEarth::HandleL);
  PlayerInputComponent->BindKey(EKeys::M, EInputEvent::IE_Pressed, this, &AEarth::HandleM);
  PlayerInputComponent->BindKey(EKeys::N, EInputEvent::IE_Pressed, this, &AEarth::HandleN);
  PlayerInputComponent->BindKey(EKeys::O, EInputEvent::IE_Pressed, this, &AEarth::HandleO);
  PlayerInputComponent->BindKey(EKeys::P, EInputEvent::IE_Pressed, this, &AEarth::HandleP);
  PlayerInputComponent->BindKey(EKeys::Q, EInputEvent::IE_Pressed, this, &AEarth::HandleQ);
  PlayerInputComponent->BindKey(EKeys::R, EInputEvent::IE_Pressed, this, &AEarth::HandleR);
  PlayerInputComponent->BindKey(EKeys::S, EInputEvent::IE_Pressed, this, &AEarth::HandleS);
  PlayerInputComponent->BindKey(EKeys::T, EInputEvent::IE_Pressed, this, &AEarth::HandleT);
  PlayerInputComponent->BindKey(EKeys::U, EInputEvent::IE_Pressed, this, &AEarth::HandleU);
  PlayerInputComponent->BindKey(EKeys::V, EInputEvent::IE_Pressed, this, &AEarth::HandleV);
  PlayerInputComponent->BindKey(EKeys::W, EInputEvent::IE_Pressed, this, &AEarth::HandleW);
  PlayerInputComponent->BindKey(EKeys::X, EInputEvent::IE_Pressed, this, &AEarth::HandleX);
  PlayerInputComponent->BindKey(EKeys::Y, EInputEvent::IE_Pressed, this, &AEarth::HandleY);
  PlayerInputComponent->BindKey(EKeys::Z, EInputEvent::IE_Pressed, this, &AEarth::HandleZ);
#pragma endregion
  // Handle TAB key
  PlayerInputComponent->BindKey(EKeys::Tab, EInputEvent::IE_Pressed, this, &AEarth::ClearTarget);
}

// Called when the game starts or when spawned
void AEarth::BeginPlay()
{
	Super::BeginPlay();
  WorldSettings = Cast<AGSBWWorldSettings>(GetWorldSettings());
  MaxHealth = WorldSettings->EarthMaxHealth;
  Health = MaxHealth;
}

// Called every frame
void AEarth::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AEarth::HandleInput(FString letter) { 
  // Target currently locked and not destroyed
  if (Target.ref) {
  SHOOT_TARGET:
    ShootTarget(letter);
  } else if (AcquireTarget(letter)) {
    UE_LOG(Earth, Log, TEXT("Target acquired."));
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

  if (tentativeTarget) {
    Target.ref = tentativeTarget;
    Target.originalWord = tentativeTarget->GetWord();
    Target.rocketCount = 0;
    
    return true;
  }

  return false;
}

void AEarth::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
  if (Cast<AAsteroid>(OtherActor)) {
    Health -= FMath::Max(WorldSettings->AsteroidDamage, 0);
  }
}

void AEarth::ShootTarget(FString& Letters) {
  GSBWUtils::KeepContainedChars(Target.ref->GetWord(), Letters);
  short wIndex = 0;

  while (!Letters.IsEmpty()) {
    FString letter = GSBWUtils::GetFirstChar(Letters);
    FString currentWord = Target.originalWord.Mid(Target.rocketCount);
    if (currentWord.StartsWith(letter)) {
      LaunchRocket();
    }
    Letters.RemoveAt(0);
  }
}

void AEarth::LaunchRocket() {
  check(Target.ref);

  FTransform transform;
  FVector targetDir = Target.ref->GetActorLocation() - GetActorLocation();
  targetDir.Normalize();
  transform.SetLocation(GetActorLocation() + RootComponent->Bounds.SphereRadius * 1.25f * targetDir);
  ARocket* rocket = GetWorld()->SpawnActor<ARocket>(BaseRocketClass, transform, GSBWUtils::GetNoFailSpawnParams());

  FRocketInitProps props;
  props.target = Target.ref;
  props.letter = Target.originalWord.Mid(Target.rocketCount, 1);
  props.speed = GetNextRocketSpeed();
  
  rocket->Init(props);
  
  Target.rocketCount++;

  // If all needed rockets to take the asteroid down are on their way,
  // then target reference can be safely set to nullptr in order to start
  // hitting another asteroid
  if (Target.rocketCount == Target.originalWord.Len()) {
    ClearTarget();
  }
}

void AEarth::ClearTarget() {
  UE_LOG(Earth, Log, TEXT("ClearTarget() called."));

  Target.originalWord = nullptr;
  Target.rocketCount = 0;
  Target.ref = nullptr;
}

void AEarth::OnTargetHit(AAsteroid& Asteroid) {

}

float AEarth::GetNextRocketSpeed() {
  // TODO: This is just a stub
  return 2000.f;
}