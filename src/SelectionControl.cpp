#include "SelectionInput4388D0.hpp"
#include "CharacterSelectScene.hpp"
#include "RecordedRange455580.hpp"
#include <stdlib.h>

// Pointer-only interfaces. No complete scene/fighter/container layout is claimed.
class SelectionSoundF130 { public: void Play(int); };
class SelectionProgressF130 {
public:
    void SetSelection(signed char, signed char);
    signed char GetSelectedValue();
};
int __cdecl AbsoluteSelectionInputF130(int);
extern SelectionSoundF130* g_SelectionSound;
extern unsigned char g_SelectionProgress[];
extern signed char g_SelectionCharacters[];
extern signed char g_SelectionPalettes[];
extern signed char g_SelectionDifficulty;
#define PROGRESS reinterpret_cast<SelectionProgressF130*>(g_SelectionProgress)
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
        if ((stageCountdown[side]) == 0) g_SelectionSound->Play(39);
        portraitReturn[side] = 100.0f;
        portraitFade[side] = 100.0f;
        portraitEnterX[side] = 80.0f;
        portraitEnterY[side] = 40.0f;
        portraitExitX[side] = 80.0f;
        portraitExitY[side] = 40.0f;
        (reinterpret_cast<signed char&>(alternateCharacter[side])) = (reinterpret_cast<signed char&>(chosenCharacter[side]));
        if ((input[side].horizontal) > 0) {
            ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
            if (g_CombatMode == 3) {
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 6 && (rightCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 7 && (rightCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 8 && (rightCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 9 && (rightCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 10 && (rightCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
            } else {
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 6 && (leftCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 7 && (leftCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 8 && (leftCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 9 && (leftCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 10 && (leftCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) ++(reinterpret_cast<signed char&>(chosenCharacter[side]));
            }
            if ((reinterpret_cast<signed char&>(chosenCharacter[side])) >= 11) (reinterpret_cast<signed char&>(chosenCharacter[side])) = 0;
        } else {
            --(reinterpret_cast<signed char&>(chosenCharacter[side]));
            if ((reinterpret_cast<signed char&>(chosenCharacter[side])) < 0) (reinterpret_cast<signed char&>(chosenCharacter[side])) = 10;
            if (g_CombatMode == 3) {
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 10 && (rightCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) --(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 9 && (rightCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) --(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 8 && (rightCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) --(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 7 && (rightCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) --(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 6 && (rightCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) --(reinterpret_cast<signed char&>(chosenCharacter[side]));
            } else {
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 10 && (leftCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) --(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 9 && (leftCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) --(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 8 && (leftCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) --(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 7 && (leftCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) --(reinterpret_cast<signed char&>(chosenCharacter[side]));
                if ((reinterpret_cast<signed char&>(chosenCharacter[side])) == 6 && (leftCharacterAvailable[reinterpret_cast<signed char&>(chosenCharacter[side])]) == 0) --(reinterpret_cast<signed char&>(chosenCharacter[side]));
            }
        }
        PROGRESS->SetSelection(reinterpret_cast<signed char&>(chosenCharacter[0]), g_SelectionDifficulty);
    }
    if ((input[side].confirm) == 1 || (input[side].toggle) == 1 || (stageCountdown[side]) == 1) {
        g_SelectionSound->Play(45);
        g_SelectionCharacters[side] = (reinterpret_cast<signed char&>(chosenCharacter[side]));
        g_SelectionPalettes[side] = (input[side].toggle) == 1;
        (playerState[side]) = 1;
        choiceStop[side] = 0;
        if (g_CombatMode != 4 && (playerState[1 - side]) != 0 && g_SelectionCharacters[0] == g_SelectionCharacters[1] && g_SelectionPalettes[side] == g_SelectionPalettes[1 - side])
            g_SelectionPalettes[side] = 1 - g_SelectionPalettes[side];
        if (g_CombatMode == 3) {
            g_SelectionPalettes[0] = 0;
            g_SelectionPalettes[1] = 0;
        }
    }
    if ((input[side].special) == 1) (stageCountdown[side]) = rand() % 10 + 30;
    if ((stageCountdown[side]) > 0) --(stageCountdown[side]);
    if ((input[side].alternative) == 1) {
        if (PROGRESS->GetSelectedValue() > 0 && g_CombatMode == 3) {
            g_SelectionSound->Play(45);
            (optionsOpen[side]) = !(optionsOpen[side]);
        }
        if (g_CombatMode != 3 && g_CombatMode != 5) {
            g_SelectionSound->Play(45);
            (optionsOpen[side]) = !(optionsOpen[side]);
        }
    }
}
#undef PROGRESS

class RecordedBytesF130 {
public:
    unsigned int Count() const;
    unsigned char& Front();
    void PopFront();
    void PushBack(const unsigned char&);
};
extern unsigned char g_ControlRecordedPress[];
extern unsigned char g_ControlRecordedAuxiliary[];
// Only actually invoked virtual slots11,12,13 have a recovered call contract.
// Earlier entries are unknown unused interface positions. Never instantiate.
class FighterControlsF130 {
public:
    virtual void UnknownSlot0();
    virtual void UnknownSlot1();
    virtual void UnknownSlot2();
    virtual void UnknownSlot3();
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
    virtual void UnknownSlot6();
    virtual void UnknownSlot7();
    virtual void UnknownSlot8();
    virtual void UnknownSlot9();
    virtual void UnknownSlot10();
    virtual void UpdateOrdinaryDirections();
    virtual void UpdatePracticeDirections();
    virtual void FinishInput();
    void UpdateControls();
    void ClearAuxiliaryWords();
    void ApplyMode5Direction();
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown004[0x060 - 0x004];
    short field060;
    unsigned char unknown062[0x066 - 0x062];
    signed char field066;
    unsigned char unknown067[0x2CD - 0x067];
    signed char field2CD;
    unsigned char unknown2CE[0x4C0 - 0x2CE];
    int field4C0;
    int field4C4;
    int field4C8;
    int field4CC;
    int field4D0;
    int field4D4;
    unsigned char unknown4D8[0x4DC - 0x4D8];
    int field4DC;
    int field4E0;
    int field4E4;
    int field4E8;
    int field4EC;
    int field4F0;
    int field4F4;
    int field4F8;
    int field4FC;
    int field500;
    int field504;
    int field508;
    int field50C;
    signed char field510;
    unsigned char field511;
    unsigned char unknown512[0x516 - 0x512];
    short field516;
};
#define PRESS reinterpret_cast<RecordedBytesF130*>(g_ControlRecordedPress)
#define AUXILIARY reinterpret_cast<RecordedBytesF130*>(g_ControlRecordedAuxiliary)
#define SAMPLES reinterpret_cast<RecordedSamples455580View*>(g_RecordedSamplesAt006718B8)
#define HISTORY reinterpret_cast<RecordedBytesF130*>(reinterpret_cast<char*>(this) + 0x518)
#define INPUT_MAPPING reinterpret_cast<InputMapping4388D0*>(reinterpret_cast<char*>(this) + 0x494)
void FighterControlsF130::UpdateControls() {
    unsigned char relativeBits = 0;
    unsigned char physicalInputBits = 0;
    if (field2CD != 0) {
        ClearAuxiliaryWords();
        field4DC = 0;
        field4E0 = 0;
        field4E8 = 0;
        field4EC = 0;
        field4F0 = 0;
        field4F4 = 0;
        field511 = 0;
        if (g_FrameClockMode == 2) {
            if (PRESS->Count() > 0) { relativeBits = PRESS->Front(); PRESS->PopFront(); }
            if (AUXILIARY->Count() > 0) { field511 = AUXILIARY->Front(); AUXILIARY->PopFront(); }
            if (SAMPLES->Count() > 0) { field516 = SAMPLES->Front(); SAMPLES->PopFront(); }
            if (relativeBits & 0x1) field4DC = -1;
            if (relativeBits & 0x2) field4DC = 1;
            if (relativeBits & 0x4) field4E0 = -1;
            if (relativeBits & 0x8) field4E0 = 1;
            if (relativeBits & 0x10) field4E8 = 1;
            if (relativeBits & 0x20) field4EC = 1;
            if (relativeBits & 0x40) field4F0 = 1;
            if (relativeBits & 0x80) field4F4 = 1;
        } else if (g_FrameClockMode == 1) {
            if (g_CombatMode == 3) UpdatePracticeDirections();
            else if (g_CombatMode == 5) ApplyMode5Direction();
            else UpdateOrdinaryDirections();
            if (g_SelectionDifficulty < 2 && rand() > (g_SelectionDifficulty * 3 + 1) * 2048) {
                field4E8 = 0;
                field4EC = 0;
                field4F0 = 0;
                field4F4 = 0;
                field511 = 0;
            }
            if (field4E8 != 0) field4E8 = 1;
            if (field4EC != 0) field4EC = 1;
            if (field4F0 != 0) field4F0 = 1;
            if (field4F4 != 0) field4F4 = 1;
            relativeBits = field4DC < 0;
            relativeBits |= static_cast<unsigned char>(field4DC > 0) << 1;
            relativeBits |= static_cast<unsigned char>(field4E0 < 0) << 2;
            relativeBits |= static_cast<unsigned char>(field4E0 > 0) << 3;
            relativeBits |= static_cast<unsigned char>(reinterpret_cast<unsigned int&>(field4E8) > 0) << 4;
            relativeBits |= static_cast<unsigned char>(reinterpret_cast<unsigned int&>(field4EC) > 0) << 5;
            relativeBits |= static_cast<unsigned char>(reinterpret_cast<unsigned int&>(field4F0) > 0) << 6;
            relativeBits |= static_cast<unsigned char>(reinterpret_cast<unsigned int&>(field4F4) > 0) << 7;
            PRESS->PushBack(relativeBits);
            AUXILIARY->PushBack(field511);
            SAMPLES->PushBack(field516);
        }
    } else {
        if (g_FrameClockMode == 2) {
            if (PRESS->Count() > 0) { physicalInputBits = PRESS->Front(); PRESS->PopFront(); }
            if (physicalInputBits & 0x1) {
                if (field4C0 > 0) field4C0 = 0;
                field4C0 = field4C0 - 1;
            } else if (physicalInputBits & 0x2) {
                if (field4C0 < 0) field4C0 = 0;
                field4C0 = field4C0 + 1;
            } else field4C0 = 0;
            if (physicalInputBits & 0x4) {
                if (field4C4 > 0) field4C4 = 0;
                field4C4 = field4C4 - 1;
            } else if (physicalInputBits & 0x8) {
                if (field4C4 < 0) field4C4 = 0;
                field4C4 = field4C4 + 1;
            } else field4C4 = 0;
            if (physicalInputBits & 0x10) field4C8 = field4C8 + 1;
            else field4C8 = 0;
            if (physicalInputBits & 0x20) field4CC = field4CC + 1;
            else field4CC = 0;
            if (physicalInputBits & 0x40) field4D0 = field4D0 + 1;
            else field4D0 = 0;
            if (physicalInputBits & 0x80) field4D4 = field4D4 + 1;
            else field4D4 = 0;
            field4DC = field4C0;
            field4E0 = field4C4;
            field4E8 = field4C8;
            field4EC = field4CC;
            field4F0 = field4D0;
            field4F4 = field4D4;
            relativeBits = field066 * field4DC < 0;
            relativeBits |= static_cast<unsigned char>(field066 * field4DC > 0) << 1;
            relativeBits |= static_cast<unsigned char>(field4E0 < 0) << 2;
            relativeBits |= static_cast<unsigned char>(field4E0 > 0) << 3;
            relativeBits |= static_cast<unsigned char>(field4E8 == 1) << 4;
            relativeBits |= static_cast<unsigned char>(field4EC == 1) << 5;
            relativeBits |= static_cast<unsigned char>(field4F0 == 1) << 6;
            relativeBits |= static_cast<unsigned char>(field4F4 == 1) << 7;
        } else {
            INPUT_MAPPING->UpdateHeldCounts();
            field4DC = field4C0;
            field4E0 = field4C4;
            field4E8 = field4C8;
            field4EC = field4CC;
            field4F0 = field4D0;
            field4F4 = field4D4;
            relativeBits = field066 * field4DC < 0;
            relativeBits |= static_cast<unsigned char>(field066 * field4DC > 0) << 1;
            relativeBits |= static_cast<unsigned char>(field4E0 < 0) << 2;
            relativeBits |= static_cast<unsigned char>(field4E0 > 0) << 3;
            physicalInputBits = field4DC < 0;
            physicalInputBits |= static_cast<unsigned char>(field4DC > 0) << 1;
            physicalInputBits |= static_cast<unsigned char>(field4E0 < 0) << 2;
            physicalInputBits |= static_cast<unsigned char>(field4E0 > 0) << 3;
            relativeBits |= static_cast<unsigned char>(field4E8 == 1) << 4;
            relativeBits |= static_cast<unsigned char>(field4EC == 1) << 5;
            relativeBits |= static_cast<unsigned char>(field4F0 == 1) << 6;
            relativeBits |= static_cast<unsigned char>(field4F4 == 1) << 7;
            physicalInputBits |= static_cast<unsigned char>(reinterpret_cast<unsigned int&>(field4E8) > 0) << 4;
            physicalInputBits |= static_cast<unsigned char>(reinterpret_cast<unsigned int&>(field4EC) > 0) << 5;
            physicalInputBits |= static_cast<unsigned char>(reinterpret_cast<unsigned int&>(field4F0) > 0) << 6;
            physicalInputBits |= static_cast<unsigned char>(reinterpret_cast<unsigned int&>(field4F4) > 0) << 7;
            if (g_FrameClockMode == 1) PRESS->PushBack(physicalInputBits);
        }
        if (field060 >= 300 && (field4E8 == 1 || field4EC == 1 || field4F0 == 1 || field4F4 == 1)) {
            field510 = 10;
            field4F8 = field4DC;
            field4FC = field4E0;
            field500 = field4E8 == 1;
            field504 = field4EC == 1;
            field508 = field4F0 == 1;
            field50C = field4F4 == 1;
        }
        if (field060 < 300 || field510 <= 0) {
            ClearAuxiliaryWords();
            field510 = 0;
        }
        if (field510 > 0) --field510;
        HISTORY->PushBack(relativeBits);
        HISTORY->PopFront();
        FinishInput();
    }
    if (field2CD == 0) field4E4 = field4E8;
    else field4E4 = 0;
}
#undef INPUT_MAPPING
#undef HISTORY
#undef SAMPLES
#undef AUXILIARY
#undef PRESS
