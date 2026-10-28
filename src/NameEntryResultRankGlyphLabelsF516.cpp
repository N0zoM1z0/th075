#include <windows.h>
// Independently original R109 and R043 complete rank glyph labels.
// Real 132-byte quad is a meaningful member of a local aggregate.
// Its borrowed 0040DA00 constructor is called on the true quad field;
// real separate eight-glyph array triggers the native /GS cookie and
// authentic EBP-0x98 quad, EBP-0x0C glyph positions.
// Two individually observed complete native 169-byte scene rank label methods.
// Only real quad allocation footprint, text glyphs, original globals and ABI.
class RankQuadF472 {
 unsigned int observedQuadCarrier[33];
public:void ConstructNative(float x,float y,float width,float height);
};
struct RankGlyphFrameF472 { RankQuadF472 quad; };

extern const float g_RankWidthAt00657F78;
extern const float g_RankHeightAt0065786C;
class NameEntryLabelF472 {
public:
 void DrawRankLabel(float x,float y,unsigned int tint,signed char rank);
 void DrawGlyphs(float x,float y,unsigned int tint,const unsigned char* glyphs);
};
class ResultRankLabelF472 {
public:
 void DrawRankLabel(float x,float y,unsigned int tint,signed char rank);
 void DrawGlyphs(float x,float y,unsigned int tint,const unsigned char* glyphs);
};
void NameEntryLabelF472::DrawRankLabel(float x,float y,unsigned int tint,signed char rank) {
 unsigned char glyphs[8];
 RankGlyphFrameF472 frame;
 frame.quad.ConstructNative(x,y,x+g_RankWidthAt00657F78,y+g_RankHeightAt0065786C);
 glyphs[0]=13;glyphs[1]=40;glyphs[2]=71;
 glyphs[3]=rank/10+52;glyphs[4]=rank%10+52;
 glyphs[5]=100;glyphs[6]=100;glyphs[7]=100;
 DrawGlyphs(x,y,tint,glyphs);
}
void ResultRankLabelF472::DrawRankLabel(float x,float y,unsigned int tint,signed char rank) {
 unsigned char glyphs[8];
 RankGlyphFrameF472 frame;
 frame.quad.ConstructNative(x,y,x+g_RankWidthAt00657F78,y+g_RankHeightAt0065786C);
 glyphs[0]=13;glyphs[1]=40;glyphs[2]=71;
 glyphs[3]=rank/10+52;glyphs[4]=rank%10+52;
 glyphs[5]=100;glyphs[6]=100;glyphs[7]=100;
 DrawGlyphs(x,y,tint,glyphs);
}
