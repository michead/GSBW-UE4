#pragma once

#include "Engine.h"

namespace GSBWUtils {
  inline FVector ScreenSpaceToWorldSpace(UWorld* world, uint8 x, uint8 y) {
    FVector worldLocation, worldDirection;
    world->GetFirstPlayerController()->DeprojectScreenPositionToWorld(x, y, worldLocation, worldDirection);
    return worldLocation;
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
}