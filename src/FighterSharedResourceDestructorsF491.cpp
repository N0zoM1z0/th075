#include "TextOverlay.hpp"
#include <windows.h>
#include <d3d8.h>
#include "TextureManagerF198.hpp"

TextOverlay::~TextOverlay() { texture->Release(); }
