// Public image declarations and complete generic nonreturn callback observers.
// This does not declare a private SDK, JPEG, PNG or zlib object layout.
#include <d3dx8.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stddef.h>

struct ImageJumpObserver {
    void (__cdecl *notify)(ImageJumpObserver *);
    jmp_buf state;
};

extern "C" void ProbeImageDestroy(ImageJumpObserver *);

void ProbeImageJump(ImageJumpObserver *observer)
{
    observer->notify(observer);
    longjmp(observer->state, 1);
}

void ProbePngJump(jmp_buf state, const char *)
{
    longjmp(state, 1);
}

void ProbeImageExit(ImageJumpObserver *observer)
{
    observer->notify(observer);
    ProbeImageDestroy(observer);
    exit(1);
}

int ProbeImageSetJump(jmp_buf state)
{
    return setjmp(state);
}

HRESULT ProbeImageInfo(const void *data, UINT size, D3DXIMAGE_INFO *info)
{
    return D3DXGetImageInfoFromFileInMemory(data, size, info);
}

HRESULT ProbeSaveSurface(const char *path, D3DXIMAGE_FILEFORMAT format,
    IDirect3DSurface8 *surface, const PALETTEENTRY *palette, const RECT *rect)
{
    return D3DXSaveSurfaceToFileA(path, format, surface, palette, rect);
}

extern const unsigned int ImageJumpPublicLayout[] = {
    sizeof(jmp_buf), sizeof(ImageJumpObserver), offsetof(ImageJumpObserver, state),
    sizeof(D3DXIMAGE_INFO), offsetof(D3DXIMAGE_INFO, Width),
    offsetof(D3DXIMAGE_INFO, Height), offsetof(D3DXIMAGE_INFO, Depth),
    offsetof(D3DXIMAGE_INFO, MipLevels), offsetof(D3DXIMAGE_INFO, Format),
    offsetof(D3DXIMAGE_INFO, ResourceType), offsetof(D3DXIMAGE_INFO, ImageFileFormat),
    D3DXIFF_BMP, D3DXIFF_JPG, D3DXIFF_TGA, D3DXIFF_PNG, D3DXIFF_DDS,
    sizeof(D3DXIMAGE_FILEFORMAT)
};
