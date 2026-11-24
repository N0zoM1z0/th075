#include "TextureManagerF198.hpp"
#include "MusicCatalogRecordF261.hpp"
#include "GraphicsTexture.hpp"
#include <windows.h>
#include <new>

// This source models only the observed local scene lifetime. The complete
// original game base identity, VTable ownership and renderer APIs are unknown.
class MusicBaseSceneF262 {
    void* configReference;
public:
    MusicBaseSceneF262();
    virtual ~MusicBaseSceneF262();
};
extern const char g_MusicTextureFileAt00657BF4[];
extern const char g_MusicTextureRootAt00657BEC[];
class MusicRoomInitializeF262 : public MusicBaseSceneF262 {
    TextureManagerF198* texture;
    IDirect3DTexture8* canvasA;
    IDirect3DTexture8* canvasB;
    IDirect3DTexture8* canvasC;
    IDirect3DTexture8* canvasD;
    MusicCatalogRecordF261 records[60];
    signed char currentTrack;
    signed char selectionState;
    signed char activeA;
    signed char activeB;
public:
    MusicRoomInitializeF262();
    virtual ~MusicRoomInitializeF262();
    void LoadCatalog();
    void RenderCatalogText();
    void SetupTrack(int);
    void RenderTitle(int);
};
MusicRoomInitializeF262::MusicRoomInitializeF262()
{
    texture=new TextureManagerF198();
    texture->AllocateUnformattedSlots(2);
    texture->LoadDefault(g_MusicTextureFileAt00657BF4,g_MusicTextureRootAt00657BEC);
    Graphics::CreateTexture(512,512,&canvasA,32);
    Graphics::CreateTexture(1024,1024,&canvasB,32);
    Graphics::CreateTexture(512,32,&canvasC,32);
    Graphics::CreateTexture(512,32,&canvasD,32);
    activeA=0;
    activeB=0;
    LoadCatalog();
    RenderCatalogText();
    SetupTrack(0);
    RenderTitle(0);
    selectionState=0;
}
