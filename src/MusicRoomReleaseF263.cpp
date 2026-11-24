#include "MusicRoomScene.hpp"
#include "TextureManagerF198.hpp"
#include "AudioControl.hpp"
#include "MusicCatalogRecordF261.hpp"
#include <windows.h>
#include <d3d8.h>

MusicRoomScene::~MusicRoomScene()
{
    canvasA->Release();
    canvasB->Release();
    canvasC->Release();
    canvasD->Release();
    if (texture)
        delete texture;
    AudioControl407CA0::Stop();
    MusicF204::PlayTrackByIndex(40);
    MusicF205::ScheduleTransitionFade();
}
