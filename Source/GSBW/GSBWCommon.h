#pragma once

#define PURE_VIRTUAL                { check(0 && "Pure Virtual Function -- Override It") }
#define IL_ALPHABET_LC              { "a", "b", "c", "d", "e",  "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" }
#define IL_ALPHABET_UC              { "A", "B", "C", "D", "E",  "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" }
#define ROCKET_HIT_DAMAGE_AMOUNT    1000.f
#define ROCKET_HIT_IMPULSE_STRENGTH 100.f
#define ASTEROID_EXPLOSION_DURATION 5.f