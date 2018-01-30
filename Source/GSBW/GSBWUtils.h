#pragma once

#include "Engine.h"
#include "Json.h"
#include "GlobalEventHandler.h"
#include "GSBWCommon.h"

#define LINE_LEN        100000
#define S2W_MULTIPLIER  10

namespace GSBWUtils {
  inline FVector ScreenSpaceToWorldSpace(UWorld* World, float X, float Y, float Z) {
    // FIXE: This is the proper way to implement this, but, alas, it does not work
    FVector worldLocation, worldDirection;
    APlayerController* controller = UGameplayStatics::GetPlayerController(World, 0);
    check(controller->DeprojectScreenPositionToWorld(X, Y, worldLocation, worldDirection));
    FPlane plane{ FVector(0, 0, Z), FVector(0, 0, 1) };
    return FMath::LinePlaneIntersection(worldLocation, worldLocation + worldDirection * LINE_LEN, plane);
  }

  inline FString GetCharAt(const FString& Str, uint8 Index) {
    return Str.Mid(Index, 1);
  }

  // For convenience, since our use cases mainly involve the first char
  inline FString GetFirstChar(const FString& Str) {
    return GetCharAt(Str, 0);
  }

  inline bool ContainsAnyOf(const FString& Str1, const FString& Str2) {
    for (int32 i = 0; i < Str2.Len(); i++) {
      FString currChar = Str2.Mid(i, 1);
      if (Str1.Contains(currChar)) return true;
    }
    return false;
  }

  inline void KeepContainedChars(const FString& Str1, FString& Str2) {
    for (int32 i = 0; i < Str2.Len(); i++) {
      FString currChar = Str2.Mid(i, 1);
      if (!Str1.Contains(currChar)) Str2.RemoveAt(i);
    }
  }

  inline AGlobalEventHandler* GetEventHandler(UWorld* World) {
    TArray<AActor*> actors;
    UGameplayStatics::GetAllActorsOfClass(World, AGlobalEventHandler::StaticClass(), actors);
    check(actors.Num() == 1);
    return Cast<AGlobalEventHandler>(actors[0]);
  }

  inline FActorSpawnParameters GetNoFailSpawnParams() {
    FActorSpawnParameters spawnParams;
    spawnParams.bNoFail = true;
    return spawnParams;
  }

  template<class T>
  inline void DestroyOnNextTick(
    UWorld* World,
    T* ActorToDestroy,
    typename FTimerDelegate::TUObjectMethodDelegate<T>::FMethodPtr TimerMethod) {
    // Hide actor until it gets destroyed
    Cast<AActor>(ActorToDestroy)->GetRootComponent()->SetVisibility(false, true);
    // Call method on next tick
    World->GetTimerManager().SetTimerForNextTick<T>(ActorToDestroy, TimerMethod);
  }

  inline GSBWWordMap LoadWordsFromFileIntoLenMap(FString Filename, uint8_t MinLen, uint8_t MaxLen) {
    GSBWWordMap wordMap;
    FString jsonStr;
    FFileHelper::LoadFileToString(jsonStr, *Filename);
    TSharedRef<TJsonReader<TCHAR>> jsonReader = FJsonStringReader::Create(jsonStr);
    TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
    check(FJsonSerializer::Deserialize(jsonReader, jsonObj));
    TArray<TSharedPtr<FJsonValue>> words = jsonObj->GetArrayField(TEXT("data"));
    for (uint8_t i = MinLen; i <= MaxLen; i++) {
      wordMap.Add(i, TMap<FString, TArray<FString>>());
      for (const FString& letter : IL_ALPHABET_LC) {
        wordMap[i].Add(letter, TArray<FString>());
      }
    }
    for (TSharedPtr<FJsonValue> pWord : words) {
      FString word = pWord->AsString();
      uint8_t wordLen = word.Len();
      if (wordLen >= MinLen && wordLen <= MaxLen) {
        wordMap[wordLen][word.Mid(0, 1)].Add(word.ToUpper());
      }
    }
    return wordMap;
  }
}