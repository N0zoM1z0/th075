#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include "GraphicsVertex.hpp"

// Independently complete132byte physical packet; original identity is unknown.
// The RECT constructor constructs the same four vectors and full payload.
class RectQuadF127 {
public:
    D3DXVECTOR4 first, second, third, fourth;
    RenderQuadPayload5E68C0 payload;
    RectQuadF127(const RECT*);
};
typedef char RectQuadSizeF127[(sizeof(RectQuadF127) == 132) ? 1 : -1];

// All private drawing/effect owners are pointer-only views, never local values.
class EffectDrawingF127 {
public:
    void SetDepthMode(int);
    void SetBlendMode(int);
    void SetTextureFilter(int);
    void DrawSprite(int, float, float, DWORD, float, float, float, float, unsigned char);
    void DrawSpriteVariant(int, float, float, DWORD, float, float, float, float, unsigned char, unsigned char);
    void DrawProjectedQuad(int, const RectQuadF127&, const RECT*, float, float, float, DWORD);
    void DrawProjectedQuad(int, const SpriteQuad40CA80&, const RECT*, float, float, float, DWORD);
    void DrawQuad(int, const RectQuadF127&, const RECT*, DWORD);
    void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD);
    void DrawTriangleStrip(int, Graphics::ScreenVertex*, int);
};
extern "C" double __cdecl sin(double);
extern float g_EffectCameraX;
extern float g_EffectCameraY;
void __cdecl FillRectangleF127(const RECT*, DWORD);
#define OWNER_INT(offset) (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + (offset)))
#define DRAWING reinterpret_cast<EffectDrawingF127*>(reinterpret_cast<char*>(this) + 0x18)
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))
// Existing owner records are viewed individually; the complete owner is unknown.
#define STRIP(index) (reinterpret_cast<Graphics::ScreenVertex*>(reinterpret_cast<char*>(this) + 0xF0)[index])
class EffectPattern00449EE0 { public: void Render(); };
class EffectPattern0044B630 { public: void Render(); };
class EffectPattern0044BB50 { public: void Render(); };
class EffectPattern0044C070 { public: void Render(); };
class EffectPattern0044D620 { public: void Render(); };
class EffectPattern0044DA90 { public: void Render(); };
class EffectPattern0044E3D0 { public: void Render(); };
class EffectPattern0044F850 { public: void Render(); };
class EffectPattern0044FAF0 { public: void Render(); };
class EffectPattern0044FD40 { public: void Render(); };
class EffectPattern00450420 { public: void Render(); };
class EffectPattern00450C10 { public: void Render(); };
class EffectPattern00450EE0 { public: void Render(); };
class EffectPattern00451440 { public: void Render(); };

void EffectPattern00449EE0::Render() {
    int cameraX = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    DRAWING->SetBlendMode(0);
    DRAWING->DrawSprite(2, cameraX * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 320.0, cameraY + 280, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 320.0, cameraY + 280, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 1);
    DRAWING->DrawSprite(0, cameraX + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
    DRAWING->SetBlendMode(2);
    DRAWING->SetTextureFilter(2);
    DRAWING->DrawSpriteVariant(3, cameraX + 35, cameraY + 272, 0xFFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.11) * 0.1 + 2.5, 0, 0, 1);
    DRAWING->DrawSpriteVariant(3, cameraX + 605, cameraY + 272, 0xFFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.1 + 2.0) * 0.1 + 2.5, 0, 0, 1);
    DRAWING->SetTextureFilter(1);
    DRAWING->SetBlendMode(0);
}

