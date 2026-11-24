#include "BattleSessionState.hpp"
#include "GameSharedState.hpp"
#include "BattleScene.hpp"
#include "PauseDebugF175.hpp"
#include "BattleMode5OptionsF168.hpp"
#include "SelectionInput4388D0.hpp"
#include "GameLeafHelpers.hpp"
#include "FighterHitResponseF164.hpp"

// Reference-only byte views from complete native accesses; no allocation or
// original global identity is established by these provisional names.
extern unsigned char g_RoundSelectionAt006714CE;
// The dword lies in the PE's uninitialized virtual data tail. No file payload
// is asserted; native comparisons/increments/stores establish this used view.
extern unsigned int g_DebugKeyRepeatAt0068D618;


void BattleScene::HandlePauseMenu()
{
    if (g_CombatMode == 5) {
        HandleMode5Options();
    } else {
        if (g_InputMappings[0].held.counts[2] == 1
            || g_InputMappings[1].held.counts[2] == 1) {
            field0A0 = 0;
            g_SoundBank->Play(45);
            switch (field118) {
            case 0:
                if (field018 == 12 && g_ContinueCountAt00671623 > 0) {
                    fighters[0]->field39D = 2;
                    fighters[0]->score = 0;
                    g_ContinueCountAt00671623--;
                    g_ContinueUsedAt00671624 = 1;
                    g_SequenceCounterAt00671622 = 2;
                    field018 = 13;
                    field00C = 299;
                }
                break;
            case 1:
                if (field018 == 12) {
                    g_RoundSelectionAt006714CE = 0;
                    field018 = 14;
                    break;
                }
                field018 = 6;
                break;
            case 2:
                if (field018 == 12) {
                    g_RoundSelectionAt006714CE = 1;
                    field018 = 14;
                } else {
                    field018 = 8;
                }
                break;
            }
        }
        if (field018 != 5 && field018 != 12
            && (g_InputMappings[0].held.counts[3] == 1
                || g_InputMappings[1].held.counts[3] == 1))
            field0A0 = 0;
        if (g_InputMappings[0].held.counts[1] == 1
            || g_InputMappings[1].held.counts[1] == 1) {
            g_SoundBank->Play(39);
            field118++;
        }
        if (g_InputMappings[0].held.counts[1] == -1
            || g_InputMappings[1].held.counts[1] == -1) {
            g_SoundBank->Play(39);
            field118--;
        }
        if (g_ReplayModeAt0066C238 == 2) {
            if (field118 < 0)
                field118 = 1;
            if (field118 > 1)
                field118 = 0;
        }
        if (field018 == 5) {
            if (field118 < 1)
                field118 = 2;
            if (field118 > 2)
                field118 = 1;
        } else if (field018 == 12 && g_ContinueCountAt00671623 == 0) {
            field118 = 1;
        } else if (g_CombatMode == 3
            && (g_ContinueUsedAt00671624 != 0 || field018 == 7)) {
            if (field118 < 0)
                field118 = 1;
            if (field118 > 1)
                field118 = 0;
        } else {
            if (field118 < 0)
                field118 = 2;
            if (field118 > 2)
                field118 = 0;
        }
    }
}

void BattleScene::ProcessDebugKeys()
{
    if (g_InputMappings[0].IsKeyDown(0x3B)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->field52C = (fighters[1]->field52C + 1) % 6;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x3C)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->field52D = (fighters[1]->field52D + 9) % 10;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x3D)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->field52D = (fighters[1]->field52D + 1) % 10;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x3E)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->field52F = (fighters[1]->field52F + 1) % 4;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x3F)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->field52E = (fighters[1]->field52E + 1) % 2;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x40)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->field530 = (fighters[1]->field530 + 1) % 4;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x41)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[1]->field531 = (fighters[1]->field531 + 1) % 2;
        g_DebugKeyRepeatAt0068D618++;
    } else if (g_InputMappings[0].IsKeyDown(0x42)) {
        if (g_DebugKeyRepeatAt0068D618 == 1)
            fighters[0]->field3A0 = 1;
        g_DebugKeyRepeatAt0068D618++;
    } else {
        g_DebugKeyRepeatAt0068D618 = 0;
    }
    fighters[0]->field39D = 2 - fighters[1]->field52C / 3;
    fighters[0]->field398[0] = fighters[1]->field52C % 3;
    fighters[0]->field398[1] = fighters[1]->field52C % 3;
}
