#include "GraphicsTexturedDraw.hpp"

namespace Graphics {
extern IDirect3DDevice8 *g_Device;
extern IDirect3DTexture8 *g_CachedTexture;
extern float g_ColorMultiplier;
extern float g_DrawScale;
extern float g_DrawOriginX;
extern float g_DrawOriginY;
extern const float g_HalfPixelOffsetAt00657478;
extern const float g_UnitDepthAt0065747C;
extern const float g_DepthClipAt00657480;

// Four complete native 28-byte vertices and borrowed Direct3D8 interfaces.
// Caller quad has four 16-byte position records; no original owner extent
// beyond that independently observed array is asserted.
void DrawProjectedTexturedQuad(const float (*positions)[4], const RECT* textureRectangle,
                               float originX, float originY, float projectionZ,
                               D3DCOLOR color, IDirect3DTexture8* texture)
{
    ScreenVertex vertices[4];
    {
        D3DSURFACE_DESC desc;
        float width, height;
        {
            IDirect3DSurface8* surface;
            texture->GetSurfaceLevel(0,&surface);
            surface->GetDesc(&desc);
            width=static_cast<float>(desc.Width);
            height=static_cast<float>(desc.Height);
            surface->Release();
        }
        {
        float projection;
        projection=projectionZ/(projectionZ-positions[0][2]);
        if (projection >= g_DepthClipAt00657480) return;
            vertices[0].x=((positions[0][0]-originX)*projection+originX)-g_HalfPixelOffsetAt00657478;
            vertices[0].y=((positions[0][1]-originY)*projection+originY)-g_HalfPixelOffsetAt00657478;
            vertices[0].z=g_UnitDepthAt0065747C-projection/g_DepthClipAt00657480;
            vertices[0].rhw=projection;
            projection=projectionZ/(projectionZ-positions[1][2]);
            if (projection >= g_DepthClipAt00657480) return;
                vertices[1].x=((positions[1][0]-originX)*projection+originX)-g_HalfPixelOffsetAt00657478;
                vertices[1].y=((positions[1][1]-originY)*projection+originY)-g_HalfPixelOffsetAt00657478;
                vertices[1].z=g_UnitDepthAt0065747C-projection/g_DepthClipAt00657480;
            vertices[1].rhw=projection;
                projection=projectionZ/(projectionZ-positions[2][2]);
                if (projection >= g_DepthClipAt00657480) return;
                    vertices[2].x=((positions[2][0]-originX)*projection+originX)-g_HalfPixelOffsetAt00657478;
                    vertices[2].y=((positions[2][1]-originY)*projection+originY)-g_HalfPixelOffsetAt00657478;
                    vertices[2].z=g_UnitDepthAt0065747C-projection/g_DepthClipAt00657480;
            vertices[2].rhw=projection;
                    projection=projectionZ/(projectionZ-positions[3][2]);
                    if (projection >= g_DepthClipAt00657480) return;
                        vertices[3].x=((positions[3][0]-originX)*projection+originX)-g_HalfPixelOffsetAt00657478;
                        vertices[3].y=((positions[3][1]-originY)*projection+originY)-g_HalfPixelOffsetAt00657478;
                        vertices[3].z=g_UnitDepthAt0065747C-projection/g_DepthClipAt00657480;
            vertices[3].rhw=projection;
                        vertices[0].u=static_cast<float>(textureRectangle->left)/width;
                        vertices[0].v=static_cast<float>(textureRectangle->top)/height;
                        vertices[1].u=static_cast<float>(textureRectangle->right)/width;
                        vertices[1].v=static_cast<float>(textureRectangle->top)/height;
                        vertices[2].u=static_cast<float>(textureRectangle->right)/width;
                        vertices[2].v=static_cast<float>(textureRectangle->bottom)/height;
                        vertices[3].u=static_cast<float>(textureRectangle->left)/width;
                        vertices[3].v=static_cast<float>(textureRectangle->bottom)/height;
                        for (int i=0;i<4;++i) {
                            vertices[i].x=g_DrawScale*vertices[i].x+g_DrawOriginX;
                            vertices[i].y=g_DrawScale*vertices[i].y+g_DrawOriginY;
                        }
                        if (*reinterpret_cast<const DWORD*>(&g_ColorMultiplier)!=0x3F800000)
                            color=D3DCOLOR_ARGB((color&0xff000000)>>24,
                                static_cast<unsigned char>(((color&0x00ff0000)>>16)*g_ColorMultiplier),
                                static_cast<unsigned char>(((color&0x0000ff00)>>8)*g_ColorMultiplier),
                                static_cast<unsigned char>((color&0x000000ff)*g_ColorMultiplier));
                        vertices[0].color=vertices[1].color=vertices[2].color=vertices[3].color=color;
                        if (g_CachedTexture!=texture) {
                            g_Device->SetTexture(0,texture);
                            g_CachedTexture=texture;
                        }
                        g_Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,vertices,sizeof(ScreenVertex));
        }
    }
}
}
