#include "Graphics.hpp"
#include <d3dx8.h>

namespace Graphics
{
    extern HWND g_Window;
    extern RECT g_PresentationDestinationRect;
    extern RECT g_PresentationSourceRect;
    extern D3DVIEWPORT8 g_TargetViewport;
    extern D3DCOLOR g_ClearColor;
    extern float g_ColorMultiplier;
    extern float g_DrawScale;
    extern float g_DrawOriginX;
    extern float g_DrawOriginY;
    extern PresentCallback g_PresentCallback;
    extern IDirect3DTexture8 *g_TargetTextures[1];
    extern ID3DXRenderToSurface *g_TargetRenderers[1];
    extern IDirect3DDevice8 *g_Device;
    extern signed char g_ActiveTarget;
    extern signed char g_PixelShaderSupport;
    extern bool g_PixelShaderEnabled;
    extern bool g_Windowed;
    extern DWORD g_PixelShader;
    extern const char g_TextureLoadError[];
    extern const char g_TargetBeginError[];
    // Reset is identified at 0x004017A0; its body has not been reconstructed.
    extern void ResetDevice();

    void ShowError(const char *message)
    {
        MessageBoxA(g_Window, message, "DGraphics-Error", 0);
    }

    void SetPresentationDestinationRect(const RECT *rect)
    {
        g_PresentationDestinationRect = *rect;
    }

    void SetTargetViewport(DWORD x, DWORD y, DWORD width, DWORD height)
    {
        g_TargetViewport.X = x;
        g_TargetViewport.Y = y;
        g_TargetViewport.Width = width;
        g_TargetViewport.Height = height;
    }

    void SetPresentationSourceRect(const RECT *rect)
    {
        g_PresentationSourceRect = *rect;
    }

    void SetClearColor(unsigned char red, unsigned char green, unsigned char blue)
    {
        g_ClearColor = D3DCOLOR_XRGB(red, green, blue);
    }

    void SetColorMultiplier(float multiplier)
    {
        g_ColorMultiplier = multiplier;
    }

    void SetDrawTransform(float scale, float originX, float originY)
    {
        g_DrawScale = scale;
        g_DrawOriginX = originX;
        g_DrawOriginY = originY;
    }

