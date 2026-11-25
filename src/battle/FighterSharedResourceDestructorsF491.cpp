#include "graphics/TextOverlay.hpp"
#include <windows.h>
#include <d3d8.h>
#include "graphics/TextureManagerF198.hpp"

TextOverlay::~TextOverlay() { texture->Release(); }
