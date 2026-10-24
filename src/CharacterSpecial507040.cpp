#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"

// Private owners are pointer-only; their complete layouts remain unknown.
class CharacterSpecial507040 { public: void Render(signed char stage); };
class QuadDrawingF121 { public: void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD); };
class CharacterInput5076F0 {
public:
    void PollCommands();
    signed char MatchInputPattern(const char*, signed char, signed char);
};

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))
#define DRAWING reinterpret_cast<TimelineDrawing438D00*>(FIELD(void*, 4))
#define QUAD_DRAWING reinterpret_cast<QuadDrawingF121*>(FIELD(void*, 0x700))
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))

void CharacterSpecial507040::Render(signed char stage)
{
    SpriteQuad40CA80 quadValue;
    RECT region;
    switch (stage) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 7:
        DRAWING->SetTextureFilter(2);
        SetRect(&region, 0, 0, 1024, 32);
        TRANSFORM(quadValue)->BuildQuad(FLOAT(0xF14), FLOAT(0xF3C), FLOAT(0xF14) + 1024.0f, FLOAT(0xF3C) + 32.0f);
        QUAD_DRAWING->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFDC), 255, 255, 255));
        SetRect(&region, 0, 0, 1024, 32);
        TRANSFORM(quadValue)->BuildQuad(FLOAT(0xF18), FLOAT(0xF40), FLOAT(0xF18) + 1024.0f, FLOAT(0xF40) + 32.0f);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFDD), 255, 255, 255));
        DRAWING->SetTextureFilter(1);
        SetRect(&region, 0, 0, 640, 128);
        TRANSFORM(quadValue)->BuildQuad(FLOAT(0xF1C), FLOAT(0xF44), FLOAT(0xF1C) + 640.0f, FLOAT(0xF44) + 128.0f);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFDE), 255, 255, 255));
        SetRect(&region, 0, 0, 304, 80);
        TRANSFORM(quadValue)->BuildQuad(FLOAT(0xF20), FLOAT(0xF48), FLOAT(0xF20) + 304.0f, FLOAT(0xF48) + 80.0f);
        QUAD_DRAWING->DrawQuad(3, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFDF), 255, 255, 255));
        if (FIELD(signed char, 0x6F8) == 1 && FIELD(unsigned char, 0xFDF) < 255 && FIELD(short, 0xEFE) == 0) {
            if (FIELD(unsigned char, 0xFDF) < 250) FIELD(unsigned char, 0xFDF) += 5;
            else FIELD(unsigned char, 0xFDF) = 255;
        }
        if (FIELD(unsigned char, 0xFDF) == 255) ++FIELD(short, 0xEFE);
        if (FIELD(short, 0xEFE) > 180) {
            if (FIELD(unsigned char, 0xFDF) > 0) FIELD(unsigned char, 0xFDF) -= 5;
            // Native code retains this unsigned clamp after the subtraction.
            // Its condition cannot succeed; preserve the actual emitted check.
            if (FIELD(unsigned char, 0xFDF) < 0) FIELD(unsigned char, 0xFDF) = 0;
        }
        break;
    case 8: case 9:
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFDC), 255, 255, 255));
        break;
    case 10:
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFDC), 255, 255, 255));
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFDD), 255, 255, 255));
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFDE), 255, 255, 255));
        break;
    }
}

#undef TRANSFORM
#undef QUAD_DRAWING
#undef DRAWING
#undef FLOAT
#undef FIELD

#define COMMAND (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x511))

void CharacterInput5076F0::PollCommands() {
    COMMAND = 0;
    if (MatchInputPattern("236236D", 7, 30))
        COMMAND = 113;
    else if (MatchInputPattern("623B", 4, 15))
        COMMAND = 31;
    else if (MatchInputPattern("421C", 4, 15))
        COMMAND = 42;
    else if (MatchInputPattern("421B", 4, 15))
        COMMAND = 41;
    else if (MatchInputPattern("421A", 4, 15))
        COMMAND = 40;
    else if (MatchInputPattern("623A", 4, 15))
        COMMAND = 30;
    else if (MatchInputPattern("214B", 4, 15))
        COMMAND = 21;
    else if (MatchInputPattern("214A", 4, 15))
        COMMAND = 20;
    else if (MatchInputPattern("236D", 4, 15))
        COMMAND = 13;
    else if (MatchInputPattern("236C", 4, 15))
        COMMAND = 12;
    else if (MatchInputPattern("236B", 4, 15))
        COMMAND = 11;
    else if (MatchInputPattern("236A", 4, 15))
        COMMAND = 10;
    else if (MatchInputPattern("2N2D", 4, 15))
        COMMAND = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        COMMAND = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        COMMAND = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        COMMAND = 100;
    else if (MatchInputPattern("N29", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N39", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N19", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N27", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N37", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N17", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N28", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N38", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N18", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("NRNR", 4, 15))
        COMMAND = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        COMMAND = 2;
}

#undef COMMAND
