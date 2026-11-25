#include "engine/SceneTransition.hpp"
#include "replay/ReplayMode.hpp"
#include "ui/NameEntryScenes.hpp"
#include "replay/ReplayRecords.hpp"
#include "battle/BattleSessionState.hpp"
#include "graphics/Graphics.hpp"
#include "audio/SoundBank.hpp"
#define SELECTED (static_cast<int>(field00E)+static_cast<int>(field010)*26)
unsigned short SharedNameEntryScene::Update()
{
    PollInput();
    if (field00C==0) {
        if (field016==1) {
            g_SoundBank->Play(0x2d);
            if (SELECTED==0x5b) {
                if (field012>7)
                    g_ReplayRecords.fileHeader.playerName[7]=100;
                else
                    g_ReplayRecords.fileHeader.playerName[field012]=100;
            } else if (SELECTED==0x5c) {
                if (g_ReplayModeAt0066C238==ReplayMode::Recording)
                    g_ReplayRecords.FinalizeFile();
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Title;
            } else {
                if (field012>7)
                    g_ReplayRecords.fileHeader.playerName[7]=static_cast<unsigned char>(SELECTED);
                else
                    g_ReplayRecords.fileHeader.playerName[field012]=static_cast<unsigned char>(SELECTED);
            }
            ++field012;
            if (field012>8)
                field012=8;
            if (field012==8) {
                field00E=14;
                field010=3;
            }
        }
        if (field016==2) {
            g_SoundBank->Play(0x28);
            --field012;
            g_ReplayRecords.fileHeader.playerName[field012]=100;
            if (field012<0) {
                field00C=1;
                field012=0;
            }
        }
    } else if (field016==1) {
        g_SoundBank->Play(0x2d);
        if (field014==0) {
            field00C=0;
            field00E=0;
            field010=0;
        } else {
            return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Title;
        }
    }
    Render();
    Graphics::Present();
    return 7;
}
#undef SELECTED
