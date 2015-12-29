// Fill out your copyright notice in the Description page of Project Settings.

#include "GetShotByWords.h"
#include "AsteroidExplosion.h"
#include "GameUtils.h"

void SpawnExplosion(UWorld* world, FTransform transform, UStaticMeshComponent* mesh)
{
	AAsteroidExplosion* explosion = world->SpawnActorDeferred<AAsteroidExplosion>(AAsteroidExplosion::StaticClass(), transform);
	explosion->staticMesh = mesh;
	UGameplayStatics::FinishSpawningActor(explosion, transform);
}