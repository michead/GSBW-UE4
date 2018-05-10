// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "GSBWCommon.h"
#include "GSBWUtils.h"
#include "GSBWGameState.h"
#include "Rocket.h"
#include "Earth.h"

DEFINE_LOG_CATEGORY(Earth);

// Sets default values
AEarth::AEarth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Reference to lower-case alphabet
  Alphabet = IL_ALPHABET_LC;

  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
  StaticMeshComponent->SetStaticMesh(Mesh);
  StaticMeshComponent->SetCollisionProfileName("Earth");
  StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEarth::OnOverlapBegin);

  // Destructible Mesh will be spawned when Earth is to be destroyed
  DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleMesh"));
  DestructibleComponent->SetDestructibleMesh(DestructibleMesh);
  DestructibleComponent->SetVisibility(false);

  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  AudioComponent = CreateDefaultSubobject<URandomizedAudioComponent>(TEXT("AudioCompoenent"));

  RootComponent = StaticMeshComponent;
}

void AEarth::OnConstruction(const FTransform& Transform) {
  Super::OnConstruction(Transform);

  Camera->SetWorldTransform(CameraTransform);
  Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
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
  PlayerInputComponent->BindKey(EKeys::Hyphen, EInputEvent::IE_Pressed, this, &AEarth::HandleHyphen);
#pragma endregion
  // Handle TAB key
  PlayerInputComponent->BindKey(EKeys::Tab, EInputEvent::IE_Pressed, this, &AEarth::ClearTarget);
  // Handle pause menu toggling
  PlayerInputComponent->BindKey(EKeys::Escape, EInputEvent::IE_Pressed, this, &AEarth::TogglePause);
}

// Called when the game starts or when spawned
void AEarth::BeginPlay() {
	Super::BeginPlay();

  WorldSettings = Cast<AGSBWWorldSettings>(GetWorldSettings());
  MaxHealth = WorldSettings->EarthMaxHealth;
  Health = MaxHealth;
  
  AudioComponent->SetAutoActivate(false);
  AudioComponent->SetSounds(RocketLaunchSounds);
}

// Called every frame
void AEarth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  Rotate(DeltaTime);
}

void AEarth::Rotate(float DeltaTime) {
  AddActorLocalRotation(DeltaRotation * DeltaTime);
  Camera->SetWorldTransform(CameraTransform);
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
    FString asteroidWord = asteroid->GetWord();
    FVector distVec = GetActorLocation() - asteroid->GetActorLocation();
    float tmpSqrdDist = FVector::DotProduct(distVec, distVec);
    
    UE_LOG(Earth, Log, TEXT("Checking asteroid with word %s for input %s."), *asteroidWord, *InputLetters);
    
    if (GSBWUtils::StartsWithAnyOf(asteroidWord, InputLetters) && tmpSqrdDist < sqrdDistance) {
      tentativeTarget = asteroid;
      sqrdDistance = tmpSqrdDist; 
    }
  }

  if (tentativeTarget) {
    Target.ref = tentativeTarget;
    Target.originalWord = tentativeTarget->GetWord();
    Target.rocketCount = 0;
    
    UE_LOG(Earth, Log, TEXT("Asteroid with word %s has been selected as target."), *Target.originalWord);
    
    GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::TARGET_CHANGE);
    Target.ref->SetIsTarget(true);
    
    return true;
  }

  return false;
}

void AEarth::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
  if (Cast<AAsteroid>(OtherActor)) {
    GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::EARTH_HIT);
    Health -= FMath::Max(WorldSettings->AsteroidDamage, 0);
    if (Health == 0) {
      GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::EARTH_DOWN);
      Explode();
    }
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
  transform.SetLocation(GetRocketSpawnLocation());
  ARocket* rocket = GetWorld()->SpawnActor<ARocket>(BaseRocketClass, transform, GSBWUtils::GetNoFailSpawnParams());

  FRocketInitProps props;
  props.target = Target.ref;
  props.letterIndex = Target.rocketCount;
  props.speed = GetRocketSpeed();
  
  rocket->Init(props);
  
  // Play rocket launch sound wave
  AudioComponent->PlayOneAtRand();
  
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
  
  if (Target.ref && Target.rocketCount < Target.originalWord.Len()) {
    Target.ref->SetIsTarget(false);
  }

  Target.originalWord = nullptr;
  Target.rocketCount = 0;
  Target.ref = nullptr;
  
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::TARGET_CHANGE);
}

void AEarth::OnTargetHit(AAsteroid& HitAsteroid) {

}

FVector AEarth::GetRocketSpawnLocation() {
  FVector dir = Target.ref->GetActorLocation() - GetActorLocation();
  float radius = RootComponent->Bounds.SphereRadius;
  float distanceFromOrigin = radius * 1.15f;
  float distanceFromSpawnPoint = GSBWUtils::GetDistanceFromEarthToSpawnerBounds(GetWorld());
  FVector2D sphericalLoc = dir.UnitCartesianToSpherical();
  float maxAngle = FMath::DegreesToRadians<float>(45.f);
  float angle = maxAngle * GetDistanceFromTarget() / distanceFromSpawnPoint;
  float phi = FMath::FRandRange(-angle, angle);
  float theta = FMath::FRandRange(-angle, angle);
  FVector2D delta = FVector2D(phi, theta);
  return (sphericalLoc + delta).SphericalToUnitCartesian() * distanceFromOrigin;
}
                                                                                
float AEarth::GetDistanceFromTarget() {
  return Target.ref->GetActorLocation().Size();
}

float AEarth::GetRocketSpeed() {
  // TODO: This is just a stub
  return 500.f;
}

void AEarth::Explode() {
  DestructibleComponent->SetVisibility(true);
  DestructibleComponent->SetWorldLocation(
    GetActorLocation() - FVector(0, 0, RootComponent->Bounds.SphereRadius));
  DestructibleComponent->ApplyRadiusDamage(
    ASTEROID_HIT_BASE_DAMAGE, GetActorLocation(),
    ASTEROID_HIT_DAMAGE_RADIUS,
    ASTEROID_HIT_IMPULSE_STRENGTH, true);

  RootComponent = DestructibleComponent;

  StaticMeshComponent->UnregisterComponent();
  StaticMeshComponent->DestroyComponent();

  const FTimerDelegate DisappearDelegate = FTimerDelegate::CreateUObject(this, &AEarth::Disappear);
  GetWorldTimerManager().SetTimer(TimerHandle, DisappearDelegate,EARTH_EXPLOSION_DURATION, false);

  // Notify all actors that game is over
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::EARTH_DOWN);
}

void AEarth::Disappear() {
  Destroy();
}

void AEarth::TogglePause() {
  GSBWUtils::GetGameState(GetWorld())->RequestPauseToggle();
}