void EffectPattern0044B630::Render() {
    int cameraHorizontal = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    DRAWING->SetDepthMode(0);
    DRAWING->SetBlendMode(0);
    RECT spriteRectFirst;
    spriteRectFirst.left = 0; spriteRectFirst.top = 0; spriteRectFirst.right = 32; spriteRectFirst.bottom = 41;
    RectQuadF127 spriteQuadFirst(&spriteRectFirst);
    TRANSFORM(spriteQuadFirst)->RotateQuad(16.0f, 41.0f, 0, -15.0f, OWNER_INT(0x68) * 16, 0);
    TRANSFORM(spriteQuadFirst)->TranslateQuad(cameraHorizontal + 796, cameraY - 26, 0);
    RECT secondTextureRect;
    secondTextureRect.left = 0; secondTextureRect.top = 0; secondTextureRect.right = 32; secondTextureRect.bottom = 41;
    RectQuadF127 secondSpriteQuad(&secondTextureRect);
    TRANSFORM(secondSpriteQuad)->RotateQuad(16.0f, 41.0f, 0, -15.0f, OWNER_INT(0x68) * 16 + 90, 0);
    TRANSFORM(secondSpriteQuad)->TranslateQuad(cameraHorizontal + 796, cameraY - 26, 0);
    DRAWING->DrawSprite(2, cameraHorizontal * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraHorizontal * 0.75 + 320.0, cameraY * 0.75 + 570.0, 0xFFFFFFFF, 600.0f, 300.0f, 1.0f, 0, 0);
    DRAWING->DrawSprite(0, cameraHorizontal + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
    DRAWING->DrawProjectedQuad(3, spriteQuadFirst, &spriteRectFirst, 320.0f, 160.0f, 1500.0f, 0xFFFFFFFF);
    DRAWING->DrawProjectedQuad(4, secondSpriteQuad, &secondTextureRect, 320.0f, 160.0f, 1500.0f, 0xFFFFFFFF);
}

void EffectPattern0044BB50::Render() {
    int cameraHorizontal = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    DRAWING->SetDepthMode(0);
    DRAWING->SetBlendMode(0);
    RECT spriteRectFirst;
    spriteRectFirst.left = 0; spriteRectFirst.top = 0; spriteRectFirst.right = 32; spriteRectFirst.bottom = 41;
    RectQuadF127 spriteQuadFirst(&spriteRectFirst);
    TRANSFORM(spriteQuadFirst)->RotateQuad(16.0f, 41.0f, 0, -15.0f, OWNER_INT(0x68) * 16, 0);
    TRANSFORM(spriteQuadFirst)->TranslateQuad(cameraHorizontal + 796, cameraY - 26, 0);
    RECT secondTextureRect;
    secondTextureRect.left = 0; secondTextureRect.top = 0; secondTextureRect.right = 32; secondTextureRect.bottom = 41;
    RectQuadF127 secondSpriteQuad(&secondTextureRect);
    TRANSFORM(secondSpriteQuad)->RotateQuad(16.0f, 41.0f, 0, -15.0f, OWNER_INT(0x68) * 16 + 90, 0);
    TRANSFORM(secondSpriteQuad)->TranslateQuad(cameraHorizontal + 796, cameraY - 26, 0);
    DRAWING->DrawSprite(2, cameraHorizontal * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraHorizontal * 0.75 + 320.0, cameraY * 0.75 + 570.0, 0xFFFFFFFF, 600.0f, 300.0f, 1.0f, 0, 0);
    DRAWING->DrawSprite(0, cameraHorizontal + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
    DRAWING->DrawProjectedQuad(3, spriteQuadFirst, &spriteRectFirst, 320.0f, 160.0f, 1500.0f, 0xFFFFFFFF);
    DRAWING->DrawProjectedQuad(4, secondSpriteQuad, &secondTextureRect, 320.0f, 160.0f, 1500.0f, 0xFFFFFFFF);
}

void EffectPattern0044C070::Render() {
    int cameraHorizontal = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    DRAWING->SetDepthMode(0);
    DRAWING->SetBlendMode(0);
    RECT spriteRectFirst;
    spriteRectFirst.left = 0; spriteRectFirst.top = 0; spriteRectFirst.right = 32; spriteRectFirst.bottom = 41;
    RectQuadF127 spriteQuadFirst(&spriteRectFirst);
    TRANSFORM(spriteQuadFirst)->RotateQuad(16.0f, 41.0f, 0, -15.0f, OWNER_INT(0x68) * 16, 0);
    TRANSFORM(spriteQuadFirst)->TranslateQuad(cameraHorizontal + 796, cameraY - 26, 0);
    RECT secondTextureRect;
    secondTextureRect.left = 0; secondTextureRect.top = 0; secondTextureRect.right = 32; secondTextureRect.bottom = 41;
    RectQuadF127 secondSpriteQuad(&secondTextureRect);
    TRANSFORM(secondSpriteQuad)->RotateQuad(16.0f, 41.0f, 0, -15.0f, OWNER_INT(0x68) * 16 + 90, 0);
    TRANSFORM(secondSpriteQuad)->TranslateQuad(cameraHorizontal + 796, cameraY - 26, 0);
    DRAWING->DrawSprite(2, cameraHorizontal * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraHorizontal * 0.75 + 320.0, cameraY * 0.75 + 570.0, 0xFFFFFFFF, 600.0f, 300.0f, 1.0f, 0, 0);
    DRAWING->DrawSprite(0, cameraHorizontal + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
    DRAWING->DrawProjectedQuad(3, spriteQuadFirst, &spriteRectFirst, 320.0f, 160.0f, 1500.0f, 0xFFFFFFFF);
    DRAWING->DrawProjectedQuad(4, secondSpriteQuad, &secondTextureRect, 320.0f, 160.0f, 1500.0f, 0xFFFFFFFF);
}

void EffectPattern0044D620::Render() {
    int cameraHorizontal = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    Graphics::ScreenVertex stripVertices[6];
    stripVertices[0].x = cameraHorizontal + 280.0;
    stripVertices[0].y = cameraY + -512.0;
    stripVertices[0].z = 0; stripVertices[0].rhw = 0;
    stripVertices[0].color = 0xC8FFFFFF;
    stripVertices[0].u = 0.0f;
    stripVertices[0].v = OWNER_INT(0x68) * 0.0004;
    stripVertices[1].x = cameraHorizontal + 360.0;
    stripVertices[1].y = cameraY + -512.0;
    stripVertices[1].z = 0; stripVertices[1].rhw = 0;
    stripVertices[1].color = 0xC8FFFFFF;
    stripVertices[1].u = 1.0f;
    stripVertices[1].v = OWNER_INT(0x68) * 0.0004;
    stripVertices[2].x = cameraHorizontal + 170.0;
    stripVertices[2].y = cameraY + 192.0;
    stripVertices[2].z = 0; stripVertices[2].rhw = 0;
    stripVertices[2].color = 0xB4FFFFFF;
    stripVertices[2].u = 0.0f;
    stripVertices[2].v = OWNER_INT(0x68) * 0.0004 + 0.9166666666666666;
    stripVertices[3].x = cameraHorizontal + 470.0;
    stripVertices[3].y = cameraY + 192.0;
    stripVertices[3].z = 0; stripVertices[3].rhw = 0;
    stripVertices[3].color = 0xB4FFFFFF;
    stripVertices[3].u = 1.0f;
    stripVertices[3].v = OWNER_INT(0x68) * 0.0004 + 0.9166666666666666;
    stripVertices[4].x = cameraHorizontal + 160.0;
    stripVertices[4].y = cameraY + 256.0;
    stripVertices[4].z = 0; stripVertices[4].rhw = 0;
    stripVertices[4].color = 0x00FFFFFF;
    stripVertices[4].u = 0.0f;
    stripVertices[4].v = OWNER_INT(0x68) * 0.0004 + 1.0;
    stripVertices[5].x = cameraHorizontal + 480.0;
    stripVertices[5].y = cameraY + 256.0;
    stripVertices[5].z = 0; stripVertices[5].rhw = 0;
    stripVertices[5].color = 0x00FFFFFF;
    stripVertices[5].u = 1.0f;
    stripVertices[5].v = OWNER_INT(0x68) * 0.0004 + 1.0;
    DRAWING->SetDepthMode(0);
    DRAWING->DrawSprite(0, cameraHorizontal + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
    DRAWING->SetBlendMode(2);
    DRAWING->DrawTriangleStrip(1, stripVertices, 6);
    DRAWING->SetBlendMode(0);
}

void EffectPattern0044DA90::Render() {
    int cameraX = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    DRAWING->SetDepthMode(0);
    DRAWING->DrawSprite(0, cameraX + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
    DRAWING->SetBlendMode(2);
    DRAWING->SetTextureFilter(2);
    DRAWING->DrawSpriteVariant(1, cameraX + 177, cameraY + (30), 0xDFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.11) * 0.05 + 1.5, 0, 0, 1);
    DRAWING->DrawSpriteVariant(1, cameraX + 286, cameraY + (25), 0xBFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.09 + 1.0) * 0.05 + 0.7f, 0, 0, 1);
    DRAWING->DrawSpriteVariant(1, cameraX + 361, cameraY + (-144), 0xA8FFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.12 + 2.0) * 0.05 + 0.7f, 0, 0, 1);
    DRAWING->DrawSpriteVariant(1, cameraX + 405, cameraY + (90), 0xBFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.1 + 2.0) * 0.05 + 1.0, 0, 0, 1);
    DRAWING->DrawSpriteVariant(1, cameraX + 513, cameraY + (-209), 0xDFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.09 + 2.0) * 0.05 + 1.7f, 0, 0, 1);
    DRAWING->SetTextureFilter(1);
    DRAWING->SetBlendMode(0);
}

