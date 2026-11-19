#include <windows.h>
#include <new>
#include "ResultListScene.hpp"

// Source-level scene view supports only independently observed fields.
// The queue has the complete physical five-DWORD VC7 deque boundary.
namespace ResultBitmapF264 { void __cdecl Allocate(int width,int height,void** slot,int depth); }
namespace ResultRecordsF264 { unsigned char __cdecl CheckSelection(unsigned char row,int mode); }
extern const char g_ResultListFileAt00658064[];
extern const char g_ResultListRootAt0065805C[];
ResultListScene::ResultListScene()
{
    canvas=0;
    auxiliaryTexture=0;
    mainTexture=new ResultListTexture();
    mainTexture->AllocateSlots(4);
    mainTexture->Load(g_ResultListFileAt00658064,g_ResultListRootAt0065805C);
    ResultBitmapF264::Allocate(1024,512,reinterpret_cast<void**>(&canvas),32);
    auxiliaryTexture=0;
    (showingRecords)=0;
    (selectedCharacter)=0;
    (difficultyIndex)=0;
    (pageIndex)=0;
    (displayAlpha)=5;
    for (int index=0;index<10;++index)
        (selectableCharacter[index])=ResultRecordsF264::CheckSelection(static_cast<unsigned char>(index),1);
    LoadCharacterTextures();
    BuildCounterPage();
}
