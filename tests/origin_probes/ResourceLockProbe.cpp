// Complete original public interfaces and GUIDs only.
#define INITGUID
#include <d3dx8.h>
#include <stddef.h>

HRESULT ProbeSurfaceDesc(IDirect3DSurface8 *surface, D3DSURFACE_DESC *desc)
{
    return surface->GetDesc(desc);
}

HRESULT ProbeSurfaceContainer(IDirect3DSurface8 *surface, void **out)
{
    return surface->GetContainer(IID_IDirect3DBaseTexture8, out);
}

HRESULT ProbeSurfaceDevice(IDirect3DSurface8 *surface, IDirect3DDevice8 **out)
{
    return surface->GetDevice(out);
}

HRESULT ProbeSurfaceLock(IDirect3DSurface8 *surface, D3DLOCKED_RECT *locked,
    const RECT *rect, DWORD flags)
{
    return surface->LockRect(locked, rect, flags);
}

HRESULT ProbeVolumeDesc(IDirect3DVolume8 *volume, D3DVOLUME_DESC *desc)
{
    return volume->GetDesc(desc);
}

HRESULT ProbeVolumeContainer(IDirect3DVolume8 *volume, void **out)
{
    return volume->GetContainer(IID_IDirect3DVolumeTexture8, out);
}

HRESULT ProbeVolumeLock(IDirect3DVolume8 *volume, D3DLOCKED_BOX *locked,
    const D3DBOX *box, DWORD flags)
{
    return volume->LockBox(locked, box, flags);
}

HRESULT ProbeSurfaceTextureContainer(IDirect3DSurface8 *surface, void **out)
{
    return surface->GetContainer(IID_IDirect3DTexture8, out);
}

DWORD ProbeTextureLevels(IDirect3DTexture8 *texture)
{
    return texture->GetLevelCount();
}

DWORD ProbeVolumeLevels(IDirect3DVolumeTexture8 *texture)
{
    return texture->GetLevelCount();
}

HRESULT ProbeSurfaceUnlock(IDirect3DSurface8 *surface)
{
    return surface->UnlockRect();
}

HRESULT ProbeVolumeUnlock(IDirect3DVolume8 *volume)
{
    return volume->UnlockBox();
}

HRESULT ProbeImageSurface(IDirect3DDevice8 *device, UINT width, UINT height,
    D3DFORMAT format, IDirect3DSurface8 **out)
{
    return device->CreateImageSurface(width, height, format, out);
}

HRESULT ProbeCopyRects(IDirect3DDevice8 *device, IDirect3DSurface8 *source,
    const RECT *rects, UINT count, IDirect3DSurface8 *destination,
    const POINT *points)
{
    return device->CopyRects(source, rects, count, destination, points);
}

ULONG ProbeResourceRelease(IUnknown *resource)
{
    return resource->Release();
}

extern const unsigned int ResourceLockPublicLayout[] = {
    sizeof(D3DSURFACE_DESC), offsetof(D3DSURFACE_DESC, Format),
    offsetof(D3DSURFACE_DESC, Type), offsetof(D3DSURFACE_DESC, Usage),
    offsetof(D3DSURFACE_DESC, Pool), offsetof(D3DSURFACE_DESC, Size),
    offsetof(D3DSURFACE_DESC, MultiSampleType),
    offsetof(D3DSURFACE_DESC, Width), offsetof(D3DSURFACE_DESC, Height),
    sizeof(D3DVOLUME_DESC), offsetof(D3DVOLUME_DESC, Width),
    offsetof(D3DVOLUME_DESC, Height), offsetof(D3DVOLUME_DESC, Depth),
    sizeof(D3DLOCKED_RECT), offsetof(D3DLOCKED_RECT, Pitch),
    offsetof(D3DLOCKED_RECT, pBits), sizeof(D3DLOCKED_BOX),
    offsetof(D3DLOCKED_BOX, RowPitch), offsetof(D3DLOCKED_BOX, SlicePitch),
    offsetof(D3DLOCKED_BOX, pBits), sizeof(RECT), sizeof(D3DBOX),
    offsetof(D3DBOX, Left), offsetof(D3DBOX, Top), offsetof(D3DBOX, Right),
    offsetof(D3DBOX, Bottom), offsetof(D3DBOX, Front), offsetof(D3DBOX, Back),
    D3DPOOL_DEFAULT, D3DPOOL_SYSTEMMEM, D3DLOCK_READONLY
};
