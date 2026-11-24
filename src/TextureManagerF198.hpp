#pragma once
#include "GraphicsResourceClient.hpp"
#include "TextureManagerBorrowedF925.hpp"
#include <d3d8.h>
#include <deque>
#include <vector>

// The independently reconstructed 80-byte TextureManager receiver.
// Constructor storage is grounded by 0040AD80; the F199 destruction view
// independently confirms the same 80-byte physical extent.
// The native deque indexes four-byte elements and destroys them trivially.
struct TextureQueueEntryF198 {
    unsigned char unknown00[4];
};

class TextureManagerF198 {
    GraphicsResourceClient graphicsClient;
public:
    WORD* palette;
    std::vector<NativeTextureElementF769> entries;
    std::vector<IDirect3DTexture8*> textures;
    std::vector<IDirect3DTexture8*> paletteTextures;
private:
    std::deque<TextureQueueEntryF198> resourceQueue;
public:
    unsigned char textureDepth;
    TextureManagerF198();
    ~TextureManagerF198();
    void AllocateUnformattedSlots(int count);
    void LoadDefault(const char* filename, const char* archiveName);
    void Load(const char* filename, signed char selectedPalette, const char* archiveName);
    void Present();
    void SetBlendMode(int mode);
    void SetDepthMode(int mode);
    void SetTextureFilter(int mode);
    void SetPixelShaderMode(signed char mode);
    void SetColorMultiplier(float multiplier);
};

typedef char AssertTextureManager80F198[
    (sizeof(TextureManagerF198) == 80) ? 1 : -1];
