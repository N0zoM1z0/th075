#include "CharacterSelectScene.hpp"
#include "Graphics.hpp"
#include <stdlib.h>

// Partial pointer-only interfaces; no private owner is instantiated or embedded.
class SelectionSoundF130 { public: void Play(int); };
extern SelectionSoundF130* g_SelectionSound;
int __cdecl AbsoluteSelectionInputF130(int);
extern signed char g_SelectionStageF131;
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
        g_SelectionSound->Play(40);
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
            g_SelectionStageF131 = 20;
        else if (stagePage[1] < 6)
            g_SelectionStageF131 = stagePage[1] + stagePage[0] * 10;
        else
            g_SelectionStageF131 = stagePage[1];
        while ((stageAvailable[g_SelectionStageF131]) == 0) {
            stagePage[1] = (stagePage[1] + 10 + horizontalDirection) % 10;
            if (stagePage[1] == 8 && stagePage[0] == 1)
                g_SelectionStageF131 = 20;
            else if (stagePage[1] < 6)
                g_SelectionStageF131 = stagePage[1] + stagePage[0] * 10;
            else
                g_SelectionStageF131 = stagePage[1];
        }
        if (stageCountdown[0] > 0) {
            stagePage[0] = rand() % 2;
            if (stagePage[1] == 8 && stagePage[0] == 1)
                g_SelectionStageF131 = 20;
            else if (stagePage[1] < 6)
                g_SelectionStageF131 = stagePage[1] + stagePage[0] * 10;
            else
                g_SelectionStageF131 = stagePage[1];
            while ((stageAvailable[g_SelectionStageF131]) == 0) {
                stagePage[0] = rand() % 2;
                if (stagePage[1] == 8 && stagePage[0] == 1)
                    g_SelectionStageF131 = 20;
                else if (stagePage[1] < 6)
                    g_SelectionStageF131 = stagePage[1] + stagePage[0] * 10;
                else
                    g_SelectionStageF131 = stagePage[1];
            }
        }
    } else if (AbsoluteSelectionInputF130((input[side].vertical)) == 1 || (input[side].toggle) == 1 ||
        (AbsoluteSelectionInputF130((input[side].vertical)) % 15 == 0 && AbsoluteSelectionInputF130((input[side].vertical)) > 60)) {
        verticalDirection = ((input[side].vertical) > 0) * 2 - 1;
        stagePage[0] = (stagePage[0] + 2 + verticalDirection) % 2;
        if (stagePage[1] == 8 && stagePage[0] == 1)
            g_SelectionStageF131 = 20;
        else if (stagePage[1] < 6)
            g_SelectionStageF131 = stagePage[1] + stagePage[0] * 10;
        else
            g_SelectionStageF131 = stagePage[1];
        while ((stageAvailable[g_SelectionStageF131]) == 0) {
            stagePage[0] = (stagePage[0] + 2 + verticalDirection) % 2;
            if (stagePage[1] == 8 && stagePage[0] == 1)
                g_SelectionStageF131 = 20;
            else if (stagePage[1] < 6)
                g_SelectionStageF131 = stagePage[1] + stagePage[0] * 10;
            else
                g_SelectionStageF131 = stagePage[1];
        }
        g_SelectionSound->Play(39);
    }
    if ((input[side].confirm) == 1 || (stageCountdown[side]) == -1) {
        playerState[0] = 8;
        playerState[1] = 8;
        g_SelectionSound->Play(45);
    }
    if ((input[side].special) == 1) stageCountdown[0] = rand() % 10 + 30;
    if (side == 0 && stageCountdown[0] > 0) --stageCountdown[0];
}

