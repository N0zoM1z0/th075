#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <stdlib.h>

// Complete physical132byte SDK packet; original identity remains unknown.
class RectTransitionQuadF128 {
public:
    D3DXVECTOR4 first, second, third, fourth;
    RenderQuadPayload5E68C0 payload;
    RectTransitionQuadF128(const RECT*);
};
typedef char RectTransitionQuadSizeF128[(sizeof(RectTransitionQuadF128) == 132) ? 1 : -1];
void __cdecl FillTransitionRectangleF128(const RECT*, DWORD);
extern int g_TransitionFrame;
extern float g_TransitionColumns[];
extern float g_TransitionPhase;
extern float g_TransitionAmplitude;
extern float g_TransitionDirectionOne;
extern float g_TransitionDirectionTwo;
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))
#define POSITIONS(value) reinterpret_cast<const float (*)[4]>(&(value))

void __cdecl DrawTransition00432200(IDirect3DTexture8* const* texture) {
    RECT textureRect;
    SetRect(&textureRect, 0, 0, 640, 480);
    RectTransitionQuadF128 transformedQuad(&textureRect);
    Graphics::SetBlendMode(1);
    DWORD drawColor = D3DCOLOR_ARGB(255 - g_TransitionFrame * 6, 255, 255, 255);
    Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, 0xFFFFFFFF, *texture);
    Graphics::SetBlendMode(2);
    FillTransitionRectangleF128(&textureRect, drawColor);
}

void __cdecl DrawTransition004322B0(IDirect3DTexture8* const* texture) {
    RECT textureRect;
    SetRect(&textureRect, 0, 0, 640, 480);
    RectTransitionQuadF128 transformedQuad(&textureRect);
    Graphics::SetBlendMode(1);
    DWORD drawColor = D3DCOLOR_ARGB(g_TransitionFrame * 6, 255, 255, 255);
    Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, 0xFFFFFFFF, *texture);
    Graphics::SetBlendMode(2);
    FillTransitionRectangleF128(&textureRect, drawColor);
}

void __cdecl DrawTransition00432360(IDirect3DTexture8* const* texture) {
    RECT textureRect;
    SetRect(&textureRect, 0, 0, 640, 480);
    RectTransitionQuadF128 transformedQuad(&textureRect);
    Graphics::SetBlendMode(1);
    DWORD drawColor = D3DCOLOR_ARGB(255, g_TransitionFrame * 24, g_TransitionFrame * 24, g_TransitionFrame * 24);
    Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, drawColor, *texture);
}

void __cdecl DrawTransition00432410(IDirect3DTexture8* const* texture) {
    RECT textureRect;
    SetRect(&textureRect, 0, 0, 640, 480);
    RectTransitionQuadF128 transformedQuad(&textureRect);
    Graphics::SetBlendMode(1);
    DWORD drawColor = D3DCOLOR_ARGB(255, 255 - g_TransitionFrame * 24, 255 - g_TransitionFrame * 24, 255 - g_TransitionFrame * 24);
    Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, drawColor, *texture);
}

void __cdecl DrawTransition004324D0(IDirect3DTexture8* const* texture) {
    SpriteQuad40CA80 transformedQuad;
    Graphics::SetBlendMode(0);
    DWORD drawColor = D3DCOLOR_ARGB(g_TransitionFrame * 2 + 135, 255, 255, 255);
    RECT textureRect;
    for (int tileX = 0; tileX < 640; tileX += 40) {
        for (int cellY = 0; cellY < 480; cellY += 40) {
            SetRect(&textureRect, tileX, cellY, tileX + 40, cellY + 40);
            TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
            TRANSFORM(transformedQuad)->RotateQuad(tileX + 20, cellY + 20, 0, 0, 90.0f - g_TransitionFrame * 1.5f, 60 - g_TransitionFrame);
            Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, drawColor, *texture);
        }
    }
}

