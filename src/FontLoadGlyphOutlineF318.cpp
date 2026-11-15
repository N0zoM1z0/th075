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
class GlyphFontF318 {public: void LoadGlyphOutline(UINT codepoint);public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x004 - 0x000];
    HDC field004;
    void* field008;
    unsigned char unknown00C[0x014 - 0x00C];
    void* field014;
    unsigned char unknown018[0x01C - 0x018];
    UINT field01C;
    UINT field020;
    unsigned long field024;
    unsigned char unknown028[0x02C - 0x028];
    LONG field02C;
    LONG field030;
    LONG field034;
};
void GlyphFontF318::LoadGlyphOutline(UINT codepoint)
{
    if (!field004 || !field008) return;
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
    frame.glyphSize=GetGlyphOutlineA(field004,codepoint,5,&frame.metrics,0,0,&frame.transform);
    if (field014) {
        frame.oldBuffer=field014;
        free(frame.oldBuffer);
        field014=0;
    }
    frame.allocatedBuffer=::operator new(frame.glyphSize);
    field014=frame.allocatedBuffer;
    GetGlyphOutlineA(field004,codepoint,5,&frame.metrics,frame.glyphSize,field014,&frame.transform);
    field020=frame.metrics.gmBlackBoxX;
    field01C=frame.metrics.gmBlackBoxY;
    field024=(frame.glyphSize/frame.metrics.gmBlackBoxY)&~3u;
    field030=frame.metrics.gmptGlyphOrigin.x;
    field034=field02C-frame.metrics.gmptGlyphOrigin.y;
}
