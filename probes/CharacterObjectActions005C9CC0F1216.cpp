// Work in progress toward complete original 005C9CC0 (43,501 CODE B).
// Only independently reviewed native states are written. This draft is
// NONEXACT, incomplete, and not an accepted executable replacement.
#include "ObjectAdvance5C9CC0F1216.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OWNER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset)))
#define OPPONENT(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset))
#define OWNER_ACTOR reinterpret_cast<OwnerActor5C9CC0F1216*>(FIELD(void*, 0xE4))

void ObjectActor5C9CC0F1216::AdvanceAction()
{
    if (OPPONENT(short, 0x3BA) != 0) return;
    if (OWNER(short, 0x3BA) != 0 && FIELD(short, 0x8A) == 0) return;
    if (FIELD(short, 0x82) != 0) {
        --FIELD(short, 0x82);
        return;
    }
    switch (FIELD(short, 0x60)) {
    case 800:
        if (OWNER(short, 0x60) != 301 && FIELD(short, 0x62) < 18)
            ResetSecondaryCounters(18);
        if (OWNER(short, 0x60) == 301) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 128;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 66.0f;
        }
        if (FIELD(int, 0x7C) == 6) {
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0x80) = 1;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.2f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x80) = 1;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 801:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 9) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex801 = 0; cancelIndex801 < 6; cancelIndex801++)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 1;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.1f;
                FLOAT(0x20) = 0.1f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (FIELD(short, 0x62) < 5) {
                FLOAT(0x1C) += 0.1f;
                FLOAT(0x20) += 0.1f;
                if (FLOAT(0x1C) >= 0.5f) {
                    ResetSecondaryCounters(FIELD(short, 0x62) + 4);
                    FLOAT(0x1C) = 0.5f;
                    FLOAT(0x20) = 0.5f;
                }
            }
            if (FIELD(short, 0x80) == 0 && FIELD(short, 0x62) < 9) {
                ResetSecondaryCounters(9);
                FLOAT(0x50) = -2.0f - RecordedRange(0, 4);
                FLOAT(0x54) = RecordedRange(0, 6) + 8.0f;
            }
            if (FIELD(short, 0x62) < 9) {
                if (FLOAT(0x54) > 3.0f) FIELD(short, 0xD8) = 1;
                if (FLOAT(0x54) < -3.0f) FIELD(short, 0xD8) = -1;
                if (FIELD(short, 0xD8) == 1) FLOAT(0x54) -= 0.2f;
                if (FIELD(short, 0xD8) == -1) FLOAT(0x54) += 0.2f;
            }
            if (FIELD(short, 0x62) > 8 && FIELD(short, 0x62) < 19) {
                FLOAT(0x54) -= 0.8f;
                if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f) {
                    ResetSecondaryCounters(19);
                    FLOAT(0x54) = 0.0f;
                    FLOAT(0x50) = 0.0f;
                    return;
                }
            }
            if (FIELD(short, 0x62) == 29) {
                if (FIELD(unsigned char, 0x11) >= 20) FIELD(unsigned char, 0x11) -= 20;
                else { ClearField74(); return; }
            }
            if (FLOAT(0x44) > 1480.0f || FLOAT(0x44) < -200.0f) {
                ClearField74();
                return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                if (FIELD(short, 0x62) == 5 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
                if (FIELD(short, 0x62) == 9 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(5);
                if (FIELD(short, 0x62) == 19 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(17);
            }
        }
        break;

    case 802:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 16) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex802 = 0; cancelIndex802 < 6; cancelIndex802++)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 1;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.1f;
                FLOAT(0x20) = 0.1f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (FIELD(short, 0x62) < 6) {
                FLOAT(0x1C) += 0.1f;
                FLOAT(0x20) += 0.1f;
                if (FLOAT(0x1C) >= 0.5f) {
                    FLOAT(0x1C) = 0.5f;
                    FLOAT(0x20) = 0.5f;
                }
                FLOAT(0x54) -= 0.6f;
                if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f) {
                    ResetSecondaryCounters(6);
                    FLOAT(0x50) = 0.0f;
                    FLOAT(0x54) = 0.0f;
                }
            }
            if (FIELD(short, 0x80) == 0 && FIELD(short, 0x62) < 16) {
                ResetSecondaryCounters(16);
                FLOAT(0x50) = -2.0f - RecordedRange(0, 4);
                FLOAT(0x54) = RecordedRange(0, 6) + 8.0f;
            }
            if (FIELD(short, 0x62) > 15 && FIELD(short, 0x62) < 26) {
                FLOAT(0x54) -= 0.8f;
                if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f) {
                    ResetSecondaryCounters(26);
                    FLOAT(0x54) = 0.0f;
                    FLOAT(0x50) = 0.0f;
                    return;
                }
            }
            if (FIELD(short, 0x62) == 36) {
                if (FIELD(unsigned char, 0x11) >= 20) FIELD(unsigned char, 0x11) -= 20;
                else { ClearField74(); return; }
            }
            if (FLOAT(0x44) > 1480.0f || FLOAT(0x44) < -200.0f) {
                ClearField74();
                return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                if (FIELD(short, 0x62) == 6 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(4);
                if (FIELD(short, 0x62) == 8 && FIELD(short, 0x64) == 0)
                    FLOAT(0x50) = RecordedRange(0, 3) + 5;
                if (FIELD(short, 0x62) == 16 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(8);
                if (FIELD(short, 0x62) == 26 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(24);
            }
        }
        break;

    case 803:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex803 = 0; cancelIndex803 < 15; cancelIndex803++)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 0;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 10.0f;
                FLOAT(0x54) = 8.0f;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (FLOAT(0x50) > 2.5f) FLOAT(0x50) -= 1.0f;
            else FLOAT(0x50) = 2.5f;
            FLOAT(0x54) -= 0.6f;
            OWNER_ACTOR->SpawnEffect(804, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ClearField74();
                OWNER_ACTOR->PlaySoundAt00453D40(18);
                OWNER_ACTOR->SetCameraShakeAt00453E60(5.0f);
                for (int burstIndex803 = 0; burstIndex803 < 18; burstIndex803++) {
                    OWNER_FLOAT(0x314) = burstIndex803 * 20;
                    OWNER_FLOAT(0x318) = 17.0f;
                    OWNER_ACTOR->SpawnEffect(805, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 0);
                }
            }
        }
        break;

    case 804:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.6f;
            FLOAT(0x20) = 0.6f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            SetPolarVelocity(RecordedRange(0, 359), RecordedRange(0, 5) + 5);
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x1C) *= 0.85f;
        FLOAT(0x20) *= 0.85f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 805:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 1) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex805 = 0; cancelIndex805 < 2; cancelIndex805++)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 0;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 2;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 1) {
                FIELD(short, 0xD8) = 0;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
            if (FLOAT(0xCC) > 2.0f) FLOAT(0xCC) -= 1.0f;
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (FIELD(short, 0x62) == 0) {
                OWNER_ACTOR->SpawnEffect(806, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                FLOAT(0x1C) = RecordedRange(0, 4) * 0.1f + 0.8f;
                FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
                if (FIELD(short, 0x80) == 0) ResetSecondaryCounters(1);
            }
            if (FIELD(short, 0x62) == 1) {
                FLOAT(0x1C) *= 0.85f;
                FLOAT(0x20) *= 0.85f;
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 806:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.75f;
            FLOAT(0x20) = 0.75f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        FLOAT(0x1C) *= 0.85f;
        FLOAT(0x20) *= 0.85f;
        if (FIELD(unsigned char, 0x11) > 15) {
            FIELD(unsigned char, 0x11) -= 15;
            FIELD(unsigned char, 0x14) -= 15;
            FIELD(unsigned char, 0x13) -= 15;
        }
        else { ClearField74(); return; }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 835:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 2.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 901:
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 902:
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
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
