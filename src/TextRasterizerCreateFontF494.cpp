#include <windows.h>
// Windowss CreateFont macro must not rename this native game method.
#undef CreateFont
// Whole native original Win32 CreateFontA pass-through. Only observed
// owner field offsets +8, +0x10, +0x28..+0x2A are modeled; other
// private Rasterizer fields remain untyped.
class TextRasterizerF494 {
 unsigned char untypedOwnerPrefix[8];
 HFONT font;
 unsigned char untypedGapAt0C[4];
 int originalHeight;
 unsigned char untypedOwnerRegion[0x14];
 unsigned char fontOptionA,fontOptionB,fontOptionC;
public:
 void CreateFont(const char* faceName,int height,unsigned char optA,unsigned char optB,unsigned char optC);
};
void TextRasterizerF494::CreateFont(const char* faceName,int height,unsigned char optA,unsigned char optB,unsigned char optC){
 originalHeight=height;
 fontOptionA=optA;
 fontOptionB=optB;
 fontOptionC=optC;
 font=::CreateFontA(height,0,0,0,400,0,0,0,0x80,4,0,2,0x31,faceName);
}
