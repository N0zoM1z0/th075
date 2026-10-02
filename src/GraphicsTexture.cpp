#include "GraphicsTexture.hpp"
#include <d3dx8.h>

namespace Graphics
{
    extern IDirect3DDevice8 *g_Device;
    extern bool g_RequireSquareTextures;
    extern const char g_Create16BitTextureError[];
    extern const char g_UnsupportedTextureDepthError[];
    extern const char g_CreateTextureError[];
    extern const char g_ResetDeviceError[];
    extern D3DPRESENT_PARAMETERS g_PresentationParameters;
    extern IDirect3DTexture8 *g_TargetTextures[1];
    extern ID3DXRenderToSurface *g_TargetRenderers[1];
    extern void SetDefaultStates();

    bool Create16BitTexture(unsigned short width, unsigned short height,
        IDirect3DTexture8 **texture)
    {
        unsigned int newWidth = width, allocatedHeight = height;
        unsigned int shiftWidth = 0, powerHeight = 0;
        HRESULT result;
        if (width > 1)
        {
            newWidth = width - 1;
            while (newWidth != 1)
            {
                newWidth >>= 1;
                ++shiftWidth;
            }
            newWidth = 2 << shiftWidth;
        }
        if (allocatedHeight > 1)
        {
            allocatedHeight = height - 1;
            while (allocatedHeight != 1)
            {
                allocatedHeight >>= 1;
                ++powerHeight;
            }
            allocatedHeight = 2 << powerHeight;
        }
        if (g_RequireSquareTextures)
        {
            if (newWidth < allocatedHeight) newWidth = allocatedHeight;
            if (newWidth > allocatedHeight) allocatedHeight = newWidth;
        }
        result = D3DXCreateTexture(g_Device, newWidth, allocatedHeight,
            1, 0, D3DFMT_A1R5G5B5, D3DPOOL_MANAGED, texture);
        if (result != D3D_OK)
        {
            ShowError(g_Create16BitTextureError);
            return false;
        }
        return true;
    }

    bool CreateTexture(unsigned short width, unsigned short height,
        IDirect3DTexture8 **texture, unsigned char bitsPerPixel)
    {
        unsigned int newWidth = width, allocatedHeight = height;
        unsigned int shiftWidth = 0, powerHeight = 0;
        HRESULT creationResult;
        if (width > 1)
        {
            newWidth = width - 1;
            while (newWidth != 1)
            {
                newWidth >>= 1;
                ++shiftWidth;
            }
            newWidth = 2 << shiftWidth;
        }
        if (allocatedHeight > 1)
        {
            allocatedHeight = height - 1;
            while (allocatedHeight != 1)
            {
                allocatedHeight >>= 1;
                ++powerHeight;
            }
            allocatedHeight = 2 << powerHeight;
        }
        if (g_RequireSquareTextures)
        {
            if (newWidth < allocatedHeight) newWidth = allocatedHeight;
            if (newWidth > allocatedHeight) allocatedHeight = newWidth;
        }
        if (bitsPerPixel == 32 || bitsPerPixel == 24)
            creationResult = D3DXCreateTexture(g_Device, newWidth, allocatedHeight,
                1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, texture);
        else if (bitsPerPixel == 8 || bitsPerPixel == 16)
            creationResult = D3DXCreateTexture(g_Device, newWidth, allocatedHeight,
                1, 0, D3DFMT_A1R5G5B5, D3DPOOL_MANAGED, texture);
        else
        {
            ShowError(g_UnsupportedTextureDepthError);
            return false;
        }
        if (creationResult != D3D_OK)
        {
            ShowError(g_CreateTextureError);
            return false;
        }
        return true;
    }

    void ResetDevice()
    {
        int index;
        for (index = 0; index < 1; ++index)
        {
            g_TargetTextures[index]->Release();
            g_TargetRenderers[index]->Release();
        }
        if (g_Device->Reset(&g_PresentationParameters) != D3D_OK)
            ShowError(g_ResetDeviceError);
        else
        {
            SetDefaultStates();
            for (index = 0; index < 1; ++index)
            {
                g_Device->CreateTexture(1024, 1024, 1, D3DUSAGE_RENDERTARGET,
                    D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_TargetTextures[index]);
                D3DXCreateRenderToSurface(g_Device, 1024, 1024,
                    D3DFMT_A8R8G8B8, TRUE, D3DFMT_D16, &g_TargetRenderers[index]);
            }
        }
    }
}
