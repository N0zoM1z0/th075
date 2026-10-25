#pragma once
#include <d3d8.h>

// Call-only constructor view. The native guarded allocation forwards the EAX
// receiver into its parent. Complete original owner identity remains unknown;
// do not instantiate, embed or measure this view.
class DigitAtlasesF177 {
public:
    DigitAtlasesF177(IDirect3DTexture8* primary, IDirect3DTexture8* secondary,
                     IDirect3DTexture8* auxiliary);
};
