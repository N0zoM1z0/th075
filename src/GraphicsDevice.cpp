#include "GraphicsDevice.hpp"
#include "DiagnosticLog.hpp"
#include <d3dx8.h>
#include <stdio.h>
#include <string.h>

namespace Graphics
{
    extern IDirect3D8 *g_Direct3D;
    extern IDirect3DDevice8 *g_Device;
    extern HWND g_Window;
    extern bool g_Windowed;
    extern int g_ClientWidth;
    extern int g_ClientHeight;
    extern D3DDISPLAYMODE g_DisplayMode;
    extern D3DPRESENT_PARAMETERS g_PresentationParameters;
    extern IDirect3DTexture8 *g_TargetTextures[1];
    extern ID3DXRenderToSurface *g_TargetRenderers[1];
    extern PresentCallback g_PresentCallback;
    extern RECT g_PresentationDestinationRect;
    extern RECT g_PresentationSourceRect;
    extern D3DVIEWPORT8 g_TargetViewport;
    extern signed char g_PixelShaderSupport;
    extern bool g_RequireSquareTextures;
    extern bool g_Use16BitBackBuffer;

    extern const char g_CreateDirect3DError[];
    extern const char g_GetDeviceCapsError[];
    extern const char g_GetDisplayModeError[];
    extern const char g_CreateDeviceError[];
    extern const char g_CreateTargetTextureError[];
    extern const char g_CreateTargetRendererError[];

    void SetDefaultStates();
    void ToggleWindowMode();

    bool Initialize(HWND window, unsigned short width, unsigned short height,
        bool windowed, bool squareTextures, bool use16BitBackBuffer)
    {
        if (!g_Direct3D)
        {
            g_Direct3D = Direct3DCreate8(D3D_SDK_VERSION);
            if (!g_Direct3D)
            {
                ShowError(g_CreateDirect3DError);
                return false;
            }

            D3DCAPS8 caps;
            char message[80];
            if (FAILED(g_Direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
            {
                ShowError(g_GetDeviceCapsError);
                return false;
            }
            sprintf(message, "max width - height :: %d - %d \r\n",
                caps.MaxTextureWidth, caps.MaxTextureHeight);
            DiagnosticLog::AppendString(message);
            sprintf(message, "max aspect ratio :: %d \r\n", caps.MaxTextureAspectRatio);
            DiagnosticLog::AppendString(message);
            if (FAILED(g_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &g_DisplayMode)))
            {
                ShowError(g_GetDisplayModeError);
                return false;
            }
        }

        if (!g_Device)
        {
            g_Window = window;
            g_Windowed = true;
            g_ClientWidth = width;
            g_ClientHeight = height;
            memset(&g_PresentationParameters, 0, sizeof(g_PresentationParameters));
            g_PresentationParameters.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
            g_PresentationParameters.BackBufferWidth = width;
            g_PresentationParameters.BackBufferHeight = height;
            g_PresentationParameters.BackBufferFormat = g_DisplayMode.Format;
            g_PresentationParameters.BackBufferCount = 1;
            g_PresentationParameters.Windowed = TRUE;
            g_PresentationParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
            g_PresentationParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
            g_PresentationParameters.hDeviceWindow = g_Window;
            g_PresentationParameters.EnableAutoDepthStencil = TRUE;
            g_PresentationParameters.AutoDepthStencilFormat = D3DFMT_D16;

            D3DCAPS8 caps;
            g_Direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
            if (caps.PixelShaderVersion < D3DPS_VERSION(1, 0))
            {
                DiagnosticLog::AppendString("PixelShader Disable\r\n");
                g_PixelShaderSupport = 0;
            }
            else
            {
                DiagnosticLog::AppendString("PixelShader Enable\r\n");
                g_PixelShaderSupport = 1;
            }

            if (FAILED(g_Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
                    g_Window, D3DCREATE_HARDWARE_VERTEXPROCESSING,
                    &g_PresentationParameters, &g_Device))
                && FAILED(g_Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
                    g_Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                    &g_PresentationParameters, &g_Device))
                && FAILED(g_Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF,
                    g_Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                    &g_PresentationParameters, &g_Device)))
            {
                ShowError(g_CreateDeviceError);
                return false;
            }

            for (int index = 0; index < 1; ++index)
            {
                if (g_Device->CreateTexture(1024, 1024, 1, D3DUSAGE_RENDERTARGET,
                    D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_TargetTextures[index]) != D3D_OK)
                    ShowError(g_CreateTargetTextureError);
                if (D3DXCreateRenderToSurface(g_Device, 1024, 1024, D3DFMT_A8R8G8B8,
                    TRUE, D3DFMT_D16, &g_TargetRenderers[index]) != D3D_OK)
                    ShowError(g_CreateTargetRendererError);
                (&g_PresentCallback)[index] = 0;
            }
            g_PresentationSourceRect.left = 0;
            g_PresentationSourceRect.right = width;
            g_PresentationSourceRect.top = 0;
            g_PresentationSourceRect.bottom = height;
            g_TargetViewport.X = 0;
            g_TargetViewport.Y = 0;
            g_TargetViewport.Width = width;
            g_TargetViewport.Height = height;
            g_TargetViewport.MinZ = 0.0f;
            g_TargetViewport.MaxZ = 1.0f;
            g_PresentationDestinationRect = g_PresentationSourceRect;
            g_RequireSquareTextures = squareTextures;
            g_Use16BitBackBuffer = use16BitBackBuffer;
            if (!windowed)
                ToggleWindowMode();
            SetDefaultStates();
        }
        SetClearColor(0, 0, 0);
        return true;
    }
}
