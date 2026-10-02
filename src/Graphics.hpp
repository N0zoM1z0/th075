#pragma once
#include <windows.h>
#include <d3d8.h>

// Inferred names for TH075's shared D3D8 state interface. These declarations
// cover the accepted functions only; resource ownership remains external.
namespace Graphics
{
typedef void (__cdecl *PresentCallback)(IDirect3DTexture8 **textures);

void ShowError(const char *message);
void SetPresentationDestinationRect(const RECT *rect);
void SetTargetViewport(DWORD x, DWORD y, DWORD width, DWORD height);
void SetPresentationSourceRect(const RECT *rect);
void SetClearColor(unsigned char red, unsigned char green, unsigned char blue);
void SetColorMultiplier(float multiplier);
void SetDrawTransform(float scale, float originX, float originY);
bool BeginTarget(signed char index);
void BeginFrame();
void SetPresentCallback(PresentCallback callback);
IDirect3DTexture8 *GetPrimaryTargetTexture();
IDirect3DTexture8 *GetTargetTexture(signed char index);
void LoadTexture(const char *filename, IDirect3DTexture8 **texture);
void SetTextureStage(signed char stage, IDirect3DTexture8 *texture, bool enabled);
void SetPixelShaderMode(signed char mode);
void EndFrame();
void Present();
void PresentToWindow(HWND window);
void SetBlendMode(int mode);
void SetAlphaMode(int mode);
void SetDepthMode(int mode);
void SetTextureFilter(int mode);
}
