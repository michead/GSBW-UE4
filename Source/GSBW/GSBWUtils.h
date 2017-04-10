#pragma once

#include "Engine.h"
#include "GlobalEventHandler.h"

#define LINE_LEN        100000
#define S2W_MULTIPLIER  10

namespace GSBWUtils {
  inline FVector ScreenSpaceToWorldSpace(UWorld* world, uint8 x, uint8 y, float z) {
    // FIXE: This is the proper way to implement this, but, alas, it does not work
    FVector worldLocation, worldDirection;
    APlayerController* controller = UGameplayStatics::GetPlayerController(world, 0);
    check(controller->DeprojectScreenPositionToWorld(x, y, worldLocation, worldDirection));
    FPlane plane{ FVector(0, 0, z), FVector(0, 0, 1) };
    return FMath::LinePlaneIntersection(worldLocation, worldLocation + worldDirection * LINE_LEN, plane);
  }

  inline FString GetCharAt(const FString& str, uint8 index) {
    return str.Mid(index, 1);
  }

  // For convenience, since our use cases mainly involve the first char
  inline FString GetFirstChar(const FString& str) {
    return GetCharAt(str, 0);
  }

  inline bool ContainsAnyOf(const FString& str1, const FString& str2) {
    for (int32 i = 0; i < str2.Len(); i++) {
      FString currChar = str2.Mid(i, 1);
      if (str1.Contains(currChar)) return true;
    }
    return false;
  }

  inline void KeepContainedChars(const FString& str1, FString& str2) {
    for (int32 i = 0; i < str2.Len(); i++) {
      FString currChar = str2.Mid(i, 1);
      if (!str1.Contains(currChar)) str2.RemoveAt(i);
    }
  }

  inline AGlobalEventHandler* GetEventHandler(UWorld* world) {
    TArray<AActor*> actors;
    UGameplayStatics::GetAllActorsOfClass(world, AGlobalEventHandler::StaticClass(), actors);
    check(actors.Num() == 1);
    return Cast<AGlobalEventHandler>(actors[0]);
  }
}