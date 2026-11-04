#include "CharacterAuxAction.hpp"

// Borrow the four real actor axes without introducing new C++ struct
// declarations into the VC7.1 switch translation unit. Definitions of
// complete types before the function change original $L label identities.
#define F1135_POSITION_X() FLOAT(0x44)
#define F1135_POSITION_Y() FLOAT(0x48)
#define F1135_MOTION_X() FLOAT(0x50)
#define F1135_MOTION_Y() FLOAT(0x54)

// Borrow only the *signed 16-bit* original action/stage/frame and
// independent animation/tick count WORDs; preserve native FIELD
// macro expansion and exact original VC7.1 $L switch identities.
#define F1136_ACTION_STAGE() FIELD(short, 0x62)
#define F1136_ACTION_FRAME() FIELD(short, 0x64)
#define F1136_ANIMATION_ACTION() FIELD(short, 0x70)
#define F1136_ACTION_TICK() FIELD(short, 0x74)
// Existing complete exact fighter-render code independently proves
// native +0x1C/+0x20 adjacent scales and +0x28/+0x2C/+0x30
// physical rotation floats. Reuse the original FLOAT expression
// grammar to preserve every original VC7.1 switch local symbol.
#define F1139_SCALE_X() FLOAT(0x1C)
#define F1139_SCALE_Y() FLOAT(0x20)
#define F1139_ROTATE_AT28() FLOAT(0x28)
#define F1139_ROTATE_AT2C() FLOAT(0x2C)
#define F1139_ROTATE_AT30() FLOAT(0x30)

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this) + offset))
#define FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + offset)

