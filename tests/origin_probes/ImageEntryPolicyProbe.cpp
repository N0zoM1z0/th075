// Original public image/surface/volume/texture declarations only.
// No incomplete SDK owner is declared or instantiated.
#include <initguid.h>
#include <d3dx8.h>
#include <stddef.h>

HRESULT ProbeInfoMemory(const void * data, UINT size, D3DXIMAGE_INFO * info)
{
    return D3DXGetImageInfoFromFileInMemory(data, size, info);
}

HRESULT ProbeInfoFileA(const char * path, D3DXIMAGE_INFO * info)
{
    return D3DXGetImageInfoFromFileA(path, info);
}

HRESULT ProbeInfoResourceA(HMODULE owner, const char * name, D3DXIMAGE_INFO * info)
{
    return D3DXGetImageInfoFromResourceA(owner, name, info);
}

HRESULT ProbeInfoFileW(const WCHAR * path, D3DXIMAGE_INFO * info)
{
    return D3DXGetImageInfoFromFileW(path, info);
}

HRESULT ProbeInfoResourceW(HMODULE owner, const WCHAR * name, D3DXIMAGE_INFO * info)
{
    return D3DXGetImageInfoFromResourceW(owner, name, info);
}

HRESULT ProbeLoadSurfaceMemory(IDirect3DSurface8 * destination, const PALETTEENTRY * destination_palette, const RECT * destination_region, const void * data, UINT size, const RECT * source_region, DWORD filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info)
{
    return D3DXLoadSurfaceFromFileInMemory(destination, destination_palette, destination_region, data, size, source_region, filter, color_key, info);
}

HRESULT ProbeLoadSurfaceFileA(IDirect3DSurface8 * destination, const PALETTEENTRY * destination_palette, const RECT * destination_region, const char * path, const RECT * source_region, DWORD filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info)
{
    return D3DXLoadSurfaceFromFileA(destination, destination_palette, destination_region, path, source_region, filter, color_key, info);
}

HRESULT ProbeLoadSurfaceResourceA(IDirect3DSurface8 * destination, const PALETTEENTRY * destination_palette, const RECT * destination_region, HMODULE owner, const char * name, const RECT * source_region, DWORD filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info)
{
    return D3DXLoadSurfaceFromResourceA(destination, destination_palette, destination_region, owner, name, source_region, filter, color_key, info);
}

HRESULT ProbeLoadSurfaceFileW(IDirect3DSurface8 * destination, const PALETTEENTRY * destination_palette, const RECT * destination_region, const WCHAR * path, const RECT * source_region, DWORD filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info)
{
    return D3DXLoadSurfaceFromFileW(destination, destination_palette, destination_region, path, source_region, filter, color_key, info);
}

HRESULT ProbeLoadSurfaceResourceW(IDirect3DSurface8 * destination, const PALETTEENTRY * destination_palette, const RECT * destination_region, HMODULE owner, const WCHAR * name, const RECT * source_region, DWORD filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info)
{
    return D3DXLoadSurfaceFromResourceW(destination, destination_palette, destination_region, owner, name, source_region, filter, color_key, info);
}

HRESULT ProbeSaveSurface(const char * path, D3DXIMAGE_FILEFORMAT image_format, IDirect3DSurface8 * source, const PALETTEENTRY * source_palette, const RECT * source_region)
{
    return D3DXSaveSurfaceToFileA(path, image_format, source, source_palette, source_region);
}

HRESULT ProbeLoadVolumeMemory(IDirect3DVolume8 * destination, const PALETTEENTRY * destination_palette, const D3DBOX * destination_region, const void * data, UINT size, const D3DBOX * source_region, DWORD filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info)
{
    return D3DXLoadVolumeFromFileInMemory(destination, destination_palette, destination_region, data, size, source_region, filter, color_key, info);
}

HRESULT ProbeLoadVolumeFileA(IDirect3DVolume8 * destination, const PALETTEENTRY * destination_palette, const D3DBOX * destination_region, const char * path, const D3DBOX * source_region, DWORD filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info)
{
    return D3DXLoadVolumeFromFileA(destination, destination_palette, destination_region, path, source_region, filter, color_key, info);
}

HRESULT ProbeLoadVolumeResourceA(IDirect3DVolume8 * destination, const PALETTEENTRY * destination_palette, const D3DBOX * destination_region, HMODULE owner, const char * name, const D3DBOX * source_region, DWORD filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info)
{
    return D3DXLoadVolumeFromResourceA(destination, destination_palette, destination_region, owner, name, source_region, filter, color_key, info);
}

HRESULT ProbeLoadVolumeFileW(IDirect3DVolume8 * destination, const PALETTEENTRY * destination_palette, const D3DBOX * destination_region, const WCHAR * path, const D3DBOX * source_region, DWORD filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info)
{
    return D3DXLoadVolumeFromFileW(destination, destination_palette, destination_region, path, source_region, filter, color_key, info);
}

HRESULT ProbeLoadVolumeResourceW(IDirect3DVolume8 * destination, const PALETTEENTRY * destination_palette, const D3DBOX * destination_region, HMODULE owner, const WCHAR * name, const D3DBOX * source_region, DWORD filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info)
{
    return D3DXLoadVolumeFromResourceW(destination, destination_palette, destination_region, owner, name, source_region, filter, color_key, info);
}

