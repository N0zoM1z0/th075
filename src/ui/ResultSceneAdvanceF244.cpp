#include "engine/SceneTransition.hpp"
#include "replay/ReplayMode.hpp"
#include "battle/BattleResultState.hpp"
#include "engine/FloatConstants.hpp"
#include "battle/PlayerState.hpp"
#include "replay/ReplayRecords.hpp"
#include "battle/BattleSessionState.hpp"
#include "engine/GameSharedState.hpp"
#include "audio/AudioControl.hpp"
#include "graphics/Graphics.hpp"
#include "audio/SoundBank.hpp"
#include <windows.h>
#include "battle/Fighter.hpp"
#include "ui/ResultScene.hpp"
namespace ResultPresentationF244 {
}
unsigned short ResultScene::Update()
{
    PollInput();
    Render();
    Graphics::Present();
    if ((advanceInput)==1) {
        if ((tallyStep)<6) {
            rowSlideX[4]=0;
            rowSlideX[3]=0;
            rowSlideX[2]=0;
            rowSlideX[1]=0;
            rowSlideX[0]=0;
            pendingBonus=values[0];
            pendingBonus=static_cast<int>((pendingBonus)*(comboMultiplier));
            pendingBonus=static_cast<int>((pendingBonus)*(spellTimeMultiplier));
            pendingBonus=static_cast<int>((pendingBonus)*(remainingHealthMultiplier));
            switch (g_OptionsModeAt006714D0) {
            case 0: pendingBonus=static_cast<int>((pendingBonus)*FloatConstants::HalfDouble);break;
            case 1: pendingBonus=static_cast<int>((pendingBonus)*FloatConstants::OneDouble);break;
            case 2: pendingBonus=static_cast<int>((pendingBonus)*FloatConstants::OneAndHalfDouble);break;
            case 3: pendingBonus=static_cast<int>((pendingBonus)*2.0);break;
            }
            g_BattleFightersAt00671418[0]->score+=pendingBonus;
            pendingBonus=0;
            tallyStep=7;
            tallyFrames=400;
        } else if ((tallyStep)==6) {
            g_BattleFightersAt00671418[0]->score+=pendingBonus;
            tallyFrames=400;
            pendingBonus=0;
            tallyStep=7;
        } else {
            if (static_cast<unsigned int>(g_BattleFightersAt00671418[0]->score)>g_MaxCombatScore)
                g_MaxCombatScore=g_BattleFightersAt00671418[0]->score;
            if (g_ReplayModeAt0066C238==ReplayMode::Playback && g_StageAt0067161E>=g_ReplayRecords.fileHeader.recordCount) {
                MusicF204::PlayTrackByIndex(0x28);
                AudioControl407CA0::ScheduleFade(-10000,-160,1,1);
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ReplayBrowser;
            }
            if (g_StoryResultAt00671621) {
                MusicF204::PlayTrackByIndex(0x28);
                AudioControl407CA0::ScheduleFade(-10000,-160,1,1);
                g_StateReturnFlag=-1;
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ReplayNameEntry;
            }
            if ((g_BattleFightersAt00671418[0]->field713)>=8) {
                if (g_ReplayModeAt0066C238==ReplayMode::Playback) {
                    MusicF204::PlayTrackByIndex(0x28);
                    AudioControl407CA0::ScheduleFade(-10000,-160,1,1);
                    return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ReplayBrowser;
                }
                return SceneTransition::WhiteIn | SceneTransition::WhiteOut | SceneId::BattleEnding;
            }
            return SceneTransition::BlackIn | SceneTransition::TilesOut | SceneId::LoadBattle;
        }
    }
    if ((g_BattleFightersAt00671418[0]->field713)==10) {
        backdropScale=1.0f;
    } else if ((backdropScale)>FloatConstants::TwoFifths) {
        backdropScale=(backdropScale)-FloatConstants::OneHundredth;
    } else {
        backdropScale=0.4f;
    }
    if ((rowsAlpha)<255) {
        rowsAlpha=(rowsAlpha)+5;
    } else {
        tallyFrames=(tallyFrames)+1;
        if ((tallyStep)<5 && (rowSlideX[static_cast<int>(tallyStep)])>0)
            rowSlideX[static_cast<int>(tallyStep)]=(rowSlideX[static_cast<int>(tallyStep)])-30;
    }
    switch (tallyFrames) {
    case 30:
        tallyStep=1;
        pendingBonus=(pendingBonus)+(values[0]);
        g_SoundBank->Play(0x2d);
        break;
    case 60:
        tallyStep=2;
        pendingBonus=static_cast<int>((pendingBonus)*(comboMultiplier));
        g_SoundBank->Play(0x2d);
        break;
    case 90:
        tallyStep=3;
        pendingBonus=static_cast<int>((pendingBonus)*(spellTimeMultiplier));
        g_SoundBank->Play(0x2d);
        break;
    case 120:
        tallyStep=4;
        pendingBonus=static_cast<int>((pendingBonus)*(remainingHealthMultiplier));
        g_SoundBank->Play(0x2d);
        break;
    case 180:
        tallyStep=5;
        g_SoundBank->Play(0x28);
        switch (g_OptionsModeAt006714D0) {
        case 0: pendingBonus=static_cast<int>((pendingBonus)*FloatConstants::HalfDouble);break;
        case 1: pendingBonus=static_cast<int>((pendingBonus)*FloatConstants::OneDouble);break;
        case 2: pendingBonus=static_cast<int>((pendingBonus)*FloatConstants::OneAndHalfDouble);break;
        case 3: pendingBonus=static_cast<int>((pendingBonus)*2.0);break;
        }
        break;
    case 300:
        pointsPerFrame=(pendingBonus)/600;
        if ((pointsPerFrame)<1234) pointsPerFrame=1234;
        tallyStep=6;
        break;
    }
    if ((tallyStep)==6) {
        if ((pendingBonus)>(pointsPerFrame)) {
            pendingBonus=(pendingBonus)-(pointsPerFrame);
            g_BattleFightersAt00671418[0]->score+=pointsPerFrame;
            tallySoundCycle=((tallySoundCycle)+1)%3;
            if ((tallySoundCycle)==0)
                g_SoundBank->Play(0x31);
        } else {
            g_BattleFightersAt00671418[0]->score+=pendingBonus;
            pendingBonus=0;
            tallyStep=7;
        }
    }
    return 6;
}
