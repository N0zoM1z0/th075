#include "BattleSessionState.hpp"
#include "CharacterSelectScene.hpp"
#include "SoundBank.hpp"
#include "Graphics.hpp"
#include "ResultListScene.hpp"
#include <stdlib.h>

// Partial pointer-only interfaces; no private owner is instantiated or embedded.
int __cdecl AbsoluteSelectionInputF130(int);
void CharacterSelectScene::UpdateChoiceAnimation(signed char side) {
    signed char horizontalDirection;
    int verticalDirection;
    if (portraitEnterX[side] < 80.0f) portraitEnterX[side] = portraitEnterX[side] + 4.0f;
    if (portraitEnterY[side] < 40.0f) portraitEnterY[side] = portraitEnterY[side] + 2.0f;
    if (portraitExitX[side] < 80.0f) portraitExitX[side] = portraitExitX[side] + 4.0f;
    if (portraitExitY[side] < 40.0f) portraitExitY[side] = portraitExitY[side] + 2.0f;
    if (choiceStop[side] > 0.0f) choiceStop[side] = choiceStop[side] - 1.0f;
    if (choiceStop[side] == 60.0f) choiceStop[side] = 0;
    if ((input[side].cancel) == 1) {
        g_SoundBank->Play(40);
        (playerState[side]) = 0;
        portraitEnterX[side] = 80.0f;
        portraitEnterY[side] = 40.0f;
        portraitExitX[side] = 80.0f;
        portraitExitY[side] = 40.0f;
        (playerReady[side]) = 1;
    }
    if ((playerState[1 - side]) < 4) return;
    if (stageCountdown[0] > 0) horizontalDirection = 1;
    else horizontalDirection = ((input[side].horizontal) > 0) * 2 - 1;
    if (AbsoluteSelectionInputF130((input[side].horizontal)) == 1 ||
        (AbsoluteSelectionInputF130((input[side].horizontal)) > 60 && AbsoluteSelectionInputF130((input[side].horizontal)) % 15 == 0) ||
        (stageCountdown[0] > 0 && side == 0)) {
        stagePage[1] = (stagePage[1] + 10 + horizontalDirection) % 10;
        if (stagePage[1] == 8 && stagePage[0] == 1)
            g_StageSelectionAt0067161D = 20;
        else if (stagePage[1] < 6)
            g_StageSelectionAt0067161D = stagePage[1] + stagePage[0] * 10;
        else
            g_StageSelectionAt0067161D = stagePage[1];
        while ((stageAvailable[g_StageSelectionAt0067161D]) == 0) {
            stagePage[1] = (stagePage[1] + 10 + horizontalDirection) % 10;
            if (stagePage[1] == 8 && stagePage[0] == 1)
                g_StageSelectionAt0067161D = 20;
            else if (stagePage[1] < 6)
                g_StageSelectionAt0067161D = stagePage[1] + stagePage[0] * 10;
            else
                g_StageSelectionAt0067161D = stagePage[1];
        }
        if (stageCountdown[0] > 0) {
            stagePage[0] = rand() % 2;
            if (stagePage[1] == 8 && stagePage[0] == 1)
                g_StageSelectionAt0067161D = 20;
            else if (stagePage[1] < 6)
                g_StageSelectionAt0067161D = stagePage[1] + stagePage[0] * 10;
            else
                g_StageSelectionAt0067161D = stagePage[1];
            while ((stageAvailable[g_StageSelectionAt0067161D]) == 0) {
                stagePage[0] = rand() % 2;
                if (stagePage[1] == 8 && stagePage[0] == 1)
                    g_StageSelectionAt0067161D = 20;
                else if (stagePage[1] < 6)
                    g_StageSelectionAt0067161D = stagePage[1] + stagePage[0] * 10;
                else
                    g_StageSelectionAt0067161D = stagePage[1];
            }
        }
    } else if (AbsoluteSelectionInputF130((input[side].vertical)) == 1 || (input[side].toggle) == 1 ||
        (AbsoluteSelectionInputF130((input[side].vertical)) % 15 == 0 && AbsoluteSelectionInputF130((input[side].vertical)) > 60)) {
        verticalDirection = ((input[side].vertical) > 0) * 2 - 1;
        stagePage[0] = (stagePage[0] + 2 + verticalDirection) % 2;
        if (stagePage[1] == 8 && stagePage[0] == 1)
            g_StageSelectionAt0067161D = 20;
        else if (stagePage[1] < 6)
            g_StageSelectionAt0067161D = stagePage[1] + stagePage[0] * 10;
        else
            g_StageSelectionAt0067161D = stagePage[1];
        while ((stageAvailable[g_StageSelectionAt0067161D]) == 0) {
            stagePage[0] = (stagePage[0] + 2 + verticalDirection) % 2;
            if (stagePage[1] == 8 && stagePage[0] == 1)
                g_StageSelectionAt0067161D = 20;
            else if (stagePage[1] < 6)
                g_StageSelectionAt0067161D = stagePage[1] + stagePage[0] * 10;
            else
                g_StageSelectionAt0067161D = stagePage[1];
        }
        g_SoundBank->Play(39);
    }
    if ((input[side].confirm) == 1 || (stageCountdown[side]) == -1) {
        playerState[0] = 8;
        playerState[1] = 8;
        g_SoundBank->Play(45);
    }
    if ((input[side].special) == 1) stageCountdown[0] = rand() % 10 + 30;
    if (side == 0 && stageCountdown[0] > 0) --stageCountdown[0];
}

