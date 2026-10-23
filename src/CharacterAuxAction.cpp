#include "CharacterAuxAction.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this) + offset))
#define FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + offset)

void CharacterAuxObject::AdvanceActionAt005FAE30()
{
    switch (FIELD(short, 0x60)) {
    case 1:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = ChooseIntegerRange(0, 45);
            FLOAT(0x2C) = ChooseIntegerRange(0, 45);
            FLOAT(0x30) = ChooseIntegerRange(0, 45);
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.3f - FIELD(short, 0x74) * 0.035f);
        FLOAT(0x20) += (0.3f - FIELD(short, 0x74) * 0.035f);
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 30;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 2:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = ChooseIntegerRange(0, 45);
            FLOAT(0x2C) = ChooseIntegerRange(0, 45);
            FLOAT(0x30) = ChooseIntegerRange(0, 45);
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
            SpawnPeer(101, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(102, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.3f - FIELD(short, 0x74) * 0.035f);
        FLOAT(0x20) += (0.3f - FIELD(short, 0x74) * 0.035f);
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 3:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = ChooseIntegerRange(0, 45);
            FLOAT(0x2C) = ChooseIntegerRange(0, 45);
            FLOAT(0x30) = ChooseIntegerRange(0, 45);
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
            SpawnPeer(103, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.3f - FIELD(short, 0x74) * 0.035f);
        FLOAT(0x20) += (0.3f - FIELD(short, 0x74) * 0.035f);
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 5:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 4.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = 100 - ChooseIntegerRange(0, 20);
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        FLOAT(0x1C) += 0.5f - FIELD(short, 0x74) * 0.035f;
        FLOAT(0x20) *= 0.75f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 60) {
                FIELD(unsigned char, 0x11) -= 60;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 60) FIELD(unsigned char, 0x12) -= 60;
            if (FIELD(unsigned char, 0x13) > 60) FIELD(unsigned char, 0x13) -= 60;
        }
        ++FIELD(short, 0x74);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 6:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 4.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = -35 - ChooseIntegerRange(0, 20);
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        FLOAT(0x1C) += 0.5f - FIELD(short, 0x74) * 0.035f;
        FLOAT(0x20) *= 0.75f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 60) {
                FIELD(unsigned char, 0x11) -= 60;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 60) FIELD(unsigned char, 0x12) -= 60;
            if (FIELD(unsigned char, 0x13) > 60) FIELD(unsigned char, 0x13) -= 60;
        }
        ++FIELD(short, 0x74);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 7:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 4.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = 10 - ChooseIntegerRange(0, 20);
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        FLOAT(0x1C) += 0.5f - FIELD(short, 0x74) * 0.035f;
        FLOAT(0x20) *= 0.75f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 60) {
                FIELD(unsigned char, 0x11) -= 60;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 60) FIELD(unsigned char, 0x12) -= 60;
            if (FIELD(unsigned char, 0x13) > 60) FIELD(unsigned char, 0x13) -= 60;
        }
        ++FIELD(short, 0x74);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 8:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 4.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = 55 - ChooseIntegerRange(0, 20);
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        FLOAT(0x1C) += 0.5f - FIELD(short, 0x74) * 0.035f;
        FLOAT(0x20) *= 0.75f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 60) {
                FIELD(unsigned char, 0x11) -= 60;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 60) FIELD(unsigned char, 0x12) -= 60;
            if (FIELD(unsigned char, 0x13) > 60) FIELD(unsigned char, 0x13) -= 60;
        }
        ++FIELD(short, 0x74);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 13:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = ChooseIntegerRange(0, 10) * 0.1f + 3.0f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(138, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        ++FIELD(short, 0x74);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 14:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(105, FLOAT(0x44) - FIELD(signed char, 0x66) * 60, FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.3f - FIELD(short, 0x74) * 0.02f);
        FLOAT(0x20) += (0.3f - FIELD(short, 0x74) * 0.02f);
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 15:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(139, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(140, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        FLOAT(0x1C) += (0.2f - FIELD(short, 0x74) * 0.02f) * ((0.2f - FIELD(short, 0x74) * 0.02f) > 0.0f);
        FLOAT(0x20) += (0.2f - FIELD(short, 0x74) * 0.02f) * ((0.2f - FIELD(short, 0x74) * 0.02f) > 0.0f);
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x12) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        ++FIELD(short, 0x74);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 50:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = 60.0f;
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.2f - FIELD(short, 0x74) * 0.02f) * ((0.2f - FIELD(short, 0x74) * 0.02f) > 0.0f);
        FLOAT(0x20) += (0.2f - FIELD(short, 0x74) * 0.02f) * ((0.2f - FIELD(short, 0x74) * 0.02f) > 0.0f);
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x12) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 51:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = 60.0f;
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(105, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(105, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(105, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(105, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(105, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(105, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(105, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(105, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.2f - FIELD(short, 0x74) * 0.02f) * ((0.2f - FIELD(short, 0x74) * 0.02f) > 0.0f);
        FLOAT(0x20) += (0.2f - FIELD(short, 0x74) * 0.02f) * ((0.2f - FIELD(short, 0x74) * 0.02f) > 0.0f);
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x14) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 52:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(107, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(107, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(107, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(107, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(107, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(107, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(107, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(107, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(107, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(107, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 53:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(108, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(109, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(110, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(110, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(110, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(110, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(110, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(110, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(110, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(110, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(104, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 54:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SpawnPeer(137, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(111, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(111, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(111, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(111, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(111, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(111, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(111, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(111, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(111, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(111, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 55:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
            SpawnPeer(112, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(113, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(114, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.5f - FIELD(short, 0x74) * 0.035f) * ((0.5f - FIELD(short, 0x74) * 0.035f) > 0.0f);
        FLOAT(0x20) += (0.5f - FIELD(short, 0x74) * 0.035f) * ((0.5f - FIELD(short, 0x74) * 0.035f) > 0.0f);
        if (FIELD(short, 0x62) > 0 && FIELD(short, 0x64) > 3) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 56:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
            SpawnPeer(57, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(57, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(57, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(57, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(57, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(57, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(57, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.5f - FIELD(short, 0x74) * 0.05f) * ((0.5f - FIELD(short, 0x74) * 0.05f) > 0.0f) + 0.05f;
        FLOAT(0x20) += (0.5f - FIELD(short, 0x74) * 0.05f) * ((0.5f - FIELD(short, 0x74) * 0.05f) > 0.0f) + 0.05f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x12) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 57:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) -= FLOAT(0x54);
        ++FIELD(short, 0x74);
        if (FIELD(short, 0x62) > 0) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) *= 0.9f;
            if (FIELD(unsigned char, 0x11) < 8) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 8;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 60:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 75.0f;
            FIELD(short, 0x1A) = FIELD(signed char, 0x66) * 350;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.2f - FIELD(short, 0x74) * 0.015f);
        FLOAT(0x20) += (0.2f - FIELD(short, 0x74) * 0.015f);
        if (FIELD(short, 0x62) >= 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 62:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = static_cast<short>(ChooseIntegerRange(0, 359));
            FLOAT(0x80) = FIELD(short, 0x74) + 180;
            SetPolarVelocity(FIELD(short, 0x74), 500.0f);
            SpawnPeer(63, FLOAT(0x44) + FLOAT(0x50), FLOAT(0x48) + FLOAT(0x54), 1, 1);
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) -= 0.03f;
        FLOAT(0x20) -= 0.03f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x12) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 63:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
            SetPolarVelocity(FLOAT(0x80), 15.0f);
        }
        if (FIELD(short, 0x74) == 0) {
            if (FIELD(unsigned char, 0x11) < 215) {
                FIELD(unsigned char, 0x11) += 40;
            }
            else {
                FIELD(unsigned char, 0x11) = 255;
                FIELD(short, 0x74) = 1;
            }
        }
        if (FIELD(short, 0x74) == 0) {
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
                FIELD(short, 0x74) = 2;
            }
        }
        FLOAT(0x30) += 5.0f;
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x1C) -= 0.033f;
        FLOAT(0x20) -= 0.033f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 64:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = static_cast<short>(ChooseIntegerRange(0, 359));
            FLOAT(0x80) = FIELD(short, 0x74) + 180;
            SetPolarVelocity(FIELD(short, 0x74), 500.0f);
            SpawnPeer(65, FLOAT(0x44) + FLOAT(0x50), FLOAT(0x48) + FLOAT(0x54), 1, 1);
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) -= 0.03f;
        FLOAT(0x20) -= 0.03f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 25) {
                FIELD(unsigned char, 0x11) -= 25;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 25) FIELD(unsigned char, 0x12) -= 25;
            if (FIELD(unsigned char, 0x13) > 25) FIELD(unsigned char, 0x13) -= 25;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 65:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
            SetPolarVelocity(FLOAT(0x80), 15.0f);
        }
        if (FIELD(short, 0x74) == 0) {
            if (FIELD(unsigned char, 0x11) < 215) {
                FIELD(unsigned char, 0x11) += 40;
            }
            else {
                FIELD(unsigned char, 0x11) = 255;
                FIELD(short, 0x74) = 1;
            }
        }
        if (FIELD(short, 0x74) == 0) {
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
                FIELD(short, 0x74) = 2;
            }
        }
        FLOAT(0x30) += 5.0f;
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x1C) -= 0.033f;
        FLOAT(0x20) -= 0.033f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 100:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SetPolarVelocity(rand(), rand() * 0.0005);
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) += FLOAT(0x54);
        ++FIELD(short, 0x74);
        FLOAT(0x1C) *= 0.85f;
        FLOAT(0x20) *= 0.85f;
        if (FIELD(unsigned char, 0x11) < 15) {
            FIELD(unsigned char, 0x11) = 0;
        }
        else {
            FIELD(unsigned char, 0x11) -= 15;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 101:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.7f;
            FLOAT(0x20) = 0.7f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.2f - FIELD(short, 0x74) * 0.02f);
        FLOAT(0x20) += (0.2f - FIELD(short, 0x74) * 0.02f);
        if (FIELD(unsigned char, 0x11) > 30) {
            FIELD(unsigned char, 0x11) -= 15;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
        }
        if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 15;
        if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 15;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 102:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FIELD(short, 0x74) = static_cast<short>(ChooseIntegerRange(0, 750) + 1000);
            FIELD(short, 0x76) = static_cast<short>(ChooseIntegerRange(0, 360) - 180);
        }
        FIELD(short, 0x74) = static_cast<short>(FIELD(short, 0x74) * 0.95f);
        SetPolarVelocity(FIELD(short, 0x76), FIELD(short, 0x74) * 0.01f);
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x30) += 5.0f;
        if (FIELD(short, 0x64) > 5) {
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
            if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 103:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.7f;
            FLOAT(0x20) = 0.7f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.3f - FIELD(short, 0x74) * 0.02f);
        FLOAT(0x20) += (0.3f - FIELD(short, 0x74) * 0.02f);
        if (FIELD(unsigned char, 0x11) > 30) {
            FIELD(unsigned char, 0x11) -= 15;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
        }
        if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 15;
        if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 15;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 104:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) -= FLOAT(0x54);
        ++FIELD(short, 0x74);
        if (FIELD(short, 0x62) > 0) {
            FLOAT(0x20) *= 0.85f;
            if (FIELD(unsigned char, 0x11) < 15) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 15;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 105:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) -= FLOAT(0x54);
        ++FIELD(short, 0x74);
        if (FIELD(short, 0x62) > 0) {
            FLOAT(0x20) *= 0.85f;
            if (FIELD(unsigned char, 0x11) < 15) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 15;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x14) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 106:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = 65.0f;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.2f - FIELD(short, 0x74) * 0.015f);
        FLOAT(0x20) += (0.2f - FIELD(short, 0x74) * 0.015f);
        if (FIELD(short, 0x62) >= 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 107:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0x78) = static_cast<short>(ChooseIntegerRange(50, 110));
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = FIELD(short, 0x78) * 0.01f;
            FLOAT(0x20) = FIELD(short, 0x78) * 0.01f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = static_cast<short>(ChooseIntegerRange(0, 750) + 1000);
            FIELD(short, 0x76) = static_cast<short>(ChooseIntegerRange(0, 360) - 180);
        }
        FIELD(short, 0x74) = static_cast<short>(FIELD(short, 0x74) * 0.96f);
        SetPolarVelocity(FIELD(short, 0x76), FIELD(short, 0x74) * 0.01f);
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) += FLOAT(0x54);
        if (FIELD(short, 0x64) > 2) {
            FLOAT(0x1C) *= 0.85f;
            FLOAT(0x20) *= 0.85f;
            if (FIELD(unsigned char, 0x11) < 15) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 15;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 15;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 15;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 108:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = 0.0f;
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x30) += 5.0f;
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.4f - FIELD(short, 0x74) * 0.01f);
        FLOAT(0x20) += (0.4f - FIELD(short, 0x74) * 0.01f);
        if (FIELD(short, 0x64) >= 30) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 109:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = 45.0f;
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x30) += 5.0f;
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.4f - FIELD(short, 0x74) * 0.01f);
        FLOAT(0x20) += (0.4f - FIELD(short, 0x74) * 0.01f);
        if (FIELD(short, 0x64) >= 30) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 110:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0x78) = static_cast<short>(ChooseIntegerRange(50, 110));
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = static_cast<short>(ChooseIntegerRange(0, 500) + 1500);
            FIELD(short, 0x76) = static_cast<short>(ChooseIntegerRange(0, 360));
            FLOAT(0x30) = FIELD(short, 0x76) - 90;
        }
        FIELD(short, 0x74) = static_cast<short>(FIELD(short, 0x74) * 0.97f);
        SetPolarVelocity(FIELD(short, 0x76) - 180, FIELD(short, 0x74) * 0.01f);
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x20) += 0.05f;
        if (FIELD(short, 0x64) > 15) {
            if (FIELD(unsigned char, 0x11) < 10) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 10;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 5;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 5;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 111:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = ChooseIntegerRange(20, 100) * 0.01f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            SetPolarVelocity(ChooseIntegerRange(-155, -25), ChooseIntegerRange(100, 250) * 0.1f);
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
        }
        FLOAT(0x54) -= 0.75f;
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x30) += 5.0f;
        if (FLOAT(0x48) < 40.0f && FLOAT(0x54) < 0.0f && ChooseIntegerRange(0, 100) < 10) {
            FLOAT(0x54) = -FLOAT(0x54);
        }
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) < 10) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 10;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 5;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 5;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 112:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 65.0f;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.5f - FIELD(short, 0x74) * 0.04f) * ((0.5f - FIELD(short, 0x74) * 0.04f) > 0.0f) + 0.02f;
        FLOAT(0x20) += (0.5f - FIELD(short, 0x74) * 0.04f) * ((0.5f - FIELD(short, 0x74) * 0.04f) > 0.0f) + 0.02f;
        if (FIELD(short, 0x64) >= 10) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 113:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.7f;
            FLOAT(0x20) = 0.7f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.3f - FIELD(short, 0x74) * 0.02f);
        FLOAT(0x20) += (0.3f - FIELD(short, 0x74) * 0.02f);
        if (FIELD(unsigned char, 0x11) > 30) {
            FIELD(unsigned char, 0x11) -= 15;
        }
        else {
            FIELD(unsigned char, 0x11) = 0;
        }
        if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 15;
        if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 15;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 114:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = ChooseIntegerRange(50, 120) * 1.0f * 0.01f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = static_cast<short>(ChooseIntegerRange(0, 1000) + 4000);
            FIELD(short, 0x76) = static_cast<short>(ChooseIntegerRange(0, 360));
        }
        FIELD(short, 0x74) = static_cast<short>(FIELD(short, 0x74) * 0.9f);
        SetPolarVelocity(FIELD(short, 0x76) - 180, FIELD(short, 0x74) * 0.01f);
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) += FLOAT(0x54);
        if (FIELD(short, 0x64) > 20) {
            FLOAT(0x1C) *= 0.9f;
            FLOAT(0x20) *= 0.9f;
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 115:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 2.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
            for (int particle = 0; particle < 25; ++particle)
                SpawnPeer(122, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(141, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(142, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(143, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(144, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(145, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 116:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 2.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
            SpawnPeer(131, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(132, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(133, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(134, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(135, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(135, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(136, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(136, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(136, FLOAT(0x44), FLOAT(0x48), 1, 1);
            SpawnPeer(136, FLOAT(0x44), FLOAT(0x48), 1, 1);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 117:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.2f;
            FLOAT(0x20) = 1.2f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = -80.0f;
            FIELD(short, 0x74) = 0;
        }
        FIELD(short, 0x1A) = 1500;
        FIELD(short, 0x16) = 0;
        FLOAT(0x30) += 3.0f;
        FLOAT(0x1C) += 0.02f;
        FLOAT(0x20) += 0.02f;
        if (FIELD(short, 0x62) > 0) FIELD(unsigned char, 0x11) -= 6;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 118:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.4f;
            FLOAT(0x20) = 1.4f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = -80.0f;
            FIELD(short, 0x74) = 0;
        }
        FIELD(short, 0x1A) = 1500;
        FIELD(short, 0x16) = 0;
        FLOAT(0x30) += 3.0f;
        FLOAT(0x1C) += 0.02f;
        FLOAT(0x20) += 0.02f;
        if (FIELD(short, 0x62) > 0) FIELD(unsigned char, 0x11) -= 6;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 119:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.1f - FIELD(short, 0x74) * 0.01f) * ((0.1f - FIELD(short, 0x74) * 0.01f) > 0.0f) + 0.01f;
        FLOAT(0x20) += (0.1f - FIELD(short, 0x74) * 0.01f) * ((0.1f - FIELD(short, 0x74) * 0.01f) > 0.0f) + 0.01f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 120:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.3f - FIELD(short, 0x74) * 0.03f) * ((0.3f - FIELD(short, 0x74) * 0.03f) > 0.0f) + 0.03f;
        FLOAT(0x20) += (0.3f - FIELD(short, 0x74) * 0.03f) * ((0.3f - FIELD(short, 0x74) * 0.03f) > 0.0f) + 0.03f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 121:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.5f - FIELD(short, 0x74) * 0.05f) * ((0.5f - FIELD(short, 0x74) * 0.05f) > 0.0f) + 0.05f;
        FLOAT(0x20) += (0.5f - FIELD(short, 0x74) * 0.05f) * ((0.5f - FIELD(short, 0x74) * 0.05f) > 0.0f) + 0.05f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 122:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) -= FLOAT(0x54);
        ++FIELD(short, 0x74);
        if (FIELD(short, 0x62) > 0) {
            FLOAT(0x1C) += 0.3f;
            FLOAT(0x20) *= 0.9f;
            if (FIELD(unsigned char, 0x11) < 8) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 8;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 123:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 3.5f;
            FLOAT(0x20) = 10.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x30) += 1.0f;
        FLOAT(0x1C) += 0.01f;
        FLOAT(0x20) *= 0.9f;
        if (FIELD(short, 0x74) > 1) {
            if (FIELD(unsigned char, 0x11) < 15) {
                FIELD(unsigned char, 0x11) = 0;
                ClearField8();
                return;
            }
            FIELD(unsigned char, 0x11) -= 15;
            if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
            if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(1);
            ++FIELD(short, 0x74);
        }
        break;
    case 124:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 3.5f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x30) -= 1.0f;
        FLOAT(0x1C) += 0.01f;
        FLOAT(0x20) *= 0.95f;
        if (FIELD(short, 0x74) > 1) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
                ClearField8();
                return;
            }
            FIELD(unsigned char, 0x11) -= 20;
            if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
            if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(1);
            ++FIELD(short, 0x74);
        }
        break;
    case 125:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = 65.0f;
            FIELD(short, 0x1A) = FIELD(signed char, 0x66) * 350;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.2f - FIELD(short, 0x74) * 0.015f);
        FLOAT(0x20) += (0.2f - FIELD(short, 0x74) * 0.015f);
        if (FIELD(short, 0x62) >= 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 126:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 127:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 128:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 129:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 130:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 131:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.1f - FIELD(short, 0x74) * 0.01f) * ((0.1f - FIELD(short, 0x74) * 0.01f) > 0.0f) + 0.01f;
        FLOAT(0x20) += (0.1f - FIELD(short, 0x74) * 0.01f) * ((0.1f - FIELD(short, 0x74) * 0.01f) > 0.0f) + 0.01f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 132:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.3f - FIELD(short, 0x74) * 0.03f) * ((0.3f - FIELD(short, 0x74) * 0.03f) > 0.0f) + 0.03f;
        FLOAT(0x20) += (0.3f - FIELD(short, 0x74) * 0.03f) * ((0.3f - FIELD(short, 0x74) * 0.03f) > 0.0f) + 0.03f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 133:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.5f - FIELD(short, 0x74) * 0.05f) * ((0.5f - FIELD(short, 0x74) * 0.05f) > 0.0f) + 0.05f;
        FLOAT(0x20) += (0.5f - FIELD(short, 0x74) * 0.05f) * ((0.5f - FIELD(short, 0x74) * 0.05f) > 0.0f) + 0.05f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 134:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            SetPolarVelocity(ChooseIntegerRange(0, 360), ChooseIntegerRange(5, 20));
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) -= FLOAT(0x54);
        ++FIELD(short, 0x74);
        if (FIELD(short, 0x62) > 0) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) *= 0.9f;
            if (FIELD(unsigned char, 0x11) < 8) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 8;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 135:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 3.5f;
            FLOAT(0x20) = 10.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x30) += 1.0f;
        FLOAT(0x1C) += 0.01f;
        FLOAT(0x20) *= 0.9f;
        if (FIELD(short, 0x74) > 1) {
            if (FIELD(unsigned char, 0x11) < 15) {
                FIELD(unsigned char, 0x11) = 0;
                ClearField8();
                return;
            }
            FIELD(unsigned char, 0x11) -= 15;
            if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
            if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(1);
            ++FIELD(short, 0x74);
        }
        break;
    case 136:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 3.5f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FIELD(short, 0x74) = 0;
        }
        FLOAT(0x30) -= 1.0f;
        FLOAT(0x1C) += 0.01f;
        FLOAT(0x20) *= 0.95f;
        if (FIELD(short, 0x74) > 1) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
                ClearField8();
                return;
            }
            FIELD(unsigned char, 0x11) -= 20;
            if (FIELD(unsigned char, 0x12) > 10) FIELD(unsigned char, 0x12) -= 10;
            if (FIELD(unsigned char, 0x13) > 10) FIELD(unsigned char, 0x13) -= 10;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(1);
            ++FIELD(short, 0x74);
        }
        break;
    case 137:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
        }
        FLOAT(0x1C) += 0.05f;
        FLOAT(0x20) += 0.05f;
        if (FIELD(unsigned char, 0x11) > 15) {
            FIELD(unsigned char, 0x11) -= 15;
        }
        else {
            ClearField8();
            break;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 138:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = -40.0f;
            FIELD(short, 0x1A) = FIELD(signed char, 0x66) * 350;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.4f - FIELD(short, 0x74) * 0.015f);
        FLOAT(0x20) += (0.4f - FIELD(short, 0x74) * 0.015f);
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 30;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 139:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 2.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x1C) += (0.1f - FIELD(short, 0x74) * 0.01f) * ((0.1f - FIELD(short, 0x74) * 0.01f) > 0.0f) + 0.01f;
        FLOAT(0x20) += (0.1f - FIELD(short, 0x74) * 0.01f) * ((0.1f - FIELD(short, 0x74) * 0.01f) > 0.0f) + 0.01f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) < 20) {
                FIELD(unsigned char, 0x11) = 0;
            }
            else {
                FIELD(unsigned char, 0x11) -= 20;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 140:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = FIELD(signed char, 0x66) * -60;
            FLOAT(0x28) = ChooseIntegerRange(0, 180);
            FIELD(short, 0x74) = 0;
        }
        ++FIELD(short, 0x74);
        FLOAT(0x30) += 5.0f;
        FLOAT(0x1C) += (0.6f - FIELD(short, 0x74) * 0.02f);
        FLOAT(0x20) += (0.6f - FIELD(short, 0x74) * 0.02f);
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 20) {
                FIELD(unsigned char, 0x11) -= 20;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
            }
            if (FIELD(unsigned char, 0x12) > 20) FIELD(unsigned char, 0x12) -= 20;
            if (FIELD(unsigned char, 0x13) > 20) FIELD(unsigned char, 0x13) -= 20;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 141:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
        }
        FLOAT(0x1C) += 0.45f;
        FLOAT(0x20) += 0.45f;
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
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 142:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
        }
        FLOAT(0x1C) += 0.25f;
        FLOAT(0x20) += 0.25f;
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
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 143:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FLOAT(0x28) = ChooseIntegerRange(0, 60) - 30;
            FLOAT(0x2C) = ChooseIntegerRange(0, 60) - 30;
        }
        FLOAT(0x30) += 15.0f;
        FLOAT(0x28) += 4.0f;
        FLOAT(0x2C) += 4.0f;
        FLOAT(0x1C) += 0.14f;
        FLOAT(0x20) += 0.14f;
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
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 144:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FLOAT(0x28) = ChooseIntegerRange(0, 60) - 30;
            FLOAT(0x2C) = ChooseIntegerRange(0, 60) - 30;
        }
        FLOAT(0x30) -= 12.0f;
        FLOAT(0x1C) += 0.12f;
        FLOAT(0x20) += 0.12f;
        FLOAT(0x28) -= 4.0f;
        FLOAT(0x2C) -= 4.0f;
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
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    case 145:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = ChooseIntegerRange(0, 360);
            FLOAT(0x28) = ChooseIntegerRange(0, 60) - 30;
            FLOAT(0x2C) = ChooseIntegerRange(0, 60) - 30;
        }
        FLOAT(0x30) -= 10.0f;
        FLOAT(0x1C) += 0.1f;
        FLOAT(0x20) += 0.1f;
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
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField8();
        break;
    }
}