void EffectPattern0044E3D0::Render() {
    int cameraHorizontal = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    DRAWING->SetDepthMode(0);
    DRAWING->SetBlendMode(0);
    DRAWING->DrawSprite(2, cameraHorizontal * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraHorizontal * 0.75 + 320.0, cameraY * 0.75 + 150.0, 0xFFFFFFFF, 700.0f, 200.0f, 1.0f, 0, 0);
    int stripCount = static_cast<int>((1536.0 - OWNER_INT(0x68) * 0.4) / 384.0);
    RECT imageRect;
    imageRect.left = 0; imageRect.top = 0; imageRect.right = stripCount * 128; imageRect.bottom = 128;
    DRAWING->SetTextureFilter(2);
    SpriteQuad40CA80 spriteQuadFirst(0, 0, stripCount * 128 * 3, 256.0f);
    TRANSFORM(spriteQuadFirst)->TranslateQuad(cameraHorizontal * 0.75 + OWNER_INT(0x68) * 0.4, cameraY * 0.75 + 160.0, 0);
    DRAWING->DrawProjectedQuad(3, spriteQuadFirst, &imageRect, 320.0f, 240.0f, 1500.0f, 0xFFFFFFFF);
    imageRect.left = 0; imageRect.top = 0; imageRect.right = (5 - stripCount) * 128; imageRect.bottom = 128;
    SpriteQuad40CA80 projectedQuadSecond(0, 0, (5 - stripCount) * 128 * 3, 256.0f);
    TRANSFORM(projectedQuadSecond)->TranslateQuad(cameraHorizontal * 0.75 + OWNER_INT(0x68) * 0.4 - (5 - stripCount) * 128 * 3, cameraY * 0.75 + 160.0, 0);
    DRAWING->DrawProjectedQuad(3, projectedQuadSecond, &imageRect, 320.0f, 240.0f, 1500.0f, 0xFFFFFFFF);
    DRAWING->SetTextureFilter(1);
    DRAWING->DrawSprite(0, cameraHorizontal + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
}

void EffectPattern0044F850::Render() {
    int cameraX = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    DRAWING->SetDepthMode(0);
    DRAWING->DrawSprite(0, cameraX + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
    DRAWING->SetBlendMode(2);
    DRAWING->SetTextureFilter(2);
    DRAWING->DrawSpriteVariant(4, cameraX + (-190), cameraY + 60, 0xFFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.11) * 0.05 + 1.2f, 0, 0, 1);
    DRAWING->DrawSpriteVariant(4, cameraX + (167), cameraY + 134, 0xFFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.09 + 1.0) * 0.05 + 0.8f, 0, 0, 1);
    DRAWING->DrawSpriteVariant(4, cameraX + (475), cameraY + 134, 0xFFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.12 + 2.0) * 0.05 + 0.8f, 0, 0, 1);
    DRAWING->DrawSpriteVariant(4, cameraX + (833), cameraY + 60, 0xFFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.1 + 2.0) * 0.05 + 1.2f, 0, 0, 1);
    DRAWING->SetTextureFilter(1);
    DRAWING->SetDepthMode(1);
    DRAWING->SetDepthMode(8);
}

