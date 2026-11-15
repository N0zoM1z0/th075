#include "Graphics.hpp"
#include <stdlib.h>

// Partial pointer-only interfaces; no private owner is instantiated or embedded.
class SelectionSoundF130 { public: void Play(int); };
extern SelectionSoundF130* g_SelectionSound;
int __cdecl AbsoluteSelectionInputF130(int);
extern signed char g_SelectionStageF131;
class ChoiceAnimationF131 { public: void Update(signed char side); public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x096 - 0x000];
    signed char field096;
    signed char field097;
    unsigned char unknown098[0x0F0 - 0x098];
    signed char field0F0;
    signed char field0F1;
    signed char field0F2;
};
#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define ANIM(offset) reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))[side]
#define HELD(offset) (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + (offset) + side * 28))
void ChoiceAnimationF131::Update(signed char side) {
    signed char horizontalDirection;
    int verticalDirection;
    if (ANIM(0xA0) < 80.0f) ANIM(0xA0) = ANIM(0xA0) + 4.0f;
    if (ANIM(0xA8) < 40.0f) ANIM(0xA8) = ANIM(0xA8) + 2.0f;
    if (ANIM(0xB0) < 80.0f) ANIM(0xB0) = ANIM(0xB0) + 4.0f;
    if (ANIM(0xB8) < 40.0f) ANIM(0xB8) = ANIM(0xB8) + 2.0f;
    if (ANIM(0xC0) > 0.0f) ANIM(0xC0) = ANIM(0xC0) - 1.0f;
    if (ANIM(0xC0) == 60.0f) ANIM(0xC0) = 0;
    if (HELD(0x18) == 1) {
        g_SelectionSound->Play(40);
        FIELD(signed char, 0x96 + side) = 0;
        ANIM(0xA0) = 80.0f;
        ANIM(0xA8) = 40.0f;
        ANIM(0xB0) = 80.0f;
        ANIM(0xB8) = 40.0f;
        FIELD(unsigned char, 0xE8 + side) = 1;
    }
    if (FIELD(signed char, 0x96 + (1 - side)) < 4) return;
    if (field0F2 > 0) horizontalDirection = 1;
    else horizontalDirection = (HELD(0xC) > 0) * 2 - 1;
    if (AbsoluteSelectionInputF130(HELD(0xC)) == 1 ||
        (AbsoluteSelectionInputF130(HELD(0xC)) > 60 && AbsoluteSelectionInputF130(HELD(0xC)) % 15 == 0) ||
        (field0F2 > 0 && side == 0)) {
        field0F1 = (field0F1 + 10 + horizontalDirection) % 10;
        if (field0F1 == 8 && field0F0 == 1)
            g_SelectionStageF131 = 20;
        else if (field0F1 < 6)
            g_SelectionStageF131 = field0F1 + field0F0 * 10;
        else
            g_SelectionStageF131 = field0F1;
        while (FIELD(unsigned char, 0x78 + g_SelectionStageF131) == 0) {
            field0F1 = (field0F1 + 10 + horizontalDirection) % 10;
            if (field0F1 == 8 && field0F0 == 1)
                g_SelectionStageF131 = 20;
            else if (field0F1 < 6)
                g_SelectionStageF131 = field0F1 + field0F0 * 10;
            else
                g_SelectionStageF131 = field0F1;
        }
        if (field0F2 > 0) {
            field0F0 = rand() % 2;
            if (field0F1 == 8 && field0F0 == 1)
                g_SelectionStageF131 = 20;
            else if (field0F1 < 6)
                g_SelectionStageF131 = field0F1 + field0F0 * 10;
            else
                g_SelectionStageF131 = field0F1;
            while (FIELD(unsigned char, 0x78 + g_SelectionStageF131) == 0) {
                field0F0 = rand() % 2;
                if (field0F1 == 8 && field0F0 == 1)
                    g_SelectionStageF131 = 20;
                else if (field0F1 < 6)
                    g_SelectionStageF131 = field0F1 + field0F0 * 10;
                else
                    g_SelectionStageF131 = field0F1;
            }
        }
    } else if (AbsoluteSelectionInputF130(HELD(0x10)) == 1 || HELD(0x20) == 1 ||
        (AbsoluteSelectionInputF130(HELD(0x10)) % 15 == 0 && AbsoluteSelectionInputF130(HELD(0x10)) > 60)) {
        verticalDirection = (HELD(0x10) > 0) * 2 - 1;
        field0F0 = (field0F0 + 2 + verticalDirection) % 2;
        if (field0F1 == 8 && field0F0 == 1)
            g_SelectionStageF131 = 20;
        else if (field0F1 < 6)
            g_SelectionStageF131 = field0F1 + field0F0 * 10;
        else
            g_SelectionStageF131 = field0F1;
        while (FIELD(unsigned char, 0x78 + g_SelectionStageF131) == 0) {
            field0F0 = (field0F0 + 2 + verticalDirection) % 2;
            if (field0F1 == 8 && field0F0 == 1)
                g_SelectionStageF131 = 20;
            else if (field0F1 < 6)
                g_SelectionStageF131 = field0F1 + field0F0 * 10;
            else
                g_SelectionStageF131 = field0F1;
        }
        g_SelectionSound->Play(39);
    }
    if (HELD(0x14) == 1 || FIELD(signed char, 0xF2 + side) == -1) {
        field096 = 8;
        field097 = 8;
        g_SelectionSound->Play(45);
    }
    if (HELD(0x1C) == 1) field0F2 = rand() % 10 + 30;
    if (side == 0 && field0F2 > 0) --field0F2;
}
#undef HELD
#undef ANIM

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
#undef FIELD
