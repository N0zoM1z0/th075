#include "engine/SceneTransition.hpp"
#include "replay/ReplayMode.hpp"
#include "ui/NameEntryScenes.hpp"
#include "replay/ReplayRecords.hpp"
#include "battle/BattleSessionState.hpp"
#include "graphics/Graphics.hpp"
#include "audio/SoundBank.hpp"
#define SELECTED (static_cast<int>(glyphColumn)+static_cast<int>(glyphRow)*26)
unsigned short SharedNameEntryScene::Update()
{
    PollInput();
    if (confirmingCancel==0) {
        if (editInput==1) {
            g_SoundBank->Play(0x2d);
            if (SELECTED==0x5b) {
                if (nameCursor>7)
                    g_ReplayRecords.fileHeader.playerName[7]=100;
                else
                    g_ReplayRecords.fileHeader.playerName[nameCursor]=100;
            } else if (SELECTED==0x5c) {
                if (g_ReplayModeAt0066C238==ReplayMode::Recording)
                    g_ReplayRecords.FinalizeFile();
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Title;
            } else {
                if (nameCursor>7)
                    g_ReplayRecords.fileHeader.playerName[7]=static_cast<unsigned char>(SELECTED);
                else
                    g_ReplayRecords.fileHeader.playerName[nameCursor]=static_cast<unsigned char>(SELECTED);
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
            g_ReplayRecords.fileHeader.playerName[nameCursor]=100;
            if (nameCursor<0) {
                confirmingCancel=1;
                nameCursor=0;
            }
        }
    } else if (editInput==1) {
        g_SoundBank->Play(0x2d);
        if (cancelChoice==0) {
            confirmingCancel=0;
            glyphColumn=0;
            glyphRow=0;
        } else {
            return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Title;
        }
    }
    Render();
    Graphics::Present();
    return 7;
}
#undef SELECTED
