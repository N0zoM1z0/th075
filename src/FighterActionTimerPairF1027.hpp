#pragma once
#include <stddef.h>

// Original SHA-pinned Japanese TH075 1.11 character/actor
// state memory: signed 16-bit value at +0x80 and independent
// signed 16-bit state timer at +0x82. Full native collision,
// action-reset, animation, render and auxiliary functions
// physically read/write these separate WORDs; some owners
// have only the latter use. Borrowed 4-byte window only,
// NOT a complete historical character or effect layout.
struct FighterActionTimerPairF1027 {
    signed short wordAt80;
    signed short timerAt82;
};
typedef char F1027WordPairSize[
    sizeof(FighterActionTimerPairF1027)==4 ? 1 : -1];
typedef char F1027TimerWordOffset[
    offsetof(FighterActionTimerPairF1027,timerAt82)==2 ? 1 : -1];
#define F1027_TIMERS(actor) (*reinterpret_cast<FighterActionTimerPairF1027*>(reinterpret_cast<unsigned char*>(actor)+0x80))
