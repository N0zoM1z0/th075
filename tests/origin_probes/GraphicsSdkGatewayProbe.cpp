// Public SDK interfaces only. No private reconstructed owner is instantiated.
#include <d3dx8.h>
#include <stddef.h>

HRESULT ProbeAssemble(LPCVOID data, UINT size, DWORD flags,
    ID3DXBuffer **constants, ID3DXBuffer **shader, ID3DXBuffer **errors)
{
    return D3DXAssembleShader(data, size, flags, constants, shader, errors);
}

HRESULT ProbeRender(IDirect3DDevice8 *device, UINT width, UINT height,
    D3DFORMAT format, BOOL depth, D3DFORMAT depthFormat, ID3DXRenderToSurface **out)
{
    return D3DXCreateRenderToSurface(device, width, height, format, depth, depthFormat, out);
}

HRESULT ProbeTexture(IDirect3DDevice8 *device, UINT width, UINT height, UINT levels,
    DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DTexture8 **out)
{
    return D3DXCreateTexture(device, width, height, levels, usage, format, pool, out);
}

HRESULT ProbeRequirements(IDirect3DDevice8 *device, UINT *width, UINT *height,
    UINT *levels, DWORD usage, D3DFORMAT *format, D3DPOOL pool)
{
    return D3DXCheckTextureRequirements(device, width, height, levels, usage, format, pool);
}

HRESULT ProbeDeviceTexture(IDirect3DDevice8 *device, UINT width, UINT height, UINT levels,
    DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DTexture8 **out)
{
    return device->CreateTexture(width, height, levels, usage, format, pool, out);
}

HRESULT ProbeDeviceContext(IDirect3DDevice8 *device, IDirect3D8 **direct3D,
    D3DCAPS8 *caps, D3DDISPLAYMODE *mode, D3DDEVICE_CREATION_PARAMETERS *creation)
{
    HRESULT result = device->GetDirect3D(direct3D);
    if (FAILED(result)) return result;
    result = device->GetDeviceCaps(caps);
    if (FAILED(result)) return result;
    result = device->GetDisplayMode(mode);
    if (FAILED(result)) return result;
    return device->GetCreationParameters(creation);
}

HRESULT ProbeDeviceFormat(IDirect3D8 *direct3D, UINT adapter, D3DDEVTYPE type,
    D3DFORMAT adapterFormat, DWORD usage, D3DRESOURCETYPE resource, D3DFORMAT format)
{
    return direct3D->CheckDeviceFormat(adapter, type, adapterFormat, usage, resource, format);
}

void *ProbeBufferData(ID3DXBuffer *buffer) { return buffer->GetBufferPointer(); }
DWORD ProbeBufferSize(ID3DXBuffer *buffer) { return buffer->GetBufferSize(); }
ULONG ProbeRelease(IUnknown *object) { return object->Release(); }

// Compiler observation for a guarded one-argument cdecl dynamic callback.
// This does not declare a private SDK interface or fix its runtime destination.
BOOL ProbeDynamicMute(HMODULE module, int mute)
{
    typedef void (__cdecl *Callback)(int);
    Callback callback = reinterpret_cast<Callback>(GetProcAddress(module, "DebugSetMute"));
    if (!callback) return FALSE;
    callback(mute);
    return TRUE;
}

extern const unsigned int GraphicsSdkPublicLayout[] = {
    sizeof(D3DCAPS8), offsetof(D3DCAPS8, TextureCaps),
    offsetof(D3DCAPS8, MaxTextureWidth), offsetof(D3DCAPS8, MaxTextureHeight),
    offsetof(D3DCAPS8, MaxVolumeExtent), sizeof(D3DDISPLAYMODE),
    offsetof(D3DDISPLAYMODE, Format), sizeof(D3DDEVICE_CREATION_PARAMETERS),
    offsetof(D3DDEVICE_CREATION_PARAMETERS, DeviceType),
    D3DRTYPE_TEXTURE, D3DPTEXTURECAPS_POW2, D3DPTEXTURECAPS_SQUAREONLY
};
