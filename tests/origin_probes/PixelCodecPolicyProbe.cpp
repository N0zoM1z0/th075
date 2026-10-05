// Public SDK declarations/layouts and a complete ordinary callback policy.
// No private SDK owner or pixel-codec layout is declared or instantiated.
#include <d3dx8.h>
#include <stddef.h>

HRESULT ProbeFilter(IDirect3DBaseTexture8 *texture, const PALETTEENTRY *palette,
    UINT level, DWORD filter)
{
    return D3DXFilterTexture(texture, palette, level, filter);
}

HRESULT ProbeSurfaceCopy(IDirect3DSurface8 *destination, const PALETTEENTRY *dstPalette,
    const RECT *dstRect, IDirect3DSurface8 *source, const PALETTEENTRY *srcPalette,
    const RECT *srcRect, DWORD filter, D3DCOLOR colorKey)
{
    return D3DXLoadSurfaceFromSurface(destination, dstPalette, dstRect,
        source, srcPalette, srcRect, filter, colorKey);
}

HRESULT ProbeVolumeCopy(IDirect3DVolume8 *destination, const PALETTEENTRY *dstPalette,
    const D3DBOX *dstBox, IDirect3DVolume8 *source, const PALETTEENTRY *srcPalette,
    const D3DBOX *srcBox, DWORD filter, D3DCOLOR colorKey)
{
    return D3DXLoadVolumeFromVolume(destination, dstPalette, dstBox,
        source, srcPalette, srcBox, filter, colorKey);
}

HRESULT ProbeSurfaceMemory(IDirect3DSurface8 *destination, const PALETTEENTRY *dstPalette,
    const RECT *dstRect, const void *source, D3DFORMAT format, UINT pitch,
    const PALETTEENTRY *srcPalette, const RECT *srcRect, DWORD filter, D3DCOLOR colorKey)
{
    return D3DXLoadSurfaceFromMemory(destination, dstPalette, dstRect,
        source, format, pitch, srcPalette, srcRect, filter, colorKey);
}

HRESULT ProbeVolumeMemory(IDirect3DVolume8 *destination, const PALETTEENTRY *dstPalette,
    const D3DBOX *dstBox, const void *source, D3DFORMAT format,
    UINT rowPitch, UINT slicePitch, const PALETTEENTRY *srcPalette,
    const D3DBOX *srcBox, DWORD filter, D3DCOLOR colorKey)
{
    return D3DXLoadVolumeFromMemory(destination, dstPalette, dstBox,
        source, format, rowPitch, slicePitch, srcPalette, srcBox, filter, colorKey);
}

HRESULT ProbeEnvEnd(ID3DXRenderToEnvMap *env)
{
    return env->End();
}

extern "C" int ProbeCpuChoice();
extern "C" HRESULT ProbePackedBox(UINT *, UINT *, UINT, UINT, UINT, UINT);
extern "C" HRESULT ProbeScalarA(UINT *, UINT *, UINT, UINT, UINT, UINT);
extern "C" HRESULT ProbeScalarX(UINT *, UINT *, UINT, UINT, UINT, UINT);
typedef HRESULT (__cdecl *BoxCallback)(UINT *, UINT *, UINT, UINT, UINT, UINT);
HRESULT ProbeSelectA(UINT *, UINT *, UINT, UINT, UINT, UINT);
HRESULT ProbeSelectX(UINT *, UINT *, UINT, UINT, UINT, UINT);
BoxCallback ProbeBoxA = ProbeSelectA;
BoxCallback ProbeBoxX = ProbeSelectX;

HRESULT ProbeSelectA(UINT *destination, UINT *source, UINT width, UINT height,
    UINT dstPitch, UINT srcPitch)
{
    if (ProbeCpuChoice()) {
        ProbeBoxA = ProbePackedBox;
        ProbeBoxX = ProbePackedBox;
    } else {
        ProbeBoxA = ProbeScalarA;
        ProbeBoxX = ProbeScalarX;
    }
    return ProbeBoxA(destination, source, width, height, dstPitch, srcPitch);
}

HRESULT ProbeSelectX(UINT *destination, UINT *source, UINT width, UINT height,
    UINT dstPitch, UINT srcPitch)
{
    if (ProbeCpuChoice()) {
        ProbeBoxA = ProbePackedBox;
        ProbeBoxX = ProbePackedBox;
    } else {
        ProbeBoxA = ProbeScalarA;
        ProbeBoxX = ProbeScalarX;
    }
    return ProbeBoxX(destination, source, width, height, dstPitch, srcPitch);
}

extern const unsigned int PixelCodecPublicLayout[] = {
    sizeof(D3DXCOLOR), offsetof(D3DXCOLOR, r), offsetof(D3DXCOLOR, g),
    offsetof(D3DXCOLOR, b), offsetof(D3DXCOLOR, a), sizeof(PALETTEENTRY),
    sizeof(RECT), sizeof(D3DBOX), sizeof(BoxCallback), D3DX_FILTER_NONE,
    D3DX_FILTER_POINT, D3DX_FILTER_LINEAR, D3DX_FILTER_TRIANGLE, D3DX_FILTER_BOX,
    D3DFMT_A8R8G8B8, D3DFMT_X8R8G8B8, D3DFMT_DXT1, D3DFMT_DXT5
};
