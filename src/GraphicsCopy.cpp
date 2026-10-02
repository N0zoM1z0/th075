#include "GraphicsCopy.hpp"

namespace Graphics
{
    extern IDirect3DDevice8 *g_Device;

    void CopyTextureOpaque(IDirect3DTexture8 **destination,
        IDirect3DTexture8 **source, const RECT *rectangle)
    {
        D3DLOCKED_RECT lockRect;
        D3DSURFACE_DESC description;
        IDirect3DSurface8 *dstSurface, *sourceTextureSurface;

        (*destination)->GetSurfaceLevel(0, &dstSurface);
        (*source)->GetSurfaceLevel(0, &sourceTextureSurface);
        g_Device->CopyRects(sourceTextureSurface, rectangle, 1, dstSurface, 0);
        (*destination)->LockRect(0, &lockRect, 0, 0);
        dstSurface->GetDesc(&description);
        // The target indexes by surface width rather than the returned pitch.
        if (rectangle == 0)
        {
            for (unsigned int x = 0; x < description.Width; ++x)
                for (unsigned int y = 0; y < description.Height; ++y)
                    static_cast<DWORD *>(lockRect.pBits)[y * description.Width + x] =
                        static_cast<DWORD *>(lockRect.pBits)[y * description.Width + x] | 0xFF000000;
        }
        else
        {
            for (int rectangleX = rectangle->left; rectangleX < rectangle->right; ++rectangleX)
                for (int rectangleY = rectangle->top; rectangleY < rectangle->bottom; ++rectangleY)
                    static_cast<DWORD *>(lockRect.pBits)[rectangleY * description.Width + rectangleX] =
                        static_cast<DWORD *>(lockRect.pBits)[rectangleY * description.Width + rectangleX] | 0xFF000000;
        }
        (*destination)->UnlockRect(0);
        dstSurface->Release();
        sourceTextureSurface->Release();
    }
}
