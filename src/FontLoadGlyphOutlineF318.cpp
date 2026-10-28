#include <windows.h>
#include <stdlib.h>
#include <new>
// A borrowed physical view of precisely the existing 64 bytes of native
// GLYPHMETRICS, identity MAT2, returned glyph size, and two real buffers.
// It is not a declaration of the original owner's complete private class.
struct GlyphFrameF318 {
    void* allocatedBuffer;
    void* oldBuffer;
    GLYPHMETRICS metrics;
    DWORD glyphSize;
    MAT2 transform;
    DWORD source0,source1,source2,source3;
};
typedef char AssertGlyphFrameF318[(sizeof(GlyphFrameF318)==64)?1:-1];
class GlyphFontF318 {public: void LoadGlyphOutline(UINT codepoint);};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void GlyphFontF318::LoadGlyphOutline(UINT codepoint)
{
    if (!FIELD(HDC,4) || !FIELD(void*,8)) return;
    GlyphFrameF318 frame;
    memset(&frame.metrics,0,sizeof(frame.metrics));
    frame.source2=0x00010000;
    frame.source0=0;
    frame.source3=0;
    frame.source1=0x00010000;
    reinterpret_cast<DWORD*>(&frame.transform)[0]=frame.source2;
    reinterpret_cast<DWORD*>(&frame.transform)[1]=frame.source0;
    reinterpret_cast<DWORD*>(&frame.transform)[2]=frame.source3;
    reinterpret_cast<DWORD*>(&frame.transform)[3]=frame.source1;
    frame.glyphSize=GetGlyphOutlineA(FIELD(HDC,4),codepoint,5,&frame.metrics,0,0,&frame.transform);
    if (FIELD(void*,0x14)) {
        frame.oldBuffer=FIELD(void*,0x14);
        free(frame.oldBuffer);
        FIELD(void*,0x14)=0;
    }
    frame.allocatedBuffer=::operator new(frame.glyphSize);
    FIELD(void*,0x14)=frame.allocatedBuffer;
    GetGlyphOutlineA(FIELD(HDC,4),codepoint,5,&frame.metrics,frame.glyphSize,FIELD(void*,0x14),&frame.transform);
    FIELD(UINT,0x20)=frame.metrics.gmBlackBoxX;
    FIELD(UINT,0x1c)=frame.metrics.gmBlackBoxY;
    FIELD(DWORD,0x24)=(frame.glyphSize/frame.metrics.gmBlackBoxY)&~3u;
    FIELD(LONG,0x30)=frame.metrics.gmptGlyphOrigin.x;
    FIELD(LONG,0x34)=FIELD(LONG,0x2c)-frame.metrics.gmptGlyphOrigin.y;
}
#undef FIELD
