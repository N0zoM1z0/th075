#include "NameEntryScenes.hpp"
#include "GameProgress.hpp"
#include "Graphics.hpp"
#include "SoundBank.hpp"
extern signed char g_NameEntryExtraFlagAt006714CE;
#define SELECTION_CODE (static_cast<int>(field010)+static_cast<int>(field012)*26)
unsigned short PlayerNameEntryScene::Update()
{
    PollInput();
    if (field016==1) {
        g_SoundBank->Play(0x2d);
        if (SELECTION_CODE==0x5b) {
            if (field014>7)
                selectedRecord->scores[rank].name[7]=100;
            else
                selectedRecord->scores[rank].name[field014]=100;
        } else if (SELECTION_CODE==0x5c) {
            g_GameProgress.SaveScoreFile();
            g_GameProgress.LoadWorkingEightBytes(rank);
            if (g_NameEntryExtraFlagAt006714CE) return 0x2207;
            return 0x2202;
        } else {
            if (field014>7)
                selectedRecord->scores[rank].name[7]=static_cast<unsigned char>(SELECTION_CODE);
            else
                selectedRecord->scores[rank].name[field014]=static_cast<unsigned char>(SELECTION_CODE);
        }
        ++field014;
        if (field014>8)
            field014=8;
        if (field014==8) {
            field010=14;
            field012=3;
        }
    }
    if (field016==2) {
        g_SoundBank->Play(0x28);
        --field014;
        if (field014<0)
            field014=0;
        selectedRecord->scores[rank].name[field014]=100;
    }
    Render();
    Graphics::Present();
    return 10;
}
#undef SELECTION_CODE
