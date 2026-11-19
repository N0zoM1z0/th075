#include <windows.h>
#include <d3d8.h>
#include "ResultListScene.hpp"

ResultListScene::~ResultListScene()
{
    ClearEntries();
    if (auxiliaryTexture) delete auxiliaryTexture;
    if (mainTexture) delete mainTexture;
    if (canvas) canvas->Release();
}
