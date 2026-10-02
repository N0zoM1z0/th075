#include "GraphicsDraw.hpp"

namespace Graphics
{
    extern IDirect3DDevice8 *g_Device;
    extern IDirect3DTexture8 *g_CachedTexture;
    extern float g_ColorMultiplier;
    extern float g_DrawScale;
    extern float g_DrawOriginX;
    extern float g_DrawOriginY;

    void DrawLine(const RECT *line, D3DCOLOR color)
    {
        ScreenVertex vertices[2];
        vertices[0].x = static_cast<float>(line->left);
        vertices[0].y = static_cast<float>(line->top);
        vertices[0].z = 0.0f;
        vertices[0].rhw = 1.0f;
        vertices[1].x = static_cast<float>(line->right);
        vertices[1].y = static_cast<float>(line->bottom);
        vertices[1].z = 0.0f;
        vertices[1].rhw = 1.0f;
        vertices[0].u = 0.0f;
        vertices[0].v = 0.0f;
        vertices[1].u = 1.0f;
        vertices[1].v = 1.0f;
        if (*reinterpret_cast<const DWORD *>(&g_ColorMultiplier) != 0x3F800000)
            color = D3DCOLOR_ARGB((color & 0xFF000000) >> 24,
                static_cast<unsigned char>(((color & 0x00FF0000) >> 16) * g_ColorMultiplier),
                static_cast<unsigned char>(((color & 0x0000FF00) >> 8) * g_ColorMultiplier),
                static_cast<unsigned char>((color & 0x000000FF) * g_ColorMultiplier));
        vertices[0].color = vertices[1].color = color;
        for (int index = 0; index < 2; ++index)
        {
            vertices[index].x = g_DrawScale * vertices[index].x + g_DrawOriginX;
            vertices[index].y = g_DrawScale * vertices[index].y + g_DrawOriginY;
        }
        g_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
        if (g_CachedTexture != 0)
        {
            g_Device->SetTexture(0, 0);
            g_CachedTexture = 0;
        }
        g_Device->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
        g_Device->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertices, sizeof(ScreenVertex));
        g_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    }

    void DrawFilledRectangle(const RECT *rectangle, D3DCOLOR color)
    {
        ScreenVertex vertices[4];
        vertices[0].x = static_cast<float>(rectangle->left);
        vertices[0].y = static_cast<float>(rectangle->top);
        vertices[0].z = 0.0f;
        vertices[0].rhw = 1.0f;
        vertices[1].x = static_cast<float>(rectangle->right) + 1.0f;
        vertices[1].y = static_cast<float>(rectangle->top);
        vertices[1].z = 0.0f;
        vertices[1].rhw = 1.0f;
        vertices[2].x = static_cast<float>(rectangle->right) + 1.0f;
        vertices[2].y = static_cast<float>(rectangle->bottom) + 1.0f;
        vertices[2].z = 0.0f;
        vertices[2].rhw = 1.0f;
        vertices[3].x = static_cast<float>(rectangle->left);
        vertices[3].y = static_cast<float>(rectangle->bottom) + 1.0f;
        vertices[3].z = 0.0f;
        vertices[3].rhw = 1.0f;
        vertices[0].u = 0.0f;
        vertices[0].v = 0.0f;
        vertices[1].u = 1.0f;
        vertices[1].v = 0.0f;
        vertices[2].u = 1.0f;
        vertices[2].v = 1.0f;
        vertices[3].u = 0.0f;
        vertices[3].v = 1.0f;
        if (*reinterpret_cast<const DWORD *>(&g_ColorMultiplier) != 0x3F800000)
            color = D3DCOLOR_ARGB((color & 0xFF000000) >> 24,
                static_cast<unsigned char>(((color & 0x00FF0000) >> 16) * g_ColorMultiplier),
                static_cast<unsigned char>(((color & 0x0000FF00) >> 8) * g_ColorMultiplier),
                static_cast<unsigned char>((color & 0x000000FF) * g_ColorMultiplier));
        vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = color;
        for (int index = 0; index < 4; ++index)
        {
            vertices[index].x = g_DrawScale * vertices[index].x + g_DrawOriginX;
            vertices[index].y = g_DrawScale * vertices[index].y + g_DrawOriginY;
        }
        if (g_CachedTexture != 0)
        {
            g_Device->SetTexture(0, 0);
            g_CachedTexture = 0;
        }
        g_Device->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
        g_Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(ScreenVertex));
    }

    void DrawRectangleOutline(const RECT *rectangle, D3DCOLOR color)
    {
        ScreenVertex vertices[5];
        vertices[0].x = static_cast<float>(rectangle->left);
        vertices[0].y = static_cast<float>(rectangle->top);
        vertices[0].z = 0.0f;
        vertices[0].rhw = 1.0f;
        vertices[1].x = static_cast<float>(rectangle->right);
        vertices[1].y = static_cast<float>(rectangle->top);
        vertices[1].z = 0.0f;
        vertices[1].rhw = 1.0f;
        vertices[2].x = static_cast<float>(rectangle->right);
        vertices[2].y = static_cast<float>(rectangle->bottom);
        vertices[2].z = 0.0f;
        vertices[2].rhw = 1.0f;
        vertices[3].x = static_cast<float>(rectangle->left);
        vertices[3].y = static_cast<float>(rectangle->bottom);
        vertices[3].z = 0.0f;
        vertices[3].rhw = 1.0f;
        vertices[0].u = 0.0f;
        vertices[0].v = 0.0f;
        vertices[1].u = 1.0f;
        vertices[1].v = 0.0f;
        vertices[2].u = 1.0f;
        vertices[2].v = 1.0f;
        vertices[3].u = 0.0f;
        vertices[3].v = 1.0f;
        if (*reinterpret_cast<const DWORD *>(&g_ColorMultiplier) != 0x3F800000)
            color = D3DCOLOR_ARGB((color & 0xFF000000) >> 24,
                static_cast<unsigned char>(((color & 0x00FF0000) >> 16) * g_ColorMultiplier),
                static_cast<unsigned char>(((color & 0x0000FF00) >> 8) * g_ColorMultiplier),
                static_cast<unsigned char>((color & 0x000000FF) * g_ColorMultiplier));
        vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = color;
        vertices[4] = vertices[0];
        for (int index = 0; index <= 4; ++index)
        {
            vertices[index].x = g_DrawScale * vertices[index].x + g_DrawOriginX;
            vertices[index].y = g_DrawScale * vertices[index].y + g_DrawOriginY;
        }
        g_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
        if (g_CachedTexture != 0)
        {
            g_Device->SetTexture(0, 0);
            g_CachedTexture = 0;
        }
        g_Device->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
        g_Device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, vertices, sizeof(ScreenVertex));
        g_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    }
}
