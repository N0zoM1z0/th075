// The options scene constructor: an 80-byte texture manager and a
// 1024x512 canvas for the option values.
#include <windows.h>
#include <d3d8.h>
#include "OptionsScene.hpp"
#include "GraphicsTexture.hpp"
class OptionsTextureF445 {
    unsigned char observedStorage[80];
public:OptionsTextureF445();void AllocateSlots(int);void LoadArchive(const char*,const char*);
};
typedef char VerifyOptionsTexture80F445[(sizeof(OptionsTextureF445)==80)?1:-1];
extern const char g_OptionsDataPathAt00657D80[];
extern const char g_OptionsArchiveRootAt00657D78[];
OptionsScene::OptionsScene() {
    canvas=0;
    textures=new OptionsTextureF445;
    static_cast<OptionsTextureF445*>(textures)->AllocateSlots(3);
    static_cast<OptionsTextureF445*>(textures)->LoadArchive(g_OptionsDataPathAt00657D80,g_OptionsArchiveRootAt00657D78);
    Graphics::CreateTexture(0x400, 0x200, &canvas, 0x20);
    field014=5;
    currentItem=0;
    pressedItem=0;
    Apply(static_cast<unsigned char>(currentItem));
}
