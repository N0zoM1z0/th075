#include <d3dx8.h>
#include <cstddef>

HRESULT ProbeCreateFont(IDirect3DDevice8* device, HFONT font, ID3DXFont** result) {
    return D3DXCreateFont(device, font, result);
}
HRESULT ProbeSaveSurfaceA(LPCSTR path, D3DXIMAGE_FILEFORMAT format, IDirect3DSurface8* surface,
                         const PALETTEENTRY* palette, const RECT* area) {
    return D3DXSaveSurfaceToFileA(path, format, surface, palette, area);
}
HRESULT ProbeSaveSurfaceW(LPCWSTR path, D3DXIMAGE_FILEFORMAT format, IDirect3DSurface8* surface,
                         const PALETTEENTRY* palette, const RECT* area) {
    return D3DXSaveSurfaceToFileW(path, format, surface, palette, area);
}
HRESULT ProbeSaveVolumeA(LPCSTR path, D3DXIMAGE_FILEFORMAT format, IDirect3DVolume8* volume,
                        const PALETTEENTRY* palette, const D3DBOX* area) {
    return D3DXSaveVolumeToFileA(path, format, volume, palette, area);
}
HRESULT ProbeSaveVolumeW(LPCWSTR path, D3DXIMAGE_FILEFORMAT format, IDirect3DVolume8* volume,
                        const PALETTEENTRY* palette, const D3DBOX* area) {
    return D3DXSaveVolumeToFileW(path, format, volume, palette, area);
}

HRESULT __cdecl OrdinarySurfacePolicy(const void*, D3DXIMAGE_FILEFORMAT, IDirect3DSurface8*,
                                     const PALETTEENTRY*, const RECT*, int);
HRESULT __cdecl OrdinaryVolumePolicy(const void*, D3DXIMAGE_FILEFORMAT, IDirect3DVolume8*,
                                    const PALETTEENTRY*, const D3DBOX*, int);

HRESULT __stdcall OrdinarySurfaceA(LPCSTR path, D3DXIMAGE_FILEFORMAT format, IDirect3DSurface8* surface,
                                  const PALETTEENTRY* palette, const RECT* area) {
    return OrdinarySurfacePolicy(path, format, surface, palette, area, 0);
}
HRESULT __stdcall OrdinarySurfaceW(LPCWSTR path, D3DXIMAGE_FILEFORMAT format, IDirect3DSurface8* surface,
                                  const PALETTEENTRY* palette, const RECT* area) {
    return OrdinarySurfacePolicy(path, format, surface, palette, area, 1);
}
HRESULT __stdcall OrdinaryVolumeA(LPCSTR path, D3DXIMAGE_FILEFORMAT format, IDirect3DVolume8* volume,
                                 const PALETTEENTRY* palette, const D3DBOX* area) {
    return OrdinaryVolumePolicy(path, format, volume, palette, area, 0);
}
HRESULT __stdcall OrdinaryVolumeW(LPCWSTR path, D3DXIMAGE_FILEFORMAT format, IDirect3DVolume8* volume,
                                 const PALETTEENTRY* palette, const D3DBOX* area) {
    return OrdinaryVolumePolicy(path, format, volume, palette, area, 1);
}
HRESULT __stdcall OrdinaryCreateFont(IDirect3DDevice8* device, HFONT font, ID3DXFont** result) {
    LOGFONTA description;
    if (!GetObjectA(font, sizeof(description), &description))
        return D3DERR_INVALIDCALL;
    return D3DXCreateFontIndirect(device, &description, result);
}

extern const unsigned long PublicWrapperLayout[] = {
    sizeof(LOGFONTA), sizeof(RECT), sizeof(D3DBOX), sizeof(PALETTEENTRY), sizeof(HFONT),
    offsetof(LOGFONTA, lfFaceName), sizeof(D3DXIMAGE_FILEFORMAT), sizeof(HRESULT)
};
