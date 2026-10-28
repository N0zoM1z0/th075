#include <windows.h>
#include <string.h>
// Entire original R043 replay filename sprite/glyph draw, full 303 CODE.
// Exact native private stack: original 16-byte character prefix+padding
// and 132-byte borrowed quad are one meaningful prefix/quad aggregate;
// the independently live 8-byte glyph array is a SEPARATE C++ local.
// This naturally retains the VC7.1 /GS cookie and original true stack
// addresses: prefix EBP-0xA8, quad EBP-0x98, glyph EBP-0x0C.
// The original prefix at 00657F9C contains 14 bytes and is read as
// three actual DWORDs and one original WORD; the final aggregate 2
// bytes are ordinary compiler alignment, not invented data fields.
// The quad is the separately accepted 132-byte native source packet.
// Entire observed replay filename glyph range and actual 8-byte glyph styles.
// SpriteQuad is the independently accepted physical 132-byte game packet.
extern const float g_ReplayWidthAt00657F78;
extern const float g_ReplayHeightAt0065786C;
struct ReplayGlyphStyleF425 {
    unsigned char b0,b1,b2,b3,b4,b5,b6,b7;
};
typedef char CheckStyle8F425[(sizeof(ReplayGlyphStyleF425)==8)?1:-1];
class ReplayQuadF510 { unsigned int physicalPacket[33]; public: void ConstructNative(float,float,float,float); };
struct OriginalReplayPrefixF511 {unsigned int part0,part1,part2;unsigned short part3;};
typedef char VerifyPrefixF511[(sizeof(OriginalReplayPrefixF511)==16)?1:-1];
extern const OriginalReplayPrefixF511 g_OriginalReplayPrefixAt00657F9C;
struct ReplayFrameF511 {OriginalReplayPrefixF511 prefix;ReplayQuadF510 quad;};
typedef char VerifyFrameF511[(sizeof(ReplayFrameF511)==148)?1:-1];
class ReplayFilenameF424 {public:
    void DrawSaveFilename(float x,float y,unsigned int tint,const signed char* filename);
    void DrawCharacters(float x,float y,unsigned int tint,const unsigned char* characters);
};
void ReplayFilenameF424::DrawSaveFilename(float x,float y,unsigned int tint,const signed char* filename) {
  ReplayFrameF511 frame;
  unsigned char glyphs[8];
  frame.quad.ConstructNative(x,y,x+g_ReplayWidthAt00657F78,y+g_ReplayHeightAt0065786C);
  frame.prefix.part0=g_OriginalReplayPrefixAt00657F9C.part0;
  frame.prefix.part1=g_OriginalReplayPrefixAt00657F9C.part1;
  frame.prefix.part2=g_OriginalReplayPrefixAt00657F9C.part2;
  frame.prefix.part3=g_OriginalReplayPrefixAt00657F9C.part3;
  if(memcmp(&frame.prefix,filename,13)==0) {
    glyphs[0]=13;glyphs[1]=40;glyphs[2]=71;
    glyphs[3]=filename[13]+4;glyphs[4]=filename[14]+4;glyphs[5]=filename[15]+4;
    glyphs[6]=100;glyphs[7]=100;
    DrawCharacters(x,y,tint,glyphs);
  } else {
    glyphs[0]=20;glyphs[1]=44;glyphs[2]=30;glyphs[3]=43;
    glyphs[4]=100;glyphs[5]=100;glyphs[6]=100;glyphs[7]=100;
    DrawCharacters(x,y,tint,glyphs);
  }
}
