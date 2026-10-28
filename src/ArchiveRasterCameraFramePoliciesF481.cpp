#include <windows.h>
#include <d3d8.h>
// Five individually native-verified original complete R-origin functions.
// Real archive list ctor and dtor lifetimes, original HWND and D3D8
// resource state and genuine five camera globals; only physical borrowed
// owner field offsets are declared, not original complete classes.
// Actual native archive small owned list plus Windows native handle ABI.
class ArchiveEntryListF481 {public: ArchiveEntryListF481(); ~ArchiveEntryListF481(); void Clear();};
class DataArchiveF481 {
    HANDLE originalHandle;
    ArchiveEntryListF481 entries;
public:
    DataArchiveF481(); ~DataArchiveF481();
};
DataArchiveF481::DataArchiveF481() {
    originalHandle=0;
    entries.Clear();
}
DataArchiveF481::~DataArchiveF481() {
    if(originalHandle) CloseHandle(originalHandle);
    entries.Clear();
}
// Original C++ receiver is the private raster device owner; only the
// independently observed field stores in the original initializer.
class RasterStateF481 {
 HWND originalWindow;
 void* selectedDevice;
 unsigned int stateA,stateB;
 unsigned int otherOwner;
 void* rawBuffer;
public: RasterStateF481* Initialize(HWND window);
};
RasterStateF481* RasterStateF481::Initialize(HWND window) {
 originalWindow=window;
 selectedDevice=0;
 stateA=0;
 stateB=0;
 rawBuffer=0;
 return this;
}
extern unsigned int g_CameraResetOneAt006713EC;
extern float g_CameraResetHeightAt0067140C;
extern unsigned int g_CameraResetTwoAt006713F8;
extern unsigned int g_CameraResetThreeAt00671410;
extern unsigned int g_CameraResetFourAt006713FC;
class CameraResetF481 {public: CameraResetF481* ResetParameters();};
CameraResetF481* CameraResetF481::ResetParameters() {
 g_CameraResetOneAt006713EC=0;
 g_CameraResetHeightAt0067140C=20.0f;
 g_CameraResetTwoAt006713F8=0;
 g_CameraResetThreeAt00671410=0;
 g_CameraResetFourAt006713FC=0;
 return this;
}
// Native simple D3D drawing wrapper: uses this+0/+4 actual texture and flag.
extern void __cdecl DrawD3DQuadAt004029F0(const float (*)[4], const RECT*,unsigned int,IDirect3DTexture8*);
class FrameTextureF481 {
 IDirect3DTexture8* originalTexture;
 unsigned char enabled;
public: void DrawIfEnabled(const float (*)[4],const RECT*,unsigned int);
};
void FrameTextureF481::DrawIfEnabled(const float (*quad)[4],const RECT* rect,unsigned int color) {
 if(enabled) DrawD3DQuadAt004029F0(quad,rect,color,originalTexture);
}
