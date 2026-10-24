#include "BattleAtlasNumber446B90.hpp"
#include <cstring>

// Private receiver views only; never instantiate or embed these owners.
class ReplayTextF125 {
public:
    void DrawMetadataNumber(float x, float y, DWORD color, int value, int digits);
    void DrawNameGlyphs(float x, float y, DWORD color, const signed char* codes);
    void DrawFilename(float x, float y, DWORD color, const char* filename);
};
class ReplayQuadDrawingF125 { public: void DrawQuad(int, const AtlasQuad446B90&, const RECT*, DWORD); };
#define DRAWING reinterpret_cast<ReplayQuadDrawingF125*>((*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 8)))
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))

void ReplayTextF125::DrawMetadataNumber(float x, float y, DWORD color, int value, int digits) {
    int digitValue = value;
    AtlasQuad446B90 mainQuad(x - 19.0f, y, x, y + 20.0f);
    RECT region;
    if (digits > 0) {
        while (digits > 0) {
            SetRect(&region, (digitValue % 10) * 19, 40, (digitValue % 10) * 19 + 19, 60);
            DRAWING->DrawQuad(2, mainQuad, &region, color);
            digitValue /= 10;
            TRANSFORM(mainQuad)->TranslateQuad(-11.0f, 0, 0);
            --digits;
        }
    } else {
        while (digitValue >= 0) {
            SetRect(&region, (digitValue % 10) * 19, 40, (digitValue % 10) * 19 + 19, 60);
            DRAWING->DrawQuad(2, mainQuad, &region, color);
            if (digitValue < 10) digitValue = -1;
            else digitValue /= 10;
            TRANSFORM(mainQuad)->TranslateQuad(-11.0f, 0, 0);
        }
    }
}

void ReplayTextF125::DrawNameGlyphs(float x, float y, DWORD color, const signed char* codes) {
    AtlasQuad446B90 quadValue(x, y, x + 19.0f, y + 20.0f);
    RECT region;
    int glyphIndex;
    for (glyphIndex = 0; glyphIndex < 8; glyphIndex++) {
        SetRect(&region, (codes[glyphIndex] % 26) * 19, (codes[glyphIndex] / 26) * 20,
                (codes[glyphIndex] % 26) * 19 + 19, (codes[glyphIndex] / 26) * 20 + 20);
        DRAWING->DrawQuad(2, quadValue, &region, color);
        TRANSFORM(quadValue)->TranslateQuad(14.0f, 0, 0);
    }
}

void ReplayTextF125::DrawFilename(float x, float y, DWORD color, const char* filename) {
    // The native helper constructs this complete value before its glyph policy.
    AtlasQuad446B90 filenameQuad(x, y, x + 19.0f, y + 20.0f);
    char expectedPrefix[] = "replay\\replay";
    signed char filenameCodes[8];
    if (std::memcmp(expectedPrefix, filename, 13) == 0 && filename[16] == '.') {
        filenameCodes[0] = 13;
        filenameCodes[1] = 40;
        filenameCodes[2] = 71;
        filenameCodes[3] = filename[13] + 4;
        filenameCodes[4] = filename[14] + 4;
        filenameCodes[5] = filename[15] + 4;
        filenameCodes[6] = 100;
        filenameCodes[7] = 100;
        DrawNameGlyphs(x, y, color, filenameCodes);
    } else {
        filenameCodes[0] = 20;
        filenameCodes[1] = 44;
        filenameCodes[2] = 30;
        filenameCodes[3] = 43;
        filenameCodes[4] = 100;
        filenameCodes[5] = 100;
        filenameCodes[6] = 100;
        filenameCodes[7] = 100;
        DrawNameGlyphs(x, y, color, filenameCodes);
    }
}

#undef TRANSFORM
#undef DRAWING
