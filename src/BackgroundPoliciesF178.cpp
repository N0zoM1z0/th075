#include "BackgroundStages.hpp"
#include "CameraUpdate4126C0.hpp"
#include "SpriteTransform.hpp"

void Background00aF376::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void Background00bF376::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG00cF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG00xF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG00xF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG00yF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG00yF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG00zF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG00zF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG01aF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG01bF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG01xF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG01xF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG01yF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG01yF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG02aF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG02bF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG02cF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG02xF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG02xF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG02yF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG02yF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG02zF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG02zF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG03aF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG03bF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG03xF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG03xF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG03yF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG03yF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG04aF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 0.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG04bF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 0.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG04xF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG04xF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG04yF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG04yF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG05aF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG05bF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG05xF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG05xF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG05yF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG05yF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG06aF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 0.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x40FFFFFF;
}

void BackgroundBG06xF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG06xF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG07aF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG07xF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG07xF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG08aF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG08xF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG08xF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}

void BackgroundBG09aF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 0.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x40FFFFFF;
}

void BackgroundBG09xF377::Render()
{
    int x = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    textureManager.DrawSprite(
        0, float(x - 30), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
    textureManager.DrawSprite(
        1, float(x + 670), float(y + 240), 0xFFFFFFFF, 350.0f, 620.0f, 1.0f, 0.0f, 0);
}

void BackgroundBG09xF377::ApplyTransform(SpriteQuad40CA80* destination,
    DWORD* color, SpriteQuad40CA80* source)
{
    reinterpret_cast<SpriteTransform*>(source)->ScaleQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.3f, 1.0f);
    reinterpret_cast<SpriteTransform*>(source)->RotateQuad(0.0f, 0.0f, 0.0f, 160.0f, 0.0f, 0.0f);
    *destination = *source;
    *color = 0x80000000;
}
