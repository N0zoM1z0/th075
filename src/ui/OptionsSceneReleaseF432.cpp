#include "ui/OptionsScene.hpp"
#include "graphics/TextureManagerF198.hpp"
#include <windows.h>
#include <d3d8.h>

// The destructor frees the texture manager and releases the D3D canvas.
OptionsScene::~OptionsScene() {
 if(textures) delete textures;
 if(canvas) canvas->Release();
}
