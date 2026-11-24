#include "MusicRoomScene.hpp"
#include "TextureManagerF198.hpp"
#include "MusicCatalogRecordF261.hpp"
#include "GraphicsTexture.hpp"
#include <windows.h>
#include <new>

extern const char g_MusicTextureFileAt00657BF4[] = "data\\system\\music.dat";
extern const char g_MusicTextureRootAt00657BEC[] = "data";
MusicRoomScene::MusicRoomScene()
{
    texture=new TextureManagerF198();
    texture->AllocateUnformattedSlots(2);
    texture->LoadDefault(g_MusicTextureFileAt00657BF4,g_MusicTextureRootAt00657BEC);
    Graphics::CreateTexture(512,512,&canvasA,32);
    Graphics::CreateTexture(1024,1024,&canvasB,32);
    Graphics::CreateTexture(512,32,&canvasC,32);
    Graphics::CreateTexture(512,32,&canvasD,32);
    selectedTrack=0;
    firstVisibleTrack=0;
    LoadCatalog();
    RenderTrackCatalogText();
    RenderSelectedDetails(0);
    RenderSelectedTitle(0);
    inputCooldown=0;
}