class ResultRecordsF131 { public: unsigned int Count() const; };
class ResultSelectionF131 {
public:
    virtual void UnknownSlot0();
    virtual void UnknownSlot1();
    virtual void Render();
    short Update();
    void PollInput();
    void LoadSelectedCharacterResources();
    void BuildRecordPage();
    void BuildCounterPage();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown004[0x1BE - 0x004];
    unsigned char field1BE;
    signed char field1BF;
    signed char field1C0;
    signed char field1C1;
    signed char field1C2;
    unsigned char unknown1C3[0x1C4 - 0x1C3];
    signed char field1C4;
    signed char field1C5;
    unsigned char unknown1C6[0x1CC - 0x1C6];
    unsigned char field1CC;
    unsigned char field1CD;
    unsigned char field1CE;
    unsigned char field1CF;
};
#define RECORDS reinterpret_cast<ResultRecordsF131*>(reinterpret_cast<char*>(this) + 0x18)
#define PAGE (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0x1BC))
#define CHARACTER (*reinterpret_cast<signed char*>(reinterpret_cast<unsigned char*>(this) + 0x1C3))
short ResultSelectionF131::Update() {
    PollInput();
    Render();
    Graphics::Present();
    if (field1C5 == 0) {
        if (field1C0 < 0) {
            g_SelectionSound->Play(39);
            --field1C4;
            if (field1C4 < 0) field1C4 = 3;
            BuildCounterPage();
        }
        if (field1C0 > 0) {
            g_SelectionSound->Play(39);
            ++field1C4;
            if (field1C4 > 3) field1C4 = 0;
            BuildCounterPage();
        }
        if (field1BF < 0) {
            g_SelectionSound->Play(39);
            --CHARACTER;
            if (CHARACTER < 0) CHARACTER = 9;
            if (CHARACTER == 9 && field1CF == 0) --CHARACTER;
            if (CHARACTER == 8 && field1CE == 0) --CHARACTER;
            if (CHARACTER == 7 && field1CD == 0) --CHARACTER;
            if (CHARACTER == 6 && field1CC == 0) --CHARACTER;
            LoadSelectedCharacterResources();
            BuildCounterPage();
        }
        if (field1BF > 0) {
            g_SelectionSound->Play(39);
            ++CHARACTER;
            if (CHARACTER == 6 && field1CC == 0) ++CHARACTER;
            if (CHARACTER == 7 && field1CD == 0) ++CHARACTER;
            if (CHARACTER == 8 && field1CE == 0) ++CHARACTER;
            if (CHARACTER == 9 && field1CF == 0) ++CHARACTER;
            if (CHARACTER > 9) CHARACTER = 0;
            LoadSelectedCharacterResources();
            BuildCounterPage();
        }
    } else {
        if (field1C0 < 0) {
            g_SelectionSound->Play(39);
            --PAGE;
            if (PAGE < 0) PAGE = (RECORDS->Count() - 1) / 10;
            BuildRecordPage();
        }
        if (field1C0 > 0) {
            g_SelectionSound->Play(39);
            ++PAGE;
            if (PAGE > (static_cast<int>(RECORDS->Count()) - 1) / 10) PAGE = 0;
            BuildRecordPage();
        }
        if (field1BF < 0) {
            g_SelectionSound->Play(39);
            --CHARACTER;
            if (CHARACTER < 0) CHARACTER = 9;
            if (CHARACTER == 9 && field1CF == 0) --CHARACTER;
            if (CHARACTER == 8 && field1CE == 0) --CHARACTER;
            if (CHARACTER == 7 && field1CD == 0) --CHARACTER;
            if (CHARACTER == 6 && field1CC == 0) --CHARACTER;
            LoadSelectedCharacterResources();
            PAGE = 0;
            BuildRecordPage();
        }
        if (field1BF > 0) {
            g_SelectionSound->Play(39);
            ++CHARACTER;
            if (CHARACTER == 6 && field1CC == 0) ++CHARACTER;
            if (CHARACTER == 7 && field1CD == 0) ++CHARACTER;
            if (CHARACTER == 8 && field1CE == 0) ++CHARACTER;
            if (CHARACTER == 9 && field1CF == 0) ++CHARACTER;
            if (CHARACTER > 9) CHARACTER = 0;
            LoadSelectedCharacterResources();
            PAGE = 0;
            BuildRecordPage();
        }
    }
    if (field1BE < 255) field1BE += 25;
    if (field1C1 == 1) {
        if (field1C5 == 0) {
            BuildRecordPage();
            g_SelectionSound->Play(45);
            PAGE = 0;
            field1C5 = 1;
        } else {
            g_SelectionSound->Play(45);
            field1C5 = 0;
            BuildCounterPage();
        }
    }
    if (field1C2 == 1) {
        g_SelectionSound->Play(40);
        return 0x2202;
    }
    return 0xE;
}
#undef CHARACTER
#undef PAGE
#undef RECORDS
