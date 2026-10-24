#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"

// Source policies name independently observed field offsets only. Original
// identities and complete owner layouts remain unknown; never construct owners.
struct StageRender471E00Policy { enum { xBase = 0xF2C, timerOffset = 0xEFE }; };
struct StageRender498540Policy { enum { xBase = 0xF34, timerOffset = 0xEFE }; };
struct StageRender4C6050Policy { enum { xBase = 0xF18, timerOffset = 0xEFE }; };
struct StageRender4E7350Policy { enum { xBase = 0xF18, timerOffset = 0xEFE }; };
struct StageRender531570Policy { enum { xBase = 0xF18, timerOffset = 0xEFE }; };
struct StageRender5568F0Policy { enum { xBase = 0xF10, timerOffset = 0xEFE }; };
struct StageRender578B70Policy { enum { xBase = 0xF14, timerOffset = 0xEFE }; };
struct StageRender59C6F0Policy { enum { xBase = 0xF34, timerOffset = 0xEFE }; };
struct StageRender5C52D0Policy { enum { xBase = 0xF2C, timerOffset = 0xF2A }; };

template<class Policy> class CharacterStageRendererF122 { public: void Render(signed char stage); };
class QuadDrawingF122 { public: void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD); };

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))
#define DRAWING reinterpret_cast<TimelineDrawing438D00*>(FIELD(void*, 4))
#define QUAD_DRAWING reinterpret_cast<QuadDrawingF122*>(FIELD(void*, 0x700))
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))

template<class Policy>
void CharacterStageRendererF122<Policy>::Render(signed char stage)
{
    SpriteQuad40CA80 quadValue;
    RECT region;
    switch (stage) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 7:
        DRAWING->SetTextureFilter(2);
        SetRect(&region, 0, 0, 1024, 32);
        TRANSFORM(quadValue)->BuildQuad(FLOAT(Policy::xBase + 0), FLOAT(Policy::xBase + 40), FLOAT(Policy::xBase + 0) + 1024.0f, FLOAT(Policy::xBase + 40) + 32.0f);
        QUAD_DRAWING->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, Policy::xBase + 200), 255, 255, 255));
        SetRect(&region, 0, 0, 1024, 32);
        TRANSFORM(quadValue)->BuildQuad(FLOAT(Policy::xBase + 4), FLOAT(Policy::xBase + 44), FLOAT(Policy::xBase + 4) + 1024.0f, FLOAT(Policy::xBase + 44) + 32.0f);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, Policy::xBase + 201), 255, 255, 255));
        DRAWING->SetTextureFilter(1);
        SetRect(&region, 0, 0, 640, 128);
        TRANSFORM(quadValue)->BuildQuad(FLOAT(Policy::xBase + 8), FLOAT(Policy::xBase + 48), FLOAT(Policy::xBase + 8) + 640.0f, FLOAT(Policy::xBase + 48) + 128.0f);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, Policy::xBase + 202), 255, 255, 255));
        SetRect(&region, 0, 0, 304, 80);
        TRANSFORM(quadValue)->BuildQuad(FLOAT(Policy::xBase + 12), FLOAT(Policy::xBase + 52), FLOAT(Policy::xBase + 12) + 304.0f, FLOAT(Policy::xBase + 52) + 80.0f);
        QUAD_DRAWING->DrawQuad(3, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, Policy::xBase + 203), 255, 255, 255));
        if (FIELD(signed char, 0x6F8) == 1 && FIELD(unsigned char, Policy::xBase + 203) < 255 && FIELD(short, Policy::timerOffset) == 0) {
            if (FIELD(unsigned char, Policy::xBase + 203) < 250) FIELD(unsigned char, Policy::xBase + 203) += 5;
            else FIELD(unsigned char, Policy::xBase + 203) = 255;
        }
        if (FIELD(unsigned char, Policy::xBase + 203) == 255) ++FIELD(short, Policy::timerOffset);
        if (FIELD(short, Policy::timerOffset) > 180) {
            if (FIELD(unsigned char, Policy::xBase + 203) > 0) FIELD(unsigned char, Policy::xBase + 203) -= 5;
            // Native code retains this unsigned clamp after the subtraction.
            // Its condition cannot succeed; preserve the actual emitted check.
            if (FIELD(unsigned char, Policy::xBase + 203) < 0) FIELD(unsigned char, Policy::xBase + 203) = 0;
        }
        break;
    case 8: case 9:
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, Policy::xBase + 200), 255, 255, 255));
        break;
    case 10:
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, Policy::xBase + 200), 255, 255, 255));
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, Policy::xBase + 201), 255, 255, 255));
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, Policy::xBase + 202), 255, 255, 255));
        break;
    }
}


template class CharacterStageRendererF122<StageRender471E00Policy>;
template class CharacterStageRendererF122<StageRender498540Policy>;
template class CharacterStageRendererF122<StageRender4C6050Policy>;
template class CharacterStageRendererF122<StageRender4E7350Policy>;
template class CharacterStageRendererF122<StageRender531570Policy>;
template class CharacterStageRendererF122<StageRender5568F0Policy>;
template class CharacterStageRendererF122<StageRender578B70Policy>;
template class CharacterStageRendererF122<StageRender59C6F0Policy>;
template class CharacterStageRendererF122<StageRender5C52D0Policy>;

#undef TRANSFORM
#undef QUAD_DRAWING
#undef DRAWING
#undef FLOAT
#undef FIELD
