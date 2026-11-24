#pragma once

#include "SceneBase.hpp"
#include "MusicCatalogRecordF261.hpp"
#include <windows.h>

class TextureManagerF198;
struct IDirect3DTexture8;

class MusicRoomScene : public SceneBase {
public:
    MusicRoomScene();
    virtual ~MusicRoomScene();
    virtual unsigned short Update();
    virtual void Render();

private:
    void PollInput();
    void LoadCatalog();
    void RenderTrackCatalogText();
    void RenderSelectedTitle(signed char selected);
    void RenderSelectedDetails(signed char selected);
    void DrawNumber(float x, float y, DWORD tint, int number, int minDigits);

    TextureManagerF198* texture;
    IDirect3DTexture8* canvasA;
    IDirect3DTexture8* canvasB;
    IDirect3DTexture8* canvasC;
    IDirect3DTexture8* canvasD;
    MusicCatalogRecordF261 records[60];
    signed char trackCount;
    signed char inputCooldown;
    signed char selectedTrack;
    signed char firstVisibleTrack;
};
