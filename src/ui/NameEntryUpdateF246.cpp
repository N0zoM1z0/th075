#include "engine/SceneTransition.hpp"
#include "battle/BattleResultState.hpp"
#include "ui/NameEntryScenes.hpp"
#include "engine/GameProgress.hpp"
#include "graphics/Graphics.hpp"
#include "audio/SoundBank.hpp"
#define SELECTION_CODE (static_cast<int>(glyphColumn)+static_cast<int>(glyphRow)*26)
unsigned short PlayerNameEntryScene::Update()
{
    PollInput();
    if (editInput==1) {
        g_SoundBank->Play(0x2d);
        if (SELECTION_CODE==0x5b) {
            if (nameCursor>7)
                selectedRecord->scores[rank].name[7]=100;
            else
                selectedRecord->scores[rank].name[nameCursor]=100;
        } else if (SELECTION_CODE==0x5c) {
            g_GameProgress.SaveScoreFile();
            g_GameProgress.CopyRankNameToWorking(rank);
            if (g_StateReturnFlag) return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ReplayNameEntry;
            return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Title;
        } else {
            if (nameCursor>7)
                selectedRecord->scores[rank].name[7]=static_cast<unsigned char>(SELECTION_CODE);
            else
                selectedRecord->scores[rank].name[nameCursor]=static_cast<unsigned char>(SELECTION_CODE);
        }
        ++nameCursor;
        if (nameCursor>8)
            nameCursor=8;
        if (nameCursor==8) {
            glyphColumn=14;
            glyphRow=3;
        }
    }
    if (editInput==2) {
        g_SoundBank->Play(0x28);
        --nameCursor;
        if (nameCursor<0)
            nameCursor=0;
        selectedRecord->scores[rank].name[nameCursor]=100;
    }
    Render();
    Graphics::Present();
    return 10;
}
#undef SELECTION_CODE
