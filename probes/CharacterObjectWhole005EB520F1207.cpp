// F1207 restores the complete F061 active07 natural C++ research parent.
// F1209 reconciles its real virtual slot 1 with native vtable/dispatch evidence.
// Original: 005EB520, 34,434 CODE bytes / 9,378 x86; 443 owned DATA bytes.
// NONEXACT: 135 GPR positions / six widths remain, all in state 998.
// Profile: /Od /Ob0 /Gy /GR- /GX- /Zi /I src, pinned VC7.1 build 3077.
// Evidence: docs/OBJECT_ADVANCE_005EB520_WHOLE_F1207.md.
// Interfaces below are borrowed receiver views; do not instantiate owners.
#include "ObjectAdvance5EB520F1207.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OWNER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset)))
#define OPPONENT(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset))
#define OWNER_ACTOR reinterpret_cast<OwnerActor5EB520Draft*>(FIELD(void*, 0xE4))

// The state labels and names describe observed behavior, not original identity.
void ObjectActor5EB520Draft::AdvanceAction() {
    if (OPPONENT(short, 0x3BA) != 0) return;
    if (OWNER(short, 0x3BA) != 0 && FIELD(short, 0x8A) == 0) return;
    if (FIELD(short, 0x82) != 0) {
        --FIELD(short, 0x82);
        return;
    }
    switch (FIELD(short, 0x60)) {
    case 800:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 8) {
            ClearField74();
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0xD8) = 10;
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;
    case 801:
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.5f;
                FLOAT(0x20) = 0.5f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x2C) = FIELD(signed char, 0x66) * 60;
                FLOAT(0x30) = FLOAT(0xC8);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0xD8) = 15;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x30) += FIELD(short, 0xD8);
            FIELD(short, 0xD8) = FIELD(short, 0xD8) - 1;
            if (FIELD(short, 0xD8) < 1) FIELD(short, 0xD8) = 1;
            FLOAT(0x1C) += 0.02f;
            FLOAT(0x20) += 0.02f;
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(unsigned char, 0x11) > 5) {
                    FIELD(unsigned char, 0x11) -= 5;
                    FIELD(unsigned char, 0x12) -= 5;
                    FIELD(unsigned char, 0x13) -= 5;
                }
                else {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;
    case 802:
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.5f;
                FLOAT(0x20) = 0.5f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x2C) = FIELD(signed char, 0x66) * 70;
                FLOAT(0x30) = RecordedRange(0, 359);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x1C) += 0.03f;
            FLOAT(0x20) += 0.03f;
            if (FIELD(short, 0x62) == 1) {
                if (FIELD(unsigned char, 0x11) > 5) {
                    FIELD(unsigned char, 0x11) -= 5;
                    FIELD(unsigned char, 0x12) -= 5;
                    FIELD(unsigned char, 0x13) -= 5;
                }
                else {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;
    case 803:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 3;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.1f;
                FLOAT(0x20) = 0.1f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 0;
                FIELD(unsigned char, 0x13) = 0;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0xD8) = 0;
                OWNER_FLOAT(0x314) = 0.0f;
                OWNER_ACTOR->SpawnEffect(801, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                OWNER_FLOAT(0x314) = 180.0f;
                OWNER_ACTOR->SpawnEffect(801, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                OWNER_ACTOR->SpawnEffect(802, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            }
            if (FIELD(short, 0x62) == 1) {
                if (FLOAT(0x1C) < 1.0f) {
                    FLOAT(0x1C) += 0.1f;
                    FLOAT(0x20) += 0.1f;
                }
                if (FIELD(unsigned char, 0x13) < 230) {
                    FIELD(unsigned char, 0x13) += 25;
                    FIELD(unsigned char, 0x12) += 25;
                }
                else {
                    FIELD(unsigned char, 0x11) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x12) = 255;
                }
            }
            if (FIELD(short, 0x62) > 2) {
                FLOAT(0x1C) += 0.3f;
                FLOAT(0x20) += 0.3f;
                if (FIELD(unsigned char, 0x11) >= 25) {
                    FIELD(unsigned char, 0x11) -= 25;
                    FIELD(unsigned char, 0x13) -= 25;
                    FIELD(unsigned char, 0x12) -= 25;
                }
                else {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && OWNER(short, 0x60) == 600 && OWNER(short, 0x62) < 8) {
                ResetSecondaryCounters(2);
                ++FIELD(short, 0xD8);
                FLOAT(0x1C) = 1.1f - RecordedRange(0, 20) * 0.01f;
                FLOAT(0x20) = FLOAT(0x1C);
                if (FIELD(short, 0xD8) > 4) {
                    FIELD(short, 0xD8) = 0;
                    FIELD(int, 0x7C) = 0;
                }
            }
        }
        break;
    case 804:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
                ClearField74();
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 10;
                    FIELD(int, 0x7C) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x11) = 255;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FLOAT(0x50) = 15.0f;
                    FLOAT(0x54) = 0.0f;
                    FIELD(short, 0xD8) = 0;
                    FIELD(short, 0xDA) = 0;
                }
                if (FIELD(int, 0x7C) == 6) {
                    FIELD(int, 0x7C) = 0;
                    ++FIELD(short, 0x80);
                }
                if (FIELD(int, 0x7C) == 4) {
                    FIELD(int, 0x7C) = 0;
                }
                FLOAT(0x50) -= 0.4f;
                if (FLOAT(0x50) <= 2.0f) FLOAT(0x50) = 2.0f;
                if (FIELD(short, 0x62) > 1) {
                    FLOAT(0x50) = 0.0f;
                    FLOAT(0x54) = 0.0f;
                    FLOAT(0x1C) += 0.3f;
                    FLOAT(0x20) += 0.3f;
                    if (FIELD(unsigned char, 0x11) >= 25) {
                        FIELD(unsigned char, 0x11) -= 25;
                        FIELD(unsigned char, 0x13) -= 25;
                        FIELD(unsigned char, 0x12) -= 25;
                    }
                    else {
                        ClearField74();
                        return;
                    }
                }
                FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                FLOAT(0x48) += FLOAT(0x54);
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0 && FIELD(short, 0x80) > 0 && FIELD(short, 0xDA) < 20) {
                    ResetSecondaryCounters(1);
                    ++FIELD(short, 0xD8);
                    ++FIELD(short, 0xDA);
                    if (FIELD(short, 0xD8) > 2) {
                        OWNER_ACTOR->SpawnEffect(805, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                        FIELD(short, 0xD8) = 0;
                    }
                    FLOAT(0x1C) = 1.1f - RecordedRange(0, 20) * 0.01f;
                    FLOAT(0x20) = FLOAT(0x1C);
                    if (FIELD(int, 0x7C) != 0) {
                        FIELD(int, 0x7C) = 0;
                        FIELD(short, 0x80) -= 3;
                    }
                }
            }
        }
        break;
    case 805:
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.5f;
                FLOAT(0x20) = 0.5f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x28) = RecordedRange(0, 359);
                FLOAT(0x2C) = RecordedRange(0, 359);
                FLOAT(0x30) = RecordedRange(0, 359);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x1C) += 0.085f;
            FLOAT(0x20) += 0.085f;
            if (FIELD(short, 0x62) == 1) {
                if (FIELD(unsigned char, 0x11) > 15) {
                    FIELD(unsigned char, 0x11) -= 15;
                    FIELD(unsigned char, 0x12) -= 15;
                    FIELD(unsigned char, 0x13) -= 15;
                }
                else {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;
    case 806:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 2.5f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (OWNER(short, 0x60) == 700 && OWNER(short, 0x62) < 11) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 807:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 0;
            FIELD(unsigned char, 0x13) = 0;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = FIELD(signed char, 0x66) * 50;
            FIELD(short, 0xD8) = 1;
        }
        FLOAT(0x30) += 1.0f;
        FLOAT(0x1C) -= 0.01f;
        FLOAT(0x20) -= 0.01f;
        if (FIELD(short, 0x62) == 1) {
            if (FIELD(unsigned char, 0x11) < 248) {
                FIELD(unsigned char, 0x11) += 7;
                FIELD(unsigned char, 0x13) += 7;
                FIELD(unsigned char, 0x12) += 7;
            }
            else {
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
            }
        }
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
                FIELD(unsigned char, 0x13) -= 10;
                FIELD(unsigned char, 0x12) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 808:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.2f;
            FLOAT(0x20) = 1.2f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 0;
            FIELD(unsigned char, 0x13) = 0;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = FIELD(signed char, 0x66) * 50;
            FIELD(short, 0xD8) = 1;
        }
        FLOAT(0x1C) -= 0.018f;
        FLOAT(0x20) -= 0.018f;
        if (FIELD(short, 0x62) == 1) {
            if (FIELD(unsigned char, 0x11) < 248) {
                FIELD(unsigned char, 0x11) += 7;
                FIELD(unsigned char, 0x13) += 7;
                FIELD(unsigned char, 0x12) += 7;
            }
            else {
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
            }
        }
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 8) {
                FIELD(unsigned char, 0x11) -= 8;
                FIELD(unsigned char, 0x13) -= 8;
                FIELD(unsigned char, 0x12) -= 8;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 809:
        if (FLOAT(0x44) > 1580.0f || FLOAT(0x44) < -300.0f) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) != 702 && FIELD(short, 0x62) < 2) {
                ClearField74();
                return;
            }
            else {
                if (FIELD(short, 0x8A) > 0 && OWNER(short, 0x3B8) == 0) {
                    FIELD(short, 0x8A) = 0;
                }
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FLOAT(0x1C) = 0.1f;
                    FLOAT(0x20) = 0.1f;
                    FIELD(unsigned char, 0x11) = 0;
                    FIELD(unsigned char, 0x12) = 0;
                    FIELD(unsigned char, 0x13) = 0;
                    FIELD(unsigned char, 0x14) = 255;
                    FIELD(short, 0x80) = 20;
                    FLOAT(0x50) = 0.0f;
                    FLOAT(0x54) = 0.0f;
                    FIELD(short, 0xD8) = 0;
                }
                if (FIELD(int, 0x7C) == 6) {
                    FIELD(int, 0x7C) = 0;
                    ++FIELD(short, 0x80);
                }
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                    FIELD(int, 0x7C) = 0;
                    ++FIELD(short, 0xD8);
                    FLOAT(0x1C) = 1.0f - RecordedRange(0, 20) * 0.01f;
                    FLOAT(0x20) = FLOAT(0x1C);
                    if (FIELD(short, 0xD8) > 1) {
                        OWNER_ACTOR->SpawnEffect(810, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                        FIELD(short, 0xD8) = 0;
                    }
                }
                if (FIELD(short, 0x62) == 1) {
                    FLOAT(0x1C) += 0.03f;
                    FLOAT(0x20) += 0.03f;
                    if (FIELD(unsigned char, 0x11) < 235) {
                        FIELD(unsigned char, 0x11) += 20;
                        FIELD(unsigned char, 0x13) += 20;
                        FIELD(unsigned char, 0x12) += 20;
                    }
                    else {
                        FIELD(unsigned char, 0x11) = 255;
                        FIELD(unsigned char, 0x12) = 255;
                        FIELD(unsigned char, 0x13) = 255;
                    }
                    if (OWNER(short, 0x62) == 15) {
                        FLOAT(0x1C) = 1.0f - RecordedRange(0, 20) * 0.01f;
                        FLOAT(0x20) = FLOAT(0x1C);
                        ResetSecondaryCounters(2);
                    }
                }
                if (FIELD(short, 0x62) == 2) {
                    FLOAT(0x50) -= 0.75f;
                    if (FLOAT(0x50) < 10.0f) FLOAT(0x50) = 10.0f;
                }
                if (FIELD(short, 0x62) > 2) {
                    if (FIELD(unsigned char, 0x11) > 10) {
                        FLOAT(0x1C) *= 0.95f;
                        FLOAT(0x20) = FLOAT(0x1C);
                        FIELD(unsigned char, 0x11) -= 10;
                        FIELD(unsigned char, 0x13) -= 10;
                        FIELD(unsigned char, 0x12) -= 10;
                    }
                    else {
                        ClearField74();
                        return;
                    }
                }
                FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                FLOAT(0x48) += FLOAT(0x54);
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                    FLOAT(0x50) = 18.5f;
                    FLOAT(0x1C) = 0.6f;
                    FLOAT(0x20) = 0.6f;
                }
                if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                    ResetSecondaryCounters(2);
                }
            }
        }
        break;
    case 810:
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.5f;
                FLOAT(0x20) = 0.5f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x28) = RecordedRange(0, 359);
                FLOAT(0x2C) = RecordedRange(0, 359);
                FLOAT(0x30) = RecordedRange(0, 359);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x1C) += 0.065f;
            FLOAT(0x20) += 0.065f;
            if (FIELD(short, 0x62) == 1) {
                if (FIELD(unsigned char, 0x11) > 10) {
                    FIELD(unsigned char, 0x11) -= 10;
                    FIELD(unsigned char, 0x12) -= 10;
                    FIELD(unsigned char, 0x13) -= 10;
                }
                else {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;
    case 811:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
                ClearField74();
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 1;
                    FIELD(int, 0x7C) = 0;
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                    FIELD(short, 0xD8) = 0;
                    FIELD(short, 0xDC) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x11) = 255;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
                }
                if (FIELD(short, 0x62) < 3 && RecordedRange(0, 100) < 40) {
                    OWNER_ACTOR->SpawnEffect(818, FLOAT(0x44) + 20.0f - RecordedRange(0, 40), FLOAT(0x48) + 20.0f - RecordedRange(0, 40), FIELD(signed char, 0x66), 1);
                }
                ++FIELD(short, 0xD8);
                if (FIELD(short, 0x62) < 2) {
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                }
                if ((FIELD(int, 0x7C) == 1 || FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4 || FIELD(int, 0x7C) == 6) && FIELD(short, 0x62) == 1) {
                    ResetSecondaryCounters(2);
                    return;
                }
                else {
                    FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                        ClearField74();
                        return;
                    }
                    else {
                        if (FIELD(short, 0x62) == 2) {
                            if (FIELD(unsigned char, 0x11) >= 60) {
                                FIELD(unsigned char, 0x11) -= 60;
                            }
                            else {
                                FIELD(unsigned char, 0x11) = 0;
                                ClearField74();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                    }
                }
            }
        }
        break;
    case 812:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
                ClearField74();
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 1;
                    FIELD(int, 0x7C) = 0;
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                    FIELD(short, 0xD8) = 0;
                    FIELD(short, 0xDC) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x11) = 255;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
                }
                if (FIELD(short, 0x62) < 3 && RecordedRange(0, 100) < 40) {
                    OWNER_ACTOR->SpawnEffect(819, FLOAT(0x44) + 20.0f - RecordedRange(0, 40), FLOAT(0x48) + 20.0f - RecordedRange(0, 40), FIELD(signed char, 0x66), 1);
                }
                ++FIELD(short, 0xD8);
                if (FIELD(short, 0x62) < 2) {
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                }
                if ((FIELD(int, 0x7C) == 1 || FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4 || FIELD(int, 0x7C) == 6) && FIELD(short, 0x62) == 1) {
                    ResetSecondaryCounters(2);
                    return;
                }
                else {
                    FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                        ClearField74();
                        return;
                    }
                    else {
                        if (FIELD(short, 0x62) == 2) {
                            if (FIELD(unsigned char, 0x11) >= 60) {
                                FIELD(unsigned char, 0x11) -= 60;
                            }
                            else {
                                FIELD(unsigned char, 0x11) = 0;
                                ClearField74();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                    }
                }
            }
        }
        break;
    case 813:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
                ClearField74();
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 1;
                    FIELD(int, 0x7C) = 0;
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                    FIELD(short, 0xD8) = 0;
                    FIELD(short, 0xDC) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x11) = 255;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
                }
                if (FIELD(short, 0x62) < 3 && RecordedRange(0, 100) < 40) {
                    OWNER_ACTOR->SpawnEffect(820, FLOAT(0x44) + 20.0f - RecordedRange(0, 40), FLOAT(0x48) + 20.0f - RecordedRange(0, 40), FIELD(signed char, 0x66), 1);
                }
                ++FIELD(short, 0xD8);
                if (FIELD(short, 0x62) < 2) {
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                }
                if ((FIELD(int, 0x7C) == 1 || FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4 || FIELD(int, 0x7C) == 6) && FIELD(short, 0x62) == 1) {
                    ResetSecondaryCounters(2);
                    return;
                }
                else {
                    FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                        ClearField74();
                        return;
                    }
                    else {
                        if (FIELD(short, 0x62) == 2) {
                            if (FIELD(unsigned char, 0x11) >= 60) {
                                FIELD(unsigned char, 0x11) -= 60;
                            }
                            else {
                                FIELD(unsigned char, 0x11) = 0;
                                ClearField74();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                    }
                }
            }
        }
        break;
    case 814:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
                ClearField74();
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 1;
                    FIELD(int, 0x7C) = 0;
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                    FIELD(short, 0xD8) = 0;
                    FIELD(short, 0xDC) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x11) = 255;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
                }
                if (FIELD(short, 0x62) < 3 && RecordedRange(0, 100) < 40) {
                    OWNER_ACTOR->SpawnEffect(821, FLOAT(0x44) + 20.0f - RecordedRange(0, 40), FLOAT(0x48) + 20.0f - RecordedRange(0, 40), FIELD(signed char, 0x66), 1);
                }
                ++FIELD(short, 0xD8);
                if (FIELD(short, 0x62) < 2) {
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                }
                if ((FIELD(int, 0x7C) == 1 || FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4 || FIELD(int, 0x7C) == 6) && FIELD(short, 0x62) == 1) {
                    ResetSecondaryCounters(2);
                    return;
                }
                else {
                    FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                        ClearField74();
                        return;
                    }
                    else {
                        if (FIELD(short, 0x62) == 2) {
                            if (FIELD(unsigned char, 0x11) >= 60) {
                                FIELD(unsigned char, 0x11) -= 60;
                            }
                            else {
                                FIELD(unsigned char, 0x11) = 0;
                                ClearField74();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                    }
                }
            }
        }
        break;
    case 815:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
                ClearField74();
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 1;
                    FIELD(int, 0x7C) = 0;
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                    FIELD(short, 0xD8) = 0;
                    FIELD(short, 0xDC) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x11) = 255;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
                }
                if (FIELD(short, 0x62) < 3 && RecordedRange(0, 100) < 40) {
                    OWNER_ACTOR->SpawnEffect(822, FLOAT(0x44) + 20.0f - RecordedRange(0, 40), FLOAT(0x48) + 20.0f - RecordedRange(0, 40), FIELD(signed char, 0x66), 1);
                }
                ++FIELD(short, 0xD8);
                if (FIELD(short, 0x62) < 2) {
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                }
                if ((FIELD(int, 0x7C) == 1 || FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4 || FIELD(int, 0x7C) == 6) && FIELD(short, 0x62) == 1) {
                    ResetSecondaryCounters(2);
                    return;
                }
                else {
                    FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                        ClearField74();
                        return;
                    }
                    else {
                        if (FIELD(short, 0x62) == 2) {
                            if (FIELD(unsigned char, 0x11) >= 60) {
                                FIELD(unsigned char, 0x11) -= 60;
                            }
                            else {
                                FIELD(unsigned char, 0x11) = 0;
                                ClearField74();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                    }
                }
            }
        }
        break;
    case 816:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
                ClearField74();
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 1;
                    FIELD(int, 0x7C) = 0;
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                    FIELD(short, 0xD8) = 0;
                    FIELD(short, 0xDC) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x11) = 255;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
                }
                if (FIELD(short, 0x62) < 3 && RecordedRange(0, 100) < 40) {
                    OWNER_ACTOR->SpawnEffect(823, FLOAT(0x44) + 20.0f - RecordedRange(0, 40), FLOAT(0x48) + 20.0f - RecordedRange(0, 40), FIELD(signed char, 0x66), 1);
                }
                ++FIELD(short, 0xD8);
                if (FIELD(short, 0x62) < 2) {
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                }
                if ((FIELD(int, 0x7C) == 1 || FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4 || FIELD(int, 0x7C) == 6) && FIELD(short, 0x62) == 1) {
                    ResetSecondaryCounters(2);
                    return;
                }
                else {
                    FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                        ClearField74();
                        return;
                    }
                    else {
                        if (FIELD(short, 0x62) == 2) {
                            if (FIELD(unsigned char, 0x11) >= 60) {
                                FIELD(unsigned char, 0x11) -= 60;
                            }
                            else {
                                FIELD(unsigned char, 0x11) = 0;
                                ClearField74();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                    }
                }
            }
        }
        break;
    case 817:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
                ClearField74();
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 1;
                    FIELD(int, 0x7C) = 0;
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                    FIELD(short, 0xD8) = 0;
                    FIELD(short, 0xDC) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x11) = 255;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / 0.017453288659453392f;
                }
                if (FIELD(short, 0x62) < 3 && RecordedRange(0, 100) < 40) {
                    OWNER_ACTOR->SpawnEffect(824, FLOAT(0x44) + 20.0f - RecordedRange(0, 40), FLOAT(0x48) + 20.0f - RecordedRange(0, 40), FIELD(signed char, 0x66), 1);
                }
                ++FIELD(short, 0xD8);
                if (FIELD(short, 0x62) < 2) {
                    SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                }
                if ((FIELD(int, 0x7C) == 1 || FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4 || FIELD(int, 0x7C) == 6) && FIELD(short, 0x62) == 1) {
                    ResetSecondaryCounters(2);
                    return;
                }
                else {
                    FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                        ClearField74();
                        return;
                    }
                    else {
                        if (FIELD(short, 0x62) == 2) {
                            if (FIELD(unsigned char, 0x11) >= 60) {
                                FIELD(unsigned char, 0x11) -= 60;
                            }
                            else {
                                FIELD(unsigned char, 0x11) = 0;
                                ClearField74();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                    }
                }
            }
        }
        break;
    case 818:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.1f - RecordedRange(0, 20) * 0.01f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 359);
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = -2.0f;
        }
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x30) += 2.0f;
        if (FIELD(short, 0x62) > 0) {
            if (FLOAT(0x1C) > 0.05f) {
                FLOAT(0x1C) -= 0.05f;
                FLOAT(0x20) -= 0.05f;
            }
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 819:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.1f - RecordedRange(0, 20) * 0.01f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 359);
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = -2.0f;
        }
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x30) += 2.0f;
        if (FIELD(short, 0x62) > 0) {
            if (FLOAT(0x1C) > 0.05f) {
                FLOAT(0x1C) -= 0.05f;
                FLOAT(0x20) -= 0.05f;
            }
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 820:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.1f - RecordedRange(0, 20) * 0.01f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 359);
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = -2.0f;
        }
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x30) += 2.0f;
        if (FIELD(short, 0x62) > 0) {
            if (FLOAT(0x1C) > 0.05f) {
                FLOAT(0x1C) -= 0.05f;
                FLOAT(0x20) -= 0.05f;
            }
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 821:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.1f - RecordedRange(0, 20) * 0.01f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 359);
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = -2.0f;
        }
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x30) += 2.0f;
        if (FIELD(short, 0x62) > 0) {
            if (FLOAT(0x1C) > 0.05f) {
                FLOAT(0x1C) -= 0.05f;
                FLOAT(0x20) -= 0.05f;
            }
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 822:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.1f - RecordedRange(0, 20) * 0.01f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 359);
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = -2.0f;
        }
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x30) += 2.0f;
        if (FIELD(short, 0x62) > 0) {
            if (FLOAT(0x1C) > 0.05f) {
                FLOAT(0x1C) -= 0.05f;
                FLOAT(0x20) -= 0.05f;
            }
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 823:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.1f - RecordedRange(0, 20) * 0.01f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 359);
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = -2.0f;
        }
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x30) += 2.0f;
        if (FIELD(short, 0x62) > 0) {
            if (FLOAT(0x1C) > 0.05f) {
                FLOAT(0x1C) -= 0.05f;
                FLOAT(0x20) -= 0.05f;
            }
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 824:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.1f - RecordedRange(0, 20) * 0.01f;
            FLOAT(0x20) = FLOAT(0x1C);
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 359);
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = -2.0f;
        }
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x30) += 2.0f;
        if (FIELD(short, 0x62) > 0) {
            if (FLOAT(0x1C) > 0.05f) {
                FLOAT(0x1C) -= 0.05f;
                FLOAT(0x20) -= 0.05f;
            }
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 825:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 26) {
                ClearField74();
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 10;
                    FIELD(int, 0x7C) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FIELD(short, 0xDA) = 2000;
                    SetPolarVelocity(0.0f, FIELD(short, 0xDA) * 0.01f);
                    FIELD(short, 0x80) = 5;
                    FIELD(short, 0xD8) = 0;
                }
                if (FIELD(int, 0x7C) == 6) {
                    FIELD(int, 0x7C) = 0;
                    ++FIELD(short, 0x80);
                }
                if (FIELD(int, 0x7C) != 0) {
                    if (FIELD(int, 0x7C) == 4) {
                        FIELD(int, 0x7C) = 0;
                    }
                    else {
                        FIELD(short, 0x80) = 0;
                    }
                }
                if (FIELD(short, 0x80) == 0 && FIELD(short, 0x62) < 26) {
                    ResetSecondaryCounters(26);
                    return;
                }
                else {
                    FIELD(short, 0xDA) -= 100;
                    if (FIELD(short, 0xDA) < 300) FIELD(short, 0xDA) = 300;
                    SetPolarVelocity(0.0f, FIELD(short, 0xDA) * 0.01f);
                    FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                    FLOAT(0x48) += FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                    if (FIELD(short, 0x62) == 26 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 2) {
                        ++FIELD(short, 0xD8);
                        ResetSecondaryCounters(13);
                    }
                }
            }
        }
        break;
    case 826:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 26) {
                ClearField74();
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 1;
                    FIELD(int, 0x7C) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FIELD(short, 0xDA) = 2000;
                    SetPolarVelocity(0.0f, FIELD(short, 0xDA) * 0.01f);
                    FIELD(short, 0x80) = 5;
                    FIELD(short, 0xD8) = 0;
                }
                if (FIELD(int, 0x7C) == 6) {
                    FIELD(int, 0x7C) = 0;
                    ++FIELD(short, 0x80);
                }
                if (FIELD(int, 0x7C) != 0) {
                    if (FIELD(int, 0x7C) == 4) {
                        FIELD(int, 0x7C) = 0;
                    }
                    else {
                        FIELD(short, 0x80) = 0;
                    }
                }
                if (FIELD(short, 0x80) == 0 && FIELD(short, 0x62) < 26) {
                    ResetSecondaryCounters(26);
                    return;
                }
                else {
                    FIELD(short, 0xDA) -= 100;
                    if (FIELD(short, 0xDA) < 300) FIELD(short, 0xDA) = 300;
                    SetPolarVelocity(0.0f, FIELD(short, 0xDA) * 0.01f);
                    FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                    FLOAT(0x48) += FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                    if (FIELD(short, 0x62) == 26 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 3) {
                        ++FIELD(short, 0xD8);
                        ResetSecondaryCounters(13);
                    }
                }
            }
        }
        break;
    case 827:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        else {
            if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 26) {
                ClearField74();
                if (OWNER(short, 0xEFA) > 25) {
                    OWNER(short, 0xEFA) = 0;
                    OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FIELD(short, 0x80) = 1;
                    FIELD(int, 0x7C) = 0;
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                    FIELD(unsigned char, 0x12) = 255;
                    FIELD(unsigned char, 0x13) = 255;
                    FIELD(unsigned char, 0x14) = 255;
                    FIELD(short, 0xDA) = 2000;
                    SetPolarVelocity(-30.0f, FIELD(short, 0xDA) * 0.01f);
                    FIELD(short, 0x80) = 5;
                    FIELD(short, 0xD8) = 0;
                }
                if (FIELD(int, 0x7C) == 6) {
                    FIELD(int, 0x7C) = 0;
                    ++FIELD(short, 0x80);
                }
                if (FIELD(int, 0x7C) != 0) {
                    if (FIELD(int, 0x7C) == 4) {
                        FIELD(int, 0x7C) = 0;
                    }
                    else {
                        FIELD(short, 0x80) = 0;
                    }
                }
                if (FIELD(short, 0x80) == 0 && FIELD(short, 0x62) < 26) {
                    ResetSecondaryCounters(26);
                    return;
                }
                else {
                    FIELD(short, 0xDA) -= 100;
                    if (FIELD(short, 0xDA) < 300) FIELD(short, 0xDA) = 300;
                    SetPolarVelocity(-30.0f, FIELD(short, 0xDA) * 0.01f);
                    FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                    FLOAT(0x48) += FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                    if (FIELD(short, 0x62) == 26 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 3) {
                        ++FIELD(short, 0xD8);
                        ResetSecondaryCounters(13);
                    }
                }
            }
        }
        break;
    case 828:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = FIELD(signed char, 0x66) * -35;
            FLOAT(0x2C) = 40.0f;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x1C) += 0.065f;
        FLOAT(0x20) += 0.065f;
        if (FIELD(short, 0x62) == 2) {
            if (FIELD(unsigned char, 0x11) > 15) {
                FIELD(unsigned char, 0x11) -= 15;
                FIELD(unsigned char, 0x14) -= 15;
                FIELD(unsigned char, 0x13) -= 15;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 829:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = FIELD(signed char, 0x66) * -35;
            FLOAT(0x2C) = 40.0f;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x1C) += 0.065f;
        FLOAT(0x20) += 0.065f;
        FLOAT(0x30) += 2.0f;
        if (FIELD(short, 0x62) == 2) {
            if (FIELD(unsigned char, 0x11) > 15) {
                FIELD(unsigned char, 0x11) -= 15;
                FIELD(unsigned char, 0x14) -= 15;
                FIELD(unsigned char, 0x13) -= 15;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 830:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = FIELD(signed char, 0x66) * -35;
            FLOAT(0x2C) = 40.0f;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x1C) += 0.2f;
        FLOAT(0x20) += 0.2f;
        if (FIELD(short, 0x62) == 2) {
            if (FIELD(unsigned char, 0x11) > 20) {
                FIELD(unsigned char, 0x11) -= 20;
                FIELD(unsigned char, 0x14) -= 20;
                FIELD(unsigned char, 0x13) -= 20;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 831:
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0xD8) = 10;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x1C) += FIELD(short, 0xD8) * 0.01f + 0.01f;
            FLOAT(0x20) += FIELD(short, 0xD8) * 0.01f + 0.01f;
            if (FIELD(short, 0xD8) > 0) --FIELD(short, 0xD8);
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(unsigned char, 0x11) > 5) {
                    FIELD(unsigned char, 0x11) -= 15;
                    FIELD(unsigned char, 0x12) -= 15;
                    FIELD(unsigned char, 0x14) -= 15;
                }
                else {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                OWNER_ACTOR->SpawnEffect(832, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                OWNER_ACTOR->SpawnEffect(833, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                OWNER_ACTOR->SpawnEffect(834, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            }
        }
        break;
    case 832:
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x1C) *= 0.9f;
            FLOAT(0x20) += 0.05f;
            if (FIELD(int, 0x7C) == 6) {
                ++FIELD(short, 0x80);
                FIELD(int, 0x7C) = 0;
            }
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(unsigned char, 0x11) > 5) {
                    FIELD(unsigned char, 0x11) -= 15;
                    FIELD(unsigned char, 0x12) -= 15;
                    FIELD(unsigned char, 0x14) -= 15;
                }
                else {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;
    case 833:
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x20) += 0.05f;
            if (FIELD(int, 0x7C) == 6) {
                ++FIELD(short, 0x80);
                FIELD(int, 0x7C) = 0;
            }
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(unsigned char, 0x11) > 5) {
                    FIELD(unsigned char, 0x11) -= 15;
                    FIELD(unsigned char, 0x12) -= 15;
                    FIELD(unsigned char, 0x14) -= 15;
                }
                else {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;
    case 834:
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) += 0.1f;
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(unsigned char, 0x11) > 5) {
                    FIELD(unsigned char, 0x11) -= 15;
                    FIELD(unsigned char, 0x12) -= 15;
                    FIELD(unsigned char, 0x14) -= 15;
                }
                else {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;
    case 835:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = FIELD(signed char, 0x66) * -80;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 10;
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0x80) = 1;
        }
        FLOAT(0x1C) += FIELD(short, 0xD8) * 0.03 + static_cast<double>(0.02f);
        FLOAT(0x20) += FIELD(short, 0xD8) * 0.03 + static_cast<double>(0.02f);
        if (FIELD(short, 0xD8) > 0) --FIELD(short, 0xD8);
        if (FIELD(short, 0x62) == 21) {
            if (FIELD(unsigned char, 0x11) > 15) {
                FIELD(unsigned char, 0x11) -= 15;
                FIELD(unsigned char, 0x14) -= 15;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 836:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.65f;
            FLOAT(0x20) = 0.65f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = FIELD(signed char, 0x66) * -80;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 10;
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0x80) = 1;
        }
        FLOAT(0x1C) += FIELD(short, 0xD8) * 0.03 + static_cast<double>(0.02f);
        FLOAT(0x20) += FIELD(short, 0xD8) * 0.03 + static_cast<double>(0.02f);
        if (FIELD(short, 0xD8) > 0) --FIELD(short, 0xD8);
        if (FIELD(short, 0x62) == 21) {
            if (FIELD(unsigned char, 0x11) > 15) {
                FIELD(unsigned char, 0x11) -= 15;
                FIELD(unsigned char, 0x14) -= 15;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 837:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = FIELD(signed char, 0x66) * -60;
            FLOAT(0x2C) = 35.0f;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 10;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x1C) += FIELD(short, 0xD8) * 0.05f + 0.05f;
        FLOAT(0x20) += FIELD(short, 0xD8) * 0.05f + 0.05f;
        if (FIELD(short, 0xD8) > 0) --FIELD(short, 0xD8);
        if (FIELD(short, 0x62) == 20) {
            if (FIELD(unsigned char, 0x11) > 15) {
                FIELD(unsigned char, 0x11) -= 15;
                FIELD(unsigned char, 0x14) -= 15;
                FIELD(unsigned char, 0x13) -= 15;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 838:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x1C) += 0.02f;
        FLOAT(0x20) += 0.02f;
        if (FIELD(short, 0x62) == 1) {
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
                FIELD(unsigned char, 0x14) -= 10;
                FIELD(unsigned char, 0x12) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 839:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x1C) += 0.05f;
        FLOAT(0x20) += 0.05f;
        if (FIELD(short, 0x62) == 1) {
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
                FIELD(unsigned char, 0x14) -= 10;
                FIELD(unsigned char, 0x12) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 840:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 2.5f;
            FLOAT(0x20) = 3.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (OWNER(short, 0x60) == 701 && OWNER(short, 0x62) < 11) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 841:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 0;
            FIELD(unsigned char, 0x13) = 0;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = FIELD(signed char, 0x66) * 50;
            FIELD(short, 0xD8) = 1;
        }
        FLOAT(0x30) += 1.0f;
        FLOAT(0x1C) -= 0.01f;
        FLOAT(0x20) -= 0.01f;
        if (FIELD(short, 0x62) == 1) {
            if (FIELD(unsigned char, 0x11) < 248) {
                FIELD(unsigned char, 0x11) += 7;
                FIELD(unsigned char, 0x13) += 7;
                FIELD(unsigned char, 0x12) += 7;
            }
            else {
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
            }
        }
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 10) {
                FIELD(unsigned char, 0x11) -= 10;
                FIELD(unsigned char, 0x13) -= 10;
                FIELD(unsigned char, 0x12) -= 10;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 842:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.2f;
            FLOAT(0x20) = 1.2f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 0;
            FIELD(unsigned char, 0x13) = 0;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = FIELD(signed char, 0x66) * 50;
            FIELD(short, 0xD8) = 1;
        }
        FLOAT(0x1C) -= 0.018f;
        FLOAT(0x20) -= 0.018f;
        if (FIELD(short, 0x62) == 1) {
            if (FIELD(unsigned char, 0x11) < 248) {
                FIELD(unsigned char, 0x11) += 7;
                FIELD(unsigned char, 0x13) += 7;
                FIELD(unsigned char, 0x12) += 7;
            }
            else {
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
            }
        }
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 8) {
                FIELD(unsigned char, 0x11) -= 8;
                FIELD(unsigned char, 0x13) -= 8;
                FIELD(unsigned char, 0x12) -= 8;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 843:
        if (FLOAT(0x44) > 1580.0f || FLOAT(0x44) < -300.0f) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x8A) > 0 && OWNER(short, 0x3B8) == 0) {
                FIELD(short, 0x8A) = 0;
            }
            if (FIELD(short, 0x62) < 3 && OWNER(short, 0x60) != 703) {
                ClearField74();
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                    EnableTransform(0.0f, 0.0f, 0.0f);
                    FLOAT(0x1C) = 0.1f;
                    FLOAT(0x20) = 0.1f;
                    FIELD(unsigned char, 0x11) = 0;
                    FIELD(unsigned char, 0x12) = 0;
                    FIELD(unsigned char, 0x13) = 0;
                    FIELD(unsigned char, 0x14) = 255;
                    FIELD(short, 0x80) = 20;
                    FLOAT(0x50) = 0.0f;
                    FLOAT(0x54) = 0.0f;
                    FIELD(short, 0xD8) = 0;
                }
                if (FIELD(short, 0x62) < 3) {
                    FLOAT(0x30) = RecordedRange(0, 360);
                }
                if (FIELD(int, 0x7C) == 6) {
                    FIELD(int, 0x7C) = 0;
                    ++FIELD(short, 0x80);
                }
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                    FIELD(int, 0x7C) = 0;
                    FLOAT(0x1C) = 1.0f - RecordedRange(0, 10) * 0.01f;
                    FLOAT(0x20) = FLOAT(0x1C);
                }
                if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                    FIELD(int, 0x7C) = 0;
                    FLOAT(0x1C) = 1.0f - RecordedRange(0, 20) * 0.01f;
                    FLOAT(0x20) = FLOAT(0x1C);
                    ++FIELD(short, 0xD8);
                    if (FIELD(short, 0xD8) > 0) {
                        OWNER_ACTOR->SpawnEffect(844, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                        FIELD(short, 0xD8) = 0;
                    }
                }
                if (FIELD(short, 0x62) == 1) {
                    FLOAT(0x1C) += 0.03f;
                    FLOAT(0x20) += 0.03f;
                    if (FIELD(unsigned char, 0x11) < 235) {
                        FIELD(unsigned char, 0x11) += 20;
                        FIELD(unsigned char, 0x13) += 20;
                        FIELD(unsigned char, 0x12) += 20;
                    }
                    else {
                        FIELD(unsigned char, 0x11) = 255;
                        FIELD(unsigned char, 0x12) = 255;
                        FIELD(unsigned char, 0x13) = 255;
                    }
                }
                if (FIELD(short, 0x62) < 3 && OWNER(short, 0x60) == 703) {
                    FLOAT(0x44) = OWNER_FLOAT(0x44) + OWNER(signed char, 0x66) * 100;
                    FLOAT(0x48) = OWNER_FLOAT(0x48) + 110.0f;
                }
                if (FIELD(short, 0x62) == 2 && OWNER(short, 0x60) == 703 && OWNER(short, 0x62) > 28) {
                    ResetSecondaryCounters(3);
                    FLOAT(0x50) = 20.0f;
                    FLOAT(0x30) = 0.0f;
                    FIELD(short, 0x80) = 20;
                    FIELD(int, 0x7C) = 0;
                }
                if (FIELD(short, 0x62) == 3) {
                    OWNER_ACTOR->SpawnEffect(RecordedRange(0, 7) + 818, FLOAT(0x44) + 150.0f - RecordedRange(0, 300), FLOAT(0x48) + 150.0f - RecordedRange(0, 300), FIELD(signed char, 0x66), 1);
                }
                if (FIELD(short, 0x62) > 3) {
                    if (FIELD(unsigned char, 0x11) > 30) {
                        FIELD(unsigned char, 0x11) -= 30;
                        FIELD(unsigned char, 0x13) -= 30;
                        FIELD(unsigned char, 0x12) -= 30;
                    }
                    else {
                        ClearField74();
                        return;
                    }
                }
                FLOAT(0x44) += FIELD(signed char, 0x66) * FLOAT(0x50);
                FLOAT(0x48) += FLOAT(0x54);
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                    ResetSecondaryCounters(2);
                    FIELD(int, 0x7C) = 0;
                }
                if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) {
                    ResetSecondaryCounters(3);
                    FIELD(int, 0x7C) = 0;
                }
            }
        }
        break;
    case 844:
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.5f;
                FLOAT(0x20) = 0.5f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x28) = RecordedRange(0, 359);
                FLOAT(0x2C) = RecordedRange(0, 359);
                FLOAT(0x30) = RecordedRange(0, 359);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x1C) += 0.085f;
            FLOAT(0x20) += 0.085f;
            if (FIELD(short, 0x62) == 1) {
                if (FIELD(unsigned char, 0x11) > 12) {
                    FIELD(unsigned char, 0x11) -= 12;
                }
                else {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;
    case 845:
        if ((OWNER(short, 0x60) == 508 || OWNER(short, 0x60) == 509) && OWNER_FLOAT(0x48) > 0.0f) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48);
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(short, 0xD8) = 1;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 846:
        if (OWNER(short, 0x60) == 305) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48);
        }
        else {
            ClearField74();
            return;
        }
        if (OWNER(short, 0x82) == 0) {
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;
    case 847:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = 60.0f;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 10;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x1C) += FIELD(short, 0xD8) * 0.02f + 0.02f;
        FLOAT(0x20) += FIELD(short, 0xD8) * 0.02f + 0.02f;
        if (FIELD(short, 0xD8) > 0) --FIELD(short, 0xD8);
        if (FIELD(short, 0x62) == 4) {
            if (FIELD(unsigned char, 0x11) > 15) {
                FIELD(unsigned char, 0x11) -= 15;
                FIELD(unsigned char, 0x14) -= 15;
                FIELD(unsigned char, 0x13) -= 15;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 848:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = 60.0f;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 10;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x1C) += FIELD(short, 0xD8) * 0.05f + 0.05f;
        FLOAT(0x20) += FIELD(short, 0xD8) * 0.05f + 0.05f;
        if (FIELD(short, 0xD8) > 0) --FIELD(short, 0xD8);
        if (FIELD(short, 0x62) == 20) {
            if (FIELD(unsigned char, 0x11) > 15) {
                FIELD(unsigned char, 0x11) -= 15;
                FIELD(unsigned char, 0x14) -= 15;
                FIELD(unsigned char, 0x13) -= 15;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 849:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = FIELD(signed char, 0x66) * -30;
            FLOAT(0x2C) = 60.0f;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 10;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x1C) += FIELD(short, 0xD8) * 0.05f + 0.05f;
        FLOAT(0x20) += FIELD(short, 0xD8) * 0.05f + 0.05f;
        if (FIELD(short, 0xD8) > 0) --FIELD(short, 0xD8);
        if (FIELD(short, 0x62) == 20) {
            if (FIELD(unsigned char, 0x11) > 15) {
                FIELD(unsigned char, 0x11) -= 15;
                FIELD(unsigned char, 0x14) -= 15;
                FIELD(unsigned char, 0x13) -= 15;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 850:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 10;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x1C) -= 0.02f;
        FLOAT(0x20) -= 0.02f;
        if (FIELD(short, 0x62) == 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 30;
            }
            else {
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;
    case 990:
        if (OWNER(short, 0xF2A) == 0 && FIELD(short, 0x62) < 2) {
            ResetSecondaryCounters(2);
            return;
        }
        else {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
            FIELD(short, 0x8A) = 1;
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 2.0f;
                FLOAT(0x20) = 2.0f;
                FIELD(unsigned char, 0x11) = 0;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            FLOAT(0x30) += 1.0f;
            if (FIELD(short, 0x62) == 0) {
                if (FIELD(unsigned char, 0x11) < 180) {
                    FIELD(unsigned char, 0x11) += 25;
                }
                else {
                    FIELD(unsigned char, 0x11) = 180;
                }
                if (OWNER(short, 0xF2A) >= 120) {
                    ResetSecondaryCounters(1);
                    FIELD(unsigned char, 0x11) = 180;
                    return;
                }
            }
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(unsigned char, 0x11) >= 30) {
                    FIELD(unsigned char, 0x11) -= 30;
                }
                else {
                    FIELD(unsigned char, 0x11) = 0;
                }
                if (FIELD(unsigned char, 0x11) == 0) {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ClearField74();
                return;
            }
        }
        break;
    case 991:
        if (OWNER(short, 0xF2A) == 0 && FIELD(short, 0x62) < 2) {
            ResetSecondaryCounters(2);
            return;
        }
        else {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
            FIELD(short, 0x8A) = 1;
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 0.0f;
                FIELD(unsigned char, 0x11) = 0;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            FLOAT(0x1C) = OWNER(short, 0xF2A) / 45.0f;
            FLOAT(0x20) = FLOAT(0x1C);
            if (FIELD(short, 0x62) == 0) {
                if (FIELD(unsigned char, 0x11) < 230) {
                    FIELD(unsigned char, 0x11) += 25;
                }
                else {
                    FIELD(unsigned char, 0x11) = 255;
                }
                if (OWNER(short, 0xF2A) >= 120) {
                    ResetSecondaryCounters(1);
                    FIELD(unsigned char, 0x11) = 255;
                    return;
                }
            }
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(unsigned char, 0x11) >= 10) {
                    FIELD(unsigned char, 0x11) -= 10;
                }
                else {
                    FIELD(unsigned char, 0x11) = 0;
                }
                if (FIELD(unsigned char, 0x11) == 0) {
                    ClearField74();
                    return;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ClearField74();
                return;
            }
        }
        break;
    case 994:
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = 1.0f;
        FIELD(short, 0x8A) = 1;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 3.0f;
            FLOAT(0x20) = 3.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x1A) = 1250;
            FLOAT(0x2C) = 0.0f;
            FLOAT(0x30) = 0.0f;
            FLOAT(0x28) = -80.0f;
            FIELD(short, 0xD8) = OWNER(short, 0x3A0);
        }
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            FLOAT(0x1C) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2 + 1.0f;
            FLOAT(0x20) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2 + 1.0f;
            FLOAT(0x30) -= 1.0f;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ResetSecondaryCounters(1);
                return;
            }
        }
        break;
    case 950:
        if (OWNER(short, 0x60) != 700 && OWNER(short, 0x60) != 701 && OWNER(short, 0x60) != 706 && OWNER(short, 0x60) != 707) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
                FLOAT(0x54) = 15.0f;
            }
            FLOAT(0x30) -= 35.0f;
            FLOAT(0x48) += FLOAT(0x54);
            if (FLOAT(0x48) > 1000.0f) {
                ClearField74();
                return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            }
        }
        break;
    case 951:
        if (FIELD(short, 0x62) < 1) {
            FLOAT(0x48) = OWNER_FLOAT(0x48);
        }
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        OWNER(short, 0xF0C) = 1;
        if (OWNER(short, 0x62) == 0 && ((OWNER(short, 0x60) >= 70 && OWNER(short, 0x60) <= 88 && OWNER(short, 0x60) != 76) || OWNER(short, 0x60) == 181 || OWNER(short, 0x60) == 180 || OWNER(short, 0x60) == 145)) {
            ClearField74();
            OWNER(short, 0xF0C) = 0;
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(-45.0f, 45.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            if (FIELD(short, 0x62) == 0 && (OWNER(short, 0x60) == 96 || OWNER(short, 0x60) == 97) && OWNER(short, 0x62) == 5) {
                ResetSecondaryCounters(1);
                FLOAT(0x30) = 0.0f;
                return;
            }
            else if (FIELD(short, 0x62) == 5 && (OWNER(short, 0x60) == 95 || OWNER(short, 0x60) == 94 || OWNER(short, 0x60) == 93 || OWNER(short, 0x60) == 796 || OWNER(short, 0x60) == 771) && OWNER(short, 0x62) == 3) {
                ResetSecondaryCounters(6);
                return;
            }
            else if (FIELD(short, 0x62) == 7 && (OWNER(short, 0x60) == 95 || OWNER(short, 0x60) == 94 || OWNER(short, 0x60) == 93 || OWNER(short, 0x60) == 796) && OWNER(short, 0x62) == 11) {
                ClearField74();
                OWNER(short, 0xF0C) = 0;
                return;
            }
            else {
                if (FIELD(short, 0x62) == 7 && FIELD(short, 0x64) == 0 && OWNER(short, 0x60) != 771 && OWNER(short, 0x60) != 772) {
                    FLOAT(0x54) = 15.0f;
                    FLOAT(0x5C) = -1.0f;
                }
                if (FIELD(short, 0x62) == 7 && OWNER(short, 0x60) != 772 && OWNER(short, 0x60) != 771) {
                    FLOAT(0x54) += FLOAT(0x5C);
                    FLOAT(0x48) += FLOAT(0x54);
                }
                if (FIELD(short, 0x62) == 7 && (OWNER(short, 0x60) == 772 || OWNER(short, 0x60) == 771)) {
                    FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 120;
                    FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
                }
                if (FIELD(short, 0x62) == 0 || FIELD(short, 0x62) == 7) {
                    FLOAT(0x30) -= 35.0f;
                }
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            }
        }
        break;
    case 995:
        FIELD(signed char, 0x66) = 1;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = -1.0f;
            FIELD(short, 0xD8) = RecordedRange(0, 360) - 180;
            FIELD(short, 0xDA) = 15;
        }
        if (FIELD(short, 0x62) == 0) {
            --FIELD(short, 0xDA);
            if (FIELD(short, 0xDA) < 3) FIELD(short, 0xDA) = 3;
            SetPolarVelocity(FIELD(short, 0xD8), FIELD(short, 0xDA) * 0.8f);
        }
        if (FIELD(short, 0x62) == 1) {
            FIELD(short, 0xD8) = static_cast<short>(AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48), OPPONENT_FLOAT(0x44) - FLOAT(0x44)) / 0.017453288659453392f);
            SetPolarVelocity(FIELD(short, 0xD8), 20.0f);
            if (FLOAT(0x44) - OPPONENT_FLOAT(0x44) < 20.0f && FLOAT(0x44) - OPPONENT_FLOAT(0x44) > -20.0f && FLOAT(0x48) - OPPONENT_FLOAT(0x48) < 120.0f && FLOAT(0x48) - OPPONENT_FLOAT(0x48) > 80.0f) {
                ClearField74();
                if (OPPONENT(signed char, 0x366) < 2) {
                    ++OPPONENT(signed char, 0x366);
                }
                else {
                    OPPONENT(int, 0x2D0) += 20000;
                }
                PlaySharedSound(46);
                return;
            }
        }
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) -= FLOAT(0x54);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(1);
        }
        break;
    case 996:
        FIELD(signed char, 0x66) = 1;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = -1.0f;
            FIELD(short, 0xD8) = RecordedRange(0, 360) - 180;
            FIELD(short, 0xDA) = 15;
        }
        if (FIELD(short, 0x62) == 0) {
            --FIELD(short, 0xDA);
            if (FIELD(short, 0xDA) < 3) FIELD(short, 0xDA) = 3;
            SetPolarVelocity(FIELD(short, 0xD8), FIELD(short, 0xDA) * 0.8f);
        }
        if (FIELD(short, 0x62) == 1) {
            FIELD(short, 0xD8) = static_cast<short>(AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48), OPPONENT_FLOAT(0x44) - FLOAT(0x44)) / 0.017453288659453392f);
            SetPolarVelocity(FIELD(short, 0xD8), 20.0f);
            if (FLOAT(0x44) - OPPONENT_FLOAT(0x44) < 20.0f && FLOAT(0x44) - OPPONENT_FLOAT(0x44) > -20.0f && FLOAT(0x48) - OPPONENT_FLOAT(0x48) < 120.0f && FLOAT(0x48) - OPPONENT_FLOAT(0x48) > 80.0f) {
                ++OWNER(short, 0xEFA);
                PlaySharedSound(46);
                ClearField74();
                if (OPPONENT(short, 0x3B6) > 0) {
                    if (OPPONENT(short, 0x3B6) > 5) {
                        OPPONENT(short, 0x3B6) -= 5;
                    }
                    else {
                        OPPONENT(short, 0x3B6) = 0;
                        OPPONENT(short, 0x3B0) = 1000;
                    }
                    return;
                }
                else if (OPPONENT(short, 0x3B0) < 990) {
                    OPPONENT(short, 0x3B0) += 10;
                }
                else {
                    OPPONENT(short, 0x3B0) = 1000;
                    if (OPPONENT(unsigned char, 0x39C) == 0) {
                        if (OPPONENT_FLOAT(0x36C) < 998.9) {
                            OPPONENT_FLOAT(0x36C) += 0.5f;
                        }
                        else {
                            OPPONENT_FLOAT(0x36C) = 900.0f;
                        }
                    }
                }
                return;
            }
        }
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) -= FLOAT(0x54);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(1);
        }
        break;
    case 997:
        FLOAT(0x44) = OWNER_FLOAT(0x44);
        FLOAT(0x48) = 0.0f;
        FIELD(short, 0x8A) = 1;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 3.0f;
            FLOAT(0x20) = 3.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x1A) = 1250;
            FLOAT(0x2C) = 0.0f;
            FLOAT(0x30) = 0.0f;
            FLOAT(0x28) = -80.0f;
            FIELD(short, 0xD8) = OWNER(short, 0x3A0);
        }
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            FLOAT(0x1C) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2;
            FLOAT(0x20) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2;
            FLOAT(0x30) += 1.0f;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ResetSecondaryCounters(10);
                break;
            }
        }
        break;
    case 998:
        FIELD(unsigned char, 0x66) = OWNER(unsigned char, 0x66);
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 2.5f;
            FLOAT(0x20) = 2.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = 50.0f;
            FIELD(short, 0xD8) = 0;
        }
        if (OWNER(short, 0x60) > 149 && OWNER(short, 0x60) < 154 && FIELD(short, 0xD8) == 0) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 57;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 94.0f;
        }
        if (OWNER(short, 0x60) > 153 && OWNER(short, 0x60) < 158 && FIELD(short, 0xD8) == 0) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 57;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 60.0f;
        }
        if (OWNER(short, 0x60) == 158 && FIELD(short, 0xD8) == 0) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 57;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        }
        if ((OWNER(short, 0x60) < 150 || OWNER(short, 0x60) > 158) && FIELD(short, 0xD8) == 0) {
            FIELD(short, 0xD8) = 1;
            OWNER(short, 0xF0A) = 0;
        }
        FLOAT(0x30) -= 3.0f;
        if (FIELD(short, 0xD8) > 0) {
            if (FIELD(unsigned char, 0x11) > 30) {
                FIELD(unsigned char, 0x11) -= 30;
            }
            else {
                FIELD(unsigned char, 0x11) = 0;
                ClearField74();
                return;
            }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(1);
        }
        break;
    default:
        AdvanceNestedFrame();
        break;
    }
}

#undef OWNER_ACTOR
#undef OPPONENT_FLOAT
#undef OWNER_FLOAT
#undef OPPONENT
#undef OWNER
#undef FLOAT
#undef FIELD
