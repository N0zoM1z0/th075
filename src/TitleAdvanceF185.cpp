#include "TitleAdvanceF185.hpp"
#include "MenuInputF184.hpp"
#include "SelectionInput4388D0.hpp"
#include "GameLeafHelpers.hpp"
#include "BattleStateMachine.hpp"
#include "CharacterSequence483350.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>

// Only a slot-2 virtual call. The original owner and base layout are unknown.
class TitleVirtualDrawF185 {
public:
    virtual void UnknownSlot0();
    virtual void UnknownSlot1();
    virtual void DrawMenuFrame();
};
namespace Graphics { void Present(); }
namespace AudioControlF185 { void __cdecl ScheduleFade(long first, long second, unsigned char third, unsigned char fourth); }

extern HWND g_TitleWindowAt00671608;
extern signed char g_TitleAttractSwitchAt00671633;
extern signed char g_TitleRoundOptionAt006714AC[2];
extern signed char g_TitleMiscOptionAt00671610[2];
extern signed char g_TitleOtherOptionAt006714CC[2];

#define FIELD(type, off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (off)))
#define FADE(i) (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + (i) + 0x24))
#define MENU_INDEX FIELD(signed char, 0x38)
#define SIDE_HELD(button, i) (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&g_HeldInputAt00671664) + (i) * 0x48 + (button) * 4))

unsigned short TitleAdvanceF185::Advance()
{
    int i;
    reinterpret_cast<TitleMenuInputF184*>(this)->PollMenuInput();
    reinterpret_cast<TitleVirtualDrawF185*>(this)->DrawMenuFrame();
    Graphics::Present();

    for (i = 0; i < 2; ++i) {
        if (SIDE_HELD(2, i) == 1 && FIELD(unsigned int, 0x0C) < 57000U) {
            g_SelectActiveSideAt006714B8 = static_cast<signed char>(i);
            switch (MENU_INDEX) {
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
                DestroyWindow(g_TitleWindowAt00671608);
                return 2;
            }
        }

        if (SIDE_HELD(3, i) == 1) {
            if (MENU_INDEX == 9) {
                DestroyWindow(g_TitleWindowAt00671608);
                return 2;
            }
            g_SoundBank->Play(40);
            MENU_INDEX = 9;
        }
    }
    if (FIELD(int, 0x1C) == 1) {
        if (MENU_INDEX == 9) {
            DestroyWindow(g_TitleWindowAt00671608);
            return 2;
        }
        g_SoundBank->Play(40);
        MENU_INDEX = 9;
    }
    if (FIELD(int, 0x18) == 1) {
        g_SoundBank->Play(39);
        MENU_INDEX++;
        if (MENU_INDEX > 9)
            MENU_INDEX = 0;
    } else if (FIELD(int, 0x18) == -1) {
        g_SoundBank->Play(39);
        MENU_INDEX--;
        if (MENU_INDEX < 0)
            MENU_INDEX = 9;
    }
    for (i = 0; i < 10; ++i) {
        if (i != MENU_INDEX) {
            if (FADE(i) > 10)
                FADE(i) -= 10;
            else
                FADE(i) = 0;
        } else {
            FADE(i) = FIELD(unsigned char, 0x23);
        }
    }
    if (FIELD(unsigned char, 0x20) < 255)
        FIELD(unsigned char, 0x20) += 10;
    if (FIELD(unsigned char, 0x21) < 255 && FIELD(unsigned char, 0x20) > 150)
        FIELD(unsigned char, 0x21) += 10;
    if (FIELD(unsigned char, 0x22) < 255 && FIELD(unsigned char, 0x21) > 150)
        FIELD(unsigned char, 0x22) += 10;
    if (FIELD(unsigned char, 0x23) < 255 && FIELD(unsigned char, 0x22) > 150)
        FIELD(unsigned char, 0x23) += 10;
    if (FIELD(unsigned int, 0x0C) > 60000U) {
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
        AudioControlF185::ScheduleFade(-10000, -300, 1, 0);
        return 0x2201;
      }
      g_TitleAttractSwitchAt00671633 = 0;
      AudioControlF185::ScheduleFade(-10000, -35, 1, 0);
      return 0x3304;
    }
    FIELD(unsigned int, 0x0C) = timeGetTime() - FIELD(unsigned int, 0x10);
    return 2;
}

#undef SIDE_HELD
#undef MENU_INDEX
#undef FADE
#undef FIELD
