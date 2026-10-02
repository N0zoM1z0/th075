#include "GraphicsTexturedDraw.hpp"

namespace Graphics
{
    extern IDirect3DDevice8 *g_Device;
    extern IDirect3DTexture8 *g_CachedTexture;
    extern float g_ColorMultiplier;
    extern float g_DrawScale;
    extern float g_DrawOriginX;
    extern float g_DrawOriginY;

    void DrawTexturedQuad(const float (*positions)[4], const RECT *textureRectangle,
        D3DCOLOR color, IDirect3DTexture8 *texture)
    {
        ScreenVertex vertices[4];
        {
            D3DSURFACE_DESC desc;
            float width, height;
            {
                IDirect3DSurface8 *surface;
                texture->GetSurfaceLevel(0, &surface);
                surface->GetDesc(&desc);
                width = static_cast<float>(desc.Width);
                height = static_cast<float>(desc.Height);
                surface->Release();
            }
            vertices[0].x = positions[0][0] - 0.5f;
            vertices[0].y = positions[0][1] - 0.5f;
            vertices[0].z = 0.5f;
            vertices[0].rhw = 1.0f;
            vertices[1].x = positions[1][0] - 0.5f;
            vertices[1].y = positions[1][1] - 0.5f;
            vertices[1].z = 0.5f;
            vertices[1].rhw = 1.0f;
            vertices[2].x = positions[3][0] - 0.5f;
            vertices[2].y = positions[3][1] - 0.5f;
            vertices[2].z = 0.5f;
            vertices[2].rhw = 1.0f;
            vertices[3].x = positions[2][0] - 0.5f;
            vertices[3].y = positions[2][1] - 0.5f;
            vertices[3].z = 0.5f;
            vertices[3].rhw = 1.0f;
            vertices[0].u = static_cast<float>(textureRectangle->left) / width;
            vertices[0].v = static_cast<float>(textureRectangle->top) / height;
            vertices[1].u = static_cast<float>(textureRectangle->right) / width;
            vertices[1].v = static_cast<float>(textureRectangle->top) / height;
            vertices[2].u = static_cast<float>(textureRectangle->left) / width;
            vertices[2].v = static_cast<float>(textureRectangle->bottom) / height;
            vertices[3].u = static_cast<float>(textureRectangle->right) / width;
            vertices[3].v = static_cast<float>(textureRectangle->bottom) / height;
        }
        for (int index = 0; index < 4; ++index)
        {
            vertices[index].x = g_DrawScale * vertices[index].x + g_DrawOriginX;
            vertices[index].y = g_DrawScale * vertices[index].y + g_DrawOriginY;
        }
        if (*reinterpret_cast<const DWORD *>(&g_ColorMultiplier) != 0x3F800000)
            color = D3DCOLOR_ARGB((color & 0xFF000000) >> 24,
                static_cast<unsigned char>(((color & 0x00FF0000) >> 16) * g_ColorMultiplier),
                static_cast<unsigned char>(((color & 0x0000FF00) >> 8) * g_ColorMultiplier),
                static_cast<unsigned char>((color & 0x000000FF) * g_ColorMultiplier));
        vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = color;
        if (g_CachedTexture != texture)
        {
            g_Device->SetTexture(0, texture);
            g_CachedTexture = texture;
        }
        g_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(ScreenVertex));
    }

    void DrawProjectedTriangleStrip(ScreenVertex *vertices, int count,
        IDirect3DTexture8 *texture)
    {
        float projection;
        for (int index = 0; index < count; ++index)
        {
            vertices[index].x = g_DrawScale * vertices[index].x + g_DrawOriginX;
            vertices[index].y = g_DrawScale * vertices[index].y + g_DrawOriginY;
            projection = 3000.0f / (3000.0f - vertices[index].z);
            vertices[index].rhw = projection;
            vertices[index].z = 1.0f - projection / 2.0f;
            if (*reinterpret_cast<const DWORD *>(&g_ColorMultiplier) != 0x3F800000)
                vertices[index].color = D3DCOLOR_ARGB((vertices[index].color & 0xFF000000) >> 24,
                    static_cast<unsigned char>(((vertices[index].color & 0x00FF0000) >> 16) * g_ColorMultiplier),
                    static_cast<unsigned char>(((vertices[index].color & 0x0000FF00) >> 8) * g_ColorMultiplier),
                    static_cast<unsigned char>((vertices[index].color & 0x000000FF) * g_ColorMultiplier));
        }
        if (g_CachedTexture != texture)
        {
            g_Device->SetTexture(0, texture);
            g_CachedTexture = texture;
        }
        g_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, count - 2, vertices, sizeof(ScreenVertex));
    }
}