void EffectPattern0044FAF0::Render() {
    int cameraHorizontal = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    RECT imageRect;
    imageRect.left = 0; imageRect.top = 0; imageRect.right = 256; imageRect.bottom = 256;
    RectQuadF127 spriteQuadFirst(&imageRect);
    TRANSFORM(spriteQuadFirst)->RotateQuad(128.0f, 128.0f, 0, 85.0f, 0, OWNER_INT(0x68) * 0.2);
    TRANSFORM(spriteQuadFirst)->ScaleQuad(128.0f, 128.0f, 0, 3.5f, 3.5f, 1.0f);
    TRANSFORM(spriteQuadFirst)->TranslateQuad(cameraHorizontal + 192, cameraY + 290, 0);
    RectQuadF127 secondProjectedQuad(&imageRect);
    TRANSFORM(secondProjectedQuad)->RotateQuad(128.0f, 128.0f, 0, 85.0f, 0, -OWNER_INT(0x68) * 0.2);
    TRANSFORM(secondProjectedQuad)->ScaleQuad(128.0f, 128.0f, 0, 4.0f, 4.0f, 1.0f);
    TRANSFORM(secondProjectedQuad)->TranslateQuad(cameraHorizontal + 192, cameraY + 290, 0);
    RECT sourceRect;
    sourceRect.left = 0; sourceRect.top = 0; sourceRect.right = 256; sourceRect.bottom = 256;
    DRAWING->SetBlendMode(2);
    DRAWING->SetTextureFilter(2);
    DRAWING->DrawQuad(1, spriteQuadFirst, &sourceRect, 0xFFFFFFFF);
    DRAWING->DrawQuad(2, secondProjectedQuad, &sourceRect, 0xFFFFFFFF);
    DRAWING->SetTextureFilter(1);
}

