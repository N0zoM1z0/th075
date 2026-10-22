#ifndef TH075_GRAPHICS_DEVICE_HPP
#define TH075_GRAPHICS_DEVICE_HPP

#include "Graphics.hpp"

namespace Graphics
{
    // Original names are unknown. Arguments follow the complete x86 callers
    // and the SDK-backed initialization body, rather than Ghidra's guessed types.
    bool Initialize(HWND window, unsigned short width, unsigned short height,
        bool windowed, bool squareTextures, bool use16BitBackBuffer);
}

#endif
