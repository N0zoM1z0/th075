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
};
#define FIELD(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
void FontSpriteF317::RenderTextToTexture(const char* text,unsigned char r,unsigned char g,
        unsigned char b,unsigned char color,unsigned char depth,unsigned char restore)
{
    if (restore)
        FIELD(unsigned char,0x15)=FIELD(unsigned char,0x14);
    else
        FIELD(unsigned char,0x15)=0;
    D3DLOCKED_RECT locked;
    if (FIELD(IDirect3DTexture8*,0)->LockRect(0,&locked,0,0)==D3D_OK) {
        if (static_cast<signed char>(depth)>5) depth=5;
        FIELD(unsigned char,0x24)=color;
        FIELD(float,0x1c)=0.0f;
        FIELD(float,0x20)=6.0f;
        FIELD(FontGlyphRasterF317*,0x18)=new FontGlyphRasterF317(0);
        FIELD(FontGlyphRasterF317*,0x18)->ConfigureTint(&g_FontRasterScaleAt006578B0,
            FIELD(unsigned char,0x24),r,g,b);
        FIELD(FontGlyphRasterF317*,0x18)->RasterizeText(text,locked.pBits,0x400,0x100,0x230,
            static_cast<int>(FIELD(float,0x1c)),static_cast<int>(FIELD(float,0x20)),4,depth);
        delete FIELD(FontGlyphRasterF317*,0x18);
        FIELD(IDirect3DTexture8*,0)->UnlockRect(0);
        FIELD(unsigned char,0x14)=depth;
    }
    FIELD(unsigned char,0x0c)=5;
}
#undef FIELD