void EffectPattern0044FD40::Render() {
    int cameraHorizontal = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    RECT imageRect;
    imageRect.left = 0; imageRect.top = 0; imageRect.right = 256; imageRect.bottom = 128;
    SpriteQuad40CA80 spriteQuadFirst;
    spriteQuadFirst.first.x = 0; spriteQuadFirst.first.y = 0; spriteQuadFirst.first.z = 0;
    spriteQuadFirst.fourth.x = 0; spriteQuadFirst.fourth.y = 128.0f; spriteQuadFirst.fourth.z = 0;
    spriteQuadFirst.second.x = 256.0f; spriteQuadFirst.second.y = 0; spriteQuadFirst.second.z = 0;
    spriteQuadFirst.third.x = 256.0f; spriteQuadFirst.third.y = 128.0f; spriteQuadFirst.third.z = 0;
    TRANSFORM(spriteQuadFirst)->ScaleQuad(0, 0, 0, 2.0f, (sin(OWNER_INT(0x68) / 0.017453288659453392f * 0.001) + 6.0) * 0.1, 1.0f);
    TRANSFORM(spriteQuadFirst)->TranslateQuad(cameraHorizontal + 320, cameraY + 388, 0.25f);
    SpriteQuad40CA80 projectedQuadSecond;
    projectedQuadSecond.first.x = 256.0f; projectedQuadSecond.first.y = 0; projectedQuadSecond.first.z = 0;
    projectedQuadSecond.fourth.x = 256.0f; projectedQuadSecond.fourth.y = 128.0f; projectedQuadSecond.fourth.z = 0;
    projectedQuadSecond.second.x = 0; projectedQuadSecond.second.y = 0; projectedQuadSecond.second.z = 0;
    projectedQuadSecond.third.x = 0; projectedQuadSecond.third.y = 128.0f; projectedQuadSecond.third.z = 0;
    TRANSFORM(projectedQuadSecond)->ScaleQuad(0, 0, 0, 2.0f, (sin(OWNER_INT(0x68) / 0.017453288659453392f * 0.001) + 6.0) * 0.1, 1.0f);
    TRANSFORM(projectedQuadSecond)->TranslateQuad(cameraHorizontal - 192, cameraY + 388, 0.25f);
    DRAWING->SetDepthMode(3);
    DRAWING->SetDepthMode(7);
    DRAWING->SetBlendMode(2);
    DRAWING->DrawQuad(3, spriteQuadFirst, &imageRect, 0xFFFFFFFF);
    DRAWING->DrawQuad(3, projectedQuadSecond, &imageRect, 0xFFFFFFFF);
    DRAWING->SetDepthMode(4);
}

