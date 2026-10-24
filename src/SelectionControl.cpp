#include "SelectionInput4388D0.hpp"
#include "RecordedRange455580.hpp"
#include <stdlib.h>

// Pointer-only interfaces. No complete scene/fighter/container layout is claimed.
class SelectionUpdateF130 { public: void Update(signed char side); };
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
#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define ANIM(offset) reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))[side]
#define SIDE_BYTE(type, offset) (reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset))[side])
#define HELD(offset) (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + (offset) + side * 28))
#define CHOICE SIDE_BYTE(signed char, 0xE0)
#define AUTO_SELECT SIDE_BYTE(signed char, 0xF2)
#define PROGRESS reinterpret_cast<SelectionProgressF130*>(g_SelectionProgress)
void SelectionUpdateF130::Update(signed char side) {
    if (ANIM(0xCC) > 0.0f) ANIM(0xCC) = ANIM(0xCC) - 5.0f;
    if (ANIM(0xA0) > 0.0f) ANIM(0xA0) = ANIM(0xA0) - 4.0f;
    if (ANIM(0xA8) > 0.0f) ANIM(0xA8) = ANIM(0xA8) - 2.0f;
    if (ANIM(0xB0) > 0.0f) ANIM(0xB0) = ANIM(0xB0) - 4.0f;
    if (ANIM(0xB8) > 0.0f) ANIM(0xB8) = ANIM(0xB8) - 2.0f;
    else SIDE_BYTE(unsigned char, 0xE8) = 0;
    if (ANIM(0xC0) > 0.0f) ANIM(0xC0) = ANIM(0xC0) - 1.0f;
    if (ANIM(0xC0) == 60.0f) ANIM(0xC0) = 0;
    if (AbsoluteSelectionInputF130(HELD(0xC)) == 1 || AbsoluteSelectionInputF130(HELD(0xC)) % 15 == 1 || AUTO_SELECT > 0) {
        if (AUTO_SELECT == 0) g_SelectionSound->Play(39);
        ANIM(0xCC) = 100.0f;
        ANIM(0x98) = 100.0f;
        ANIM(0xA0) = 80.0f;
        ANIM(0xA8) = 40.0f;
        ANIM(0xB0) = 80.0f;
        ANIM(0xB8) = 40.0f;
        SIDE_BYTE(signed char, 0xE2) = CHOICE;
        if (HELD(0xC) > 0) {
            ++CHOICE;
            if (g_CombatMode == 3) {
                if (CHOICE == 6 && FIELD(unsigned char, 0x64 + CHOICE) == 0) ++CHOICE;
                if (CHOICE == 7 && FIELD(unsigned char, 0x64 + CHOICE) == 0) ++CHOICE;
                if (CHOICE == 8 && FIELD(unsigned char, 0x64 + CHOICE) == 0) ++CHOICE;
                if (CHOICE == 9 && FIELD(unsigned char, 0x64 + CHOICE) == 0) ++CHOICE;
                if (CHOICE == 10 && FIELD(unsigned char, 0x64 + CHOICE) == 0) ++CHOICE;
            } else {
                if (CHOICE == 6 && FIELD(unsigned char, 0x50 + CHOICE) == 0) ++CHOICE;
                if (CHOICE == 7 && FIELD(unsigned char, 0x50 + CHOICE) == 0) ++CHOICE;
                if (CHOICE == 8 && FIELD(unsigned char, 0x50 + CHOICE) == 0) ++CHOICE;
                if (CHOICE == 9 && FIELD(unsigned char, 0x50 + CHOICE) == 0) ++CHOICE;
                if (CHOICE == 10 && FIELD(unsigned char, 0x50 + CHOICE) == 0) ++CHOICE;
            }
            if (CHOICE >= 11) CHOICE = 0;
        } else {
            --CHOICE;
            if (CHOICE < 0) CHOICE = 10;
            if (g_CombatMode == 3) {
                if (CHOICE == 10 && FIELD(unsigned char, 0x64 + CHOICE) == 0) --CHOICE;
                if (CHOICE == 9 && FIELD(unsigned char, 0x64 + CHOICE) == 0) --CHOICE;
                if (CHOICE == 8 && FIELD(unsigned char, 0x64 + CHOICE) == 0) --CHOICE;
                if (CHOICE == 7 && FIELD(unsigned char, 0x64 + CHOICE) == 0) --CHOICE;
                if (CHOICE == 6 && FIELD(unsigned char, 0x64 + CHOICE) == 0) --CHOICE;
            } else {
                if (CHOICE == 10 && FIELD(unsigned char, 0x50 + CHOICE) == 0) --CHOICE;
                if (CHOICE == 9 && FIELD(unsigned char, 0x50 + CHOICE) == 0) --CHOICE;
                if (CHOICE == 8 && FIELD(unsigned char, 0x50 + CHOICE) == 0) --CHOICE;
                if (CHOICE == 7 && FIELD(unsigned char, 0x50 + CHOICE) == 0) --CHOICE;
                if (CHOICE == 6 && FIELD(unsigned char, 0x50 + CHOICE) == 0) --CHOICE;
            }
        }
        PROGRESS->SetSelection(FIELD(signed char, 0xE0), g_SelectionDifficulty);
    }
    if (HELD(0x14) == 1 || HELD(0x20) == 1 || AUTO_SELECT == 1) {
        g_SelectionSound->Play(45);
        g_SelectionCharacters[side] = CHOICE;
        g_SelectionPalettes[side] = HELD(0x20) == 1;
        SIDE_BYTE(signed char, 0x96) = 1;
        ANIM(0xC0) = 0;
        if (g_CombatMode != 4 && FIELD(signed char, 0x96 + (1 - side)) != 0 && g_SelectionCharacters[0] == g_SelectionCharacters[1] && g_SelectionPalettes[side] == g_SelectionPalettes[1 - side])
            g_SelectionPalettes[side] = 1 - g_SelectionPalettes[side];
        if (g_CombatMode == 3) {
            g_SelectionPalettes[0] = 0;
            g_SelectionPalettes[1] = 0;
        }
    }
    if (HELD(0x1C) == 1) AUTO_SELECT = rand() % 10 + 30;
    if (AUTO_SELECT > 0) --AUTO_SELECT;
    if (HELD(0x24) == 1) {
        if (PROGRESS->GetSelectedValue() > 0 && g_CombatMode == 3) {
            g_SelectionSound->Play(45);
            SIDE_BYTE(signed char, 0xEA) = !SIDE_BYTE(signed char, 0xEA);
        }
        if (g_CombatMode != 3 && g_CombatMode != 5) {
            g_SelectionSound->Play(45);
            SIDE_BYTE(signed char, 0xEA) = !SIDE_BYTE(signed char, 0xEA);
        }
    }
}
#undef PROGRESS
#undef AUTO_SELECT
#undef CHOICE
#undef HELD
#undef SIDE_BYTE
#undef ANIM

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
};
#define PRESS reinterpret_cast<RecordedBytesF130*>(g_ControlRecordedPress)
#define AUXILIARY reinterpret_cast<RecordedBytesF130*>(g_ControlRecordedAuxiliary)
#define SAMPLES reinterpret_cast<RecordedSamples455580View*>(g_RecordedSamplesAt006718B8)
#define HISTORY reinterpret_cast<RecordedBytesF130*>(reinterpret_cast<char*>(this) + 0x518)
#define INPUT_MAPPING reinterpret_cast<InputMapping4388D0*>(reinterpret_cast<char*>(this) + 0x494)
void FighterControlsF130::UpdateControls() {
    unsigned char relativeBits = 0;
    unsigned char physicalInputBits = 0;
    if (FIELD(signed char, 0x2CD) != 0) {
        ClearAuxiliaryWords();
        FIELD(int, 0x4DC) = 0;
        FIELD(int, 0x4E0) = 0;
        FIELD(int, 0x4E8) = 0;
        FIELD(int, 0x4EC) = 0;
        FIELD(int, 0x4F0) = 0;
        FIELD(int, 0x4F4) = 0;
        FIELD(unsigned char, 0x511) = 0;
        if (g_FrameClockMode == 2) {
            if (PRESS->Count() > 0) { relativeBits = PRESS->Front(); PRESS->PopFront(); }
            if (AUXILIARY->Count() > 0) { FIELD(unsigned char, 0x511) = AUXILIARY->Front(); AUXILIARY->PopFront(); }
            if (SAMPLES->Count() > 0) { FIELD(short, 0x516) = SAMPLES->Front(); SAMPLES->PopFront(); }
            if (relativeBits & 0x1) FIELD(int, 0x4DC) = -1;
            if (relativeBits & 0x2) FIELD(int, 0x4DC) = 1;
            if (relativeBits & 0x4) FIELD(int, 0x4E0) = -1;
            if (relativeBits & 0x8) FIELD(int, 0x4E0) = 1;
            if (relativeBits & 0x10) FIELD(int, 0x4E8) = 1;
            if (relativeBits & 0x20) FIELD(int, 0x4EC) = 1;
            if (relativeBits & 0x40) FIELD(int, 0x4F0) = 1;
            if (relativeBits & 0x80) FIELD(int, 0x4F4) = 1;
        } else if (g_FrameClockMode == 1) {
            if (g_CombatMode == 3) UpdatePracticeDirections();
            else if (g_CombatMode == 5) ApplyMode5Direction();
            else UpdateOrdinaryDirections();
            if (g_SelectionDifficulty < 2 && rand() > (g_SelectionDifficulty * 3 + 1) * 2048) {
                FIELD(int, 0x4E8) = 0;
                FIELD(int, 0x4EC) = 0;
                FIELD(int, 0x4F0) = 0;
                FIELD(int, 0x4F4) = 0;
                FIELD(unsigned char, 0x511) = 0;
            }
            if (FIELD(int, 0x4E8) != 0) FIELD(int, 0x4E8) = 1;
            if (FIELD(int, 0x4EC) != 0) FIELD(int, 0x4EC) = 1;
            if (FIELD(int, 0x4F0) != 0) FIELD(int, 0x4F0) = 1;
            if (FIELD(int, 0x4F4) != 0) FIELD(int, 0x4F4) = 1;
            relativeBits = FIELD(int, 0x4DC) < 0;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4DC) > 0) << 1;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4E0) < 0) << 2;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4E0) > 0) << 3;
            relativeBits |= static_cast<unsigned char>(FIELD(unsigned int, 0x4E8) > 0) << 4;
            relativeBits |= static_cast<unsigned char>(FIELD(unsigned int, 0x4EC) > 0) << 5;
            relativeBits |= static_cast<unsigned char>(FIELD(unsigned int, 0x4F0) > 0) << 6;
            relativeBits |= static_cast<unsigned char>(FIELD(unsigned int, 0x4F4) > 0) << 7;
            PRESS->PushBack(relativeBits);
            AUXILIARY->PushBack(FIELD(unsigned char, 0x511));
            SAMPLES->PushBack(FIELD(short, 0x516));
        }
    } else {
        if (g_FrameClockMode == 2) {
            if (PRESS->Count() > 0) { physicalInputBits = PRESS->Front(); PRESS->PopFront(); }
            if (physicalInputBits & 0x1) {
                if (FIELD(int, 0x4C0) > 0) FIELD(int, 0x4C0) = 0;
                FIELD(int, 0x4C0) = FIELD(int, 0x4C0) - 1;
            } else if (physicalInputBits & 0x2) {
                if (FIELD(int, 0x4C0) < 0) FIELD(int, 0x4C0) = 0;
                FIELD(int, 0x4C0) = FIELD(int, 0x4C0) + 1;
            } else FIELD(int, 0x4C0) = 0;
            if (physicalInputBits & 0x4) {
                if (FIELD(int, 0x4C4) > 0) FIELD(int, 0x4C4) = 0;
                FIELD(int, 0x4C4) = FIELD(int, 0x4C4) - 1;
            } else if (physicalInputBits & 0x8) {
                if (FIELD(int, 0x4C4) < 0) FIELD(int, 0x4C4) = 0;
                FIELD(int, 0x4C4) = FIELD(int, 0x4C4) + 1;
            } else FIELD(int, 0x4C4) = 0;
            if (physicalInputBits & 0x10) FIELD(int, 0x4C8) = FIELD(int, 0x4C8) + 1;
            else FIELD(int, 0x4C8) = 0;
            if (physicalInputBits & 0x20) FIELD(int, 0x4CC) = FIELD(int, 0x4CC) + 1;
            else FIELD(int, 0x4CC) = 0;
            if (physicalInputBits & 0x40) FIELD(int, 0x4D0) = FIELD(int, 0x4D0) + 1;
            else FIELD(int, 0x4D0) = 0;
            if (physicalInputBits & 0x80) FIELD(int, 0x4D4) = FIELD(int, 0x4D4) + 1;
            else FIELD(int, 0x4D4) = 0;
            FIELD(int, 0x4DC) = FIELD(int, 0x4C0);
            FIELD(int, 0x4E0) = FIELD(int, 0x4C4);
            FIELD(int, 0x4E8) = FIELD(int, 0x4C8);
            FIELD(int, 0x4EC) = FIELD(int, 0x4CC);
            FIELD(int, 0x4F0) = FIELD(int, 0x4D0);
            FIELD(int, 0x4F4) = FIELD(int, 0x4D4);
            relativeBits = FIELD(signed char, 0x66) * FIELD(int, 0x4DC) < 0;
            relativeBits |= static_cast<unsigned char>(FIELD(signed char, 0x66) * FIELD(int, 0x4DC) > 0) << 1;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4E0) < 0) << 2;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4E0) > 0) << 3;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4E8) == 1) << 4;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4EC) == 1) << 5;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4F0) == 1) << 6;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4F4) == 1) << 7;
        } else {
            INPUT_MAPPING->UpdateHeldCounts();
            FIELD(int, 0x4DC) = FIELD(int, 0x4C0);
            FIELD(int, 0x4E0) = FIELD(int, 0x4C4);
            FIELD(int, 0x4E8) = FIELD(int, 0x4C8);
            FIELD(int, 0x4EC) = FIELD(int, 0x4CC);
            FIELD(int, 0x4F0) = FIELD(int, 0x4D0);
            FIELD(int, 0x4F4) = FIELD(int, 0x4D4);
            relativeBits = FIELD(signed char, 0x66) * FIELD(int, 0x4DC) < 0;
            relativeBits |= static_cast<unsigned char>(FIELD(signed char, 0x66) * FIELD(int, 0x4DC) > 0) << 1;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4E0) < 0) << 2;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4E0) > 0) << 3;
            physicalInputBits = FIELD(int, 0x4DC) < 0;
            physicalInputBits |= static_cast<unsigned char>(FIELD(int, 0x4DC) > 0) << 1;
            physicalInputBits |= static_cast<unsigned char>(FIELD(int, 0x4E0) < 0) << 2;
            physicalInputBits |= static_cast<unsigned char>(FIELD(int, 0x4E0) > 0) << 3;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4E8) == 1) << 4;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4EC) == 1) << 5;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4F0) == 1) << 6;
            relativeBits |= static_cast<unsigned char>(FIELD(int, 0x4F4) == 1) << 7;
            physicalInputBits |= static_cast<unsigned char>(FIELD(unsigned int, 0x4E8) > 0) << 4;
            physicalInputBits |= static_cast<unsigned char>(FIELD(unsigned int, 0x4EC) > 0) << 5;
            physicalInputBits |= static_cast<unsigned char>(FIELD(unsigned int, 0x4F0) > 0) << 6;
            physicalInputBits |= static_cast<unsigned char>(FIELD(unsigned int, 0x4F4) > 0) << 7;
            if (g_FrameClockMode == 1) PRESS->PushBack(physicalInputBits);
        }
        if (FIELD(short, 0x60) >= 300 && (FIELD(int, 0x4E8) == 1 || FIELD(int, 0x4EC) == 1 || FIELD(int, 0x4F0) == 1 || FIELD(int, 0x4F4) == 1)) {
            FIELD(signed char, 0x510) = 10;
            FIELD(int, 0x4F8) = FIELD(int, 0x4DC);
            FIELD(int, 0x4FC) = FIELD(int, 0x4E0);
            FIELD(int, 0x500) = FIELD(int, 0x4E8) == 1;
            FIELD(int, 0x504) = FIELD(int, 0x4EC) == 1;
            FIELD(int, 0x508) = FIELD(int, 0x4F0) == 1;
            FIELD(int, 0x50C) = FIELD(int, 0x4F4) == 1;
        }
        if (FIELD(short, 0x60) < 300 || FIELD(signed char, 0x510) <= 0) {
            ClearAuxiliaryWords();
            FIELD(signed char, 0x510) = 0;
        }
        if (FIELD(signed char, 0x510) > 0) --FIELD(signed char, 0x510);
        HISTORY->PushBack(relativeBits);
        HISTORY->PopFront();
        FinishInput();
    }
    if (FIELD(signed char, 0x2CD) == 0) FIELD(int, 0x4E4) = FIELD(int, 0x4E8);
    else FIELD(int, 0x4E4) = 0;
}
#undef INPUT_MAPPING
#undef HISTORY
#undef SAMPLES
#undef AUXILIARY
#undef PRESS
#undef FIELD
