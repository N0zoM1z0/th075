// Complete public SDK types only; private SDK owners are never instantiated.
#include <d3dx8.h>
#include <stddef.h>

HRESULT ProbeCheckCube(IDirect3DDevice8 *device, UINT *edge, UINT *levels,
    DWORD usage, D3DFORMAT *format, D3DPOOL pool)
{
    return D3DXCheckCubeTextureRequirements(device, edge, levels, usage, format, pool);
}

HRESULT ProbeCheckVolume(IDirect3DDevice8 *device, UINT *width, UINT *height,
    UINT *depth, UINT *levels, DWORD usage, D3DFORMAT *format, D3DPOOL pool)
{
    return D3DXCheckVolumeTextureRequirements(device, width, height, depth, levels, usage, format, pool);
}

HRESULT ProbeCreateCube(IDirect3DDevice8 *device, UINT edge, UINT levels,
    DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DCubeTexture8 **out)
{
    return D3DXCreateCubeTexture(device, edge, levels, usage, format, pool, out);
}

HRESULT ProbeCreateVolume(IDirect3DDevice8 *device, UINT width, UINT height,
    UINT depth, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool,
    IDirect3DVolumeTexture8 **out)
{
    return D3DXCreateVolumeTexture(device, width, height, depth, levels, usage, format, pool, out);
}

HRESULT ProbeCreateEnv(IDirect3DDevice8 *device, UINT size,
    D3DFORMAT format, BOOL depth, D3DFORMAT depthFormat, ID3DXRenderToEnvMap **out)
{
    return D3DXCreateRenderToEnvMap(device, size, format, depth, depthFormat, out);
}

HRESULT ProbeDeviceCube(IDirect3DDevice8 *device, UINT edge, UINT levels,
    DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DCubeTexture8 **out)
{
    return device->CreateCubeTexture(edge, levels, usage, format, pool, out);
}

HRESULT ProbeDeviceVolume(IDirect3DDevice8 *device, UINT width, UINT height,
    UINT depth, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool,
    IDirect3DVolumeTexture8 **out)
{
    return device->CreateVolumeTexture(width, height, depth, levels, usage, format, pool, out);
}

HRESULT ProbeEnvDesc(ID3DXRenderToEnvMap *env, D3DXRTE_DESC *desc)
{
    return env->GetDesc(desc);
}

extern const unsigned int CubeVolumePublicLayout[] = {
    D3DRTYPE_CUBETEXTURE, D3DRTYPE_VOLUMETEXTURE, sizeof(D3DXRTE_DESC),
    offsetof(D3DXRTE_DESC, Size),
    offsetof(D3DXRTE_DESC, Format), offsetof(D3DXRTE_DESC, DepthStencil),
    offsetof(D3DXRTE_DESC, DepthStencilFormat)
};
