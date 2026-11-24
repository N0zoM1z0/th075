#include "TextureManagerF198.hpp"
#include <windows.h>
#include <new>
#include "ResultListScene.hpp"
#include "GraphicsTexture.hpp"
#include "GameProgress.hpp"

extern const char g_ResultListFileAt00658064[];
extern const char g_ResultListRootAt0065805C[];
ResultListScene::ResultListScene()
{
    canvas=0;
    auxiliaryTexture=0;
    mainTexture=new TextureManagerF198();
    mainTexture->AllocateUnformattedSlots(4);
    mainTexture->LoadDefault(g_ResultListFileAt00658064,g_ResultListRootAt0065805C);
    Graphics::CreateTexture(1024, 512, &canvas, 32);
    auxiliaryTexture=0;
    (showingRecords)=0;
    (selectedCharacter)=0;
    (difficultyIndex)=0;
    (pageIndex)=0;
    (displayAlpha)=5;
    for (int index=0;index<10;++index)
        (selectableCharacter[index])=GameProgressF203::CheckSelection(static_cast<signed char>(index),1);
    LoadSelectedCharacterResources();
    BuildCounterPage();
}
