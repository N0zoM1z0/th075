#pragma once
#include <d3d8.h>

// The battle scene allocates one byte. The atlas metadata is shared by the HUD.
class DigitAtlasesF177 {
public:
    DigitAtlasesF177(IDirect3DTexture8* primary, IDirect3DTexture8* secondary,
                     IDirect3DTexture8* auxiliary);
};
typedef char DigitAtlasesAllocationSize[sizeof(DigitAtlasesF177) == 1 ? 1 : -1];