HRESULT ProbeSaveVolume(const char * path, D3DXIMAGE_FILEFORMAT image_format, IDirect3DVolume8 * source, const PALETTEENTRY * source_palette, const D3DBOX * source_region)
{
    return D3DXSaveVolumeToFileA(path, image_format, source, source_palette, source_region);
}

HRESULT ProbeCreateTextureMemory(IDirect3DDevice8 * device, const void * data, UINT size, UINT width, UINT height, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DTexture8 ** texture)
{
    return D3DXCreateTextureFromFileInMemoryEx(device, data, size, width, height, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateTextureFileA(IDirect3DDevice8 * device, const char * path, UINT width, UINT height, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DTexture8 ** texture)
{
    return D3DXCreateTextureFromFileExA(device, path, width, height, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateTextureResourceA(IDirect3DDevice8 * device, HMODULE owner, const char * name, UINT width, UINT height, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DTexture8 ** texture)
{
    return D3DXCreateTextureFromResourceExA(device, owner, name, width, height, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateTextureFileW(IDirect3DDevice8 * device, const WCHAR * path, UINT width, UINT height, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DTexture8 ** texture)
{
    return D3DXCreateTextureFromFileExW(device, path, width, height, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateTextureResourceW(IDirect3DDevice8 * device, HMODULE owner, const WCHAR * name, UINT width, UINT height, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DTexture8 ** texture)
{
    return D3DXCreateTextureFromResourceExW(device, owner, name, width, height, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateCubeTextureMemory(IDirect3DDevice8 * device, const void * data, UINT size, UINT edge, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DCubeTexture8 ** texture)
{
    return D3DXCreateCubeTextureFromFileInMemoryEx(device, data, size, edge, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateCubeTextureFileA(IDirect3DDevice8 * device, const char * path, UINT edge, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DCubeTexture8 ** texture)
{
    return D3DXCreateCubeTextureFromFileExA(device, path, edge, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateCubeTextureResourceA(IDirect3DDevice8 * device, HMODULE owner, const char * name, UINT edge, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DCubeTexture8 ** texture)
{
    return D3DXCreateCubeTextureFromResourceExA(device, owner, name, edge, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateCubeTextureFileW(IDirect3DDevice8 * device, const WCHAR * path, UINT edge, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DCubeTexture8 ** texture)
{
    return D3DXCreateCubeTextureFromFileExW(device, path, edge, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateCubeTextureResourceW(IDirect3DDevice8 * device, HMODULE owner, const WCHAR * name, UINT edge, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DCubeTexture8 ** texture)
{
    return D3DXCreateCubeTextureFromResourceExW(device, owner, name, edge, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateVolumeTextureMemory(IDirect3DDevice8 * device, const void * data, UINT size, UINT width, UINT height, UINT depth, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DVolumeTexture8 ** texture)
{
    return D3DXCreateVolumeTextureFromFileInMemoryEx(device, data, size, width, height, depth, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateVolumeTextureFileA(IDirect3DDevice8 * device, const char * path, UINT width, UINT height, UINT depth, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DVolumeTexture8 ** texture)
{
    return D3DXCreateVolumeTextureFromFileExA(device, path, width, height, depth, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateVolumeTextureResourceA(IDirect3DDevice8 * device, HMODULE owner, const char * name, UINT width, UINT height, UINT depth, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DVolumeTexture8 ** texture)
{
    return D3DXCreateVolumeTextureFromResourceExA(device, owner, name, width, height, depth, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateVolumeTextureFileW(IDirect3DDevice8 * device, const WCHAR * path, UINT width, UINT height, UINT depth, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DVolumeTexture8 ** texture)
{
    return D3DXCreateVolumeTextureFromFileExW(device, path, width, height, depth, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

HRESULT ProbeCreateVolumeTextureResourceW(IDirect3DDevice8 * device, HMODULE owner, const WCHAR * name, UINT width, UINT height, UINT depth, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, DWORD filter, DWORD mip_filter, D3DCOLOR color_key, D3DXIMAGE_INFO * info, PALETTEENTRY * palette, IDirect3DVolumeTexture8 ** texture)
{
    return D3DXCreateVolumeTextureFromResourceExW(device, owner, name, width, height, depth, levels, usage, format, pool, filter, mip_filter, color_key, info, palette, texture);
}

extern const unsigned int ImageEntryPublicLayout[] = {
    sizeof(D3DXIMAGE_INFO), sizeof(RECT), sizeof(D3DBOX),
    sizeof(PALETTEENTRY), sizeof(WCHAR), sizeof(GUID), sizeof(void *),
    offsetof(D3DXIMAGE_INFO, Width), offsetof(D3DXIMAGE_INFO, Height),
    offsetof(D3DXIMAGE_INFO, Depth), offsetof(D3DXIMAGE_INFO, MipLevels),
    offsetof(D3DXIMAGE_INFO, Format), offsetof(D3DXIMAGE_INFO, ResourceType),
    offsetof(D3DXIMAGE_INFO, ImageFileFormat),
    D3DRTYPE_SURFACE, D3DRTYPE_VOLUME, D3DRTYPE_TEXTURE,
    D3DRTYPE_VOLUMETEXTURE, D3DRTYPE_CUBETEXTURE,
    D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_FILTER_NONE
};