unsigned short ResultListScene::Update() {
    PollInput();
    Render();
    Graphics::Present();
    if (showingRecords == 0) {
        if (verticalInput < 0) {
            g_SoundBank->Play(39);
            --difficultyIndex;
            if (difficultyIndex < 0) difficultyIndex = 3;
            BuildCounterPage();
        }
        if (verticalInput > 0) {
            g_SoundBank->Play(39);
            ++difficultyIndex;
            if (difficultyIndex > 3) difficultyIndex = 0;
            BuildCounterPage();
        }
        if (horizontalInput < 0) {
            g_SoundBank->Play(39);
            --(selectedCharacter);
            if ((selectedCharacter) < 0) (selectedCharacter) = 9;
            if ((selectedCharacter) == 9 && selectableCharacter[9] == 0) --(selectedCharacter);
            if ((selectedCharacter) == 8 && selectableCharacter[8] == 0) --(selectedCharacter);
            if ((selectedCharacter) == 7 && selectableCharacter[7] == 0) --(selectedCharacter);
            if ((selectedCharacter) == 6 && selectableCharacter[6] == 0) --(selectedCharacter);
            LoadSelectedCharacterResources();
            BuildCounterPage();
        }
        if (horizontalInput > 0) {
            g_SoundBank->Play(39);
            ++(selectedCharacter);
            if ((selectedCharacter) == 6 && selectableCharacter[6] == 0) ++(selectedCharacter);
            if ((selectedCharacter) == 7 && selectableCharacter[7] == 0) ++(selectedCharacter);
            if ((selectedCharacter) == 8 && selectableCharacter[8] == 0) ++(selectedCharacter);
            if ((selectedCharacter) == 9 && selectableCharacter[9] == 0) ++(selectedCharacter);
            if ((selectedCharacter) > 9) (selectedCharacter) = 0;
            LoadSelectedCharacterResources();
            BuildCounterPage();
        }
    } else {
        if (verticalInput < 0) {
            g_SoundBank->Play(39);
            --(pageIndex);
            if ((pageIndex) < 0) (pageIndex) = (records.Count() - 1) / 10;
            BuildRecordPage();
        }
        if (verticalInput > 0) {
            g_SoundBank->Play(39);
            ++(pageIndex);
            if ((pageIndex) > (static_cast<int>(records.Count()) - 1) / 10) (pageIndex) = 0;
            BuildRecordPage();
        }
        if (horizontalInput < 0) {
            g_SoundBank->Play(39);
            --(selectedCharacter);
            if ((selectedCharacter) < 0) (selectedCharacter) = 9;
            if ((selectedCharacter) == 9 && selectableCharacter[9] == 0) --(selectedCharacter);
            if ((selectedCharacter) == 8 && selectableCharacter[8] == 0) --(selectedCharacter);
            if ((selectedCharacter) == 7 && selectableCharacter[7] == 0) --(selectedCharacter);
            if ((selectedCharacter) == 6 && selectableCharacter[6] == 0) --(selectedCharacter);
            LoadSelectedCharacterResources();
            (pageIndex) = 0;
            BuildRecordPage();
        }
        if (horizontalInput > 0) {
            g_SoundBank->Play(39);
            ++(selectedCharacter);
            if ((selectedCharacter) == 6 && selectableCharacter[6] == 0) ++(selectedCharacter);
            if ((selectedCharacter) == 7 && selectableCharacter[7] == 0) ++(selectedCharacter);
            if ((selectedCharacter) == 8 && selectableCharacter[8] == 0) ++(selectedCharacter);
            if ((selectedCharacter) == 9 && selectableCharacter[9] == 0) ++(selectedCharacter);
            if ((selectedCharacter) > 9) (selectedCharacter) = 0;
            LoadSelectedCharacterResources();
            (pageIndex) = 0;
            BuildRecordPage();
        }
    }
    if (displayAlpha < 255) displayAlpha += 25;
    if (confirmInput == 1) {
        if (showingRecords == 0) {
            BuildRecordPage();
            g_SoundBank->Play(45);
            (pageIndex) = 0;
            showingRecords = 1;
        } else {
            g_SoundBank->Play(45);
            showingRecords = 0;
            BuildCounterPage();
        }
    }
    if (cancelInput == 1) {
        g_SoundBank->Play(40);
        return 0x2202;
    }
    return 0xE;
}