void CharacterAuxObject::AdvanceActionAt005FAE30()
{
    switch (FIELD(short, 0x60)) {
    case 1:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.5f;
            F1139_SCALE_Y() = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT28() = ChooseIntegerRange(0, 45);
            F1139_ROTATE_AT2C() = ChooseIntegerRange(0, 45);
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 45);
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.3f - F1136_ACTION_TICK() * 0.035f);
        F1139_SCALE_Y() += (0.3f - F1136_ACTION_TICK() * 0.035f);
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 30;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 2:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.5f;
            F1139_SCALE_Y() = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT28() = ChooseIntegerRange(0, 45);
            F1139_ROTATE_AT2C() = ChooseIntegerRange(0, 45);
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 45);
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 1 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(101, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(102, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.3f - F1136_ACTION_TICK() * 0.035f);
        F1139_SCALE_Y() += (0.3f - F1136_ACTION_TICK() * 0.035f);
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 3:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.5f;
            F1139_SCALE_Y() = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT28() = ChooseIntegerRange(0, 45);
            F1139_ROTATE_AT2C() = ChooseIntegerRange(0, 45);
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 45);
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 1 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(103, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.3f - F1136_ACTION_TICK() * 0.035f);
        F1139_SCALE_Y() += (0.3f - F1136_ACTION_TICK() * 0.035f);
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 5:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 4.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = 100 - ChooseIntegerRange(0, 20);
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        F1139_SCALE_X() += 0.5f - F1136_ACTION_TICK() * 0.035f;
        F1139_SCALE_Y() *= 0.75f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 60) {
                FIELD(unsigned char, 0x11) -= 60;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 60) FIELD(unsigned char, 0x12) -= 60;
            if (FIELD(unsigned char, 0x13) > 60) FIELD(unsigned char, 0x13) -= 60;
        }
        ++F1136_ACTION_TICK();
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 6:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 4.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = -35 - ChooseIntegerRange(0, 20);
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        F1139_SCALE_X() += 0.5f - F1136_ACTION_TICK() * 0.035f;
        F1139_SCALE_Y() *= 0.75f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 60) {
                FIELD(unsigned char, 0x11) -= 60;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 60) FIELD(unsigned char, 0x12) -= 60;
            if (FIELD(unsigned char, 0x13) > 60) FIELD(unsigned char, 0x13) -= 60;
        }
        ++F1136_ACTION_TICK();
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 7:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 4.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = 10 - ChooseIntegerRange(0, 20);
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        F1139_SCALE_X() += 0.5f - F1136_ACTION_TICK() * 0.035f;
        F1139_SCALE_Y() *= 0.75f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 60) {
                FIELD(unsigned char, 0x11) -= 60;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 60) FIELD(unsigned char, 0x12) -= 60;
            if (FIELD(unsigned char, 0x13) > 60) FIELD(unsigned char, 0x13) -= 60;
        }
        ++F1136_ACTION_TICK();
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 8:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 4.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = 55 - ChooseIntegerRange(0, 20);
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        F1139_SCALE_X() += 0.5f - F1136_ACTION_TICK() * 0.035f;
        F1139_SCALE_Y() *= 0.75f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 60) {
                FIELD(unsigned char, 0x11) -= 60;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 60) FIELD(unsigned char, 0x12) -= 60;
            if (FIELD(unsigned char, 0x13) > 60) FIELD(unsigned char, 0x13) -= 60;
        }
        ++F1136_ACTION_TICK();
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 13:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = ChooseIntegerRange(0, 10) * 0.1f + 3.0f;
            F1139_SCALE_Y() = F1139_SCALE_X();
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(138, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        ++F1136_ACTION_TICK();
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 14:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.5f;
            F1139_SCALE_Y() = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(105, F1135_POSITION_X() - FIELD(signed char, 0x66) * 60, F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.3f - F1136_ACTION_TICK() * 0.02f);
        F1139_SCALE_Y() += (0.3f - F1136_ACTION_TICK() * 0.02f);
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 15:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.5f;
            F1139_SCALE_Y() = F1139_SCALE_X();
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(139, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(140, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        F1139_SCALE_X() += (0.2f - F1136_ACTION_TICK() * 0.02f) * ((0.2f - F1136_ACTION_TICK() * 0.02f) > 0.0f);
        F1139_SCALE_Y() += (0.2f - F1136_ACTION_TICK() * 0.02f) * ((0.2f - F1136_ACTION_TICK() * 0.02f) > 0.0f);
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x12) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        ++F1136_ACTION_TICK();
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 50:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.25f;
            F1139_SCALE_Y() = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT2C() = 60.0f;
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.2f - F1136_ACTION_TICK() * 0.02f) * ((0.2f - F1136_ACTION_TICK() * 0.02f) > 0.0f);
        F1139_SCALE_Y() += (0.2f - F1136_ACTION_TICK() * 0.02f) * ((0.2f - F1136_ACTION_TICK() * 0.02f) > 0.0f);
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x12) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 51:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.25f;
            F1139_SCALE_Y() = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT2C() = 60.0f;
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(105, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(105, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(105, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(105, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(105, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(105, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(105, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(105, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.2f - F1136_ACTION_TICK() * 0.02f) * ((0.2f - F1136_ACTION_TICK() * 0.02f) > 0.0f);
        F1139_SCALE_Y() += (0.2f - F1136_ACTION_TICK() * 0.02f) * ((0.2f - F1136_ACTION_TICK() * 0.02f) > 0.0f);
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x14) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 52:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(107, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(107, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(107, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(107, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(107, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(107, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(107, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(107, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(107, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(107, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 53:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(108, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(109, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(110, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(110, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(110, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(110, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(110, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(110, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(110, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(110, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(104, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 54:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(137, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(111, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(111, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(111, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(111, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(111, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(111, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(111, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(111, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(111, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(111, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 55:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        if (F1136_ACTION_STAGE() == 1 && F1136_ACTION_FRAME() == 0) {
            SpawnPeer(112, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(113, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(114, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.5f - F1136_ACTION_TICK() * 0.035f) * ((0.5f - F1136_ACTION_TICK() * 0.035f) > 0.0f);
        F1139_SCALE_Y() += (0.5f - F1136_ACTION_TICK() * 0.035f) * ((0.5f - F1136_ACTION_TICK() * 0.035f) > 0.0f);
        if (F1136_ACTION_STAGE() > 0 && F1136_ACTION_FRAME() > 3) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 56:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
            SpawnPeer(57, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(57, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(57, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(57, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(57, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(57, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(57, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.5f - F1136_ACTION_TICK() * 0.05f) * ((0.5f - F1136_ACTION_TICK() * 0.05f) > 0.0f) + 0.05f;
        F1139_SCALE_Y() += (0.5f - F1136_ACTION_TICK() * 0.05f) * ((0.5f - F1136_ACTION_TICK() * 0.05f) > 0.0f) + 0.05f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x12) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 57:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = AngleAt00483300(F1135_MOTION_Y(), F1135_MOTION_X()) / 0.017453288659453392f;
            F1136_ACTION_TICK() = 0;
        }
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() -= F1135_MOTION_Y();
        ++F1136_ACTION_TICK();
        if (F1136_ACTION_STAGE() > 0) {
            F1139_SCALE_X() += 0.1f;
            F1139_SCALE_Y() *= 0.9f;
            if (FIELD(unsigned char, 0x11) < 8) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 8;
            }
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 60:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.25f;
            F1139_SCALE_Y() = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT28() = 75.0f;
            FIELD(short, 0x1A) = FIELD(signed char, 0x66) * 350;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.2f - F1136_ACTION_TICK() * 0.015f);
        F1139_SCALE_Y() += (0.2f - F1136_ACTION_TICK() * 0.015f);
        if (F1136_ACTION_STAGE() >= 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 62:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = static_cast<short>(ChooseIntegerRange(0, 359));
            FLOAT(0x80) = F1136_ACTION_TICK() + 180;
            SetPolarVelocity(F1136_ACTION_TICK(), 500.0f);
            SpawnPeer(63, F1135_POSITION_X() + F1135_MOTION_X(), F1135_POSITION_Y() + F1135_MOTION_Y(), 1, 1);
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() -= 0.03f;
        F1139_SCALE_Y() -= 0.03f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x12) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 63:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
            SetPolarVelocity(FLOAT(0x80), 15.0f);
        }
        if (F1136_ACTION_TICK() == 0) {
            if (FIELD(unsigned char, 0x11) < 215) {
                FIELD(unsigned char, 0x11) += 40;
            }
            else {
                FIELD(unsigned char, 0x11) = 255;
                F1136_ACTION_TICK() = 1;
            }
        }
        if (F1136_ACTION_TICK() == 0) {
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
                F1136_ACTION_TICK() = 2;
            }
        }
        F1139_ROTATE_AT30() += 5.0f;
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() += F1135_MOTION_Y();
        F1139_SCALE_X() -= 0.033f;
        F1139_SCALE_Y() -= 0.033f;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 64:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = static_cast<short>(ChooseIntegerRange(0, 359));
            FLOAT(0x80) = F1136_ACTION_TICK() + 180;
            SetPolarVelocity(F1136_ACTION_TICK(), 500.0f);
            SpawnPeer(65, F1135_POSITION_X() + F1135_MOTION_X(), F1135_POSITION_Y() + F1135_MOTION_Y(), 1, 1);
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() -= 0.03f;
        F1139_SCALE_Y() -= 0.03f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x12) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 65:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
            SetPolarVelocity(FLOAT(0x80), 15.0f);
        }
        if (F1136_ACTION_TICK() == 0) {
            if (FIELD(unsigned char, 0x11) < 215) {
                FIELD(unsigned char, 0x11) += 40;
            }
            else {
                FIELD(unsigned char, 0x11) = 255;
                F1136_ACTION_TICK() = 1;
            }
        }
        if (F1136_ACTION_TICK() == 0) {
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
                F1136_ACTION_TICK() = 2;
            }
        }
        F1139_ROTATE_AT30() += 5.0f;
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() += F1135_MOTION_Y();
        F1139_SCALE_X() -= 0.033f;
        F1139_SCALE_Y() -= 0.033f;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 100:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SetPolarVelocity(rand(), rand() * 0.0005);
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.5f;
            F1139_SCALE_Y() = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() += F1135_MOTION_Y();
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() *= 0.85f;
        F1139_SCALE_Y() *= 0.85f;
        if (FIELD(unsigned char, 0x11) < 15) {
            FIELD(unsigned char, 0x11) = 0;
        }
        else {
            FIELD(unsigned char, 0x11) -= 15;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 101:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.7f;
            F1139_SCALE_Y() = 0.7f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.2f - F1136_ACTION_TICK() * 0.02f);
        F1139_SCALE_Y() += (0.2f - F1136_ACTION_TICK() * 0.02f);
        if (FIELD(unsigned char, 0x11) > 30) {
            FIELD(unsigned char, 0x11) -= 15;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
        }
        if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 15;
        if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 15;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 102:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1136_ACTION_TICK() = static_cast<short>(ChooseIntegerRange(0, 750) + 1000);
            FIELD(short, 0x76) = static_cast<short>(ChooseIntegerRange(0, 360) - 180);
        }
        F1136_ACTION_TICK() = static_cast<short>(F1136_ACTION_TICK() * 0.95f);
        SetPolarVelocity(FIELD(short, 0x76), F1136_ACTION_TICK() * 0.01f);
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() += F1135_MOTION_Y();
        F1139_ROTATE_AT30() += 5.0f;
        if (F1136_ACTION_FRAME() > 5) {
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
            if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 103:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.7f;
            F1139_SCALE_Y() = 0.7f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.3f - F1136_ACTION_TICK() * 0.02f);
        F1139_SCALE_Y() += (0.3f - F1136_ACTION_TICK() * 0.02f);
        if (FIELD(unsigned char, 0x11) > 30) {
            FIELD(unsigned char, 0x11) -= 15;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
        }
        if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 15;
        if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 15;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 104:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = AngleAt00483300(F1135_MOTION_Y(), F1135_MOTION_X()) / 0.017453288659453392f;
            F1136_ACTION_TICK() = 0;
        }
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() -= F1135_MOTION_Y();
        ++F1136_ACTION_TICK();
        if (F1136_ACTION_STAGE() > 0) {
            F1139_SCALE_Y() *= 0.85f;
            if (FIELD(unsigned char, 0x11) < 15) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 15;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 105:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = AngleAt00483300(F1135_MOTION_Y(), F1135_MOTION_X()) / 0.017453288659453392f;
            F1136_ACTION_TICK() = 0;
        }
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() -= F1135_MOTION_Y();
        ++F1136_ACTION_TICK();
        if (F1136_ACTION_STAGE() > 0) {
            F1139_SCALE_Y() *= 0.85f;
            if (FIELD(unsigned char, 0x11) < 15) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 15;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x14) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 106:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.25f;
            F1139_SCALE_Y() = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT2C() = 65.0f;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.2f - F1136_ACTION_TICK() * 0.015f);
        F1139_SCALE_Y() += (0.2f - F1136_ACTION_TICK() * 0.015f);
        if (F1136_ACTION_STAGE() >= 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 107:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            FIELD(short, 0x78) = static_cast<short>(ChooseIntegerRange(50, 110));
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = FIELD(short, 0x78) * 0.01f;
            F1139_SCALE_Y() = FIELD(short, 0x78) * 0.01f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = static_cast<short>(ChooseIntegerRange(0, 750) + 1000);
            FIELD(short, 0x76) = static_cast<short>(ChooseIntegerRange(0, 360) - 180);
        }
        F1136_ACTION_TICK() = static_cast<short>(F1136_ACTION_TICK() * 0.96f);
        SetPolarVelocity(FIELD(short, 0x76), F1136_ACTION_TICK() * 0.01f);
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() += F1135_MOTION_Y();
        if (F1136_ACTION_FRAME() > 2) {
            F1139_SCALE_X() *= 0.85f;
            F1139_SCALE_Y() *= 0.85f;
            if (FIELD(unsigned char, 0x11) < 15) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 15;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 15;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 15;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 108:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.25f;
            F1139_SCALE_Y() = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = 0.0f;
            F1136_ACTION_TICK() = 0;
        }
        F1139_ROTATE_AT30() += 5.0f;
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.4f - F1136_ACTION_TICK() * 0.01f);
        F1139_SCALE_Y() += (0.4f - F1136_ACTION_TICK() * 0.01f);
        if (F1136_ACTION_FRAME() >= 30) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 109:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.25f;
            F1139_SCALE_Y() = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = 45.0f;
            F1136_ACTION_TICK() = 0;
        }
        F1139_ROTATE_AT30() += 5.0f;
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.4f - F1136_ACTION_TICK() * 0.01f);
        F1139_SCALE_Y() += (0.4f - F1136_ACTION_TICK() * 0.01f);
        if (F1136_ACTION_FRAME() >= 30) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 110:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            FIELD(short, 0x78) = static_cast<short>(ChooseIntegerRange(50, 110));
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = static_cast<short>(ChooseIntegerRange(0, 500) + 1500);
            FIELD(short, 0x76) = static_cast<short>(ChooseIntegerRange(0, 360));
            F1139_ROTATE_AT30() = FIELD(short, 0x76) - 90;
        }
        F1136_ACTION_TICK() = static_cast<short>(F1136_ACTION_TICK() * 0.97f);
        SetPolarVelocity(FIELD(short, 0x76) - 180, F1136_ACTION_TICK() * 0.01f);
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() += F1135_MOTION_Y();
        F1139_SCALE_Y() += 0.05f;
        if (F1136_ACTION_FRAME() > 15) {
            if (FIELD(unsigned char, 0x11) < 10) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 10;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 5;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 5;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 111:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = ChooseIntegerRange(20, 100) * 0.01f;
            F1139_SCALE_Y() = F1139_SCALE_X();
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            SetPolarVelocity(ChooseIntegerRange(-155, -25), ChooseIntegerRange(100, 250) * 0.1f);
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
        }
        F1135_MOTION_Y() -= 0.75f;
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() += F1135_MOTION_Y();
        F1139_ROTATE_AT30() += 5.0f;
        if (F1135_POSITION_Y() < 40.0f && F1135_MOTION_Y() < 0.0f && ChooseIntegerRange(0, 100) < 10) {
            F1135_MOTION_Y() = -F1135_MOTION_Y();
        }
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) < 10) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 10;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 5;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 5;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 112:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.5f;
            F1139_SCALE_Y() = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT28() = 65.0f;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.5f - F1136_ACTION_TICK() * 0.04f) * ((0.5f - F1136_ACTION_TICK() * 0.04f) > 0.0f) + 0.02f;
        F1139_SCALE_Y() += (0.5f - F1136_ACTION_TICK() * 0.04f) * ((0.5f - F1136_ACTION_TICK() * 0.04f) > 0.0f) + 0.02f;
        if (F1136_ACTION_FRAME() >= 10) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 113:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.7f;
            F1139_SCALE_Y() = 0.7f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.3f - F1136_ACTION_TICK() * 0.02f);
        F1139_SCALE_Y() += (0.3f - F1136_ACTION_TICK() * 0.02f);
        if (FIELD(unsigned char, 0x11) > 30) {
            FIELD(unsigned char, 0x11) -= 15;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
        }
        if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 15;
        if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 15;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 114:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = ChooseIntegerRange(50, 120) * 1.0f * 0.01f;
            F1139_SCALE_Y() = F1139_SCALE_X();
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = static_cast<short>(ChooseIntegerRange(0, 1000) + 4000);
            FIELD(short, 0x76) = static_cast<short>(ChooseIntegerRange(0, 360));
        }
        F1136_ACTION_TICK() = static_cast<short>(F1136_ACTION_TICK() * 0.9f);
        SetPolarVelocity(FIELD(short, 0x76) - 180, F1136_ACTION_TICK() * 0.01f);
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() += F1135_MOTION_Y();
        if (F1136_ACTION_FRAME() > 20) {
            F1139_SCALE_X() *= 0.9f;
            F1139_SCALE_Y() *= 0.9f;
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 115:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 2.0f;
            F1139_SCALE_Y() = 2.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
            for (int particle = 0; particle < 25; ++particle)
                SpawnPeer(122, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(141, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(142, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(143, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(144, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(145, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 116:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 2.0f;
            F1139_SCALE_Y() = 2.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
            SpawnPeer(131, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(132, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(133, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(134, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(135, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(135, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(136, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(136, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(136, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
            SpawnPeer(136, F1135_POSITION_X(), F1135_POSITION_Y(), 1, 1);
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 117:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.2f;
            F1139_SCALE_Y() = 1.2f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT28() = -80.0f;
            F1136_ACTION_TICK() = 0;
        }
        FIELD(short, 0x1A) = 1500;
        FIELD(short, 0x16) = 0;
        F1139_ROTATE_AT30() += 3.0f;
        F1139_SCALE_X() += 0.02f;
        F1139_SCALE_Y() += 0.02f;
        if (F1136_ACTION_STAGE() > 0) FIELD(unsigned char, 0x11) -= 6;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 118:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.4f;
            F1139_SCALE_Y() = 1.4f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT28() = -80.0f;
            F1136_ACTION_TICK() = 0;
        }
        FIELD(short, 0x1A) = 1500;
        FIELD(short, 0x16) = 0;
        F1139_ROTATE_AT30() += 3.0f;
        F1139_SCALE_X() += 0.02f;
        F1139_SCALE_Y() += 0.02f;
        if (F1136_ACTION_STAGE() > 0) FIELD(unsigned char, 0x11) -= 6;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 119:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.1f - F1136_ACTION_TICK() * 0.01f) * ((0.1f - F1136_ACTION_TICK() * 0.01f) > 0.0f) + 0.01f;
        F1139_SCALE_Y() += (0.1f - F1136_ACTION_TICK() * 0.01f) * ((0.1f - F1136_ACTION_TICK() * 0.01f) > 0.0f) + 0.01f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 120:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.3f - F1136_ACTION_TICK() * 0.03f) * ((0.3f - F1136_ACTION_TICK() * 0.03f) > 0.0f) + 0.03f;
        F1139_SCALE_Y() += (0.3f - F1136_ACTION_TICK() * 0.03f) * ((0.3f - F1136_ACTION_TICK() * 0.03f) > 0.0f) + 0.03f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 121:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.5f - F1136_ACTION_TICK() * 0.05f) * ((0.5f - F1136_ACTION_TICK() * 0.05f) > 0.0f) + 0.05f;
        F1139_SCALE_Y() += (0.5f - F1136_ACTION_TICK() * 0.05f) * ((0.5f - F1136_ACTION_TICK() * 0.05f) > 0.0f) + 0.05f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 122:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = AngleAt00483300(F1135_MOTION_Y(), F1135_MOTION_X()) / 0.017453288659453392f;
            F1136_ACTION_TICK() = 0;
        }
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() -= F1135_MOTION_Y();
        ++F1136_ACTION_TICK();
        if (F1136_ACTION_STAGE() > 0) {
            F1139_SCALE_X() += 0.3f;
            F1139_SCALE_Y() *= 0.9f;
            if (FIELD(unsigned char, 0x11) < 8) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 8;
            }
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 123:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 3.5f;
            F1139_SCALE_Y() = 10.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1136_ACTION_TICK() = 0;
        }
        F1139_ROTATE_AT30() += 1.0f;
        F1139_SCALE_X() += 0.01f;
        F1139_SCALE_Y() *= 0.9f;
        if (F1136_ACTION_TICK() > 1) {
            if (FIELD(unsigned char, 0x11) < 15) {
                FIELD(unsigned char, 0x11) = 0;
                ClearField8();
                return;
            }
            FIELD(unsigned char, 0x11) -= 15;
            if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
            if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) {
            ResetSecondaryCounters(1);
            ++F1136_ACTION_TICK();
        }
        break;
    case 124:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 3.5f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1136_ACTION_TICK() = 0;
        }
        F1139_ROTATE_AT30() -= 1.0f;
        F1139_SCALE_X() += 0.01f;
        F1139_SCALE_Y() *= 0.95f;
        if (F1136_ACTION_TICK() > 1) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
                ClearField8();
                return;
            }
            FIELD(unsigned char, 0x11) -= 20;
            if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
            if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) {
            ResetSecondaryCounters(1);
            ++F1136_ACTION_TICK();
        }
        break;
    case 125:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 0.25f;
            F1139_SCALE_Y() = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT2C() = 65.0f;
            FIELD(short, 0x1A) = FIELD(signed char, 0x66) * 350;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.2f - F1136_ACTION_TICK() * 0.015f);
        F1139_SCALE_Y() += (0.2f - F1136_ACTION_TICK() * 0.015f);
        if (F1136_ACTION_STAGE() >= 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 126:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 127:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 128:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 129:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 130:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.5f;
            F1139_SCALE_Y() = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 131:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.1f - F1136_ACTION_TICK() * 0.01f) * ((0.1f - F1136_ACTION_TICK() * 0.01f) > 0.0f) + 0.01f;
        F1139_SCALE_Y() += (0.1f - F1136_ACTION_TICK() * 0.01f) * ((0.1f - F1136_ACTION_TICK() * 0.01f) > 0.0f) + 0.01f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 132:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.3f - F1136_ACTION_TICK() * 0.03f) * ((0.3f - F1136_ACTION_TICK() * 0.03f) > 0.0f) + 0.03f;
        F1139_SCALE_Y() += (0.3f - F1136_ACTION_TICK() * 0.03f) * ((0.3f - F1136_ACTION_TICK() * 0.03f) > 0.0f) + 0.03f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 133:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.5f - F1136_ACTION_TICK() * 0.05f) * ((0.5f - F1136_ACTION_TICK() * 0.05f) > 0.0f) + 0.05f;
        F1139_SCALE_Y() += (0.5f - F1136_ACTION_TICK() * 0.05f) * ((0.5f - F1136_ACTION_TICK() * 0.05f) > 0.0f) + 0.05f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 134:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = AngleAt00483300(F1135_MOTION_Y(), F1135_MOTION_X()) / 0.017453288659453392f;
            F1136_ACTION_TICK() = 0;
        }
        F1135_POSITION_X() += F1135_MOTION_X();
        F1135_POSITION_Y() -= F1135_MOTION_Y();
        ++F1136_ACTION_TICK();
        if (F1136_ACTION_STAGE() > 0) {
            F1139_SCALE_X() += 0.1f;
            F1139_SCALE_Y() *= 0.9f;
            if (FIELD(unsigned char, 0x11) < 8) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 8;
            }
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 135:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 3.5f;
            F1139_SCALE_Y() = 10.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1136_ACTION_TICK() = 0;
        }
        F1139_ROTATE_AT30() += 1.0f;
        F1139_SCALE_X() += 0.01f;
        F1139_SCALE_Y() *= 0.9f;
        if (F1136_ACTION_TICK() > 1) {
            if (FIELD(unsigned char, 0x11) < 15) {
                FIELD(unsigned char, 0x11) = 0;
                ClearField8();
                return;
            }
            FIELD(unsigned char, 0x11) -= 15;
            if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
            if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) {
            ResetSecondaryCounters(1);
            ++F1136_ACTION_TICK();
        }
        break;
    case 136:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 3.5f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1136_ACTION_TICK() = 0;
        }
        F1139_ROTATE_AT30() -= 1.0f;
        F1139_SCALE_X() += 0.01f;
        F1139_SCALE_Y() *= 0.95f;
        if (F1136_ACTION_TICK() > 1) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
                ClearField8();
                return;
            }
            FIELD(unsigned char, 0x11) -= 20;
            if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
            if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) {
            ResetSecondaryCounters(1);
            ++F1136_ACTION_TICK();
        }
        break;
    case 137:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
        }
        F1139_SCALE_X() += 0.05f;
        F1139_SCALE_Y() += 0.05f;
        if (FIELD(unsigned char, 0x11) > 15) {
            FIELD(unsigned char, 0x11) -= 15;
        }
        else {
            ClearField8();
            break;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 138:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT2C() = -40.0f;
            FIELD(short, 0x1A) = FIELD(signed char, 0x66) * 350;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.4f - F1136_ACTION_TICK() * 0.015f);
        F1139_SCALE_Y() += (0.4f - F1136_ACTION_TICK() * 0.015f);
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 30;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 139:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 2.0f;
            F1139_SCALE_Y() = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_SCALE_X() += (0.1f - F1136_ACTION_TICK() * 0.01f) * ((0.1f - F1136_ACTION_TICK() * 0.01f) > 0.0f) + 0.01f;
        F1139_SCALE_Y() += (0.1f - F1136_ACTION_TICK() * 0.01f) * ((0.1f - F1136_ACTION_TICK() * 0.01f) > 0.0f) + 0.01f;
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 140:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT2C() = FIELD(signed char, 0x66) * -60;
            F1139_ROTATE_AT28() = ChooseIntegerRange(0, 180);
            F1136_ACTION_TICK() = 0;
        }
        ++F1136_ACTION_TICK();
        F1139_ROTATE_AT30() += 5.0f;
        F1139_SCALE_X() += (0.6f - F1136_ACTION_TICK() * 0.02f);
        F1139_SCALE_Y() += (0.6f - F1136_ACTION_TICK() * 0.02f);
        if (F1136_ACTION_STAGE() > 0) {
            if (FIELD(unsigned char, 0x11) > 20) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 141:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
        }
        F1139_SCALE_X() += 0.45f;
        F1139_SCALE_Y() += 0.45f;
        if (FIELD(unsigned char, 0x11) > 10) {
            FIELD(unsigned char, 0x11) -= 10;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
            ClearField8();
            break;
        }
        if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
        if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 142:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
        }
        F1139_SCALE_X() += 0.25f;
        F1139_SCALE_Y() += 0.25f;
        if (FIELD(unsigned char, 0x11) > 10) {
            FIELD(unsigned char, 0x11) -= 10;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
            ClearField8();
            break;
        }
        if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
        if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 143:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1139_ROTATE_AT28() = ChooseIntegerRange(0, 60) - 30;
            F1139_ROTATE_AT2C() = ChooseIntegerRange(0, 60) - 30;
        }
        F1139_ROTATE_AT30() += 15.0f;
        F1139_ROTATE_AT28() += 4.0f;
        F1139_ROTATE_AT2C() += 4.0f;
        F1139_SCALE_X() += 0.14f;
        F1139_SCALE_Y() += 0.14f;
        if (FIELD(unsigned char, 0x11) > 10) {
            FIELD(unsigned char, 0x11) -= 10;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
            ClearField8();
            break;
        }
        if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
        if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 144:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1139_ROTATE_AT28() = ChooseIntegerRange(0, 60) - 30;
            F1139_ROTATE_AT2C() = ChooseIntegerRange(0, 60) - 30;
        }
        F1139_ROTATE_AT30() -= 12.0f;
        F1139_SCALE_X() += 0.12f;
        F1139_SCALE_Y() += 0.12f;
        F1139_ROTATE_AT28() -= 4.0f;
        F1139_ROTATE_AT2C() -= 4.0f;
        if (FIELD(unsigned char, 0x11) > 10) {
            FIELD(unsigned char, 0x11) -= 10;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
            ClearField8();
            break;
        }
        if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
        if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    case 145:
        if (F1136_ACTION_STAGE() == 0 && F1136_ACTION_FRAME() == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            F1139_SCALE_X() = 1.0f;
            F1139_SCALE_Y() = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            F1139_ROTATE_AT30() = ChooseIntegerRange(0, 360);
            F1139_ROTATE_AT28() = ChooseIntegerRange(0, 60) - 30;
            F1139_ROTATE_AT2C() = ChooseIntegerRange(0, 60) - 30;
        }
        F1139_ROTATE_AT30() -= 10.0f;
        F1139_SCALE_X() += 0.1f;
        F1139_SCALE_Y() += 0.1f;
        if (FIELD(unsigned char, 0x11) > 10) {
            FIELD(unsigned char, 0x11) -= 10;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
            ClearField8();
            break;
        }
        if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
        if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        if (AdvanceNestedFrame() == F1136_ANIMATION_ACTION()) ClearField8();
        break;
    }
}

#undef F1135_POSITION_X
#undef F1135_POSITION_Y
#undef F1135_MOTION_X
#undef F1135_MOTION_Y

#undef F1136_ACTION_STAGE
#undef F1136_ACTION_FRAME
#undef F1136_ANIMATION_ACTION
#undef F1136_ACTION_TICK

#undef F1139_SCALE_X
#undef F1139_SCALE_Y
#undef F1139_ROTATE_AT28
#undef F1139_ROTATE_AT2C
#undef F1139_ROTATE_AT30
