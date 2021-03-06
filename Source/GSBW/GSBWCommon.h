#pragma once

#include "Engine.h"

#define STR_ALPHABET_LC                        "abcdefghijklmnopqrstuvwxyz"
#define IL_ALPHABET_LC                         { "a", "b", "c", "d", "e",  "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "-" }
#define IL_ALPHABET_UC                         { "A", "B", "C", "D", "E",  "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "-" }
#define GSBW_PI                                3.141592653589793f
#define ASTEROID_HIT_BASE_DAMAGE               100.f
#define ASTEROID_HIT_DAMAGE_RADIUS             1000.f
#define ASTEROID_HIT_IMPULSE_STRENGTH          5000.f
#define ASTEROID_EXPLOSION_DURATION            10.f               // Make sure it is greater than any effect duration
#define ASTEROID_SELECTED_OUTLINE_CUSTOM_DEPTH 200
#define EARTH_EXPLOSION_DURATION               10.f               // Make sure it is greater than any effect duration
#define ROCKET_HIT_BASE_DAMAGE                 100.f
#define ROCKET_HIT_DAMAGE_RADIUS               1000.f
#define ROCKET_HIT_IMPULSE_STRENGTH            5000.f
#define ROCKET_EXPLOSION_DURATION              5.f
#define MIN_WORD_LEN                           3
#define MAX_WORD_LEN                           15

typedef TMap<uint8_t, TMap<FString, TArray<FString>>> GSBWWordMap;

UENUM()
enum EGSBWEvent {
  ASTEROID_HIT,
  ASTEROID_DOWN,
  ASTEROID_TIME_SCALE_CHANGE,
  EARTH_HIT,
  EARTH_DOWN,
  TARGET_CHANGE,
  GAME_START,
  GAME_OVER,
  GAME_PAUSE,
  GAME_UNPAUSE,
  DIFFICULTY_BUMP
};

UENUM()
enum class EDifficulty : uint8 {
  EASY,
  NORMAL,
  HARD,
  BARUCH,
  NUM_DIFFICULTIES
};
