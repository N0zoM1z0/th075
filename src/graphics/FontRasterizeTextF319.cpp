#include "graphics/FontSurface.hpp"
#include <windows.h>
#include <string.h>
#define CHAR_STEP ((fontHeight/2)*state.unitSize+spaceX)
#define ROW_STEP (fontHeight+spaceY)
// Exactly 48 original frame bytes: two output pointers, row/byte counters,
// 4-byte source color packets, decoded text, and actual glyph position.
// Every member holds data used by the original function. The original RGB
// stores reference only physically observed bytes inside its dword slots.
struct NativeTextStateF319 {
 unsigned short* output16;
 DWORD* output32;
 int iy;
 int unitSize;
 int offset;
 size_t length;
 DWORD redBlueStorage;
 int code;
 int ix;
 int x;
 int y;
 DWORD greenStorage;
};
typedef char AssertNativeTextState48F319[(sizeof(NativeTextStateF319)==48)?1:-1];
void FontSurface::RasterizeText(const char* text,void* pixels,int width,int height,
                                  int maxWidth,int spaceX,int spaceY,
                                  unsigned char depth,signed char lines)
{
 NativeTextStateF319 state;
 if(!font) return;
 memset(pixels,0,width*height*static_cast<unsigned int>(depth));
 reinterpret_cast<unsigned char*>(&state.redBlueStorage)[2]=red;
 reinterpret_cast<unsigned char*>(&state.greenStorage)[3]=green;
 reinterpret_cast<unsigned char*>(&state.redBlueStorage)[3]=blue;
 state.x=1;
 state.y=1;
 state.offset=0;



 state.length=strlen(text);
 SelectFont();
 if(depth==4) {
     state.output32=reinterpret_cast<DWORD*>(pixels);
     while(static_cast<int>(state.length)>state.offset) {
         state.unitSize=DecodeUnit(text+state.offset,&state.code);
         state.offset+=state.unitSize;
         if(state.code==0) break;
         if(state.code==0x5c) {
             state.unitSize=DecodeUnit(text+state.offset,&state.code);
             if(state.unitSize>1) continue;
              switch(state.code) {
               case 0x6e: {
                 state.x=1;
                 state.y+=ROW_STEP;
                 --lines;
                 if(lines<=0) {state.length=0;break;}
                 else ++state.offset;
               break;
               }
               case 99: {
                 reinterpret_cast<unsigned char*>(&state.redBlueStorage)[2]=static_cast<unsigned char>(DecodeHexDigit(text[state.offset+1])*16+DecodeHexDigit(text[state.offset+2]));
                 reinterpret_cast<unsigned char*>(&state.greenStorage)[3]=static_cast<unsigned char>(DecodeHexDigit(text[state.offset+3])*16+DecodeHexDigit(text[state.offset+4]));
                 reinterpret_cast<unsigned char*>(&state.redBlueStorage)[3]=static_cast<unsigned char>(DecodeHexDigit(text[state.offset+5])*16+DecodeHexDigit(text[state.offset+6]));
                 state.offset+=7;
               break;
               }
               case 0x65: {
                 reinterpret_cast<unsigned char*>(&state.redBlueStorage)[2]=red;
                 reinterpret_cast<unsigned char*>(&state.greenStorage)[3]=green;
                 reinterpret_cast<unsigned char*>(&state.redBlueStorage)[3]=blue;
                 state.offset+=1;
               break;
               }
               default: continue;
              }
         } else if (state.code==0x20) {
             if(maxWidth-state.x<CHAR_STEP) {
                 state.x=1;
                 if(height-state.y<ROW_STEP) {state.length=0; break;}
                 state.y+=ROW_STEP;
                 --lines;
                 if(lines<=0) {state.length=0; break;}
             }
             state.x+=CHAR_STEP;
         } else if(state.code==0x8140) {
             if(maxWidth-state.x<CHAR_STEP) {
                 state.x=1;
                 if(height-state.y<ROW_STEP) {state.length=0; break;}
                 state.y+=ROW_STEP;
                 --lines;
                 if(lines<=0) {state.length=0; break;}
             }
             state.x+=CHAR_STEP;
         } else {
             LoadGlyphOutline(state.code);
             if(maxWidth-state.x<CHAR_STEP) {
                 state.x=1;
                 if(height-state.y<ROW_STEP) {state.length=0; break;}
                 state.y+=ROW_STEP;
                 --lines;
                 if(lines<=0) {state.length=0; break;}
             }
             for(state.ix=0;state.ix<glyphWidth;++state.ix) {
                 for(state.iy=0;state.iy<glyphHeight;++state.iy) {
                     if(glyphBitmap[state.iy*glyphPitch+state.ix]!=0) {
                         state.output32[(state.x+glyphX+state.ix+(state.y+glyphY+state.iy)*width)]=(static_cast<unsigned int>(glyphBitmap[state.iy*glyphPitch+state.ix])<<1)*0x07000000 | 0x03000000 |
                           (255-static_cast<unsigned char>((glyphY+state.iy)*(255-static_cast<int>(reinterpret_cast<unsigned char*>(&state.redBlueStorage)[2]))/fontHeight))*0x10000 |
                           (255-static_cast<unsigned char>((glyphY+state.iy)*(255-static_cast<int>(reinterpret_cast<unsigned char*>(&state.greenStorage)[3]))/fontHeight))*0x100 |
                           (255-static_cast<unsigned char>((glyphY+state.iy)*(255-static_cast<int>(reinterpret_cast<unsigned char*>(&state.redBlueStorage)[3]))/fontHeight));

                     }
                 }
             }
             state.x+=CHAR_STEP;
         }
     }
 } else if (depth==2) {
     state.output16=reinterpret_cast<unsigned short*>(pixels);
     while(static_cast<int>(state.length)>state.offset) {
         state.unitSize=DecodeUnit(text+state.offset,&state.code);
         state.offset+=state.unitSize;
         if(state.code==0x20) {
             state.x+=CHAR_STEP;
         } else if(state.code==0x8140) {
             state.x+=CHAR_STEP;
         } else {
             LoadGlyphOutline(state.code);
             if(width-state.x<CHAR_STEP) {
                 state.x=0;
                 if(height-state.y<ROW_STEP) {state.length=0; break;}
                 state.y+=ROW_STEP;
             }
             for(state.ix=0;state.ix<glyphWidth;++state.ix) {
                 for(state.iy=0;state.iy<glyphHeight;++state.iy) {
                     if(glyphBitmap[state.iy*glyphPitch+state.ix]!=0) {
                         state.output16[state.x+glyphX+state.ix+(state.y+glyphY+state.iy)*width]=
                           static_cast<unsigned short>((static_cast<unsigned short>(glyphBitmap[state.iy*glyphPitch+state.ix])*2-1)*0x421 |0x8000);
                     }
                 }
             }
             state.x+=CHAR_STEP;
         }
     }
 }
 ReleaseRasterResources();
}
#undef ROW_STEP
#undef CHAR_STEP
