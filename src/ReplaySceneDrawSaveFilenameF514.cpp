#include "NameEntryScenes.hpp"
#include "SpriteQuad.hpp"
#include <cstring>

void SharedNameEntryScene::DrawSaveFilename(float x, float y, DWORD color, const char* filename) {
    // The native helper constructs this complete value before its glyph policy.
    SpriteQuad40CA80 filenameQuad(x, y, x + 19.0f, y + 20.0f);
    char expectedPrefix[] = "replay\\replay";
    signed char filenameCodes[8];
    if (std::memcmp(expectedPrefix, filename, 13) == 0) {
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
