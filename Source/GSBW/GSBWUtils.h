#pragma once

#include "Engine.h"

inline FVector ScreenSpaceToWorldSpace(UWorld* world, uint8 x, uint8 y) {
  FVector worldLocation, worldDirection;
  world->GetFirstPlayerController()->DeprojectScreenPositionToWorld(x, y, worldLocation, worldDirection);
  return worldLocation;
}