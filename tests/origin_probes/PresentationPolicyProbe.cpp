// Original public interfaces and a complete ordinary array lifetime observer.
// No private text, sprite, image or resource-lock layout is declared.
#include <initguid.h>
#include <d3dx8.h>
#include <malloc.h>
#include <stddef.h>

HRESULT ProbeErrorText(HRESULT code, char *buffer, UINT size)
{
    return D3DXGetErrorStringA(code, buffer, size);
}

HRESULT ProbeSaveTexture(const char *path, D3DXIMAGE_FILEFORMAT format,
    IDirect3DBaseTexture8 *texture, const PALETTEENTRY *palette)
{
    return D3DXSaveTextureToFileA(path, format, texture, palette);
}

INT ProbeFontText(ID3DXFont *font, const char *text, INT count,
    RECT *rect, DWORD format, D3DCOLOR color)
{
    return font->DrawTextA(text, count, rect, format, color);
}

HRESULT ProbeSpriteDraw(ID3DXSprite *sprite, IDirect3DTexture8 *texture,
    const RECT *rect, const D3DXVECTOR2 *scale, const D3DXVECTOR2 *center,
    FLOAT rotation, const D3DXVECTOR2 *position, D3DCOLOR color)
{
    return sprite->Draw(texture, rect, scale, center, rotation, position, color);
}

extern "C" void ProbeUseTextStorage(void *, UINT);
void ProbeTextStorage(UINT size)
{
    void *storage = _alloca(size);
    ProbeUseTextStorage(storage, size);
}

class ArrayLifetimeObserver {
public:
    ArrayLifetimeObserver();
    virtual ~ArrayLifetimeObserver();
    IDirect3DSurface8 *surface;
};

ArrayLifetimeObserver::ArrayLifetimeObserver() : surface(0) {}
ArrayLifetimeObserver::~ArrayLifetimeObserver()
{
    if (surface)
        surface->Release();
}

ArrayLifetimeObserver *ProbeArrayCreate(UINT count)
{
    return new ArrayLifetimeObserver[count];
}

void ProbeArrayDelete(ArrayLifetimeObserver *items)
{
    delete[] items;
}

class DirectArrayObserver {
public:
    DirectArrayObserver();
    ~DirectArrayObserver();
    IDirect3DSurface8 *surface;
};

DirectArrayObserver::DirectArrayObserver() : surface(0) {}
DirectArrayObserver::~DirectArrayObserver()
{
    if (surface)
        surface->Release();
}

DirectArrayObserver *ProbeDirectArrayCreate(UINT count)
{
    return new DirectArrayObserver[count];
}

void ProbeDirectArrayDelete(DirectArrayObserver *items)
{
    delete[] items;
}

extern const GUID PresentationIUnknown = __uuidof(IUnknown);
extern const unsigned int PresentationPublicLayout[] = {
    sizeof(GUID), sizeof(RECT), sizeof(D3DXVECTOR2), sizeof(D3DXMATRIX),
    sizeof(D3DCOLOR), sizeof(ArrayLifetimeObserver), sizeof(void *),
    D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, sizeof(DirectArrayObserver)
};