void __cdecl DrawTransition00432660(IDirect3DTexture8* const* texture) {
    SpriteQuad40CA80 transformedQuad;
    Graphics::SetBlendMode(0);
    DWORD drawColor = D3DCOLOR_ARGB(255 - g_TransitionFrame * 2, 255, 255, 255);
    RECT textureRect;
    for (int tileX = 0; tileX < 640; tileX += 40) {
        for (int cellY = 0; cellY < 480; cellY += 40) {
            SetRect(&textureRect, tileX, cellY, tileX + 40, cellY + 40);
            TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
            TRANSFORM(transformedQuad)->RotateQuad(tileX + 20, cellY + 20, 0, 0, -g_TransitionFrame * 1.5f, -g_TransitionFrame);
            Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, drawColor, *texture);
        }
    }
}

void __cdecl DrawTransition004327F0(IDirect3DTexture8* const* texture) {
    SpriteQuad40CA80 transformedQuad;
    if (g_TransitionFrame >= 40) {
        for (int randomColumnIndex = 0; randomColumnIndex < 640; ++randomColumnIndex)
            g_TransitionColumns[randomColumnIndex] = rand() / 3000.0f;
    }
    Graphics::SetBlendMode(0);
    DWORD drawColor = D3DCOLOR_ARGB(g_TransitionFrame * 6, 255, 255, 255);
    RECT textureRect;
    for (int tileX = 0; tileX < 640; ++tileX) {
        SetRect(&textureRect, tileX, 0, tileX + 1, 640);
        TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
        TRANSFORM(transformedQuad)->TranslateQuad(0, (40 - g_TransitionFrame) * g_TransitionColumns[tileX], 0);
        Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, drawColor, *texture);
    }
}

void __cdecl DrawTransition00432960(IDirect3DTexture8* const* texture) {
    SpriteQuad40CA80 transformedQuad;
    Graphics::SetBlendMode(0);
    DWORD drawColor = D3DCOLOR_ARGB(g_TransitionFrame * 6, 255, 255, 255);
    RECT textureRect;
    for (int tileX = 0; tileX < 640; tileX = tileX + (40 - g_TransitionFrame) + 1) {
        for (int cellY = 0; cellY < 480; cellY = cellY + (40 - g_TransitionFrame) + 1) {
            SetRect(&textureRect, tileX, cellY, tileX + 1, cellY + 1);
            TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
            TRANSFORM(transformedQuad)->ScaleQuad(tileX, cellY, 0, 40 - g_TransitionFrame + 1, 40 - g_TransitionFrame + 1, 0);
            Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, drawColor, *texture);
        }
    }
}

void __cdecl DrawTransition00432AF0(IDirect3DTexture8* const* texture) {
    SpriteQuad40CA80 transformedQuad;
    if (g_TransitionFrame >= 60) {
        g_TransitionPhase = 0;
        g_TransitionAmplitude = 0;
    }
    DWORD drawColor = D3DCOLOR_ARGB(g_TransitionFrame * 4, 255, 255, 255);
    g_TransitionPhase += 8.0f;
    g_TransitionAmplitude += 15.0f;
    RECT textureRect;
    for (int cellY = 0; cellY < 480; ++cellY) {
        SetRect(&textureRect, 0, cellY, 640, cellY + 1);
        TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
        TRANSFORM(transformedQuad)->TranslateQuad(CameraSineAt0040D940((cellY + g_TransitionPhase) * 0.017453288659453392f * 3.0f) * g_TransitionAmplitude, 0, 0);
        Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, drawColor, *texture);
    }
}

void __cdecl DrawTransition00432C40(IDirect3DTexture8* const* texture) {
    SpriteQuad40CA80 transformedQuad;
    if (g_TransitionFrame >= 60) g_TransitionDirectionOne = 1 - (rand() % 2) * 2;
    DWORD drawColor = D3DCOLOR_ARGB(g_TransitionFrame * 4, 255, 255, 255);
    RECT textureRect;
    SetRect(&textureRect, 0, 0, 640, 480);
    TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
    for (int pass = 0; pass < 6; ++pass) {
        TRANSFORM(transformedQuad)->RotateQuad(320.0f, 240.0f, 0, 0, 0, (g_TransitionFrame - 60) * g_TransitionDirectionOne / 2.0f);
        Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, drawColor, *texture);
    }
}

