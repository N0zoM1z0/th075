#include "ui/MusicRoomScene.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "audio/AudioControl.hpp"
#include "audio/MusicCatalogRecordF261.hpp"
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
