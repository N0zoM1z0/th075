#include "AudioControl.hpp"
#include "TitleScene.hpp"
#include "MenuInputF184.hpp"
#include "SelectionInput4388D0.hpp"
#include "GameLeafHelpers.hpp"
#include "BattleStateMachine.hpp"
#include "CharacterSequence483350.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>

// Only a slot-2 virtual call. The original owner and base layout are unknown.
namespace Graphics { void Present(); }

extern HWND g_GameMainWindowAt00671608;
extern signed char g_TitleAttractSwitchAt00671633;
extern signed char g_TitleRoundOptionAt006714AC[2];
extern signed char g_TitleMiscOptionAt00671610[2];
extern signed char g_TitleOtherOptionAt006714CC[2];

#define SIDE_HELD(button, i) (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&g_HeldInputAt00671664) + (i) * 0x48 + (button) * 4))

unsigned short TitleScene::Update()
{
    int i;
    PollMenuInput();
    Render();
    Graphics::Present();

    for (i = 0; i < 2; ++i) {
        if (SIDE_HELD(2, i) == 1 && field00C < 57000U) {
            g_SelectActiveSideAt006714B8 = static_cast<signed char>(i);
            switch (menuIndex) {
            case 0:
                if (i == 0) {
                    g_SoundBank->Play(45);
                    g_CombatMode = 3;
                    return 0x2203;
                }
                break;
            case 1:
                if (i == 0) {
                    g_SoundBank->Play(45);
                    g_CombatMode = 4;
                    return 0x2203;
                }
                break;
            case 2:
                g_SoundBank->Play(45);
                g_CombatMode = 2;
                return 0x2203;
            case 3:
                g_SoundBank->Play(45);
                g_CombatMode = 1;
                return 0x2203;
            case 4:
                if (i == 0) {
                    g_SoundBank->Play(45);
                    g_CombatMode = 5;
                    return 0x2203;
                }
                break;
            case 5:
                g_SoundBank->Play(45);
                g_SelectActiveSideAt006714B8 = 0;
                return 0x2205;
            case 6:
                g_SoundBank->Play(45);
                return 0x220C;
            case 7:
                g_SoundBank->Play(45);
                return 0x220E;
            case 8:
                g_SoundBank->Play(45);
                return 0x2209;
            case 9:
                DestroyWindow(g_GameMainWindowAt00671608);
                return 2;
            }
        }

        if (SIDE_HELD(3, i) == 1) {
            if (menuIndex == 9) {
                DestroyWindow(g_GameMainWindowAt00671608);
                return 2;
            }
            g_SoundBank->Play(40);
            menuIndex = 9;
        }
    }
    if (field01C == 1) {
        if (menuIndex == 9) {
            DestroyWindow(g_GameMainWindowAt00671608);
            return 2;
        }
        g_SoundBank->Play(40);
        menuIndex = 9;
    }
    if (field018 == 1) {
        g_SoundBank->Play(39);
        menuIndex++;
        if (menuIndex > 9)
            menuIndex = 0;
    } else if (field018 == -1) {
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
            itemAlpha[i] = field023;
        }
    }
    if (field020 < 255)
        field020 += 10;
    if (field021 < 255 && field020 > 150)
        field021 += 10;
    if (field022 < 255 && field021 > 150)
        field022 += 10;
    if (field023 < 255 && field022 > 150)
        field023 += 10;
    if (field00C > 60000U) {
      if (!g_TitleAttractSwitchAt00671633) {
        for (i = 0; i < 2; ++i) {
            g_StatePlayerIds[i] = static_cast<signed char>(rand() % 6);
            g_TitleRoundOptionAt006714AC[i] = 0;
            g_TitleMiscOptionAt00671610[i] = static_cast<signed char>(rand() % 3);
            g_TitleOtherOptionAt006714CC[i] = static_cast<signed char>(rand() % 3);
        }
        if (g_StatePlayerIds[0] == g_StatePlayerIds[1])
            g_StatePlayerIds[1] = static_cast<signed char>((g_StatePlayerIds[1] + 1) % 6);
        g_SequenceStageAt0067161D = static_cast<unsigned char>(rand() % 6 + (rand() % 2) * 10);
        g_CombatMode = 6;
        ++g_TitleAttractSwitchAt00671633;
        AudioControl407CA0::ScheduleFade(-10000, -300, 1, 0);
        return 0x2201;
      }
      g_TitleAttractSwitchAt00671633 = 0;
      AudioControl407CA0::ScheduleFade(-10000, -35, 1, 0);
      return 0x3304;
    }
    field00C = timeGetTime() - field010;
    return 2;
}

#undef SIDE_HELD
