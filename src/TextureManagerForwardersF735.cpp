#include "Graphics.hpp"

// F735: five complete original authored TextureManager forwarders.
// Their native object receiver is saved but unused by the actual shared
// Graphics policy calls. This source establishes each original x86 body,
// not a complete or historically named TextureManager class layout.
class TextureManagerF735 {
public:
    void Present();
    void SetDepthMode(int mode);
    void SetTextureFilter(int mode);
    void SetPixelShaderMode(signed char mode);
    void SetColorMultiplier(float multiplier);
};

void TextureManagerF735::Present() { Graphics::Present(); }
void TextureManagerF735::SetDepthMode(int mode) { Graphics::SetDepthMode(mode); }
void TextureManagerF735::SetTextureFilter(int mode) { Graphics::SetTextureFilter(mode); }
void TextureManagerF735::SetPixelShaderMode(signed char mode) { Graphics::SetPixelShaderMode(mode); }
void TextureManagerF735::SetColorMultiplier(float multiplier) { Graphics::SetColorMultiplier(multiplier); }
