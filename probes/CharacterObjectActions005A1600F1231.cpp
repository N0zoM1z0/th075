// Complete research source for original 005A1600 (43,599 CODE bytes).
// All native states are written; still NONEXACT and not an accepted replacement.
#include "ObjectAdvance5A1600F1231.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OWNER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset)))
#define OPPONENT(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset))
#define OWNER_ACTOR reinterpret_cast<OwnerActor5A1600F1231*>(FIELD(void*, 0xE4))

extern float g_F1211_AngleDivAt00657828;
extern signed char g_F1212_DifficultyAt006714D0;

void ObjectActor5A1600F1231::AdvanceAction()
{
    if (OPPONENT(short, 0x3BA) != 0) return;
    if (OWNER(short, 0x3BA) != 0 && FIELD(short, 0x8A) == 0) return;
    if (FIELD(short, 0x82) != 0) {
        --FIELD(short, 0x82);
        return;
    }
    switch (FIELD(short, 0x60)) {
    case 800:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        else if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex = 0; rewardIndex < 3; ++rewardIndex)
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
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
            }
            ++FIELD(short, 0xD8);
            if (FIELD(short, 0x62) < 2)
                SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.1f + FLOAT(0xCC));
            if ((FIELD(int, 0x7C) == 1 || FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4 || FIELD(int, 0x7C) == 6) && FIELD(short, 0x62) == 1) {
                ResetSecondaryCounters(2);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                return;
            }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        FLOAT(0x30) += 15.0f;
                        FLOAT(0x1C) *= 0.9f;
                        FLOAT(0x20) *= 0.9f;
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

    case 801:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 75.0f;
        }
        FLOAT(0x1C) += 0.2f;
        FLOAT(0x20) += 0.2f;
        if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 802:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        FLOAT(0x1C) += 0.2f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 803:
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
            FLOAT(0x50) = 25.0f;
        }
        FLOAT(0x50) -= 0.8f;
        if (FLOAT(0x50) < 2.5f) FLOAT(0x50) = 2.5f;
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 804:
        if (OWNER(short, 0x60) == 700 && OWNER(short, 0x62) < 7) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 126;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 139.0f;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 0.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = -30.0f;
            FLOAT(0x2C) = FIELD(signed char, 0x66) * 60;
            FIELD(short, 0xD8) = 0;
        }
        FLOAT(0x30) += 5.0f;
        if (FLOAT(0x1C) < 1.0f) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) += 0.1f;
        }
        if (FLOAT(0x1C) <= 1.0f && FIELD(short, 0xD8) == 0) {
            OWNER_ACTOR->SpawnEffect(805, OWNER_FLOAT(0x44), OWNER_FLOAT(0x48), FIELD(signed char, 0x66), 0);
            ++FIELD(short, 0xD8);
        }
        if ((OWNER(short, 0x62) > 6 && OWNER(short, 0x60) == 700) || OWNER(short, 0x60) != 700) {
            if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 805:
        if (OWNER(short, 0x60) == 700 && OWNER(short, 0x62) < 7) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x80) = 99;
        }
        if ((OWNER(short, 0x62) > 6 && OWNER(short, 0x60) == 700) || OWNER(short, 0x60) != 700) {
            ClearField74(); return;
        }
        else if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(1);
            FIELD(int, 0x7C) = 0;
        }
        break;

    case 806:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex806 = 0; rewardIndex806 < 3; ++rewardIndex806)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
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
                SetPolarVelocity(FLOAT(0xC8), 10.0f);
            }
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) >= FLOAT(0xCC)) {
                ResetSecondaryCounters(1);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (FIELD(short, 0x62) == 1) {
                SetPolarVelocity(FLOAT(0xD0), FIELD(short, 0xD8) * 0.1f);
                FIELD(short, 0xD8) += 10;
                OWNER(unsigned int, 0x314) = FIELD(unsigned int, 0xD0);
                OWNER_FLOAT(0x318) = FIELD(short, 0xD8);
                OWNER_ACTOR->SpawnEffect(807, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                if (FIELD(int, 0x7C) != 0) {
                    FLOAT(0x50) = 0.0f;
                    FLOAT(0x54) = 0.0f;
                    ResetSecondaryCounters(2);
                    return;
                }
            }
            if (FIELD(short, 0x62) == 2) {
                FIELD(short, 0xD8) -= 20;
                if (FIELD(short, 0xD8) < 0) FIELD(short, 0xD8) = 0;
                OWNER(unsigned int, 0x314) = FIELD(unsigned int, 0xD0);
                OWNER_FLOAT(0x318) = FIELD(short, 0xD8);
                OWNER_ACTOR->SpawnEffect(807, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                FLOAT(0x1C) *= 0.95f;
                FLOAT(0x20) *= 0.95f;
            }
            if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -520.0f || FLOAT(0x48) > 1400.0f || FLOAT(0x48) < -520.0f) {
                ClearField74(); return;
            }
            else if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 807:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = FLOAT(0xCC) * 0.01f + 0.0f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0x80) = 1;
            FIELD(unsigned int, 0x30) = FIELD(unsigned int, 0xC8);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 808:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x80) = 255;
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x62) < 6) {
            FLOAT(0x1C) += 0.2f;
            if (FLOAT(0x1C) > 1.5) FLOAT(0x1C) = 1.5f;
        }
        if (FIELD(short, 0x62) > 5 && FIELD(int, 0x7C) == 5) {
            FIELD(int, 0x7C) = 0;
            ++OWNER(short, 0xF30);
            if (OWNER(short, 0xF30) > 10) OWNER(short, 0xF30) = 10;
        }
        if (FIELD(short, 0x80) == 0) {
            if (FLOAT(0x1C) > 0.15f) FLOAT(0x1C) -= 0.15f;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(6);
            ++FIELD(short, 0xD8);
            if (FIELD(short, 0xD8) > 1) FIELD(short, 0x80) = 0;
        }
        break;

    case 809:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x80) = 255;
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x62) < 6) {
            FLOAT(0x1C) += 0.2f;
            if (FLOAT(0x1C) > 1.5) FLOAT(0x1C) = 1.5f;
        }
        if (FIELD(short, 0x62) > 5 && FIELD(int, 0x7C) == 5) {
            FIELD(int, 0x7C) = 0;
            ++OWNER(short, 0xF30);
            if (OWNER(short, 0xF30) > 10) OWNER(short, 0xF30) = 10;
        }
        if (FIELD(short, 0x80) == 0) {
            if (FLOAT(0x1C) > 0.15f) FLOAT(0x1C) -= 0.15f;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(6);
            ++FIELD(short, 0xD8);
            if (FIELD(short, 0xD8) > 2) FIELD(short, 0x80) = 0;
        }
        break;

    case 810:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0)
            OWNER_ACTOR->SpawnEffect(811, FLOAT(0x44), FLOAT(0x48) - 220.0f, FIELD(signed char, 0x66), 1);
        break;

    case 811:
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
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f && FIELD(short, 0x62) < 7) {
            FLOAT(0x54) = 0.0f;
            FLOAT(0x48) = 0.0f;
            OWNER_ACTOR->SetCameraShakeAt00453E60(5.0f);
            ResetSecondaryCounters(7);
            OWNER_ACTOR->PlaySoundAt00453D40(10);
            OWNER_ACTOR->SpawnAuxEffectAt00453C80(129, FLOAT(0x44) - 50.0f, 0.0f, 1, 1);
            OWNER_ACTOR->SpawnAuxEffectAt00453C80(129, FLOAT(0x44) + 50.0f, 0.0f, -1, 1);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 8) {
                if (FIELD(unsigned char, 0x11) > 15) FIELD(unsigned char, 0x11) -= 15;
                else { ClearField74(); return; }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 6 && FIELD(short, 0x64) == 0) {
                FLOAT(0x54) = -18.0f;
                OWNER_ACTOR->PlaySoundAt00453D40(5);
            }
        }
        break;

    case 813:
        OWNER(short, 0xF0E) = 1;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 20;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x62) == 1) {
            if (FLOAT(0x1C) < 1.0f) FLOAT(0x1C) += 0.25f;
            if (FLOAT(0x20) > 1.0f) FLOAT(0x20) -= 0.25f;
        }
        if (FIELD(short, 0x62) == 2 && AbsFloatAt00412D90(FLOAT(0x44) - OPPONENT_FLOAT(0x44)) < 100.0f) {
            ResetSecondaryCounters(3);
            FLOAT(0x50) = 10.0f;
            UnknownAt0045B850(8);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 3) {
                FLOAT(0x30) -= 30.0f;
                if (FLOAT(0x50) > 1.0f) FLOAT(0x50) -= 1.0f;
            }
            if (FIELD(short, 0x62) == 4) {
                FLOAT(0x54) -= 0.4f;
                FLOAT(0x30) -= 30.0f;
            }
            if (FIELD(short, 0x62) == 5) {
                FLOAT(0x30) -= 30.0f;
                if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
                else { ClearField74(); OWNER(short, 0xF0E) = 0; return; }
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (FLOAT(0x44) > 1480.0f || FLOAT(0x44) < -200.0f) {
                ClearField74(); OWNER(short, 0xF0E) = 0; return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                    ClearField74(); OWNER(short, 0xF0E) = 0; return;
                }
                else {
                    if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) FLOAT(0x50) = 30.0f;
                    if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) {
                        if (FIELD(short, 0xD8) < 20 && FIELD(short, 0x80) > 0) {
                            ResetSecondaryCounters(3);
                            FIELD(int, 0x7C) = 0;
                            ++FIELD(short, 0xD8);
                            return;
                        }
                        if (FIELD(int, 0x7C) != 0) {
                            ResetSecondaryCounters(4);
                            FLOAT(0x50) = -3.0f;
                            FLOAT(0x54) = 15.0f;
                        }
                        else ResetSecondaryCounters(5);
                    }
                    if (FIELD(short, 0x62) == 5 && FIELD(short, 0x64) == 0) UnknownAt0045B850(9);
                }
            }
        }
        break;

    case 814:
        OWNER(short, 0xF0E) = 1;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 30;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x8A) > 0 && OWNER(short, 0x3B8) == 0) FIELD(short, 0x8A) = 0;
        if (FIELD(short, 0x62) == 1) {
            if (FLOAT(0x1C) < 1.0f) FLOAT(0x1C) += 0.25f;
            if (FLOAT(0x20) > 1.0f) FLOAT(0x20) -= 0.25f;
        }
        if (FIELD(short, 0x62) == 2 && AbsFloatAt00412D90(FLOAT(0x44) - OPPONENT_FLOAT(0x44)) < 100.0f) {
            ResetSecondaryCounters(3);
            FLOAT(0x50) = 10.0f;
            UnknownAt0045B850(8);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 3) {
                FLOAT(0x30) -= 30.0f;
                if (FLOAT(0x50) > 1.0f) FLOAT(0x50) -= 1.0f;
            }
            if (FIELD(short, 0x62) == 4) {
                FLOAT(0x54) -= 0.4f;
                FLOAT(0x30) -= 30.0f;
            }
            if (FIELD(short, 0x62) == 5) {
                FLOAT(0x30) -= 30.0f;
                if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
                else { ClearField74(); OWNER(short, 0xF0E) = 0; return; }
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (FLOAT(0x44) > 1480.0f || FLOAT(0x44) < -200.0f) {
                ClearField74(); OWNER(short, 0xF0E) = 0; return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                    ClearField74(); OWNER(short, 0xF0E) = 0; return;
                }
                else {
                    if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) FLOAT(0x50) = 30.0f;
                    if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) {
                        if (FIELD(short, 0xD8) < 30 && FIELD(short, 0x80) > 0) {
                            ResetSecondaryCounters(3);
                            FIELD(int, 0x7C) = 0;
                            ++FIELD(short, 0xD8);
                            return;
                        }
                        if (FIELD(int, 0x7C) != 0) {
                            ResetSecondaryCounters(4);
                            FLOAT(0x50) = -2.0f;
                            FLOAT(0x54) = 15.0f;
                        }
                        else ResetSecondaryCounters(5);
                    }
                    if (FIELD(short, 0x62) == 5 && FIELD(short, 0x64) == 0) UnknownAt0045B850(9);
                }
            }
        }
        break;

    case 815:
        OWNER(short, 0xF10) = 1;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 20;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x8A) > 0 && OWNER(short, 0x3B8) == 0) FIELD(short, 0x8A) = 0;
        if (FIELD(short, 0x62) == 1) {
            if (FLOAT(0x1C) < 1.0f) FLOAT(0x1C) += 0.25f;
            if (FLOAT(0x20) > 1.0f) FLOAT(0x20) -= 0.25f;
        }
        if (FIELD(short, 0x62) > 1) {
            if ((FIELD(signed char, 0x66) == 1 &&
                 ((FLOAT(0x50) > 0.0f && FLOAT(0x44) > OWNER_FLOAT(0x2DC)) ||
                  (FLOAT(0x50) < 0.0f && FLOAT(0x44) < OWNER_FLOAT(0x2D8)))) ||
                (FIELD(signed char, 0x66) == -1 &&
                 ((FLOAT(0x50) < 0.0f && FLOAT(0x44) > OWNER_FLOAT(0x2DC)) ||
                  (FLOAT(0x50) > 0.0f && FLOAT(0x44) < OWNER_FLOAT(0x2D8)))))
                FLOAT(0x50) = -FLOAT(0x50);
            FLOAT(0x30) -= 30.0f;
            FLOAT(0x54) -= 0.8f;
            if (FLOAT(0x48) + FLOAT(0x54) < 0.0f && FLOAT(0x54) < 0.0f) {
                ++FIELD(short, 0xD8);
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
                FLOAT(0x54) = -FLOAT(0x54);
                OWNER_ACTOR->PlaySoundAt00453D40(13);
            }
        }
        if (FIELD(short, 0x62) == 5) {
            FLOAT(0x30) -= 30.0f;
            if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
            else { ClearField74(); OWNER(short, 0xF10) = 0; return; }
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ClearField74(); OWNER(short, 0xF10) = 0; return;
        }
        else {
            if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                FLOAT(0x50) = 6.0f;
                FLOAT(0x54) = 16.0f;
            }
            if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 5)
                ResetSecondaryCounters(3);
        }
        break;

    case 816:
        if (OWNER(short, 0x60) == 703 && OWNER(short, 0x62) < 7) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 126;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 140.0f;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 0.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 20.0f;
            FLOAT(0x2C) = FIELD(signed char, 0x66) * -50;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
            FIELD(short, 0x80) = 99;
            FIELD(int, 0x7C) = 0;
        }
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) OWNER_FLOAT(0x490) = 0.0f;
        FLOAT(0x30) += 5.0f;
        if (FLOAT(0x1C) < 1.0f) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) += 0.1f;
        }
        else {
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            if (FIELD(short, 0x62) < 2) { ResetSecondaryCounters(2); return; }
        }
        if (((OWNER(short, 0x62) > 6 && OWNER(short, 0x60) == 703) || OWNER(short, 0x60) != 703) && FIELD(short, 0x62) == 2) {
            ResetSecondaryCounters(3); return;
        }
        else {
            if (FIELD(short, 0x62) == 2) {
                ++FIELD(short, 0xDA);
                if (FIELD(short, 0xDA) > 80) FIELD(short, 0xDA) = 80;
                OWNER_FLOAT(0x490) = -(FIELD(short, 0xDA) * 0.1f) *
                    (FIELD(signed char, 0x66) * OPPONENT(signed char, 0x66)) *
                    (((OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66) > 0.0f) * 2 - 1);
            }
            if (FIELD(short, 0x62) == 3) {
                if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
                else { ClearField74(); return; }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                ResetSecondaryCounters(2);
                FIELD(int, 0x7C) = 0;
            }
        }
        break;

    case 817:
        if (OWNER(short, 0x60) == 703 && OWNER(short, 0x62) < 7) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 127;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 140.0f;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 0.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 20.0f;
            FLOAT(0x2C) = FIELD(signed char, 0x66) * -50;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
            FIELD(short, 0x80) = 99;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x30) -= 5.0f;
        if (FLOAT(0x1C) < 1.0f) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) += 0.1f;
        }
        else {
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            if (FIELD(short, 0x62) < 2) { ResetSecondaryCounters(2); return; }
        }
        if (((OWNER(short, 0x62) > 6 && OWNER(short, 0x60) == 703) || OWNER(short, 0x60) != 703) && FIELD(short, 0x62) == 2) {
            ResetSecondaryCounters(3); return;
        }
        else {
            if (FIELD(short, 0x62) == 3) {
                if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
                else { ClearField74(); return; }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                ResetSecondaryCounters(2);
                FIELD(int, 0x7C) = 0;
            }
        }
        break;

    case 818:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            SetPolarVelocity(FLOAT(0xC8), 12.0f);
            FIELD(unsigned int, 0x30) = FIELD(unsigned int, 0xC8);
        }
        if (FLOAT(0xC8) == 0.0f) FLOAT(0x48) = 0.0f;
        if (FLOAT(0xC8) == -90.0f) {
            if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
            if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
        }
        if (FLOAT(0xC8) == -180.0f) FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x2E0);
        if (FLOAT(0xC8) == 90.0f) {
            if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
            if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 819:
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
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0xD8) > 5 || (OWNER(short, 0x60) == 702 && OWNER(short, 0x62) == 3)) {
            ClearField74(); return;
        }
        else {
            if (FIELD(short, 0x62) == 1) {
                if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = 0.0f;
                    OWNER_ACTOR->SpawnEffect(818, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = 12.0f;
                FLOAT(0x48) = 0.0f;
                if ((FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(signed char, 0x66) == -1) ||
                    (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(signed char, 0x66) == 1)) {
                    ResetSecondaryCounters(2);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = -90.0f;
                    OWNER_ACTOR->SpawnEffect(818, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 12.0f;
                if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
                if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
                if (FLOAT(0x48) > OWNER_FLOAT(0x2E0)) {
                    ResetSecondaryCounters(3);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            if (FIELD(short, 0x62) == 3) {
                if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = -180.0f;
                    OWNER_ACTOR->SpawnEffect(818, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = -12.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x2E0);
                if ((FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(signed char, 0x66) == 1) ||
                    (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(signed char, 0x66) == -1)) {
                    ResetSecondaryCounters(4);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            if (FIELD(short, 0x62) == 4) {
                if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = 90.0f;
                    OWNER_ACTOR->SpawnEffect(818, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = -12.0f;
                if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
                if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
                if (FLOAT(0x48) < 0.0f) {
                    ResetSecondaryCounters(1);
                    FLOAT(0x50) = 8.0f;
                    FLOAT(0x54) = 0.0f;
                    FLOAT(0x48) = 0.0f;
                    OWNER_FLOAT(0x314) = 0.0f;
                    OWNER_ACTOR->SpawnEffect(818, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ResetSecondaryCounters(4); return; }
            else {
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
                if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
                if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(3);
            }
        }
        break;

    case 820:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            SetPolarVelocity(FLOAT(0xC8), 12.0f);
            FIELD(unsigned int, 0x30) = FIELD(unsigned int, 0xC8);
        }
        if (FLOAT(0xC8) == 0.0f) FLOAT(0x48) = 0.0f;
        if (FLOAT(0xC8) == -90.0f) {
            if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
            if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
        }
        if (FLOAT(0xC8) == -180.0f) FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x2E0);
        if (FLOAT(0xC8) == 90.0f) {
            if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
            if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 821:
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
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0xD8) > 5 || (OWNER(short, 0x60) == 706 && OWNER(short, 0x62) == 3)) {
            ClearField74(); return;
        }
        else {
            if (FIELD(short, 0x62) == 1) {
                if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = 0.0f;
                    OWNER_ACTOR->SpawnEffect(820, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = 12.0f;
                FLOAT(0x48) = 0.0f;
                if ((FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(signed char, 0x66) == -1) ||
                    (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(signed char, 0x66) == 1)) {
                    ResetSecondaryCounters(2);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = -90.0f;
                    OWNER_ACTOR->SpawnEffect(820, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 12.0f;
                if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
                if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
                if (FLOAT(0x48) > OWNER_FLOAT(0x2E0)) {
                    ResetSecondaryCounters(3);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            if (FIELD(short, 0x62) == 3) {
                if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = -180.0f;
                    OWNER_ACTOR->SpawnEffect(820, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = -12.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x2E0);
                if ((FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(signed char, 0x66) == 1) ||
                    (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(signed char, 0x66) == -1)) {
                    ResetSecondaryCounters(4);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            if (FIELD(short, 0x62) == 4) {
                if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = 90.0f;
                    OWNER_ACTOR->SpawnEffect(820, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = -12.0f;
                if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
                if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
                if (FLOAT(0x48) < 0.0f) {
                    ResetSecondaryCounters(1);
                    FLOAT(0x50) = 8.0f;
                    FLOAT(0x54) = 0.0f;
                    FLOAT(0x48) = 0.0f;
                    OWNER_FLOAT(0x314) = 0.0f;
                    OWNER_ACTOR->SpawnEffect(820, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ResetSecondaryCounters(4); return; }
            else {
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
                if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
                if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(3);
            }
        }
        break;

    case 822:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            SetPolarVelocity(FLOAT(0xC8), 16.0f);
            FIELD(unsigned int, 0x30) = FIELD(unsigned int, 0xC8);
        }
        if (FLOAT(0xC8) == 0.0f) FLOAT(0x48) = 0.0f;
        if (FLOAT(0xC8) == -90.0f) {
            if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
            if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
        }
        if (FLOAT(0xC8) == -180.0f) FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x2E0);
        if (FLOAT(0xC8) == 90.0f) {
            if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
            if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 823:
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
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0xD8) > 5 || (OWNER(short, 0x60) == 706 && OWNER(short, 0x62) == 3)) {
            ClearField74(); return;
        }
        else {
            if (FIELD(short, 0x62) == 1) {
                if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = 0.0f;
                    OWNER_ACTOR->SpawnEffect(822, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = 16.0f;
                FLOAT(0x48) = 0.0f;
                if ((FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(signed char, 0x66) == -1) ||
                    (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(signed char, 0x66) == 1)) {
                    ResetSecondaryCounters(2);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = -90.0f;
                    OWNER_ACTOR->SpawnEffect(822, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 16.0f;
                if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
                if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
                if (FLOAT(0x48) > OWNER_FLOAT(0x2E0)) {
                    ResetSecondaryCounters(3);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            if (FIELD(short, 0x62) == 3) {
                if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = -180.0f;
                    OWNER_ACTOR->SpawnEffect(822, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = -16.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x2E0);
                if ((FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(signed char, 0x66) == 1) ||
                    (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(signed char, 0x66) == -1)) {
                    ResetSecondaryCounters(4);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            if (FIELD(short, 0x62) == 4) {
                if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) {
                    OWNER_FLOAT(0x314) = 90.0f;
                    OWNER_ACTOR->SpawnEffect(822, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = -16.0f;
                if (FIELD(signed char, 0x66) == -1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2DC);
                if (FIELD(signed char, 0x66) == 1) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x2D8);
                if (FLOAT(0x48) < 0.0f) {
                    ResetSecondaryCounters(1);
                    FLOAT(0x50) = 8.0f;
                    FLOAT(0x54) = 0.0f;
                    FLOAT(0x48) = 0.0f;
                    OWNER_FLOAT(0x314) = 0.0f;
                    OWNER_ACTOR->SpawnEffect(822, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                    ++FIELD(short, 0xD8);
                    FIELD(int, 0x7C) = 0;
                    FIELD(short, 0x80) = 1;
                }
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ResetSecondaryCounters(4); return; }
            else {
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
                if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
                if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(3);
            }
        }
        break;

    case 824:
        if (OWNER(short, 0x60) == 301 || OWNER(short, 0x60) == 391) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 825:
        if (OWNER(short, 0x60) == 321) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 826:
        if (OWNER(short, 0x60) == 305) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 827:
        if (OWNER(short, 0x60) == 500 || OWNER(short, 0x60) == 501) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + OWNER(signed char, 0x66) * 8;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 135.0f;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        FLOAT(0x30) += 15.0f;
        if (FIELD(short, 0x62) == 0 &&
            ((OWNER(short, 0x60) != 500 && OWNER(short, 0x60) != 501) ||
             (OWNER(short, 0x60) == 500 && OWNER(short, 0x62) > 8) ||
             (OWNER(short, 0x60) == 501 && OWNER(short, 0x62) > 8))) {
            ResetSecondaryCounters(1); return;
        }
        else {
            if (FIELD(short, 0x62) == 1) {
                if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
                else { ClearField74(); return; }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 828:
        if (OWNER(short, 0x62) < 20 &&
            (OWNER(short, 0x60) == 503 || OWNER(short, 0x60) == 504 || OWNER(short, 0x60) == 505)) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 829:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) { ClearField74(); return; }
        else {
            if (OWNER(short, 0x60) > 502 && OWNER(short, 0x60) < 506 && OWNER(short, 0x62) < 7)
                FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 0.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x2C) = 60.0f;
                FIELD(short, 0x80) = 255;
                FIELD(int, 0x7C) = 0;
            }
            if (FIELD(short, 0x62) == 1) {
                FLOAT(0x20) += 0.25;
                if (FLOAT(0x20) > 1.0f) FLOAT(0x20) = 1.0f;
            }
            if (FIELD(short, 0x62) == 2) FLOAT(0x1C) += 0.25f;
            if (FIELD(short, 0x62) == 3) {
                FLOAT(0x1C) -= 0.25f;
                if (FLOAT(0x1C) < 0.0f) FLOAT(0x1C) = 0.0f;
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) FLOAT(0x1C) = 0.05f;
        }
        break;

    case 830:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 0.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 20.0f;
            FLOAT(0x2C) = FIELD(signed char, 0x66) * -50;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
            FIELD(short, 0x80) = 99;
            FIELD(int, 0x7C) = 0;
        }
        FLOAT(0x30) -= 5.0f;
        if (FLOAT(0x1C) < 1.0f) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) += 0.1f;
        }
        else {
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            if (FIELD(short, 0x62) < 2) { ResetSecondaryCounters(2); return; }
        }
        if (FIELD(short, 0x62) == 3) {
            if (FIELD(unsigned char, 0x11) > 30) FIELD(unsigned char, 0x11) -= 30;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 831:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x50) = 30.0f;
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x1C) += 0.2f;
        FLOAT(0x20) *= 0.95f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 832:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x54) = 30.0f;
        }
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x20) += 0.2f;
        FLOAT(0x1C) *= 0.95f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 833:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) FIELD(short, 0xD8) = 0;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x80) = 255;
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0xD8) = OWNER(short, 0xF30) + 3;
            OWNER(short, 0xF30) = 0;
        }
        if (FIELD(short, 0x62) < 6) {
            FLOAT(0x1C) += 0.2f;
            if (FLOAT(0x1C) > 1.5) FLOAT(0x1C) = 1.5f;
        }
        if (FIELD(short, 0xD8) == 0) {
            if (FLOAT(0x1C) > 0.15f) FLOAT(0x1C) -= 0.15f;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(6);
        if (FIELD(short, 0x62) > 6 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) > 0) {
            --FIELD(short, 0xD8);
            OWNER_ACTOR->PlaySoundAt00453D40(3);
            OWNER_FLOAT(0x314) = RecordedRange(0, 359);
            OWNER_FLOAT(0x318) = 10.0f;
            OWNER_FLOAT(0x31C) = RecordedRange(0, 30) - 15;
            OWNER_ACTOR->SpawnEffect(806, FLOAT(0x44), FLOAT(0x48) + 30.0f - RecordedRange(0, 60), FIELD(signed char, 0x66), 1);
            ResetSecondaryCounters(3);
        }
        break;

    case 834:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) FIELD(short, 0xD8) = 0;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = OWNER(short, 0xF30) * 2 + 6;
            OWNER(short, 0xF30) = 0;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 21 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) > 0)
                ResetSecondaryCounters(10);
            if (FIELD(short, 0x62) > 9 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) > 0) {
                --FIELD(short, 0xD8);
                OWNER_ACTOR->PlaySoundAt00453D40(3);
                OWNER_FLOAT(0x318) = 10.0f;
                OWNER_FLOAT(0x314) = -RecordedRange(0, 30) - 75;
                OWNER_ACTOR->SpawnEffect(835, FLOAT(0x44) + 60.0f - RecordedRange(0, 120), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            }
        }
        break;

    case 835:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        else if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex835 = 0; rewardIndex835 < 3; ++rewardIndex835)
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
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
            }
            ++FIELD(short, 0xD8);
            if (FIELD(short, 0x62) < 2) {
                SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.1f + FLOAT(0xCC));
                if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f) {
                    FLOAT(0x50) = 0.0f;
                    FLOAT(0x54) = 0.0f;
                    ResetSecondaryCounters(2);
                    return;
                }
            }
            if ((FIELD(int, 0x7C) == 1 || FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4 || FIELD(int, 0x7C) == 6) && FIELD(short, 0x62) == 1) {
                ResetSecondaryCounters(2);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                return;
            }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        FLOAT(0x30) += 15.0f;
                        FLOAT(0x1C) *= 0.9f;
                        FLOAT(0x20) *= 0.9f;
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

    case 836:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) FIELD(short, 0xD8) = 0;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = OWNER(short, 0xF30) + 3;
            OWNER(short, 0xF30) = 0;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 21 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) > 0)
                ResetSecondaryCounters(10);
            if (FIELD(short, 0x62) > 9 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) > 0) {
                --FIELD(short, 0xD8);
                OWNER_ACTOR->PlaySoundAt00453D40(3);
                OWNER_FLOAT(0x318) = 10.0f;
                OWNER_FLOAT(0x314) = -RecordedRange(0, 30) - 75;
                OWNER_ACTOR->SpawnEffect(837, FLOAT(0x44) + 60.0f - RecordedRange(0, 120), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            }
        }
        break;

    case 837:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex837 = 0; rewardIndex837 < 3; ++rewardIndex837)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
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
                SetPolarVelocity(-90.0f, 10.0f);
            }
            if (FIELD(short, 0x62) == 0) {
                ResetSecondaryCounters(1);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (FIELD(short, 0x62) == 1) {
                SetPolarVelocity(-90.0f, FIELD(short, 0xD8) * 0.1f);
                FIELD(short, 0xD8) += 10;
                OWNER_FLOAT(0x314) = -90.0f;
                OWNER_FLOAT(0x318) = 0.0f;
                OWNER_ACTOR->SpawnEffect(807, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                if (FIELD(int, 0x7C) != 0) {
                    FLOAT(0x50) = 0.0f;
                    FLOAT(0x54) = 0.0f;
                    ResetSecondaryCounters(2);
                    return;
                }
            }
            if (FIELD(short, 0x62) == 2) {
                FIELD(short, 0xD8) -= 20;
                if (FIELD(short, 0xD8) < 0) FIELD(short, 0xD8) = 0;
                OWNER(unsigned int, 0x314) = FIELD(unsigned int, 0xD0);
                OWNER_FLOAT(0x318) = FIELD(short, 0xD8);
                OWNER_ACTOR->SpawnEffect(807, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                FLOAT(0x1C) *= 0.95f;
                FLOAT(0x20) *= 0.95f;
            }
            if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -520.0f || FLOAT(0x48) > 1400.0f || FLOAT(0x48) < -520.0f) {
                ClearField74(); return;
            }
            else if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 838:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 80.0f;
        }
        if (FIELD(short, 0x62) == 1) {
            FLOAT(0x1C) += 0.2f;
            FLOAT(0x20) += 0.2f;
        }
        if (FIELD(short, 0x62) == 2) {
            FLOAT(0x1C) += 0.01f;
            FLOAT(0x20) += 0.01f;
            if (FIELD(unsigned char, 0x11) > 15) FIELD(unsigned char, 0x11) -= 15;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 839:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 80.0f;
        }
        if (FIELD(short, 0x62) == 1) {
            FLOAT(0x1C) += 0.2f;
            FLOAT(0x20) += 0.2f;
        }
        if (FIELD(short, 0x62) == 2) {
            FLOAT(0x1C) += 0.01f;
            FLOAT(0x20) += 0.01f;
            if (FIELD(unsigned char, 0x11) > 15) FIELD(unsigned char, 0x11) -= 15;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 840:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 80.0f;
        }
        if (FIELD(short, 0x62) == 1) {
            FLOAT(0x1C) += 0.2f;
            FLOAT(0x20) += 0.2f;
        }
        if (FIELD(short, 0x62) == 2) {
            FLOAT(0x1C) += 0.01f;
            FLOAT(0x20) += 0.01f;
            if (FIELD(unsigned char, 0x11) > 15) FIELD(unsigned char, 0x11) -= 15;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 841:
        if (OWNER(short, 0x60) == 309)
            FLOAT(0x44) = OWNER_FLOAT(0x44) + OWNER(signed char, 0x66) * 155;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (FIELD(short, 0x62) == 0) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) += 0.1f;
        }
        if (FIELD(short, 0x62) == 1) {
            FLOAT(0x1C) += 0.01f;
            FLOAT(0x20) += 0.01f;
            if (FIELD(unsigned char, 0x11) > 15) FIELD(unsigned char, 0x11) -= 15;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 842:
        if (OWNER(short, 0x60) == 309)
            FLOAT(0x44) = OWNER_FLOAT(0x44) + OWNER(signed char, 0x66) * 155;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 80.0f;
        }
        if (FIELD(short, 0x62) == 1) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) += 0.1f;
        }
        if (FIELD(short, 0x62) == 2) {
            FLOAT(0x1C) += 0.01f;
            FLOAT(0x20) += 0.01f;
            if (FIELD(unsigned char, 0x11) > 15) FIELD(unsigned char, 0x11) -= 15;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 843:
        if (OWNER(short, 0x60) == 309)
            FLOAT(0x44) = OWNER_FLOAT(0x44) + OWNER(signed char, 0x66) * 155;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 80.0f;
        }
        if (FIELD(short, 0x62) == 1) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) += 0.1f;
        }
        if (FIELD(short, 0x62) == 2) {
            FLOAT(0x1C) += 0.01f;
            FLOAT(0x20) += 0.01f;
            if (FIELD(unsigned char, 0x11) > 15) FIELD(unsigned char, 0x11) -= 15;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 844:
        if (OWNER(short, 0x60) == 303) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 900:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 20;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 2.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                FIELD(short, 0xDC) = 0;
            }
            if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                SetPolarVelocity(FIELD(short, 0xDA), 30.0f);
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            if (FIELD(short, 0x62) == 1) {
                if (FLOAT(0x1C) < 1.0f) FLOAT(0x1C) += 0.25f;
                if (FLOAT(0x20) > 1.0f) FLOAT(0x20) -= 0.25f;
            }
            if (FIELD(short, 0x62) == 3) {
                FLOAT(0x30) -= 30.0f;
                SetPolarVelocity(FIELD(short, 0xDA), 30.0f);
            }
            if (FIELD(short, 0x62) == 4) {
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FLOAT(0x30) -= 30.0f;
            }
            if (FIELD(short, 0x62) == 5) {
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FLOAT(0x30) -= 30.0f;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) -= FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ResetSecondaryCounters(3);
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
                return;
            }
            else {
                if (FIELD(short, 0x62) == 5 && FIELD(short, 0x64) == 0) {
                    if (FIELD(short, 0xDC) < 3 - g_F1212_DifficultyAt006714D0) {
                        ResetSecondaryCounters(4);
                        ++FIELD(short, 0xDC);
                        return;
                    }
                    FIELD(short, 0xDC) = 0;
                }
                if (FIELD(short, 0x62) == 5 && FIELD(short, 0x64) == 0) {
                    OWNER_ACTOR->PlaySoundAt00453D40(15);
                    FIELD(short, 0xDA) = static_cast<short>(AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                        (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828 );
                    OWNER_FLOAT(0x314) = FIELD(short, 0xDA);
                    OWNER_ACTOR->SpawnEffect(903, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
            }
        }
        break;

    case 901:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0xD8) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
            }
            SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.1f + FLOAT(0xCC));
            if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) == 1) { ResetSecondaryCounters(2); return; }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        FLOAT(0x50) = 0.0f;
                        FLOAT(0x54) = 0.0f;
                        FLOAT(0x1C) *= 0.85f;
                        FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

    case 902:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0xD8) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.1f + FLOAT(0xCC));
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
            }
            if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) == 1) { ResetSecondaryCounters(2); return; }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
                        else { ClearField74(); return; }
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

    case 903:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 7.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x30) = -FLOAT(0xC8);
            }
            FLOAT(0x20) *= 0.95;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 904:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 20;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 2.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 45;
            }
            if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                SetPolarVelocity(FIELD(short, 0xDA), 30.0f);
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            if (FIELD(short, 0x62) == 1) {
                if (FLOAT(0x1C) < 1.0f) FLOAT(0x1C) += 0.25f;
                if (FLOAT(0x20) > 1.0f) FLOAT(0x20) -= 0.25f;
            }
            if (FIELD(short, 0x62) == 3) {
                FLOAT(0x30) -= 30.0f;
                SetPolarVelocity(FIELD(short, 0xDA), 30.0f);
            }
            if (FIELD(short, 0x62) == 4) {
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FLOAT(0x30) -= 30.0f;
            }
            if (FIELD(short, 0x62) == 5) {
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FLOAT(0x30) -= 30.0f;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) -= FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ResetSecondaryCounters(3);
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
                return;
            }
            else {
                if (FIELD(short, 0x62) == 5 && FIELD(short, 0x64) == 0) {
                    if (FIELD(short, 0xDC) < 3 - g_F1212_DifficultyAt006714D0) {
                        ResetSecondaryCounters(4);
                        ++FIELD(short, 0xDC);
                        return;
                    }
                    FIELD(short, 0xDC) = 0;
                }
                if (FIELD(short, 0x62) == 5 && FIELD(short, 0x64) == 0) {
                    OWNER_ACTOR->PlaySoundAt00453D40(15);
                    FIELD(short, 0xDA) = static_cast<short>(AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                        (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828 + RecordedRange(0, 30) - 15.0f );
                    OWNER_FLOAT(0x314) = FIELD(short, 0xDA);
                    OWNER_ACTOR->SpawnEffect(913, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
            }
        }
        break;

    case 905:
        if (OWNER(short, 0x60) == 741 && OWNER(short, 0x62) < 12) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        }
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 0.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            if (OWNER(short, 0x60) != 741 || (OWNER(short, 0x60) == 741 && OWNER(short, 0x62) > 11)) {
                if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
                else { ClearField74(); return; }
            }
            FLOAT(0x30) += 2.0f;
            if (FLOAT(0x1C) < 1.0f) {
                FLOAT(0x1C) += 0.1f;
                FLOAT(0x20) += 0.1f;
                if (FLOAT(0x1C) > 1.0f) { FLOAT(0x1C) = 1.0f; FLOAT(0x20) = 1.0f; }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ResetSecondaryCounters(1);
                OWNER(unsigned int, 0x314) = FIELD(unsigned int, 0x30);
                OWNER_ACTOR->SpawnEffect(909, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            }
        }
        break;

    case 906:
        if (OWNER(short, 0x60) == 741 && OWNER(short, 0x62) < 12) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        }
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 0.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            if (OWNER(short, 0x60) != 741 || (OWNER(short, 0x60) == 741 && OWNER(short, 0x62) > 11)) {
                if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
                else { ClearField74(); return; }
            }
            FLOAT(0x30) -= 2.0f;
            if (FLOAT(0x1C) < 1.0f) {
                FLOAT(0x1C) += 0.1f;
                FLOAT(0x20) += 0.1f;
                if (FLOAT(0x1C) > 1.0f) { FLOAT(0x1C) = 1.0f; FLOAT(0x20) = 1.0f; }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ResetSecondaryCounters(1);
                OWNER(unsigned int, 0x314) = FIELD(unsigned int, 0x30);
                OWNER_ACTOR->SpawnEffect(909, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            }
        }
        break;

    case 907:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
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
                FIELD(short, 0xD8) = 0;
                SetPolarVelocity(FLOAT(0xC8), 7.0f);
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            if (FIELD(short, 0x62) == 1 && FIELD(int, 0x7C) != 0) { ResetSecondaryCounters(2); return; }
            else {
                if (FIELD(short, 0x62) == 2) { FLOAT(0x1C) *= 0.85f; FLOAT(0x20) *= 0.85f; }
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                    ClearField74(); return;
                }
                else {
                    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
                }
            }
        }
        break;

    case 908:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 0;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0xDA) = RecordedRange(0, 359);
                SetPolarVelocity(FIELD(short, 0xDA), 20.0f);
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDC) = 0;
            }
            if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                if (RecordedRange(0, 100) < 50) SetPolarVelocity(FIELD(short, 0xDA) + 90, 40.0f);
                else SetPolarVelocity(FIELD(short, 0xDA) - 90, 40.0f);
                OWNER_ACTOR->PlaySoundAt00453D40(16);
                OWNER_FLOAT(0x314) = AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                    (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828;
                for (int effectIndex908 = 0; effectIndex908 < g_F1212_DifficultyAt006714D0 * 2 + 3; ++effectIndex908) {
                    if (FIELD(short, 0xDC) == 0) {
                        OWNER_ACTOR->SpawnEffect(907, effectIndex908 * FLOAT(0x50) + FLOAT(0x44),
                            effectIndex908 * FLOAT(0x54) + FLOAT(0x48), FIELD(signed char, 0x66), 1);
                        FIELD(short, 0xDC) = 1;
                    }
                    if (FIELD(short, 0xDC) == 1) {
                        OWNER_ACTOR->SpawnEffect(910, effectIndex908 * FLOAT(0x50) + FLOAT(0x44),
                            effectIndex908 * FLOAT(0x54) + FLOAT(0x48), FIELD(signed char, 0x66), 1);
                        FIELD(short, 0xDC) = 0;
                    }
                }
            }
            if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                ClearField74(); return;
            }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) += FLOAT(0x54);
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
            }
        }
        break;

    case 909:
        if (OWNER(short, 0x60) == 741 && OWNER(short, 0x62) < 12) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        }
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(unsigned int, 0x30) = FIELD(unsigned int, 0xC8);
            }
            if (OWNER(short, 0x60) != 741 || (OWNER(short, 0x60) == 741 && OWNER(short, 0x62) > 11)) {
                if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
                else { ClearField74(); return; }
            }
            FLOAT(0x1C) += 0.05f;
            FLOAT(0x20) += 0.05f;
            if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
            else { ClearField74(); return; }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
        }
        break;

    case 910:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
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
                FIELD(short, 0xD8) = 0;
                SetPolarVelocity(FLOAT(0xC8), 7.0f);
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            if (FIELD(short, 0x62) == 1 && FIELD(int, 0x7C) != 0) { ResetSecondaryCounters(2); return; }
            else {
                if (FIELD(short, 0x62) == 2) { FLOAT(0x1C) *= 0.85f; FLOAT(0x20) *= 0.85f; }
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                    ClearField74(); return;
                }
                else {
                    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
                }
            }
        }
        break;

    case 911:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            FLOAT(0x30) += 15.0f;
            if (FIELD(short, 0x62) == 0) {
                if (OWNER(short, 0x60) == 732 && OWNER(short, 0x62) > 6) {
                    ResetSecondaryCounters(1);
                    FLOAT(0x50) = OWNER(signed char, 0x66) * 8.0f;
                    FLOAT(0x54) = -20.0f;
                    FIELD(short, 0x80) = 15;
                    return;
                }
                if (OWNER(short, 0x60) == 731 || (OWNER(short, 0x60) == 732 && OWNER(short, 0x62) < 7)) {
                    FLOAT(0x44) = OWNER_FLOAT(0x44) + OWNER(signed char, 0x66) * 8;
                    FLOAT(0x48) = OWNER_FLOAT(0x48) + 135.0f;
                }
                if ((OWNER(short, 0x60) != 731 && OWNER(short, 0x60) != 732) ||
                    (OWNER(short, 0x60) == 500 && OWNER(short, 0x62) > 8) ||
                    (OWNER(short, 0x60) == 731 && OWNER(short, 0x62) > 9)) {
                    ResetSecondaryCounters(2); return;
                }
            }
            if (FIELD(short, 0x62) == 1) {
                if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f) { FLOAT(0x48) = 0.0f; FLOAT(0x54) = 0.0f; }
                if (FLOAT(0x44) > 1680.0f || FLOAT(0x44) < -400.0f || FLOAT(0x48) < -500.0f || FLOAT(0x48) > 1280.0f) {
                    ClearField74(); return;
                }
            }
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
                else { ClearField74(); return; }
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                ResetSecondaryCounters(1);
                FIELD(int, 0x7C) = 0;
            }
        }
        break;

    case 912:
        if (OWNER(short, 0x60) == 733) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + OWNER(signed char, 0x66) * 8;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 135.0f;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        FLOAT(0x30) += 15.0f;
        if (FIELD(short, 0x62) == 0 && (OWNER(short, 0x60) != 733 || (OWNER(short, 0x60) == 733 && OWNER(short, 0x62) > 8))) {
            ResetSecondaryCounters(1); return;
        }
        else {
            if (FIELD(short, 0x62) == 1) {
                if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
                else { ClearField74(); return; }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 913:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 7.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x30) = -FLOAT(0xC8);
            }
            FLOAT(0x20) *= 0.95;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 914:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 7.0f;
                FLOAT(0x20) = 2.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            FLOAT(0x1C) += 0.05f;
            FLOAT(0x20) *= 0.95;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ClearField74();
                OWNER_ACTOR->PlaySoundAt00453D40(23);
                if (g_F1212_DifficultyAt006714D0 == 0)
                    OWNER_ACTOR->SpawnEffect(915, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                else OWNER_ACTOR->SpawnEffect(916, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            }
        }
        break;

    case 915:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                OWNER_ACTOR->SetCameraShakeAt00453E60(5.0f);
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 4.0f;
                FLOAT(0x20) = 2.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x1C) += 0.5f;
            FLOAT(0x20) *= 0.95;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 916:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                OWNER_ACTOR->SetCameraShakeAt00453E60(5.0f);
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 4.0f;
                FLOAT(0x20) = 2.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0x1C) += 0.5f;
            FLOAT(0x20) *= 0.95;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 917:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 1;
            FIELD(short, 0xDC) = 0;
            if (OPPONENT_FLOAT(0x48) > 0.0f) ++FIELD(short, 0xDC);
            if (OPPONENT_FLOAT(0x48) > 250.0f) ++FIELD(short, 0xDC);
            if (OPPONENT_FLOAT(0x48) > 400.0f) ++FIELD(short, 0xDC);
            FIELD(short, 0xDE) = RecordedRange(0, 5) - 1;
            if (FIELD(short, 0xDE) == FIELD(short, 0xDC)) {
                --FIELD(short, 0xDE);
                if (FIELD(short, 0xDE) < 0) FIELD(short, 0xDE) = 3;
            }
            FIELD(short, 0xE0) = RecordedRange(0, 5) - 1;
            if (FIELD(short, 0xE0) == FIELD(short, 0xDC)) {
                --FIELD(short, 0xE0);
                if (FIELD(short, 0xE0) < 0) FIELD(short, 0xE0) = 3;
            }
            if (FIELD(short, 0xE0) == FIELD(short, 0xDE)) {
                --FIELD(short, 0xE0);
                if (FIELD(short, 0xE0) < 0) FIELD(short, 0xE0) = 3;
            }
        }
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (OWNER(short, 0x324) < 3500) {
                ++FIELD(short, 0xD8);
                if (g_F1212_DifficultyAt006714D0 <= 1 && FIELD(short, 0xD8) > 140) {
                    OWNER_ACTOR->PlaySoundAt00453D40(15);
                    OWNER_ACTOR->SpawnEffect(914, (FIELD(short, 0xDA) == -1) * 1280,
                        FIELD(short, 0xDC) * 150 + 50, FIELD(short, 0xDA), 1);
                    OWNER_ACTOR->SpawnEffect(914, (FIELD(short, 0xDA) == -1) * 1280,
                        FIELD(short, 0xDE) * 150 + 50, FIELD(short, 0xDA), 1);
                    FIELD(short, 0xD8) = 0;
                    FIELD(short, 0xDA) = -FIELD(short, 0xDA);
                }
                if (g_F1212_DifficultyAt006714D0 == 2 && FIELD(short, 0xD8) > 120) {
                    OWNER_ACTOR->PlaySoundAt00453D40(15);
                    FIELD(short, 0xDA) = -FIELD(short, 0xDA);
                    OWNER_ACTOR->SpawnEffect(914, (FIELD(short, 0xDA) == -1) * 1280,
                        FIELD(short, 0xDC) * 150 + 50, FIELD(short, 0xDA), 1);
                    OWNER_ACTOR->SpawnEffect(914, (FIELD(short, 0xDA) == -1) * 1280,
                        FIELD(short, 0xDE) * 150 + 50, FIELD(short, 0xDA), 1);
                    OWNER_ACTOR->SpawnEffect(914, (FIELD(short, 0xDA) == -1) * 1280,
                        FIELD(short, 0xE0) * 150 + 50, FIELD(short, 0xDA), 1);
                    FIELD(short, 0xD8) = 0;
                }
                if (g_F1212_DifficultyAt006714D0 == 3 && FIELD(short, 0xD8) > 90) {
                    OWNER_ACTOR->PlaySoundAt00453D40(15);
                    FIELD(short, 0xDA) = -FIELD(short, 0xDA);
                    OWNER_ACTOR->SpawnEffect(914, (FIELD(short, 0xDA) == -1) * 1280,
                        FIELD(short, 0xDC) * 150 + 50, FIELD(short, 0xDA), 1);
                    OWNER_ACTOR->SpawnEffect(914, (FIELD(short, 0xDA) == -1) * 1280,
                        FIELD(short, 0xDE) * 150 + 50, FIELD(short, 0xDA), 1);
                    OWNER_ACTOR->SpawnEffect(914, (FIELD(short, 0xDA) == -1) * 1280,
                        FIELD(short, 0xE0) * 150 + 50, FIELD(short, 0xDA), 1);
                    FIELD(short, 0xD8) = 0;
                }
                FIELD(short, 0xDC) = 0;
                if (OPPONENT_FLOAT(0x48) > 0.0f) ++FIELD(short, 0xDC);
                if (OPPONENT_FLOAT(0x48) > 250.0f) ++FIELD(short, 0xDC);
                if (OPPONENT_FLOAT(0x48) > 400.0f) ++FIELD(short, 0xDC);
                FIELD(short, 0xDE) = RecordedRange(0, 5) - 1;
                if (FIELD(short, 0xDE) == FIELD(short, 0xDC)) {
                    --FIELD(short, 0xDE);
                    if (FIELD(short, 0xDE) < 0) FIELD(short, 0xDE) = 3;
                }
                FIELD(short, 0xE0) = RecordedRange(0, 5) - 1;
                if (FIELD(short, 0xE0) == FIELD(short, 0xDC)) {
                    --FIELD(short, 0xE0);
                    if (FIELD(short, 0xE0) < 0) FIELD(short, 0xE0) = 3;
                }
                if (FIELD(short, 0xE0) == FIELD(short, 0xDE)) {
                    --FIELD(short, 0xE0);
                    if (FIELD(short, 0xE0) < 0) FIELD(short, 0xE0) = 3;
                }
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
        }
        break;

    case 918:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            FIELD(signed char, 0x66) = 1;
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                FIELD(short, 0xDC) = 0;
                FIELD(short, 0xDE) = 0;
                FIELD(short, 0xE0) = 0;
            }
            --FIELD(short, 0xE0);
            SetPolarVelocity(OWNER(short, 0xF12) + FLOAT(0xC8), OWNER(short, 0xF14));
            FLOAT(0x44) = OWNER(short, 0xF18) + FIELD(signed char, 0x66) * FLOAT(0x50);
            FLOAT(0x48) = OWNER(short, 0xF1A) + FLOAT(0x54);
            OWNER_ACTOR->SpawnEffect(919, FLOAT(0x44), FLOAT(0x48), 1, 1);
            if (FIELD(short, 0xE0) <= 0) {
                OWNER_ACTOR->PlaySoundAt00453D40(18);
                OWNER_FLOAT(0x314) = -(OWNER(short, 0xF12) + FLOAT(0xC8)) * FIELD(signed char, 0x66);
                OWNER_FLOAT(0x318) = 5.0f;
                OWNER_ACTOR->SpawnEffect(921, FLOAT(0x44), FLOAT(0x48), 1, 1);
                FIELD(short, 0xE0) = 4;
            }
            if (OWNER(short, 0xF16) == 2) {
                OWNER_ACTOR->PlaySoundAt00453D40(16);
                for (int effectIndex918 = 0; effectIndex918 < g_F1212_DifficultyAt006714D0 * 2 + 4; ++effectIndex918) {
                    OWNER_FLOAT(0x314) = -(OWNER(short, 0xF12) + FLOAT(0xC8)) * FIELD(signed char, 0x66);
                    OWNER_FLOAT(0x318) = 4.0f;
                    OWNER_ACTOR->SpawnEffect(922, FLOAT(0x44), FLOAT(0x48), 1, 1);
                }
            }
            if (OWNER(short, 0xF16) == 3) {
                OWNER_ACTOR->PlaySoundAt00453D40(18);
                OWNER_FLOAT(0x314) = -(OWNER(short, 0xF12) + FLOAT(0xC8)) + 180.0f;
                OWNER_FLOAT(0x318) = 5.0f;
                OWNER_ACTOR->SpawnEffect(923, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
        }
        break;

    case 919:
        FIELD(signed char, 0x66) = 1;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (FIELD(unsigned char, 0x11) > 13) FIELD(unsigned char, 0x11) -= 13;
        else FIELD(unsigned char, 0x11) = 0;
        FLOAT(0x1C) *= 0.85f;
        FLOAT(0x20) *= 0.85f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 920:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            FIELD(signed char, 0x66) = 1;
            if (OWNER(short, 0x3B8) == 0) {
                OWNER(short, 0xF18) = static_cast<short>(FLOAT(0x44));
                OWNER(short, 0xF1A) = static_cast<short>(FLOAT(0x48));
            }
            if (OWNER(short, 0xF14) > 340) --OWNER(short, 0xF14);
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                FIELD(short, 0xDC) = 60;
                FIELD(short, 0xDE) = 0;
                FIELD(short, 0xE0) = 180;
            }
            --FIELD(short, 0xE0);
            --FIELD(short, 0xDC);
            ++FIELD(short, 0xDA);
            if (FIELD(short, 0xDC) == 1) OWNER(short, 0xF16) = 2;
            if (FIELD(short, 0xDC) == 0) {
                --FIELD(short, 0xDC);
                FIELD(short, 0xDC) = 260;
                OWNER(short, 0xF16) = 0;
            }
            if (FIELD(short, 0xDA) == 300) OWNER(short, 0xF16) = 3;
            if (FIELD(short, 0xDA) == 301) {
                FIELD(short, 0xDA) = g_F1212_DifficultyAt006714D0 * 20 - 60;
                OWNER(short, 0xF16) = 0;
            }
            if (FIELD(short, 0xDE) > 0) {
                --FIELD(short, 0xDE);
                OWNER(short, 0xF16) = 1;
                if (FIELD(short, 0xDE) == 0) OWNER(short, 0xF16) = 0;
            }
            FLOAT(0x50) = (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * 0.02f;
            if (FLOAT(0x50) < 0.25f && FLOAT(0x50) > -0.25f) FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = (OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48)) * 0.02f;
            if (FLOAT(0x54) < 0.25f && FLOAT(0x54) > -0.25f) FLOAT(0x54) = 0.0f;
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
        }
        break;

    case 921:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
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
                FIELD(short, 0xD8) = 0;
                SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            if (FIELD(short, 0x62) == 1 && FIELD(int, 0x7C) != 0) { ResetSecondaryCounters(2); return; }
            else {
                if (FIELD(short, 0x62) == 2) { FLOAT(0x1C) *= 0.8f; FLOAT(0x20) *= 0.8f; }
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                    ClearField74(); return;
                }
                else {
                    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
                }
            }
        }
        break;

    case 922:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 3.0f;
                FLOAT(0x20) = 3.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = RecordedRange(0, 359);
                SetPolarVelocity(FIELD(short, 0xDA), FIELD(short, 0xD8) * 0.05f);
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            if (FIELD(short, 0x62) == 1) {
                FLOAT(0x1C) -= 0.1f;
                FLOAT(0x20) -= 0.1f;
                if (FLOAT(0x1C) < 1.0f) { FLOAT(0x1C) = 1.0f; FLOAT(0x20) = 1.0f; }
            }
            if (FIELD(short, 0x62) == 2 && FIELD(int, 0x7C) != 0) {
                ResetSecondaryCounters(3);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                return;
            }
            else {
                if (FIELD(short, 0x62) == 3) { FLOAT(0x1C) *= 0.8f; FLOAT(0x20) *= 0.8f; }
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) == 2) {
                        ++FIELD(short, 0xD8);
                        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                        FLOAT(0x48) -= FLOAT(0x54);
                        SetPolarVelocity(FIELD(short, 0xDA), FIELD(short, 0xD8) * 0.05f);
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
                }
            }
        }
        break;

    case 923:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 3.0f;
                FLOAT(0x20) = 3.0f;
                FIELD(unsigned char, 0x11) = 0;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0xD8) = 0;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            if (FIELD(short, 0x62) == 1) {
                FLOAT(0x1C) -= 0.1f;
                FLOAT(0x20) -= 0.1f;
                if (FLOAT(0x1C) < 1.0f) { FLOAT(0x1C) = 1.0f; FLOAT(0x20) = 1.0f; }
                if (FIELD(unsigned char, 0x11) < 245) FIELD(unsigned char, 0x11) += 10;
                else FIELD(unsigned char, 0x11) = 255;
            }
            if (FIELD(short, 0x62) == 2 && FIELD(int, 0x7C) != 0) {
                ResetSecondaryCounters(3);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                return;
            }
            else {
                if (FIELD(short, 0x62) == 3) { FLOAT(0x1C) *= 0.8f; FLOAT(0x20) *= 0.8f; }
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) == 2) {
                        ++FIELD(short, 0xD8);
                        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
                        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                        FLOAT(0x48) -= FLOAT(0x54);
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
                }
            }
        }
        break;

    case 924:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            FLOAT(0x30) += 15.0f;
            if (FIELD(short, 0x62) == 0) {
                if (OWNER(short, 0x60) == 732 && OWNER(short, 0x62) > 6) {
                    ResetSecondaryCounters(1);
                    FLOAT(0x50) = OWNER(signed char, 0x66) * 8.0f;
                    FLOAT(0x54) = -20.0f;
                    FIELD(short, 0x80) = 15;
                    return;
                }
                if (OWNER(short, 0x60) == 731 || (OWNER(short, 0x60) == 732 && OWNER(short, 0x62) < 7)) {
                    FLOAT(0x44) = OWNER_FLOAT(0x44) + OWNER(signed char, 0x66) * 8;
                    FLOAT(0x48) = OWNER_FLOAT(0x48) + 135.0f;
                }
                if ((OWNER(short, 0x60) != 731 && OWNER(short, 0x60) != 732) ||
                    (OWNER(short, 0x60) == 500 && OWNER(short, 0x62) > 8)) {
                    ResetSecondaryCounters(2); return;
                }
            }
            if (FIELD(short, 0x62) == 1) {
                if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f) { FLOAT(0x48) = 0.0f; FLOAT(0x54) = 0.0f; }
                if (FLOAT(0x44) > 1680.0f || FLOAT(0x44) < -400.0f || FLOAT(0x48) < -500.0f || FLOAT(0x48) > 1280.0f) {
                    ClearField74(); return;
                }
            }
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
                else { ClearField74(); return; }
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                ResetSecondaryCounters(1);
                FIELD(int, 0x7C) = 0;
            }
        }
        break;

    case 925:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            FLOAT(0x30) += 15.0f;
            if (FIELD(short, 0x62) == 0) {
                if (OWNER(short, 0x60) == 732 && OWNER(short, 0x62) > 6) {
                    ResetSecondaryCounters(1);
                    FLOAT(0x50) = OWNER(signed char, 0x66) * 10.0f;
                    FLOAT(0x54) = -20.0f;
                    FIELD(short, 0x80) = 15;
                    return;
                }
                if (OWNER(short, 0x60) == 731 || (OWNER(short, 0x60) == 732 && OWNER(short, 0x62) < 7)) {
                    FLOAT(0x44) = OWNER_FLOAT(0x44) + OWNER(signed char, 0x66) * 8;
                    FLOAT(0x48) = OWNER_FLOAT(0x48) + 135.0f;
                }
                if ((OWNER(short, 0x60) != 731 && OWNER(short, 0x60) != 732) ||
                    (OWNER(short, 0x60) == 500 && OWNER(short, 0x62) > 8)) {
                    ResetSecondaryCounters(2); return;
                }
            }
            if (FIELD(short, 0x62) == 1) {
                if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f) { FLOAT(0x48) = 0.0f; FLOAT(0x54) = 0.0f; }
                if (FLOAT(0x44) > 1680.0f || FLOAT(0x44) < -400.0f || FLOAT(0x48) < -500.0f || FLOAT(0x48) > 1280.0f) {
                    ClearField74(); return;
                }
            }
            if (FIELD(short, 0x62) == 2) {
                if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
                else { ClearField74(); return; }
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                ResetSecondaryCounters(1);
                FIELD(int, 0x7C) = 0;
            }
        }
        break;

    case 988:
        if (OWNER(short, 0x62) > 10) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 989:
        if (OWNER(short, 0x62) < 9) FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
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
        FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
        FLOAT(0x48) = 2.0f;
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
            FIELD(short, 0xDA) = 0;
        }
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            FLOAT(0x1C) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2;
            FLOAT(0x20) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2;
            FLOAT(0x30) += 1.0f;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(9);
        }
        break;

    case 999:
        if (FIELD(short, 0x62) < 1) FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
        OWNER(short, 0xF0C) = 1;
        if (OWNER(short, 0x62) == 0 &&
            (((OWNER(short, 0x60) >= 70 && OWNER(short, 0x60) <= 88 && OWNER(short, 0x60) != 76)) ||
             OWNER(short, 0x60) == 181 || OWNER(short, 0x60) == 180 || OWNER(short, 0x60) == 145)) {
            ClearField74();
            OWNER(short, 0xF0C) = 0;
            return;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(60.0f, 130.0f, 0.0f);
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
        if (FIELD(short, 0x62) == 1 && (OWNER(short, 0x60) == 95 || OWNER(short, 0x60) == 94 || OWNER(short, 0x60) == 93 || OWNER(short, 0x60) == 796) && OWNER(short, 0x62) == 3) {
            ResetSecondaryCounters(2);
            return;
        }
        if (FIELD(short, 0x62) == 0) FLOAT(0x30) -= 35.0f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ClearField74();
            OWNER(short, 0xF0C) = 0;
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
