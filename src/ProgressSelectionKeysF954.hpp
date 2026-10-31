#pragma once
#include <stddef.h>

// Signed physical one-byte indices observed independently in the pinned
// original Japanese TH075 PE: this+0x16AC4 and this+0x16AC5.
// They address the genuine character/difficulty record matrix (0x17F0
// /0x5FC original strides) but we do NOT reconstruct the whole enormous
// owner or embed this two-byte borrowed tail as a complete object.
struct ProgressSelectionKeysF954 {
    signed char fighterAt16AC4;
    signed char difficultyAt16AC5;
};
typedef char ProgressSelectionKeysF954Size[
    sizeof(ProgressSelectionKeysF954)==2 ? 1 : -1];
typedef char ProgressSelectionKeysF954SecondOffset[
    offsetof(ProgressSelectionKeysF954,difficultyAt16AC5)==1 ? 1 : -1];
#define F954_PROGRESS_KEYS(receiver) (*reinterpret_cast<ProgressSelectionKeysF954*>(reinterpret_cast<unsigned char*>(receiver)+0x16AC4))
