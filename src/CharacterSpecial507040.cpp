#include "TextureManagerF198.hpp"
#include "PatchouliFighter.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"

// Private owners are pointer-only; their complete layouts remain unknown.
class QuadDrawingF121 { public: void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD); };

#define DRAWING reinterpret_cast<TextureManagerF198*>(drawing)
#define QUAD_DRAWING reinterpret_cast<QuadDrawingF121*>(stageDrawing)
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))

void PatchouliFighter::RenderStage(signed char stage)
{
    SpriteQuad40CA80 quadValue;
    RECT region;
    switch (stage) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 7:
        reinterpret_cast<TextureManagerF198*>(DRAWING)->SetTextureFilter(2);
        SetRect(&region, 0, 0, 1024, 32);
        TRANSFORM(quadValue)->BuildQuad(fieldF14, fieldF3C, fieldF14 + 1024.0f, fieldF3C + 32.0f);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(fieldFDC, 255, 255, 255));
        SetRect(&region, 0, 0, 1024, 32);
        TRANSFORM(quadValue)->BuildQuad(fieldF18, fieldF40, fieldF18 + 1024.0f, fieldF40 + 32.0f);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(fieldFDD, 255, 255, 255));
        reinterpret_cast<TextureManagerF198*>(DRAWING)->SetTextureFilter(1);
        SetRect(&region, 0, 0, 640, 128);
        TRANSFORM(quadValue)->BuildQuad(fieldF1C, fieldF44, fieldF1C + 640.0f, fieldF44 + 128.0f);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(fieldFDE, 255, 255, 255));
        SetRect(&region, 0, 0, 304, 80);
        TRANSFORM(quadValue)->BuildQuad(fieldF20, fieldF48, fieldF20 + 304.0f, fieldF48 + 80.0f);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(3, quadValue, &region, D3DCOLOR_ARGB(fieldFDF, 255, 255, 255));
        if ((field6F8) == 1 && (fieldFDF) < 255 && (fieldEFE) == 0) {
            if ((fieldFDF) < 250) fieldFDF += 5;
            else fieldFDF = 255;
        }
        if ((fieldFDF) == 255) ++fieldEFE;
        if ((fieldEFE) > 180) {
            if ((fieldFDF) > 0) fieldFDF -= 5;
            // Native code retains this unsigned clamp after the subtraction.
            // Its condition cannot succeed; preserve the actual emitted check.
            if ((fieldFDF) < 0) fieldFDF = 0;
        }
        break;
    case 8: case 9:
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(fieldFDC, 255, 255, 255));
        break;
    case 10:
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(fieldFDC, 255, 255, 255));
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(fieldFDD, 255, 255, 255));
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(fieldFDE, 255, 255, 255));
        break;
    }
}

#undef TRANSFORM
#undef QUAD_DRAWING
#undef DRAWING


void PatchouliFighter::PollCommands() {
    aiCommand = 0;
    if (MatchInputPattern("236236D", 7, 30))
        aiCommand = 113;
    else if (MatchInputPattern("623B", 4, 15))
        aiCommand = 31;
    else if (MatchInputPattern("421C", 4, 15))
        aiCommand = 42;
    else if (MatchInputPattern("421B", 4, 15))
        aiCommand = 41;
    else if (MatchInputPattern("421A", 4, 15))
        aiCommand = 40;
    else if (MatchInputPattern("623A", 4, 15))
        aiCommand = 30;
    else if (MatchInputPattern("214B", 4, 15))
        aiCommand = 21;
    else if (MatchInputPattern("214A", 4, 15))
        aiCommand = 20;
    else if (MatchInputPattern("236D", 4, 15))
        aiCommand = 13;
    else if (MatchInputPattern("236C", 4, 15))
        aiCommand = 12;
    else if (MatchInputPattern("236B", 4, 15))
        aiCommand = 11;
    else if (MatchInputPattern("236A", 4, 15))
        aiCommand = 10;
    else if (MatchInputPattern("2N2D", 4, 15))
        aiCommand = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        aiCommand = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        aiCommand = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        aiCommand = 100;
    else if (MatchInputPattern("N29", 3, 10))
        aiCommand = 5;
    else if (MatchInputPattern("N39", 3, 10))
        aiCommand = 5;
    else if (MatchInputPattern("N19", 3, 10))
        aiCommand = 5;
    else if (MatchInputPattern("N27", 3, 10))
        aiCommand = 4;
    else if (MatchInputPattern("N37", 3, 10))
        aiCommand = 4;
    else if (MatchInputPattern("N17", 3, 10))
        aiCommand = 4;
    else if (MatchInputPattern("N28", 3, 10))
        aiCommand = 3;
    else if (MatchInputPattern("N38", 3, 10))
        aiCommand = 3;
    else if (MatchInputPattern("N18", 3, 10))
        aiCommand = 3;
    else if (MatchInputPattern("NRNR", 4, 15))
        aiCommand = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        aiCommand = 2;
}
