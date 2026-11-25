#include "engine/SceneTransition.hpp"
#include "input/InputControl.hpp"
#include "battle/CombatMode.hpp"
#include "battle/PlayerState.hpp"
#include "engine/GameSharedState.hpp"
#include "audio/AudioControl.hpp"
#include "ui/TitleScene.hpp"
#include "ui/MenuInputF184.hpp"
#include "ui/SelectionInput4388D0.hpp"
#include "engine/GameLeafHelpers.hpp"
#include "battle/BattleStateMachine.hpp"
#include "characters/CharacterSequence483350.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>

// Only a slot-2 virtual call. The original owner and base layout are unknown.
namespace Graphics { void Present(); }

extern HWND g_GameMainWindowAt00671608;
signed char g_TitleAttractSwitchAt00671633;

#define SIDE_HELD(button, i) g_InputMappings[i].held.counts[button]

unsigned short TitleScene::Update()
{
    int i;
    PollMenuInput();
    Render();
    Graphics::Present();

    for (i = 0; i < 2; ++i) {
        if (SIDE_HELD(InputControl::ButtonA, i) == 1 && elapsedMs < 57000U) {
            g_SelectedSideAt006714B8 = static_cast<signed char>(i);
            switch (menuIndex) {
            case 0:
                if (i == 0) {
                    g_SoundBank->Play(45);
                    g_CombatMode = CombatMode::Story;
                    return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::CharacterSelect;
                }
                break;
            case 1:
                if (i == 0) {
                    g_SoundBank->Play(45);
                    g_CombatMode = CombatMode::Arcade;
                    return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::CharacterSelect;
                }
                break;
            case 2:
                g_SoundBank->Play(45);
                g_CombatMode = CombatMode::DuelHuman;
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::CharacterSelect;
            case 3:
                g_SoundBank->Play(45);
                g_CombatMode = CombatMode::DuelCpu;
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::CharacterSelect;
            case 4:
                if (i == 0) {
                    g_SoundBank->Play(45);
                    g_CombatMode = CombatMode::Practice;
                    return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::CharacterSelect;
                }
                break;
            case 5:
                g_SoundBank->Play(45);
                g_SelectedSideAt006714B8 = 0;
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::ReplayBrowser;
            case 6:
                g_SoundBank->Play(45);
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::MusicRoom;
            case 7:
                g_SoundBank->Play(45);
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::RecordBrowser;
            case 8:
                g_SoundBank->Play(45);
                return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::Options;
            case 9:
                DestroyWindow(g_GameMainWindowAt00671608);
                return 2;
            }
        }

        if (SIDE_HELD(InputControl::ButtonB, i) == 1) {
            if (menuIndex == 9) {
                DestroyWindow(g_GameMainWindowAt00671608);
                return 2;
            }
            g_SoundBank->Play(40);
            menuIndex = 9;
        }
    }
    if (escapeHeldFrames == 1) {
        if (menuIndex == 9) {
            DestroyWindow(g_GameMainWindowAt00671608);
            return 2;
        }
        g_SoundBank->Play(40);
        menuIndex = 9;
    }
    if (verticalInput == 1) {
        g_SoundBank->Play(39);
        menuIndex++;
        if (menuIndex > 9)
            menuIndex = 0;
    } else if (verticalInput == -1) {
        g_SoundBank->Play(39);
        menuIndex--;
        if (menuIndex < 0)
            menuIndex = 9;
    }
    for (i = 0; i < 10; ++i) {
        if (i != menuIndex) {
            if (itemAlpha[i] > 10)
                itemAlpha[i] -= 10;
            else
                itemAlpha[i] = 0;
        } else {
            itemAlpha[i] = menuAlpha;
        }
    }
    if (backgroundAlpha < 255)
        backgroundAlpha += 10;
    if (logoAlpha < 255 && backgroundAlpha > 150)
        logoAlpha += 10;
    if (footerAlpha < 255 && logoAlpha > 150)
        footerAlpha += 10;
    if (menuAlpha < 255 && footerAlpha > 150)
        menuAlpha += 10;
    if (elapsedMs > 60000U) {
      if (!g_TitleAttractSwitchAt00671633) {
        for (i = 0; i < 2; ++i) {
            g_PlayerIdAt006714C8[i] = static_cast<signed char>(rand() % 6);
            g_PlayerRoundAt006714AC[i] = 0;
            g_PlayerAltAt00671610[i] = static_cast<signed char>(rand() % 3);
            g_PlayerOtherAt006714CC[i] = static_cast<signed char>(rand() % 3);
        }
        if (g_PlayerIdAt006714C8[0] == g_PlayerIdAt006714C8[1])
            g_PlayerIdAt006714C8[1] = static_cast<signed char>((g_PlayerIdAt006714C8[1] + 1) % 6);
        g_StageSelectionAt0067161D = static_cast<unsigned char>(rand() % 6 + (rand() % 2) * 10);
        g_CombatMode = CombatMode::Attract;
        ++g_TitleAttractSwitchAt00671633;
        AudioControl407CA0::ScheduleFade(-10000, -300, 1, 0);
        return SceneTransition::BlackIn | SceneTransition::BlackOut | SceneId::LoadBattle;
      }
      g_TitleAttractSwitchAt00671633 = 0;
      AudioControl407CA0::ScheduleFade(-10000, -35, 1, 0);
      return SceneTransition::TilesIn | SceneTransition::TilesOut | SceneId::Logo;
    }
    elapsedMs = timeGetTime() - openedAtMs;
    return 2;
}

#undef SIDE_HELD
