// Fill out your copyright notice in the Description page of Project Settings.

#include "GSBW.h"
#include "Earth.h"
#include "Rocket.h"
#include "GSBWCommon.h"
#include "GSBWUtils.h"
#include "AsteroidExplosion.h"
#include "Asteroid.h"

DEFINE_LOG_CATEGORY(Asteroid);

// Sets default values
AAsteroid::AAsteroid() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Default value for AsteroidTextComponent class
  AsteroidTextComponentClass = UAsteroidTextComponent::StaticClass();

  StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
  StaticMeshComponent->SetEnableGravity(false);
  StaticMeshComponent->SetSimulatePhysics(true);
  StaticMeshComponent->SetCollisionProfileName("Asteroid");
  StaticMeshComponent->SetCustomDepthStencilValue(ASTEROID_SELECTED_OUTLINE_CUSTOM_DEPTH);
  StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlapBegin);
  SetRootComponent(StaticMeshComponent);
  
  AsteroidTimeScaleChangeDelegate.BindUFunction(this, "OnAsteroidTimeScaleChange");
  
  EffectDuration = 0.f;
  RocketCount = 0;
  Speed = 0.f;
  WordLenRadiusConstantFactor = 2.f;
  MinRadius = 50.f;
  MaxRadius = 100.f;
  TextSphericalPositionOffset = { 0.f, 0.f };
  TextWorldRotationAxis = { 1.f, 0.f, 0.f };
}

void AAsteroid::OnConstruction(const FTransform& Transform) {
  Super::OnConstruction(Transform);

  StaticMeshComponent->SetStaticMesh(StaticMesh);

  // Set default value mostly for debugging purposes
  WordToDisplay = Word;
  
  FAsteroidInitProps props = {};
  props.speed = Speed;
  props.torque = Torque;
  props.type = Type;
  props.word = Word;

  Init(props);
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay() {
  Super::BeginPlay();
  
  GSBWUtils::GetEventHandler(GetWorld())->SubscribeToEvent(EGSBWEvent::ASTEROID_TIME_SCALE_CHANGE, AsteroidTimeScaleChangeDelegate);
  
  CustomTimeDilation = GSBWUtils::GetGameState(GetWorld())->AsteroidTimeScale;
}

// Called every frame
void AAsteroid::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
  
  // Hack for nullifying the effect of custom time dilation in children components
  AsteroidTextComponent->UpdatePosition((1.f / CustomTimeDilation) * DeltaTime);
}

void AAsteroid::Init(const FAsteroidInitProps& props) {
  Type = props.type;
  Word = props.word;
  Speed = props.speed;
  Torque = props.torque;

  WordToDisplay = Word;
  
  ScaleAccordingToWordLen();
  InitTextComponent();
  ApplyImpulse();
}

void AAsteroid::InitTextComponent() {
  if (!AsteroidTextComponentClass || !TextRenderComponentClass) {
    UE_LOG(Asteroid, Warning, TEXT("Cannot initialize text component because of core props have not been defined."));
    return;
  }
  
  FAsteroidTextComponentInitProps props = {};
  props.rootComponent = RootComponent;
  props.word = WordToDisplay;
  props.charSpacing = CharSpacing;
  props.radius = RootComponent->Bounds.SphereRadius;
  props.fontScalingFactor = FontScalingFactor;
  props.baseRotation = BaseTextRotation;
  props.textColor = TextColor;
  props.textRenderComponentClass = TextRenderComponentClass;
  props.textWorldRotationAxis = TextWorldRotationAxis;
  props.textSphericalPositionOffset = TextSphericalPositionOffset;
  
  if (!AsteroidTextComponent) {
    AsteroidTextComponent = NewObject<UAsteroidTextComponent>(this, AsteroidTextComponentClass);
    AsteroidTextComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
  }
  
  AsteroidTextComponent->Init(props);
}

void AAsteroid::SetIsTarget(bool IsTarget) {
  StaticMeshComponent->SetRenderCustomDepth(IsTarget);
}

