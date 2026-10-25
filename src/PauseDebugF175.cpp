#include "PauseDebugF175.hpp"
#include "BattleMode5OptionsF168.hpp"
#include "SelectionInput4388D0.hpp"
#include "GameLeafHelpers.hpp"
#include "FighterHitResponseF164.hpp"

extern unsigned char g_SequenceCounterAt00671622;
// Reference-only byte views from complete native accesses; no allocation or
// original global identity is established by these provisional names.
extern signed char g_ContinueCountAt00671623;
extern unsigned char g_ContinueUsedAt00671624;
extern unsigned char g_RoundSelectionAt006714CE;
// The dword lies in the PE's uninitialized virtual data tail. No file payload
// is asserted; native comparisons/increments/stores establish this used view.
extern unsigned int g_DebugKeyRepeatAt0068D618;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FIRST(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x44) + (offset)))
#define SECOND(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x48) + (offset)))

void PauseDebugF175::HandlePauseMenu()
{
    if (g_CombatMode == 5) {
        reinterpret_cast<BattleMode5OptionsF168*>(this)->HandleMode5Options();
    } else {
        if (g_HeldInputAt00671664.counts[2] == 1
            || g_HeldInputAt006716AC.counts[2] == 1) {
            FIELD(unsigned char, 0xA0) = 0;
            g_SoundBank->Play(45);
            switch (FIELD(signed char, 0x118)) {
            case 0:
                if (FIELD(signed char, 0x18) == 12 && g_ContinueCountAt00671623 > 0) {
                    FIRST(signed char, 0x39D) = 2;
                    FIRST(unsigned long, 0x2D0) = 0;
                    g_ContinueCountAt00671623--;
                    g_ContinueUsedAt00671624 = 1;
                    g_SequenceCounterAt00671622 = 2;
                    FIELD(unsigned char, 0x18) = 13;
                    FIELD(int, 0xC) = 299;
                }
                break;
            case 1:
                if (FIELD(signed char, 0x18) == 12) {
                    g_RoundSelectionAt006714CE = 0;
                    FIELD(unsigned char, 0x18) = 14;
                    break;
                }
                FIELD(unsigned char, 0x18) = 6;
                break;
            case 2:
                if (FIELD(signed char, 0x18) == 12) {
                    g_RoundSelectionAt006714CE = 1;
                    FIELD(unsigned char, 0x18) = 14;
                } else {
                    FIELD(unsigned char, 0x18) = 8;
                }
                break;
            }
        }
        if (FIELD(signed char, 0x18) != 5 && FIELD(signed char, 0x18) != 12
            && (g_HeldInputAt00671664.counts[3] == 1
                || g_HeldInputAt006716AC.counts[3] == 1))
            FIELD(unsigned char, 0xA0) = 0;
        if (g_HeldInputAt00671664.counts[1] == 1
            || g_HeldInputAt006716AC.counts[1] == 1) {
            g_SoundBank->Play(39);
            FIELD(signed char, 0x118)++;
        }
        if (g_HeldInputAt00671664.counts[1] == -1
            || g_HeldInputAt006716AC.counts[1] == -1) {
            g_SoundBank->Play(39);
            FIELD(signed char, 0x118)--;
        }
        if (g_InputReplayModeAt0066C238 == 2) {
            if (FIELD(signed char, 0x118) < 0)
                FIELD(signed char, 0x118) = 1;
            if (FIELD(signed char, 0x118) > 1)
                FIELD(signed char, 0x118) = 0;
        }
        if (FIELD(signed char, 0x18) == 5) {
            if (FIELD(signed char, 0x118) < 1)
                FIELD(signed char, 0x118) = 2;
            if (FIELD(signed char, 0x118) > 2)
                FIELD(signed char, 0x118) = 1;
        } else if (FIELD(signed char, 0x18) == 12 && g_ContinueCountAt00671623 == 0) {
            FIELD(signed char, 0x118) = 1;
        } else if (g_CombatMode == 3
            && (g_ContinueUsedAt00671624 != 0 || FIELD(signed char, 0x18) == 7)) {
            if (FIELD(signed char, 0x118) < 0)
                FIELD(signed char, 0x118) = 1;
            if (FIELD(signed char, 0x118) > 1)
                FIELD(signed char, 0x118) = 0;
        } else {
            if (FIELD(signed char, 0x118) < 0)
                FIELD(signed char, 0x118) = 2;
            if (FIELD(signed char, 0x118) > 2)
                FIELD(signed char, 0x118) = 0;
        }
    }
}

void PauseDebugF175::ProcessDebugKeys()
{
    if (g_InputMappingAt00671638.IsKeyDown(0x3B)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            SECOND(signed char, 0x52C) = (SECOND(signed char, 0x52C) + 1) % 6;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappingAt00671638.IsKeyDown(0x3C)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            SECOND(signed char, 0x52D) = (SECOND(signed char, 0x52D) + 9) % 10;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappingAt00671638.IsKeyDown(0x3D)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            SECOND(signed char, 0x52D) = (SECOND(signed char, 0x52D) + 1) % 10;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappingAt00671638.IsKeyDown(0x3E)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            SECOND(signed char, 0x52F) = (SECOND(signed char, 0x52F) + 1) % 4;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappingAt00671638.IsKeyDown(0x3F)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            SECOND(signed char, 0x52E) = (SECOND(signed char, 0x52E) + 1) % 2;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappingAt00671638.IsKeyDown(0x40)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            SECOND(signed char, 0x530) = (SECOND(signed char, 0x530) + 1) % 4;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappingAt00671638.IsKeyDown(0x41)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            SECOND(signed char, 0x531) = (SECOND(signed char, 0x531) + 1) % 2;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappingAt00671638.IsKeyDown(0x42)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            FIRST(short, 0x3A0) = 1;
        g_DebugKeyRepeatAt0068D618++;
    } else {
        g_DebugKeyRepeatAt0068D618 = 0;
    }
    FIRST(signed char, 0x39D) = 2 - SECOND(signed char, 0x52C) / 3;
    FIRST(short, 0x398) = SECOND(signed char, 0x52C) % 3;
    FIRST(short, 0x39A) = SECOND(signed char, 0x52C) % 3;
}

#undef SECOND
#undef FIRST
#undef FIELD
