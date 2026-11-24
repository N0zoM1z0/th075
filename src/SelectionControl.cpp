#include "PlayerState.hpp"
#include "GameSharedState.hpp"
#include "GameProgress.hpp"
#include "SelectionInput4388D0.hpp"
#include "SoundBank.hpp"
#include "CharacterSelectScene.hpp"
#include "BattleSessionState.hpp"
#include "ReplaySegmentedQueueF219.hpp"
#include "Fighter.hpp"
#include <stdlib.h>

// Pointer-only interfaces. No complete scene/fighter/container layout is claimed.
int __cdecl AbsoluteSelectionInputF130(int);
void CharacterSelectScene::UpdateSelect(signed char side) {
    if (portraitReturn[side] > 0.0f) portraitReturn[side] = portraitReturn[side] - 5.0f;
    if (portraitEnterX[side] > 0.0f) portraitEnterX[side] = portraitEnterX[side] - 4.0f;
    if (portraitEnterY[side] > 0.0f) portraitEnterY[side] = portraitEnterY[side] - 2.0f;
    if (portraitExitX[side] > 0.0f) portraitExitX[side] = portraitExitX[side] - 4.0f;
    if (portraitExitY[side] > 0.0f) portraitExitY[side] = portraitExitY[side] - 2.0f;
    else (playerReady[side]) = 0;
    if (choiceStop[side] > 0.0f) choiceStop[side] = choiceStop[side] - 1.0f;
    if (choiceStop[side] == 60.0f) choiceStop[side] = 0;
    if (AbsoluteSelectionInputF130((input[side].horizontal)) == 1 || AbsoluteSelectionInputF130((input[side].horizontal)) % 15 == 1 || (stageCountdown[side]) > 0) {
        if ((stageCountdown[side]) == 0) g_SoundBank->Play(39);
        portraitReturn[side] = 100.0f;
        portraitFade[side] = 100.0f;
        portraitEnterX[side] = 80.0f;
        portraitEnterY[side] = 40.0f;
        portraitExitX[side] = 80.0f;
        portraitExitY[side] = 40.0f;
        (alternateCharacter[side]) = (chosenCharacter[side]);
        if ((input[side].horizontal) > 0) {
            ++(chosenCharacter[side]);
            if (g_CombatMode == 3) {
                if ((chosenCharacter[side]) == 6 && (rightCharacterAvailable[chosenCharacter[side]]) == 0) ++(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 7 && (rightCharacterAvailable[chosenCharacter[side]]) == 0) ++(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 8 && (rightCharacterAvailable[chosenCharacter[side]]) == 0) ++(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 9 && (rightCharacterAvailable[chosenCharacter[side]]) == 0) ++(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 10 && (rightCharacterAvailable[chosenCharacter[side]]) == 0) ++(chosenCharacter[side]);
            } else {
                if ((chosenCharacter[side]) == 6 && (leftCharacterAvailable[chosenCharacter[side]]) == 0) ++(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 7 && (leftCharacterAvailable[chosenCharacter[side]]) == 0) ++(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 8 && (leftCharacterAvailable[chosenCharacter[side]]) == 0) ++(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 9 && (leftCharacterAvailable[chosenCharacter[side]]) == 0) ++(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 10 && (leftCharacterAvailable[chosenCharacter[side]]) == 0) ++(chosenCharacter[side]);
            }
            if ((chosenCharacter[side]) >= 11) (chosenCharacter[side]) = 0;
        } else {
            --(chosenCharacter[side]);
            if ((chosenCharacter[side]) < 0) (chosenCharacter[side]) = 10;
            if (g_CombatMode == 3) {
                if ((chosenCharacter[side]) == 10 && (rightCharacterAvailable[chosenCharacter[side]]) == 0) --(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 9 && (rightCharacterAvailable[chosenCharacter[side]]) == 0) --(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 8 && (rightCharacterAvailable[chosenCharacter[side]]) == 0) --(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 7 && (rightCharacterAvailable[chosenCharacter[side]]) == 0) --(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 6 && (rightCharacterAvailable[chosenCharacter[side]]) == 0) --(chosenCharacter[side]);
            } else {
                if ((chosenCharacter[side]) == 10 && (leftCharacterAvailable[chosenCharacter[side]]) == 0) --(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 9 && (leftCharacterAvailable[chosenCharacter[side]]) == 0) --(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 8 && (leftCharacterAvailable[chosenCharacter[side]]) == 0) --(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 7 && (leftCharacterAvailable[chosenCharacter[side]]) == 0) --(chosenCharacter[side]);
                if ((chosenCharacter[side]) == 6 && (leftCharacterAvailable[chosenCharacter[side]]) == 0) --(chosenCharacter[side]);
            }
        }
        g_GameProgress.SetSelection(chosenCharacter[0], g_OptionsModeAt006714D0);
    }
    if ((input[side].confirm) == 1 || (input[side].toggle) == 1 || (stageCountdown[side]) == 1) {
        g_SoundBank->Play(45);
        g_PlayerIdAt006714C8[side] = (chosenCharacter[side]);
        g_PlayerRoundAt006714AC[side] = (input[side].toggle) == 1;
        (playerState[side]) = 1;
        choiceStop[side] = 0;
        if (g_CombatMode != 4 && (playerState[1 - side]) != 0 && g_PlayerIdAt006714C8[0] == g_PlayerIdAt006714C8[1] && g_PlayerRoundAt006714AC[side] == g_PlayerRoundAt006714AC[1 - side])
            g_PlayerRoundAt006714AC[side] = 1 - g_PlayerRoundAt006714AC[side];
        if (g_CombatMode == 3) {
            g_PlayerRoundAt006714AC[0] = 0;
            g_PlayerRoundAt006714AC[1] = 0;
        }
    }
    if ((input[side].special) == 1) (stageCountdown[side]) = rand() % 10 + 30;
    if ((stageCountdown[side]) > 0) --(stageCountdown[side]);
    if ((input[side].alternative) == 1) {
        if (g_GameProgress.GetSelectedValue() > 0 && g_CombatMode == 3) {
            g_SoundBank->Play(45);
            (optionsOpen[side]) = !(optionsOpen[side]);
        }
        if (g_CombatMode != 3 && g_CombatMode != 5) {
            g_SoundBank->Play(45);
            (optionsOpen[side]) = !(optionsOpen[side]);
        }
    }
}

