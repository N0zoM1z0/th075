#include "LoadingLogoScenes.hpp"
#include "TextureManagerF198.hpp"

extern const char g_LoadArchiveRootAt00657B94[] = "data";
extern const char g_LoadArchivePathAt00657B9C[] = "data\\system\\load.dat";
extern const char g_LogoArchiveRootAt00657BC0[] = "data";
extern const char g_LogoArchivePathAt00657BC8[] = "data\\system\\logo.dat";

LoadingScene::LoadingScene() {
    texture=new TextureManagerF198;
    texture->AllocateUnformattedSlots(1);
    texture->LoadDefault(g_LoadArchivePathAt00657B9C,g_LoadArchiveRootAt00657B94);
    loaded=0;
}
LogoScene::LogoScene() {
    texture=new TextureManagerF198;
    texture->AllocateUnformattedSlots(1);
    texture->LoadDefault(g_LogoArchivePathAt00657BC8,g_LogoArchiveRootAt00657BC0);
    elapsedFrames=0;
}
