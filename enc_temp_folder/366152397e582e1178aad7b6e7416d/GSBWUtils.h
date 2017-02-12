#pragma once

#include "Engine.h"
#include "GlobalEventHandler.h"

#define LINE_LEN        100000
#define S2W_MULTIPLIER  1

namespace GSBWUtils {
  inline FVector ScreenSpaceToWorldSpace(const UWorld* world, const FVector2D& viewportSize, uint8 x, uint8 y, float z) {
    // FIXE: This is the proper way to implement this, but, alas, it does not work
    // FVector worldLocation, worldDirection;
    // APlayerController* controller = UGameplayStatics::GetPlayerController(world, 0);
    // check(controller->DeprojectScreenPositionToWorld(x, y, worldLocation, worldDirection));
    // FPlane plane{ FVector(0, 0, z), FVector(0, 0, 1) };
    // return FMath::LinePlaneIntersection(worldLocation, worldLocation + worldDirection * LINE_LEN, plane);

    float xF = x - (viewportSize.X * 0.5f);
    float yF = y - (viewportSize.Y * 0.5f);

    return FVector(xF * S2W_MULTIPLIER, yF * S2W_MULTIPLIER, z);
  }

  inline FString GetCharAt(const FString& str, uint8 index) {
    return FString(str[index] + "");
  }

  // For convenience, since our use cases mainly involve the first char
  inline FString GetFirstChar(const FString& str) {
    return GetCharAt(str, 0);
  }

  inline bool ContainsAnyOf(const FString& str1, const FString& str2) {
    for (TCHAR c : str2) {
      if (str1.Contains(c+"")) return true;
    }
    return false;
  }

  inline void KeepContainedChars(const FString& str1, FString& str2) {
    uint8 i = 0;
    for (TCHAR c : str2) {
      if (!str1.Contains(c + "")) str2.RemoveAt(i);
      i++;
    }
  }

  inline AGlobalEventHandler* GetEventHandler(UWorld* world) {
    TArray<AActor*> actors;
    UGameplayStatics::GetAllActorsOfClass(world, AGlobalEventHandler::StaticClass(), actors);
    check(actors.Num() == 1);
    return Cast<AGlobalEventHandler>(actors[0]);
  }
}