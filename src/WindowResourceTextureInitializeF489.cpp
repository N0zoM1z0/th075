#include <windows.h>
// Independently exact native R035 full 128-byte C++ /GX owner ctor.
// The genuine nontrivial member destructor forces original compiler
// SEH cleanup and EH state; deleting that destructor incorrectly
// yields an 83-byte non-EH body even with the same resource calls.
// Real native +0x28-owned texture archive and the whole observed
// 128-byte /GX window graphics startup/resource owner constructor.
// Unknown owner fields at this+0..this+0x27 are untyped, not named.
class WindowTextureArchiveF489 {
 unsigned char nativeAllocationBytes[80];
public:WindowTextureArchiveF489(); ~WindowTextureArchiveF489(); void AllocateSlots(int);void LoadArchive(const char*,const char*);
};
class WindowResourceF489 {
 unsigned char nativeOwnerPrefixBytes[0x28];
 WindowTextureArchiveF489 texture;
public:WindowResourceF489();
};
extern const char g_WindowResourceFileAt00657898[];
extern const char g_WindowResourceRootAt00657890[];
extern void __cdecl CreateWindowDrawingSurfaceAt00401C20(int width,int height,WindowResourceF489* output,int format);
WindowResourceF489::WindowResourceF489() {
 texture.AllocateSlots(1);
 texture.LoadArchive(g_WindowResourceFileAt00657898,g_WindowResourceRootAt00657890);
 CreateWindowDrawingSurfaceAt00401C20(1024,512,this,0x20);
}