void EffectPattern00450420::Render() {
    int cameraHorizontal = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    RECT clearRect;
    SetRect(&clearRect, 0, 0, 960, 720);
    DRAWING->SetBlendMode(0);
    FillRectangleF127(&clearRect, 0xFF21212C);
    DRAWING->DrawSprite(3, cameraHorizontal * 0.75 + 320.0, cameraY * 0.75 + 240.0, 0xFFFFFFFF, 64.0f, 64.0f, 1.0f, 0, 0);
    int atlasSliceCount = static_cast<int>((3072.0 - OWNER_INT(0x68) * 0.1) / 768.0);
    RECT imageRect;
    imageRect.left = 0; imageRect.top = 1; imageRect.right = atlasSliceCount * 128; imageRect.bottom = 128;
    DRAWING->SetTextureFilter(2);
    SpriteQuad40CA80 firstQuad(0, 1.0f, atlasSliceCount * 128 * 6, 256.0f);
    TRANSFORM(firstQuad)->TranslateQuad(cameraHorizontal * 0.75 + OWNER_INT(0x68) * 0.1, cameraY * 0.75 + 120.0, 0);
    DRAWING->DrawProjectedQuad(2, firstQuad, &imageRect, 320.0f, 240.0f, 1500.0f, 0x64FFFFFF);
    imageRect.left = 0; imageRect.top = 1; imageRect.right = (5 - atlasSliceCount) * 128; imageRect.bottom = 128;
    SpriteQuad40CA80 projectedQuadSecond(0, 1.0f, (5 - atlasSliceCount) * 128 * 6, 256.0f);
    TRANSFORM(projectedQuadSecond)->TranslateQuad(cameraHorizontal * 0.75 + OWNER_INT(0x68) * 0.1 - (5 - atlasSliceCount) * 128 * 6, cameraY * 0.75 + 120.0, 0);
    DRAWING->DrawProjectedQuad(2, projectedQuadSecond, &imageRect, 320.0f, 240.0f, 1500.0f, 0x64FFFFFF);
    DRAWING->SetTextureFilter(1);
    DRAWING->DrawSprite(1, cameraHorizontal + 320, cameraY * 0.75 + 60.0, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraHorizontal + 320, cameraY * 0.75 + 60.0, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 1);
    DRAWING->DrawSprite(0, cameraHorizontal + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 120.0f, 1.0f, 0, 0);
}

void EffectPattern00450C10::Render() {
    int cameraX = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    DRAWING->SetBlendMode(0);
    DRAWING->DrawSprite(2, cameraX * 0.6 + 384.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0, 0);
    DRAWING->DrawSprite(1, cameraX * 0.75 + 320.0, cameraY + 280, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 0);
    DRAWING->DrawSprite(4, cameraX * 0.75 + 320.0, cameraY + 280, 0xFFFFFFFF, 700.0f, 350.0f, 1.0f, 0, 1);
    DRAWING->DrawSprite(0, cameraX + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0, 0);
    DRAWING->SetBlendMode(2);
    DRAWING->SetTextureFilter(2);
    DRAWING->DrawSpriteVariant(3, cameraX + 605, cameraY + 272, 0xFFFFFFFF, 32.0f, 32.0f, sin(OWNER_INT(0x68) * 0.1 + 2.0) * 0.1 + 2.5, 0, 0, 1);
    DRAWING->DrawSprite(OWNER_INT(0x6C) / 3 + 29, cameraX + 221, cameraY - 84, 0xFFFFFFFF, 32.0f, 128.0f, 2.0f, 0, 0);
    DRAWING->DrawSprite(OWNER_INT(0x6C) / 3 + 5, cameraX + 52, cameraY + 428, 0xFFFFFFFF, 256.0f, 128.0f, 2.0f, 0, 0);
    DRAWING->SetTextureFilter(1);
    DRAWING->SetBlendMode(0);
}

void EffectPattern00450EE0::Render() {
    int cameraHorizontal = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    RECT imageRect;
    imageRect.left = 0; imageRect.top = 0; imageRect.right = 64; imageRect.bottom = 256;
    SpriteQuad40CA80 spriteQuadFirst;
    spriteQuadFirst.first.x = 0; spriteQuadFirst.first.y = 0; spriteQuadFirst.first.z = 0;
    spriteQuadFirst.fourth.x = 0; spriteQuadFirst.fourth.y = 128.0f; spriteQuadFirst.fourth.z = 0;
    spriteQuadFirst.second.x = 64.0f; spriteQuadFirst.second.y = 0; spriteQuadFirst.second.z = 0;
    spriteQuadFirst.third.x = 64.0f; spriteQuadFirst.third.y = 128.0f; spriteQuadFirst.third.z = 0;
    TRANSFORM(spriteQuadFirst)->ScaleQuad(0, 0, 0, 1.0f, (sin(OWNER_INT(0x68) / 0.017453288659453392f * 0.0005) + 12.0) * 0.1, 1.0f);
    TRANSFORM(spriteQuadFirst)->TranslateQuad(cameraHorizontal + 110, cameraY + 388, 0.25f);
    DRAWING->SetDepthMode(7);
    DRAWING->SetBlendMode(2);
    DRAWING->DrawQuad(53, spriteQuadFirst, &imageRect, 0xFFFFFFFF);
}

