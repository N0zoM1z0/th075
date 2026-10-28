#include "MusicCatalogRecordF261.hpp"
#include <windows.h>
#include <d3d8.h>

// Physically observed scene-boundary and independently verified record
// lifetimes. Original names and the full private scene layout are unknown.
class MusicBaseSceneF263 {
    void* configReference;
public:
    MusicBaseSceneF263();
    virtual ~MusicBaseSceneF263();
};
class MusicTextureF263 {
public:
    ~MusicTextureF263();
};
namespace MusicRoomSoundF263 {
    void __cdecl Stop();
    void __cdecl ReleasePending(int);
    void __cdecl Reset();
}
class MusicRoomReleaseF263 : public MusicBaseSceneF263 {
    MusicTextureF263* texture;
    IDirect3DTexture8* canvasA;
    IDirect3DTexture8* canvasB;
    IDirect3DTexture8* canvasC;
    IDirect3DTexture8* canvasD;
    MusicCatalogRecordF261 records[60];
    signed char trackCount;
    signed char mode;
    signed char flagA;
    signed char flagB;
public:
    MusicRoomReleaseF263();
    virtual ~MusicRoomReleaseF263();
};
MusicRoomReleaseF263::~MusicRoomReleaseF263()
{
    canvasA->Release();
    canvasB->Release();
    canvasC->Release();
    canvasD->Release();
    if (texture)
        delete texture;
    MusicRoomSoundF263::Stop();
    MusicRoomSoundF263::ReleasePending(40);
    MusicRoomSoundF263::Reset();
}
