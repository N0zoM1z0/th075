#include "OptionsScene.hpp"
#include <windows.h>
#include <d3d8.h>
class OptionTextureF432 {public: ~OptionTextureF432();};

// The destructor frees the texture manager and releases the D3D canvas.
OptionsScene::~OptionsScene() {
 if(textures) delete static_cast<OptionTextureF432*>(textures);
 if(canvas) canvas->Release();
}
