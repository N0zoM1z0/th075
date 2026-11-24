#include "GraphicsTexturedDraw.hpp"
#include "CameraResetF481.hpp"
#include <windows.h>
#include <d3d8.h>
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
extern float g_CameraHorizontalBiasAt006713EC;
extern float g_CameraVerticalBiasAt0067140C;
extern float g_CameraShakeAmountAt006713F8;
extern float g_CameraShakePhaseXAt00671410;
extern float g_CameraShakePhaseYAt006713FC;
CameraResetF481* CameraResetF481::ResetParameters() {
 g_CameraHorizontalBiasAt006713EC=0;
 g_CameraVerticalBiasAt0067140C=20.0f;
 g_CameraShakeAmountAt006713F8=0;
 g_CameraShakePhaseXAt00671410=0;
 g_CameraShakePhaseYAt006713FC=0;
 return this;
}
// Native simple D3D drawing wrapper: uses this+0/+4 actual texture and flag.
class FrameTextureF481 {
 IDirect3DTexture8* originalTexture;
 unsigned char enabled;
public: void DrawIfEnabled(const float (*)[4],const RECT*,unsigned int);
};
void FrameTextureF481::DrawIfEnabled(const float (*quad)[4],const RECT* rect,unsigned int color) {
 if(enabled) Graphics::DrawTexturedQuad(quad,rect,color,originalTexture);
}
