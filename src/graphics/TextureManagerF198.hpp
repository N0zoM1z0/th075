#pragma once
#include "graphics/GraphicsResourceClient.hpp"
#include "graphics/TextureManagerBorrowedF925.hpp"
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

class SpriteQuad40CA80;
namespace Graphics { struct ScreenVertex; }

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
    void AllocateTextureSlots(unsigned int count, unsigned char kind);
    void AllocateUnformattedSlots(int count);
    void ClearSlots();
    void LoadDefault(const char* filename, const char* archiveName);
    void Load(const char* filename, signed char selectedPalette, const char* archiveName);
    void LoadPalette(const char* filename);
    void LoadBitmapDirectory(const char* baseDir);
    void LoadBitmapDirectoryWithFormat(const char* baseDir);
    void Refresh(int index);
    void Present();
    void SetBlendMode(int mode);
    void SetDepthMode(int mode);
    void SetTextureFilter(int mode);
    void SetPixelShaderMode(signed char mode);
    void SetColorMultiplier(float multiplier);
    IDirect3DTexture8* GetTexture(int index);
    void GetTextureRect(int index, RECT* rectangle);
    void DrawQuad(int texture, const SpriteQuad40CA80& quad, const RECT* rect, DWORD color);
    void DrawProjectedQuad(int texture, const SpriteQuad40CA80& quad, const RECT* rect,
        float x, float y, float z, DWORD color);
    void DrawProjectedTriangleStrip(int texture, Graphics::ScreenVertex* vertices, int count);
    void DrawSprite(int texture, float x, float y, DWORD color, float pivotX,
        float pivotY, float scale, float angle, unsigned char flags);
    void DrawSpriteVariant(int texture, float x, float y, DWORD color, float pivotX,
        float pivotY, float scale, float angle, unsigned char flags, unsigned char mode);
    void DrawScaled(int texture, float x, float y, DWORD color, float pivotX, float pivotY,
        float scaleX, float scaleY, float angle, unsigned char flags);
    void DrawOpaqueSprite(int texture, int x, int y, DWORD color);
    void DrawOpaqueSpriteMirrored(int texture, int x, int y, DWORD color, unsigned char flip);
    void DrawOpaqueSpriteWhite(int texture, int x, int y);
};

typedef char AssertTextureManager80F198[
    (sizeof(TextureManagerF198) == 80) ? 1 : -1];
