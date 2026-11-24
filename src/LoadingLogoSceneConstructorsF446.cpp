#include "LoadingLogoScenes.hpp"
#include "TextureManagerF198.hpp"

extern char g_LoadArchiveRootAt00657B94[];
extern char g_LoadArchivePathAt00657B9C[];
extern char g_LogoArchiveRootAt00657BC0[];
extern char g_LogoArchivePathAt00657BC8[];

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
