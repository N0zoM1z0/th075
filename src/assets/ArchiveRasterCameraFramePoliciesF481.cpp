#include "graphics/FontSurface.hpp"
#include "graphics/GraphicsTexturedDraw.hpp"
#include "battle/CameraResetF481.hpp"
#include "ui/WindowOverlayF212.hpp"
#include <windows.h>
#include <d3d8.h>
FontSurface::FontSurface(HWND ownerWindow) {
 window=ownerWindow;
 deviceContext=0;
 font=0;
 previouslySelectedFont=0;
 glyphBitmap=0;
}
extern float g_CameraHorizontalBiasAt006713EC;
extern float g_CameraVerticalBiasAt0067140C;
extern float g_CameraShakeAmountAt006713F8;
extern float g_CameraShakePhaseXAt00671410;
extern float g_CameraShakePhaseYAt006713FC;
CameraResetF481::CameraResetF481() {
 g_CameraHorizontalBiasAt006713EC=0;
 g_CameraVerticalBiasAt0067140C=20.0f;
 g_CameraShakeAmountAt006713F8=0;
 g_CameraShakePhaseXAt00671410=0;
 g_CameraShakePhaseYAt006713FC=0;
}
void WindowOverlayF212::DrawIfEnabled(const SpriteQuad40CA80& quad, const RECT* rect, DWORD color)
{
    if (enabled)
        Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&quad), rect, color, texture);
}