void EffectPattern00451440::Render() {
    int currentVertexPair;
    unsigned int greenColor;
    int cameraHorizontal = static_cast<int>(g_EffectCameraX + 160.0f);
    int cameraY = static_cast<int>(g_EffectCameraY);
    unsigned int redChannelWave = static_cast<int>(sin(OWNER_INT(0x68) / 0.017453288659453392f * 0.0003) * 128.0 + 127.0);
    greenColor = static_cast<int>(sin(OWNER_INT(0x68) / 0.017453288659453392f * 0.0002) * 64.0 + 191.0);
    unsigned int tintBlue = static_cast<int>(sin(OWNER_INT(0x68) / 0.017453288659453392f * 0.0005) * 64.0 + 191.0);
    DRAWING->SetTextureFilter(1);
    DRAWING->DrawSprite(1, 480.0f, cameraY * 0.8 + 240.0, 0xFF000000 | (redChannelWave & 255) << 16 | (greenColor & 255) << 8 | (tintBlue & 255), 512.0f, 450.0f, 2.0f, 0, 0);
    DRAWING->DrawSprite(2, 480.0f, cameraY * 0.8 + 160.0, 0xFFFFFFFF, 256.0f, 256.0f, 2.0f, 0, 0);
    DRAWING->DrawSprite(0, cameraHorizontal * 0.1 + 464.0, cameraY + 240, 0xFFFFFFFF, 512.0f, 232.0f, 1.0f, 0, 0);
    DRAWING->SetBlendMode(2);
    for (currentVertexPair = 0; currentVertexPair <= 128; currentVertexPair += 2) {
        STRIP(currentVertexPair).x = currentVertexPair * g_EffectCameraX / 128.0f + -60.0f - (currentVertexPair * 160) / 128.0f;
        STRIP(currentVertexPair + 1).x = currentVertexPair * g_EffectCameraX / 128.0f + 1020.0f + (currentVertexPair * 160) / 128.0f;
        STRIP(currentVertexPair + 1).y = cameraY + 264 + currentVertexPair * 2;
        STRIP(currentVertexPair).y = STRIP(currentVertexPair + 1).y;
        STRIP(currentVertexPair).u = 0;
        STRIP(currentVertexPair + 1).u = 0.68359375f;
        STRIP(currentVertexPair + 1).v = (currentVertexPair + 1) / 128.0f;
        STRIP(currentVertexPair).v = STRIP(currentVertexPair + 1).v;
        STRIP(currentVertexPair).z = STRIP(currentVertexPair + 1).z = 0;
        STRIP(currentVertexPair).color = STRIP(currentVertexPair + 1).color = 0xFFFFFFFF;
    }
    DRAWING->DrawTriangleStrip(3, reinterpret_cast<Graphics::ScreenVertex*>(reinterpret_cast<char*>(this) + 0xF0), 130);
    RECT imageRect;
    imageRect.left = 0; imageRect.top = 0; imageRect.right = 256; imageRect.bottom = 256;
    SpriteQuad40CA80 spriteQuadFirst;
    spriteQuadFirst.first.x = -150.0f; spriteQuadFirst.first.y = cameraY * 0.8 + -4.0; spriteQuadFirst.first.z = 0;
    spriteQuadFirst.fourth.x = cameraHorizontal * 0.5 + -150.0; spriteQuadFirst.fourth.y = (cameraY + 384) + -4.0; spriteQuadFirst.fourth.z = 0;
    spriteQuadFirst.second.x = 874.0f; spriteQuadFirst.second.y = cameraY * 0.8 + -4.0; spriteQuadFirst.second.z = 0;
    spriteQuadFirst.third.x = cameraHorizontal * 0.5 + 1024.0 + -150.0; spriteQuadFirst.third.y = (cameraY + 384) + -4.0; spriteQuadFirst.third.z = 0;
    DRAWING->DrawQuad((OWNER_INT(0x68) / 2) % 21 + 5, spriteQuadFirst, &imageRect, 0xC0FFFFFF);
    DRAWING->SetBlendMode(0);
}

#undef STRIP
#undef TRANSFORM
#undef DRAWING
#undef OWNER_INT
