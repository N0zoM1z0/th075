#include "graphics/TextureManagerF198.hpp"
#include "graphics/GraphicsTexture.hpp"
#include <stdio.h>
#include <stdlib.h>

#define ENTRY entries[work.index]
void TextureManagerF198::LoadBitmapDirectoryWithFormat(const char* baseDir)
{
    struct BitmapDirectoryWork {
        int index;
        int total;
        char filename[260];
    } work;
    work.total = static_cast<int>(entries.size());
    for (work.index = 0; work.index < work.total; ++work.index) {
        ENTRY.bitsPerPixel = textureDepth;
        ENTRY.palette = palette;
        sprintf(work.filename, "%s\\%04d.bmp", baseDir, work.index);
        if (ENTRY.LoadFile(work.filename)) {
            ENTRY.usesSharedPaletteTexture = 0;
            Graphics::CreateTexture(static_cast<unsigned short>(ENTRY.storedWidth),
                static_cast<unsigned short>(ENTRY.storedHeight), &textures[work.index], ENTRY.bitsPerPixel);
            Refresh(work.index);
            void* buffer = ENTRY.pixels;
            free(buffer);
            ENTRY.pixels = 0;
        } else {
            entries.erase(entries.begin() + work.index, entries.end());
            work.total = work.index;
        }
    }
}
#undef ENTRY
