#include "Graphics.hpp"
#include <d3dx8.h>
#include <string.h>

namespace Graphics {
extern IDirect3DDevice8 *g_Device;
extern signed char g_PixelShaderSupport;
extern DWORD g_PixelShader;
extern char g_GrayPixelShaderCodeAt0066C090[];
void SetBlendMode(int);
void SetDepthMode(int);
void SetTextureFilter(int);
void SetPixelShaderMode(signed char);

void SetDefaultStates()
{
    if (g_Device == 0) return;
        g_Device->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x1B), 1);
        g_Device->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x0F), 1);
        g_Device->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x18), 1);
        g_Device->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x19), 7);
        SetBlendMode(0);
        SetDepthMode(0);
        SetTextureFilter(1);
        g_Device->SetTextureStageState(0, static_cast<D3DTEXTURESTAGESTATETYPE>(4), 4);
        g_Device->SetTextureStageState(0, static_cast<D3DTEXTURESTAGESTATETYPE>(2), 2);
        g_Device->SetTextureStageState(0, static_cast<D3DTEXTURESTAGESTATETYPE>(3), 0);
        g_Device->SetTextureStageState(0, static_cast<D3DTEXTURESTAGESTATETYPE>(5), 2);
        g_Device->SetTextureStageState(0, static_cast<D3DTEXTURESTAGESTATETYPE>(6), 1);
        g_Device->SetTextureStageState(0, static_cast<D3DTEXTURESTAGESTATETYPE>(15), 0);
        g_Device->SetTextureStageState(0, static_cast<D3DTEXTURESTAGESTATETYPE>(13), 1);
        g_Device->SetTextureStageState(0, static_cast<D3DTEXTURESTAGESTATETYPE>(14), 1);
        g_Device->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x16), 1);
        g_Device->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x89), 0);
        g_Device->SetVertexShader(0x144);
        if (g_PixelShaderSupport >= 1) {
            LPD3DXBUFFER shaderBuffer;
            HRESULT assembleStatus;
            float grayscaleWeights[4];
            assembleStatus = D3DXAssembleShader(g_GrayPixelShaderCodeAt0066C090,
                strlen(g_GrayPixelShaderCodeAt0066C090), 0, 0, &shaderBuffer, 0);
            g_Device->CreatePixelShader(static_cast<const DWORD*>(shaderBuffer->GetBufferPointer()), &g_PixelShader);
            shaderBuffer->Release();
            grayscaleWeights[0] = 0.3f;
            grayscaleWeights[1] = 0.59f;
            grayscaleWeights[2] = 0.11f;
            grayscaleWeights[3] = 1.0f;
            g_Device->SetPixelShaderConstant(0, grayscaleWeights, 1);
            SetPixelShaderMode(-1);
        }
}
}
