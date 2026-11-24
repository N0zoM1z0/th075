#include "GraphicsTexture.hpp"
// Independently exact native R035 full 128-byte C++ /GX owner ctor.
// The genuine nontrivial member destructor forces original compiler
// SEH cleanup and EH state; deleting that destructor incorrectly
// yields an 83-byte non-EH body even with the same resource calls.
// Real native +0x28-owned texture archive and the whole observed
// 128-byte /GX window graphics startup/resource owner constructor.
class WindowTextureArchiveF489 {
 unsigned char nativeAllocationBytes[80];
public:WindowTextureArchiveF489(); ~WindowTextureArchiveF489(); void AllocateSlots(int);void LoadArchive(const char*,const char*);
};
class WindowResourceF489 {
 IDirect3DTexture8* canvas;
 unsigned char unknown004[0x28 - 0x04];
 WindowTextureArchiveF489 texture;
public:WindowResourceF489();
};
extern const char g_WindowResourceFileAt00657898[];
extern const char g_WindowResourceRootAt00657890[];
WindowResourceF489::WindowResourceF489() {
 texture.AllocateSlots(1);
 texture.LoadArchive(g_WindowResourceFileAt00657898,g_WindowResourceRootAt00657890);
 Graphics::CreateTexture(1024, 512, &canvas, 0x20);
}
