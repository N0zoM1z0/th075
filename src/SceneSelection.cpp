#include "Graphics.hpp"
#include <stdlib.h>

// Partial pointer-only interfaces; no private owner is instantiated or embedded.
class SelectionSoundF130 { public: void Play(int); };
extern SelectionSoundF130* g_SelectionSound;
int __cdecl AbsoluteSelectionInputF130(int);
extern signed char g_SelectionStageF131;
class ChoiceAnimationF131 { public: void Update(signed char side); };
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
    if (FIELD(signed char, 0xF2) > 0) horizontalDirection = 1;
    else horizontalDirection = (HELD(0xC) > 0) * 2 - 1;
    if (AbsoluteSelectionInputF130(HELD(0xC)) == 1 ||
        (AbsoluteSelectionInputF130(HELD(0xC)) > 60 && AbsoluteSelectionInputF130(HELD(0xC)) % 15 == 0) ||
        (FIELD(signed char, 0xF2) > 0 && side == 0)) {
        FIELD(signed char, 0xF1) = (FIELD(signed char, 0xF1) + 10 + horizontalDirection) % 10;
        if (FIELD(signed char, 0xF1) == 8 && FIELD(signed char, 0xF0) == 1)
            g_SelectionStageF131 = 20;
        else if (FIELD(signed char, 0xF1) < 6)
            g_SelectionStageF131 = FIELD(signed char, 0xF1) + FIELD(signed char, 0xF0) * 10;
        else
            g_SelectionStageF131 = FIELD(signed char, 0xF1);
        while (FIELD(unsigned char, 0x78 + g_SelectionStageF131) == 0) {
            FIELD(signed char, 0xF1) = (FIELD(signed char, 0xF1) + 10 + horizontalDirection) % 10;
            if (FIELD(signed char, 0xF1) == 8 && FIELD(signed char, 0xF0) == 1)
                g_SelectionStageF131 = 20;
            else if (FIELD(signed char, 0xF1) < 6)
                g_SelectionStageF131 = FIELD(signed char, 0xF1) + FIELD(signed char, 0xF0) * 10;
            else
                g_SelectionStageF131 = FIELD(signed char, 0xF1);
        }
        if (FIELD(signed char, 0xF2) > 0) {
            FIELD(signed char, 0xF0) = rand() % 2;
            if (FIELD(signed char, 0xF1) == 8 && FIELD(signed char, 0xF0) == 1)
                g_SelectionStageF131 = 20;
            else if (FIELD(signed char, 0xF1) < 6)
                g_SelectionStageF131 = FIELD(signed char, 0xF1) + FIELD(signed char, 0xF0) * 10;
            else
                g_SelectionStageF131 = FIELD(signed char, 0xF1);
            while (FIELD(unsigned char, 0x78 + g_SelectionStageF131) == 0) {
                FIELD(signed char, 0xF0) = rand() % 2;
                if (FIELD(signed char, 0xF1) == 8 && FIELD(signed char, 0xF0) == 1)
                    g_SelectionStageF131 = 20;
                else if (FIELD(signed char, 0xF1) < 6)
                    g_SelectionStageF131 = FIELD(signed char, 0xF1) + FIELD(signed char, 0xF0) * 10;
                else
                    g_SelectionStageF131 = FIELD(signed char, 0xF1);
            }
        }
    } else if (AbsoluteSelectionInputF130(HELD(0x10)) == 1 || HELD(0x20) == 1 ||
        (AbsoluteSelectionInputF130(HELD(0x10)) % 15 == 0 && AbsoluteSelectionInputF130(HELD(0x10)) > 60)) {
        verticalDirection = (HELD(0x10) > 0) * 2 - 1;
        FIELD(signed char, 0xF0) = (FIELD(signed char, 0xF0) + 2 + verticalDirection) % 2;
        if (FIELD(signed char, 0xF1) == 8 && FIELD(signed char, 0xF0) == 1)
            g_SelectionStageF131 = 20;
        else if (FIELD(signed char, 0xF1) < 6)
            g_SelectionStageF131 = FIELD(signed char, 0xF1) + FIELD(signed char, 0xF0) * 10;
        else
            g_SelectionStageF131 = FIELD(signed char, 0xF1);
        while (FIELD(unsigned char, 0x78 + g_SelectionStageF131) == 0) {
            FIELD(signed char, 0xF0) = (FIELD(signed char, 0xF0) + 2 + verticalDirection) % 2;
            if (FIELD(signed char, 0xF1) == 8 && FIELD(signed char, 0xF0) == 1)
                g_SelectionStageF131 = 20;
            else if (FIELD(signed char, 0xF1) < 6)
                g_SelectionStageF131 = FIELD(signed char, 0xF1) + FIELD(signed char, 0xF0) * 10;
            else
                g_SelectionStageF131 = FIELD(signed char, 0xF1);
        }
        g_SelectionSound->Play(39);
    }
    if (HELD(0x14) == 1 || FIELD(signed char, 0xF2 + side) == -1) {
        FIELD(signed char, 0x96) = 8;
        FIELD(signed char, 0x97) = 8;
        g_SelectionSound->Play(45);
    }
    if (HELD(0x1C) == 1) FIELD(signed char, 0xF2) = rand() % 10 + 30;
    if (side == 0 && FIELD(signed char, 0xF2) > 0) --FIELD(signed char, 0xF2);
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
};
#define RECORDS reinterpret_cast<ResultRecordsF131*>(reinterpret_cast<char*>(this) + 0x18)
#define PAGE FIELD(short, 0x1BC)
#define CHARACTER FIELD(signed char, 0x1C3)
short ResultSelectionF131::Update() {
    PollInput();
    Render();
    Graphics::Present();
    if (FIELD(signed char, 0x1C5) == 0) {
        if (FIELD(signed char, 0x1C0) < 0) {
            g_SelectionSound->Play(39);
            --FIELD(signed char, 0x1C4);
            if (FIELD(signed char, 0x1C4) < 0) FIELD(signed char, 0x1C4) = 3;
            BuildCounterPage();
        }
        if (FIELD(signed char, 0x1C0) > 0) {
            g_SelectionSound->Play(39);
            ++FIELD(signed char, 0x1C4);
            if (FIELD(signed char, 0x1C4) > 3) FIELD(signed char, 0x1C4) = 0;
            BuildCounterPage();
        }
        if (FIELD(signed char, 0x1BF) < 0) {
            g_SelectionSound->Play(39);
            --CHARACTER;
            if (CHARACTER < 0) CHARACTER = 9;
            if (CHARACTER == 9 && FIELD(unsigned char, 0x1CF) == 0) --CHARACTER;
            if (CHARACTER == 8 && FIELD(unsigned char, 0x1CE) == 0) --CHARACTER;
            if (CHARACTER == 7 && FIELD(unsigned char, 0x1CD) == 0) --CHARACTER;
            if (CHARACTER == 6 && FIELD(unsigned char, 0x1CC) == 0) --CHARACTER;
            LoadSelectedCharacterResources();
            BuildCounterPage();
        }
        if (FIELD(signed char, 0x1BF) > 0) {
            g_SelectionSound->Play(39);
            ++CHARACTER;
            if (CHARACTER == 6 && FIELD(unsigned char, 0x1CC) == 0) ++CHARACTER;
            if (CHARACTER == 7 && FIELD(unsigned char, 0x1CD) == 0) ++CHARACTER;
            if (CHARACTER == 8 && FIELD(unsigned char, 0x1CE) == 0) ++CHARACTER;
            if (CHARACTER == 9 && FIELD(unsigned char, 0x1CF) == 0) ++CHARACTER;
            if (CHARACTER > 9) CHARACTER = 0;
            LoadSelectedCharacterResources();
            BuildCounterPage();
        }
    } else {
        if (FIELD(signed char, 0x1C0) < 0) {
            g_SelectionSound->Play(39);
            --PAGE;
            if (PAGE < 0) PAGE = (RECORDS->Count() - 1) / 10;
            BuildRecordPage();
        }
        if (FIELD(signed char, 0x1C0) > 0) {
            g_SelectionSound->Play(39);
            ++PAGE;
            if (PAGE > (static_cast<int>(RECORDS->Count()) - 1) / 10) PAGE = 0;
            BuildRecordPage();
        }
        if (FIELD(signed char, 0x1BF) < 0) {
            g_SelectionSound->Play(39);
            --CHARACTER;
            if (CHARACTER < 0) CHARACTER = 9;
            if (CHARACTER == 9 && FIELD(unsigned char, 0x1CF) == 0) --CHARACTER;
            if (CHARACTER == 8 && FIELD(unsigned char, 0x1CE) == 0) --CHARACTER;
            if (CHARACTER == 7 && FIELD(unsigned char, 0x1CD) == 0) --CHARACTER;
            if (CHARACTER == 6 && FIELD(unsigned char, 0x1CC) == 0) --CHARACTER;
            LoadSelectedCharacterResources();
            PAGE = 0;
            BuildRecordPage();
        }
        if (FIELD(signed char, 0x1BF) > 0) {
            g_SelectionSound->Play(39);
            ++CHARACTER;
            if (CHARACTER == 6 && FIELD(unsigned char, 0x1CC) == 0) ++CHARACTER;
            if (CHARACTER == 7 && FIELD(unsigned char, 0x1CD) == 0) ++CHARACTER;
            if (CHARACTER == 8 && FIELD(unsigned char, 0x1CE) == 0) ++CHARACTER;
            if (CHARACTER == 9 && FIELD(unsigned char, 0x1CF) == 0) ++CHARACTER;
            if (CHARACTER > 9) CHARACTER = 0;
            LoadSelectedCharacterResources();
            PAGE = 0;
            BuildRecordPage();
        }
    }
    if (FIELD(unsigned char, 0x1BE) < 255) FIELD(unsigned char, 0x1BE) += 25;
    if (FIELD(signed char, 0x1C1) == 1) {
        if (FIELD(signed char, 0x1C5) == 0) {
            BuildRecordPage();
            g_SelectionSound->Play(45);
            PAGE = 0;
            FIELD(signed char, 0x1C5) = 1;
        } else {
            g_SelectionSound->Play(45);
            FIELD(signed char, 0x1C5) = 0;
            BuildCounterPage();
        }
    }
    if (FIELD(signed char, 0x1C2) == 1) {
        g_SelectionSound->Play(40);
        return 0x2202;
    }
    return 0xE;
}
#undef CHARACTER
#undef PAGE
#undef RECORDS
#undef FIELD
