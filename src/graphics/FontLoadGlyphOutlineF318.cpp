#include "graphics/FontSurface.hpp"
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
void FontSurface::LoadGlyphOutline(UINT codepoint)
{
    if (!deviceContext || !font) return;
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
    frame.glyphSize=GetGlyphOutlineA(deviceContext,codepoint,5,&frame.metrics,0,0,&frame.transform);
    if (glyphBitmap) {
        frame.oldBuffer=glyphBitmap;
        free(frame.oldBuffer);
        glyphBitmap=0;
    }
    frame.allocatedBuffer=::operator new(frame.glyphSize);
    glyphBitmap=static_cast<BYTE*>(frame.allocatedBuffer);
    GetGlyphOutlineA(deviceContext,codepoint,5,&frame.metrics,frame.glyphSize,glyphBitmap,&frame.transform);
    glyphWidth=frame.metrics.gmBlackBoxX;
    glyphHeight=frame.metrics.gmBlackBoxY;
    glyphPitch=(frame.glyphSize/frame.metrics.gmBlackBoxY)&~3u;
    glyphX=frame.metrics.gmptGlyphOrigin.x;
    glyphY=ascent-frame.metrics.gmptGlyphOrigin.y;
}