void AAsteroid::ApplyImpulse() {
  if (!Speed) {
    // Workaround for testing actor in blueprint's viewport
    return;
  }
  
  TArray<AActor*> actors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEarth::StaticClass(), actors);

  FVector direction = (actors[0]->GetActorLocation() - GetActorLocation());
  direction.Normalize();

  // Self-apply impulse and torque
  StaticMeshComponent->AddImpulse(direction * Speed * CustomTimeDilation);
  StaticMeshComponent->AddTorque(Torque * CustomTimeDilation);
}

void AAsteroid::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                               class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (Cast<AEarth>(OtherActor)) {
		OnEarthHit(OtherActor, SweepResult);
	} else if (Cast<ARocket>(OtherActor)
          && Cast<ARocket>(OtherActor)->GetTargetID() == GetUniqueID()) {
		OnRocketHit(OtherActor, SweepResult);
	}
}

void AAsteroid::OnEarthHit(class AActor* Actor, const FHitResult& Hit) {
  Explode(Hit, false);
}

void AAsteroid::OnRocketHit(class AActor* Actor, const FHitResult& Hit) {
  uint32 rocketLetterIndex = Cast<ARocket>(Actor)->LetterIndex;
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::ASTEROID_HIT);

  RocketCount++;

  AsteroidTextComponent->DestroyLetterAt(rocketLetterIndex);
  if (Word.Len() == RocketCount) {
    Explode(Hit);
  } else {
    WordToDisplay = WordToDisplay.Mid(1);
  }
}

void AAsteroid::OnAsteroidTimeScaleChange() {
  CustomTimeDilation = GSBWUtils::GetGameState(GetWorld())->AsteroidTimeScale;
  StaticMeshComponent->SetPhysicsLinearVelocity(FVector(0));
  // Re-apply impulse with new time dilation
  ApplyImpulse();
}

void AAsteroid::OnDestruction() {
  // Base asteroid class has no logic to execute on destruction
}

void AAsteroid::Explode(const FHitResult& Hit, bool TriggerEffect) {
  // Notify other actors about event
  GSBWUtils::GetEventHandler(GetWorld())->BroadcastEvent(EGSBWEvent::ASTEROID_DOWN);

  if (TriggerEffect) {
    // Trigger asteroid-specific logic on destruction
    OnDestruction();
  }
  
  // Spawn explosion
  AAsteroidExplosion* explosion = GetWorld()->SpawnActor<AAsteroidExplosion>(GetActorLocation(), GetActorRotation());
  explosion->Init({ DestructibleMesh, Hit });
    
  // Hide actor and defer its destruction
  SetActorHiddenInGame(true);
  const FTimerDelegate DestroyDelegate = FTimerDelegate::CreateUObject(this, &AAsteroid::Disappear);
  GetWorldTimerManager().SetTimer(DestroyTimerHandle, DestroyDelegate, ASTEROID_EXPLOSION_DURATION, false);
}

FString AAsteroid::GetWord() const {
  return WordToDisplay;
}

void AAsteroid::ScaleAccordingToWordLen() {
  FVector currScale = RootComponent->GetComponentScale();
  float currRadius = RootComponent->Bounds.SphereRadius;
  float nextRadius = FMath::Min(MinRadius + Word.Len() * WordLenRadiusConstantFactor, MaxRadius);
  FVector nextScale = (currScale * nextRadius) / currRadius;
  RootComponent->SetWorldScale3D(nextScale);
  UE_LOG(Asteroid, Log, TEXT("Asteroid has been scaled by %.2f. Previous radius was %.2f, current radius is %.2f."), nextScale.X, currRadius, nextRadius);
}

void AAsteroid::RestoreAsteroidTimeScale() {
  GSBWUtils::GetGameState(GetWorld())->RequestAsteroidTimeScaleChange(1);
}

void AAsteroid::Disappear() {
  Destroy();
}