    // Negative indices select the back buffer; only target index zero is valid.
    // Keep the target-observed 28-bit clear mask; it retains four bits of alpha.
    bool BeginTarget(signed char index)
    {
        IDirect3DSurface8 *surface;
        if (index >= 1) return false;
        if (index >= 0)
        {
            g_ActiveTarget = index;
            g_TargetTextures[g_ActiveTarget]->GetSurfaceLevel(0, &surface);
            if (g_TargetRenderers[g_ActiveTarget]->BeginScene(surface, &g_TargetViewport) != D3D_OK)
            {
                ShowError(g_TargetBeginError);
                surface->Release();
                return false;
            }
            surface->Release();
            g_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, g_ClearColor & 0x0fffffffU, 1.0f, 0);
        }
        else
        {
            if (g_Device->BeginScene() != D3D_OK) return false;
            g_ActiveTarget = -1;
            g_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, g_ClearColor & 0x0fffffffU, 1.0f, 0);
        }
        return true;
    }

    void BeginFrame()
    {
        if (g_PresentCallback) BeginTarget(0);
        else BeginTarget(-1);
    }

    void SetPresentCallback(PresentCallback callback)
    {
        g_PresentCallback = callback;
    }

    IDirect3DTexture8 *GetPrimaryTargetTexture()
    {
        return g_TargetTextures[0];
    }

    IDirect3DTexture8 *GetTargetTexture(signed char index)
    {
        if (index < 0 || index >= 1) return 0;
        return g_TargetTextures[index];
    }

    void LoadTexture(const char *filename, IDirect3DTexture8 **texture)
    {
        HRESULT result = D3DXCreateTextureFromFileExA(g_Device, filename,
            D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_A1R5G5B5, D3DPOOL_MANAGED,
            D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, 0, 0, texture);
        if (result != D3D_OK) ShowError(g_TextureLoadError);
    }

    void SetTextureStage(signed char stage, IDirect3DTexture8 *texture, bool enabled)
    {
        if (enabled)
        {
            g_Device->SetTextureStageState(stage, D3DTSS_COLOROP, D3DTOP_ADD);
            g_Device->SetTextureStageState(stage, D3DTSS_COLORARG1, D3DTA_CURRENT);
            g_Device->SetTextureStageState(stage, D3DTSS_COLORARG2, D3DTA_TEXTURE);
            g_Device->SetTexture(stage, texture);
        }
        else g_Device->SetTextureStageState(stage, D3DTSS_COLOROP, D3DTOP_DISABLE);
    }

    void SetPixelShaderMode(signed char mode)
    {
        if (g_PixelShaderSupport < 1) return;
        if (mode < 0)
        {
            if (g_PixelShaderEnabled)
            {
                g_Device->SetPixelShader(0);
                g_PixelShaderEnabled = false;
            }
        }
        else
        {
            g_Device->SetPixelShader(g_PixelShader);
            g_PixelShaderEnabled = true;
        }
    }

    void EndFrame()
    {
        if (g_ActiveTarget >= 0)
        {
            g_TargetRenderers[g_ActiveTarget]->EndScene();
            g_ActiveTarget = -1;
            if (g_PresentCallback)
            {
                if (g_Device->BeginScene() != D3D_OK) return;
                g_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, g_ClearColor | 0xff000000U, 1.0f, 0);
                g_PresentCallback(g_TargetTextures);
                g_Device->EndScene();
            }
        }
        else g_Device->EndScene();
    }

    void Present()
    {
        HRESULT result;
        if (g_Windowed) result = g_Device->Present(&g_PresentationSourceRect, &g_PresentationDestinationRect, 0, 0);
        else result = g_Device->Present(0, 0, 0, 0);
        if (result < 0)
        {
            result = g_Device->TestCooperativeLevel();
            if (result == D3DERR_DEVICENOTRESET) ResetDevice();
        }
    }

    void PresentToWindow(HWND window)
    {
        HRESULT result;
        if (g_Windowed) result = g_Device->Present(&g_PresentationSourceRect, &g_PresentationDestinationRect, window, 0);
        else result = g_Device->Present(0, 0, window, 0);
        if (result < 0)
        {
            result = g_Device->TestCooperativeLevel();
            if (result == D3DERR_DEVICENOTRESET) ResetDevice();
        }
    }

    // The target emits case 1 before case 0; VC7 preserves this source order.
    void SetBlendMode(int mode)
    {
        switch (mode)
        {
            case 1:
                g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
                g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
                break;
            case 0:
                g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
                g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
                break;
            case 2:
                g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
                g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
                break;
            case 3:
                g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
                g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
                break;
            case 4:
                g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
                g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
                break;
            case 5:
                g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
                g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
                break;
            case 6:
                g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
                g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
                break;
            case 7:
                g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
                g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
                break;
        }
    }

    void SetAlphaMode(int mode)
    {
        switch (mode)
        {
            case 0:
                g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
                g_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
                g_Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
                break;
            case 1:
                g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
                g_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
                g_Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
                break;
            case 2:
                g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
                g_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
                g_Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
                break;
        }
    }

    // The enable operation selects the default depth comparison through case 4.
    void SetDepthMode(int mode)
    {
        switch (mode)
        {
            case 1:
                g_Device->SetRenderState(D3DRS_ZENABLE, TRUE);
                SetDepthMode(4);
                break;
            case 0:
                g_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
                break;
            case 2:
                g_Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                break;
            case 3:
                g_Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                break;
            case 4:
                g_Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
                break;
            case 5:
                g_Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
                break;
            case 6:
                g_Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
                break;
            case 7:
                g_Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATEREQUAL);
                break;
            case 8:
                g_Device->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
                break;
        }
    }

    // Mode 3 uses the legacy flat-cubic filter value, including for mip filtering.
    void SetTextureFilter(int mode)
    {
        switch (mode)
        {
            case 0:
                g_Device->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_NONE);
                g_Device->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_NONE);
                g_Device->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_NONE);
                break;
            case 1:
                g_Device->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_POINT);
                g_Device->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_POINT);
                g_Device->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
                break;
            case 2:
                g_Device->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
                g_Device->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
                g_Device->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
                break;
            case 3:
                g_Device->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_FLATCUBIC);
                g_Device->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_FLATCUBIC);
                g_Device->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_FLATCUBIC);
                break;
        }
    }
}
