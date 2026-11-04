#pragma once
#include <stddef.h>

// Observed complete original BattleStatus::RenderStatus uses three
// independent 8-byte pairs of float values indexed by player side:
// native HUD owner+0xE4, +0xF4 and +0x104. This is a borrowed
// two-element scalar window only, NOT an allocated/completed owner.
struct BattleStatusFloatPairF1096 {
    float bySide[2];
};
typedef char F1096FloatSideSize[sizeof(BattleStatusFloatPairF1096)==8?1:-1];
typedef char F1096FloatSideBase[offsetof(BattleStatusFloatPairF1096,bySide)==0?1:-1];
#define F1096_STATUS_FLOAT(owner,base,side) (*reinterpret_cast<BattleStatusFloatPairF1096*>(reinterpret_cast<unsigned char*>(owner)+(base))).bySide[(side)]

// Two actual signed 16-bit player name-group IDs at native actor
// +0x398/+0x39A, selected by the independent byte at +0x39D.
struct FighterNameGroupWordsF1096 {
    signed short groupWhenSelector2At398;
    signed short groupOtherwiseAt39A;
};
typedef char F1096GroupWordSize[sizeof(FighterNameGroupWordsF1096)==4?1:-1];
typedef char F1096GroupSecondOffset[offsetof(FighterNameGroupWordsF1096,groupOtherwiseAt39A)==2?1:-1];
#define F1096_NAME_GROUP(actor) (*reinterpret_cast<FighterNameGroupWordsF1096*>(reinterpret_cast<unsigned char*>(actor)+0x398))
