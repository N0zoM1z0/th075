#include "MusicCatalogRecordF261.hpp"
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
class MusicTextureManagerF262 {
    unsigned char physicalBytes[80];
public:
    MusicTextureManagerF262();
    void AllocateUnformattedSlots(int slots);
    void LoadDefault(const char* filename, const char* root);
};
typedef char AssertMusicTexSizeF262[(sizeof(MusicTextureManagerF262)==80)?1:-1];
extern const char g_MusicTextureFileAt00657BF4[];
extern const char g_MusicTextureRootAt00657BEC[];
namespace MusicSurfaceF262 { void __cdecl Allocate(int width,int height,void** resource,int depth); }
class MusicRoomInitializeF262 : public MusicBaseSceneF262 {
    MusicTextureManagerF262* texture;
    void* canvasA;
    void* canvasB;
    void* canvasC;
    void* canvasD;
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
    texture=new MusicTextureManagerF262();
    texture->AllocateUnformattedSlots(2);
    texture->LoadDefault(g_MusicTextureFileAt00657BF4,g_MusicTextureRootAt00657BEC);
    MusicSurfaceF262::Allocate(512,512,&canvasA,32);
    MusicSurfaceF262::Allocate(1024,1024,&canvasB,32);
    MusicSurfaceF262::Allocate(512,32,&canvasC,32);
    MusicSurfaceF262::Allocate(512,32,&canvasD,32);
    activeA=0;
    activeB=0;
    LoadCatalog();
    RenderCatalogText();
    SetupTrack(0);
    RenderTitle(0);
    selectionState=0;
}
