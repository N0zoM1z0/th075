#pragma once
#include "TextureManagerBorrowedF925.hpp"
#include <d3d8.h>
#include <vector>

// The independently reconstructed 80-byte TextureManager receiver.
// Constructor storage is grounded by 0040AD80; the F199 destruction view
// independently confirms the same 80-byte physical extent.
class TextureRefCountF198 {
    unsigned int refCountAt0;
public:
    TextureRefCountF198();
    ~TextureRefCountF198();
};

class TextureQueueF198 {
    unsigned int observedStorage[5];
public:
    TextureQueueF198();
    ~TextureQueueF198();
};

class TextureManagerF198 : public TextureRefCountF198 {
public:
    WORD* palette;
    std::vector<NativeTextureElementF769> entries;
    std::vector<IDirect3DTexture8*> textures;
    std::vector<IDirect3DTexture8*> paletteTextures;
private:
    TextureQueueF198 resourceQueue;
public:
    unsigned char textureDepth;
    TextureManagerF198();
    ~TextureManagerF198();
    void AllocateUnformattedSlots(int count);
    void LoadDefault(const char* filename, const char* archiveName);
    void Load(const char* filename, signed char selectedPalette, const char* archiveName);
    void SetBlendMode(int mode);
};

typedef char AssertTextureManager80F198[
    (sizeof(TextureManagerF198) == 80) ? 1 : -1];
