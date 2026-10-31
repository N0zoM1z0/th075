#pragma once
#include <stddef.h>

// The SHA-pinned original Japanese TH075 executable physically
// stores adjacent, 16-bit actor script counter WORDs at +0xF00
// and +0xF02. Multiple complete native per-character reset
// callables plus stage-driven boss cases independently prove
// these exact field widths and offsets. This is a BORROWED
// four-byte window only, NOT a complete fighter/owner layout.
struct FighterScriptCounterWindowF1022 {
    unsigned short counterAtF00;
    unsigned short counterAtF02;
};
typedef char F1022ScriptCounterSize[
    sizeof(FighterScriptCounterWindowF1022)==4 ? 1 : -1];
typedef char F1022ScriptCounterOffset[
    offsetof(FighterScriptCounterWindowF1022,counterAtF02)==2 ? 1 : -1];
#define F1022_SCRIPT(actor) (*reinterpret_cast<FighterScriptCounterWindowF1022*>(reinterpret_cast<unsigned char*>(actor)+0xF00))
