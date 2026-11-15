#include <windows.h>
#include <d3d8.h>
#include <new>
// Only original physical 0x38-byte raster owner and D3D8 texture ABI are
// borrowed. This is not a claim about the original complete font class.
class FontGlyphRasterF317 {
    unsigned int nativePhysicalWords[14];
public:
    FontGlyphRasterF317(int style);
    ~FontGlyphRasterF317();
    void ConfigureTint(const float* scale,unsigned int mode,unsigned char r,unsigned char g,unsigned char b);
    void RasterizeText(const char* text,void* image,int width,int height,int maxWidth,
                       int startX,int startY,unsigned char depth,signed char lines);
};
typedef char AssertRasterOwner56F317[(sizeof(FontGlyphRasterF317)==0x38)?1:-1];
extern const float g_FontRasterScaleAt006578B0;
class FontSpriteF317 {
public:
    void RenderTextToTexture(const char* text,unsigned char r,unsigned char g,
           unsigned char b,unsigned char color,unsigned char depth,unsigned char restore);
public:
    // Observed fields; meanings not yet known.
    IDirect3DTexture8* field000;
    unsigned char unknown004[0x00C - 0x004];
    unsigned char field00C;
    unsigned char unknown00D[0x014 - 0x00D];
    unsigned char field014;
    unsigned char field015;
    unsigned char unknown016[0x018 - 0x016];
    FontGlyphRasterF317* field018;
    float field01C;
    float field020;
    unsigned char field024;
};
void FontSpriteF317::RenderTextToTexture(const char* text,unsigned char r,unsigned char g,
        unsigned char b,unsigned char color,unsigned char depth,unsigned char restore)
{
    if (restore)
        field015=field014;
    else
        field015=0;
    D3DLOCKED_RECT locked;
    if (field000->LockRect(0,&locked,0,0)==D3D_OK) {
        if (static_cast<signed char>(depth)>5) depth=5;
        field024=color;
        field01C=0.0f;
        field020=6.0f;
        field018=new FontGlyphRasterF317(0);
        field018->ConfigureTint(&g_FontRasterScaleAt006578B0,
            field024,r,g,b);
        field018->RasterizeText(text,locked.pBits,0x400,0x100,0x230,
            static_cast<int>(field01C),static_cast<int>(field020),4,depth);
        delete field018;
        field000->UnlockRect(0);
        field014=depth;
    }
    field00C=5;
}
