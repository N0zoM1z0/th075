#include "graphics/Graphics.hpp"
#include "graphics/TextureManagerF198.hpp"

void TextureManagerF198::Present() { Graphics::Present(); }
void TextureManagerF198::SetDepthMode(int mode) { Graphics::SetDepthMode(mode); }
void TextureManagerF198::SetTextureFilter(int mode) { Graphics::SetTextureFilter(mode); }
void TextureManagerF198::SetPixelShaderMode(signed char mode) { Graphics::SetPixelShaderMode(mode); }
void TextureManagerF198::SetColorMultiplier(float multiplier) { Graphics::SetColorMultiplier(multiplier); }