void __cdecl DrawTransition00432D70(IDirect3DTexture8* const* texture) {
    SpriteQuad40CA80 transformedQuad;
    if (g_TransitionFrame >= 60) g_TransitionDirectionTwo = 1 - (rand() % 2) * 2;
    DWORD drawColor = D3DCOLOR_ARGB(255 - (g_TransitionFrame * 4 + 15), 255, 255, 255);
    RECT textureRect;
    SetRect(&textureRect, 0, 0, 640, 480);
    TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
    for (int pass = 0; pass < 6; ++pass) {
        TRANSFORM(transformedQuad)->RotateQuad(320.0f, 240.0f, 0, 0, 0, g_TransitionFrame * g_TransitionDirectionTwo / 2.0f);
        Graphics::DrawTexturedQuad(POSITIONS(transformedQuad), &textureRect, drawColor, *texture);
    }
}

// Private effect/drawing owners are pointer-only views, never local values.
class LayerDrawingF128 {
public:
    void SetBlendMode(int);
    void DrawSprite(int, float, float, DWORD, float, float, float, float, unsigned char);
};
extern float g_LayerCameraX;
extern float g_LayerCameraY;
#define DRAWING reinterpret_cast<LayerDrawingF128*>(reinterpret_cast<char*>(this) + 0x18)
class EffectLayer00449B50 { public: void Draw(); };
class EffectLayer0044A2E0 { public: void Draw(); };
class EffectLayer0044AC60 { public: void Draw(); };
class EffectLayer0044AF00 { public: void Draw(); };
class EffectLayer0044CC20 { public: void Draw(); };
class EffectLayer0044CEC0 { public: void Draw(); };
void EffectLayer00449B50::Draw() {
    int cameraX = static_cast<int>(g_LayerCameraX + 160.0f);
    int cameraY = static_cast<int>(g_LayerCameraY);
    DRAWING->SetBlendMode(0);
    DRAWING->DrawSprite(2, cameraX * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 320.0, cameraY + 280, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 320.0, cameraY + 280, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 1);
    DRAWING->DrawSprite(0, cameraX + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
}

void EffectLayer0044A2E0::Draw() {
    int cameraX = static_cast<int>(g_LayerCameraX + 160.0f);
    int cameraY = static_cast<int>(g_LayerCameraY);
    DRAWING->SetBlendMode(0);
    DRAWING->DrawSprite(2, cameraX * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 320.0, cameraY + 280, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 320.0, cameraY + 280, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 1);
    DRAWING->DrawSprite(0, cameraX + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
}

void EffectLayer0044AC60::Draw() {
    int cameraX = static_cast<int>(g_LayerCameraX + 160.0f);
    int cameraY = static_cast<int>(g_LayerCameraY);
    DRAWING->SetBlendMode(0);
    DRAWING->DrawSprite(2, cameraX * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 345.0, cameraY + 240, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 0);
    DRAWING->DrawSprite(0, cameraX + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
}

void EffectLayer0044AF00::Draw() {
    int cameraX = static_cast<int>(g_LayerCameraX + 160.0f);
    int cameraY = static_cast<int>(g_LayerCameraY);
    DRAWING->SetBlendMode(0);
    DRAWING->DrawSprite(2, cameraX * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 345.0, cameraY + 240, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 0);
    DRAWING->DrawSprite(0, cameraX + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
}

void EffectLayer0044CC20::Draw() {
    int cameraX = static_cast<int>(g_LayerCameraX + 160.0f);
    int cameraY = static_cast<int>(g_LayerCameraY);
    DRAWING->SetBlendMode(0);
    DRAWING->DrawSprite(2, cameraX * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 320.0, cameraY + 280, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 1);
    DRAWING->DrawSprite(0, cameraX + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
}

void EffectLayer0044CEC0::Draw() {
    int cameraX = static_cast<int>(g_LayerCameraX + 160.0f);
    int cameraY = static_cast<int>(g_LayerCameraY);
    DRAWING->SetBlendMode(0);
    DRAWING->DrawSprite(2, cameraX * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 320.0, cameraY + 280, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 1);
    DRAWING->DrawSprite(0, cameraX + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
}

#undef DRAWING
#undef POSITIONS
#undef TRANSFORM
