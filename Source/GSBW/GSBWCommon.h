#pragma once

#include "Engine.h"

#define STR_ALPHABET_LC               "abcdefghijklmnopqrstuvwxyz" 
#define IL_ALPHABET_LC                { "a", "b", "c", "d", "e",  "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "-" }
#define IL_ALPHABET_UC                { "A", "B", "C", "D", "E",  "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "-" }
#define ASTEROID_HIT_BASE_DAMAGE      100.f
#define ASTEROID_HIT_DAMAGE_RADIUS    1000.f
#define ASTEROID_HIT_IMPULSE_STRENGTH 5000.f
#define EARTH_EXPLOSION_DURATION      2.f
#define ROCKET_HIT_BASE_DAMAGE        100.f
#define ROCKET_HIT_DAMAGE_RADIUS      1000.f
#define ROCKET_HIT_IMPULSE_STRENGTH   5000.f
#define ROCKET_EXPLOSION_DURATION     5.f
#define ASTEROID_EXPLOSION_DURATION   5.f
#define MIN_WORD_LEN                  3
#define MAX_WORD_LEN                  15

typedef TMap<uint8_t, TMap<FString, TArray<FString>>> GSBWWordMap;

UENUM()
enum EGSBWEvent {
  ASTEROID_HIT,
  ASTEROID_DOWN,
  ASTEROID_TIME_SCALE_CHANGE,
  EARTH_HIT,
  EARTH_DOWN,
  GAME_PAUSED,
  GAME_UNPAUSED,
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
