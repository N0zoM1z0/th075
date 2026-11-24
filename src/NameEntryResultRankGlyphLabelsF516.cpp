#include "NameEntryScenes.hpp"
#include "GeometryConstants.hpp"
#include <windows.h>
#include "ResultListScene.hpp"
#include "SpriteQuad.hpp"

void PlayerNameEntryScene::DrawRankLabel(float x,float y,DWORD tint,signed char rank) {
    SpriteQuad40CA80 rankQuad(x, y, x + GeometryConstants::Nineteen, y + GeometryConstants::Twenty);
    signed char glyphCodes[8];
    glyphCodes[0]=13;glyphCodes[1]=40;glyphCodes[2]=71;
    glyphCodes[3]=rank/10+52;glyphCodes[4]=rank%10+52;
    glyphCodes[5]=100;glyphCodes[6]=100;glyphCodes[7]=100;
    DrawNameGlyphs(x,y,tint,glyphCodes);
}
void ResultListScene::DrawRankLabel(float x,float y,unsigned int tint,signed char rank) {
    SpriteQuad40CA80 rankQuad(x, y, x + GeometryConstants::Nineteen, y + GeometryConstants::Twenty);
    signed char glyphCodes[8];
    glyphCodes[0]=13;glyphCodes[1]=40;glyphCodes[2]=71;
    glyphCodes[3]=rank/10+52;glyphCodes[4]=rank%10+52;
    glyphCodes[5]=100;glyphCodes[6]=100;glyphCodes[7]=100;
    DrawNameGlyphs(x,y,tint,glyphCodes);
}