void Fighter::UpdateControls() {
    unsigned char relativeBits = 0;
    unsigned char physicalInputBits = 0;
    if (field2CD != 0) {
        ClearAuxiliaryWords();
        inputX = 0;
        inputY = 0;
        inputA = 0;
        inputB = 0;
        inputC = 0;
        inputD = 0;
        aiCommand = 0;
        if (g_ReplayModeAt0066C238 == 2) {
            if (g_ReplayRecords.byteInputs.size() > 0) { relativeBits = g_ReplayRecords.byteInputs.front(); g_ReplayRecords.byteInputs.pop_front(); }
            if (g_ReplayRecords.secondaryInputs.size() > 0) { aiCommand = g_ReplayRecords.secondaryInputs.front(); g_ReplayRecords.secondaryInputs.pop_front(); }
            if (g_ReplayRecords.wordInputs.size() > 0) { aiCardTimer = g_ReplayRecords.wordInputs.front(); g_ReplayRecords.wordInputs.pop_front(); }
            if (relativeBits & 0x1) inputX = -1;
            if (relativeBits & 0x2) inputX = 1;
            if (relativeBits & 0x4) inputY = -1;
            if (relativeBits & 0x8) inputY = 1;
            if (relativeBits & 0x10) inputA = 1;
            if (relativeBits & 0x20) inputB = 1;
            if (relativeBits & 0x40) inputC = 1;
            if (relativeBits & 0x80) inputD = 1;
        } else if (g_ReplayModeAt0066C238 == 1) {
            if (g_CombatMode == 3) ChooseCardAction();
            else if (g_CombatMode == 5) ApplyMode5Direction();
            else ChooseAction();
            if (g_OptionsModeAt006714D0 < 2 && rand() > (g_OptionsModeAt006714D0 * 3 + 1) * 2048) {
                inputA = 0;
                inputB = 0;
                inputC = 0;
                inputD = 0;
                aiCommand = 0;
            }
            if (inputA != 0) inputA = 1;
            if (inputB != 0) inputB = 1;
            if (inputC != 0) inputC = 1;
            if (inputD != 0) inputD = 1;
            relativeBits = inputX < 0;
            relativeBits |= static_cast<unsigned char>(inputX > 0) << 1;
            relativeBits |= static_cast<unsigned char>(inputY < 0) << 2;
            relativeBits |= static_cast<unsigned char>(inputY > 0) << 3;
            relativeBits |= static_cast<unsigned char>(static_cast<unsigned int>(inputA) > 0) << 4;
            relativeBits |= static_cast<unsigned char>(static_cast<unsigned int>(inputB) > 0) << 5;
            relativeBits |= static_cast<unsigned char>(static_cast<unsigned int>(inputC) > 0) << 6;
            relativeBits |= static_cast<unsigned char>(static_cast<unsigned int>(inputD) > 0) << 7;
            g_ReplayRecords.byteInputs.push_back(relativeBits);
            g_ReplayRecords.secondaryInputs.push_back(aiCommand);
            g_ReplayRecords.wordInputs.push_back(aiCardTimer);
        }
    } else {
        if (g_ReplayModeAt0066C238 == 2) {
            if (g_ReplayRecords.byteInputs.size() > 0) { physicalInputBits = g_ReplayRecords.byteInputs.front(); g_ReplayRecords.byteInputs.pop_front(); }
            if (physicalInputBits & 0x1) {
                if (inputBindings.held.counts[0] > 0) inputBindings.held.counts[0] = 0;
                inputBindings.held.counts[0] = inputBindings.held.counts[0] - 1;
            } else if (physicalInputBits & 0x2) {
                if (inputBindings.held.counts[0] < 0) inputBindings.held.counts[0] = 0;
                inputBindings.held.counts[0] = inputBindings.held.counts[0] + 1;
            } else inputBindings.held.counts[0] = 0;
            if (physicalInputBits & 0x4) {
                if (inputBindings.held.counts[1] > 0) inputBindings.held.counts[1] = 0;
                inputBindings.held.counts[1] = inputBindings.held.counts[1] - 1;
            } else if (physicalInputBits & 0x8) {
                if (inputBindings.held.counts[1] < 0) inputBindings.held.counts[1] = 0;
                inputBindings.held.counts[1] = inputBindings.held.counts[1] + 1;
            } else inputBindings.held.counts[1] = 0;
            if (physicalInputBits & 0x10) inputBindings.held.counts[2] = inputBindings.held.counts[2] + 1;
            else inputBindings.held.counts[2] = 0;
            if (physicalInputBits & 0x20) inputBindings.held.counts[3] = inputBindings.held.counts[3] + 1;
            else inputBindings.held.counts[3] = 0;
            if (physicalInputBits & 0x40) inputBindings.held.counts[4] = inputBindings.held.counts[4] + 1;
            else inputBindings.held.counts[4] = 0;
            if (physicalInputBits & 0x80) inputBindings.held.counts[5] = inputBindings.held.counts[5] + 1;
            else inputBindings.held.counts[5] = 0;
            inputX = inputBindings.held.counts[0];
            inputY = inputBindings.held.counts[1];
            inputA = inputBindings.held.counts[2];
            inputB = inputBindings.held.counts[3];
            inputC = inputBindings.held.counts[4];
            inputD = inputBindings.held.counts[5];
            relativeBits = facing * inputX < 0;
            relativeBits |= static_cast<unsigned char>(facing * inputX > 0) << 1;
            relativeBits |= static_cast<unsigned char>(inputY < 0) << 2;
            relativeBits |= static_cast<unsigned char>(inputY > 0) << 3;
            relativeBits |= static_cast<unsigned char>(inputA == 1) << 4;
            relativeBits |= static_cast<unsigned char>(inputB == 1) << 5;
            relativeBits |= static_cast<unsigned char>(inputC == 1) << 6;
            relativeBits |= static_cast<unsigned char>(inputD == 1) << 7;
        } else {
            inputBindings.UpdateHeldCounts();
            inputX = inputBindings.held.counts[0];
            inputY = inputBindings.held.counts[1];
            inputA = inputBindings.held.counts[2];
            inputB = inputBindings.held.counts[3];
            inputC = inputBindings.held.counts[4];
            inputD = inputBindings.held.counts[5];
            relativeBits = facing * inputX < 0;
            relativeBits |= static_cast<unsigned char>(facing * inputX > 0) << 1;
            relativeBits |= static_cast<unsigned char>(inputY < 0) << 2;
            relativeBits |= static_cast<unsigned char>(inputY > 0) << 3;
            physicalInputBits = inputX < 0;
            physicalInputBits |= static_cast<unsigned char>(inputX > 0) << 1;
            physicalInputBits |= static_cast<unsigned char>(inputY < 0) << 2;
            physicalInputBits |= static_cast<unsigned char>(inputY > 0) << 3;
            relativeBits |= static_cast<unsigned char>(inputA == 1) << 4;
            relativeBits |= static_cast<unsigned char>(inputB == 1) << 5;
            relativeBits |= static_cast<unsigned char>(inputC == 1) << 6;
            relativeBits |= static_cast<unsigned char>(inputD == 1) << 7;
            physicalInputBits |= static_cast<unsigned char>(static_cast<unsigned int>(inputA) > 0) << 4;
            physicalInputBits |= static_cast<unsigned char>(static_cast<unsigned int>(inputB) > 0) << 5;
            physicalInputBits |= static_cast<unsigned char>(static_cast<unsigned int>(inputC) > 0) << 6;
            physicalInputBits |= static_cast<unsigned char>(static_cast<unsigned int>(inputD) > 0) << 7;
            if (g_ReplayModeAt0066C238 == 1) g_ReplayRecords.byteInputs.push_back(physicalInputBits);
        }
        if (action >= 300 && (inputA == 1 || inputB == 1 || inputC == 1 || inputD == 1)) {
            field510 = 10;
            bufferedX = inputX;
            bufferedY = inputY;
            bufferedA = inputA == 1;
            bufferedB = inputB == 1;
            bufferedC = inputC == 1;
            bufferedD = inputD == 1;
        }
        if (action < 300 || field510 <= 0) {
            ClearAuxiliaryWords();
            field510 = 0;
        }
        if (field510 > 0) --field510;
        inputHistory.push_back(relativeBits);
        inputHistory.pop_front();
        PollCommands();
    }
    if (field2CD == 0) field4E4 = inputA;
    else field4E4 = 0;
}
