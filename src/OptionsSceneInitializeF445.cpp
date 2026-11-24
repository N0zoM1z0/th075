#include "TextureManagerF198.hpp"
// The options scene constructor: an 80-byte texture manager and a
// 1024x512 canvas for the option values.
#include <windows.h>
#include <d3d8.h>
#include "OptionsScene.hpp"
#include "GraphicsTexture.hpp"
extern const char g_OptionsDataPathAt00657D80[];
extern const char g_OptionsArchiveRootAt00657D78[];
OptionsScene::OptionsScene() {
    canvas=0;
    textures=new TextureManagerF198;
    static_cast<TextureManagerF198*>(textures)->AllocateUnformattedSlots(3);
    static_cast<TextureManagerF198*>(textures)->LoadDefault(g_OptionsDataPathAt00657D80,g_OptionsArchiveRootAt00657D78);
    Graphics::CreateTexture(0x400, 0x200, &canvas, 0x20);
    field014=5;
    currentItem=0;
    pressedItem=0;
    Apply(static_cast<unsigned char>(currentItem));
}
