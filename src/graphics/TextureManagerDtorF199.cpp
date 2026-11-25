#include "graphics/TextureManagerF198.hpp"

TextureManagerF198::~TextureManagerF198()
{
    if (palette)
        delete[] palette;
    if (textures.size() > 0) {
        for (unsigned int i = 0; i < textures.size(); ++i) {
            if (textures[i]) {
                // The native destructor stores the COM Release result.
                ULONG remainingReferenceCount = textures[i]->Release();
                textures[i] = 0;
            }
        }
        textures.clear();
    }
    if (paletteTextures.size() > 0) {
        for (unsigned int j = 0; j < paletteTextures.size(); ++j) {
            if (paletteTextures[j])
                paletteTextures[j]->Release();
        }
        paletteTextures.clear();
    }
    if (entries.size() > 0)
        entries.clear();
}
