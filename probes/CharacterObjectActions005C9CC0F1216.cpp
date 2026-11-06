// Work in progress toward complete original 005C9CC0 (43,501 CODE B).
// All native states are written. This complete research parent remains
// NONEXACT and is not an accepted executable replacement.
#include "ObjectAdvance5C9CC0F1216.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OWNER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset)))
#define OPPONENT(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset))
#define OWNER_ACTOR reinterpret_cast<OwnerActor5C9CC0F1216*>(FIELD(void*, 0xE4))

extern float g_F1057_NudgeAt00657480;
extern float g_F1211_AngleDivAt00657828;
extern signed char g_F1212_DifficultyAt006714D0;

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

    case 807:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex807 = 0; cancelIndex807 < 15; cancelIndex807++)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            if (FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(short, 0xD8) == 0 &&
                ((FIELD(signed char, 0x66) == -1 && FLOAT(0x50) > 0.0f) ||
                 (FIELD(signed char, 0x66) == 1 && FLOAT(0x50) < 0.0f))) {
                FIELD(signed char, 0x66) = -FIELD(signed char, 0x66);
                ++FIELD(short, 0xD8);
            }
            if (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(short, 0xD8) == 0 &&
                ((FIELD(signed char, 0x66) == -1 && FLOAT(0x50) < 0.0f) ||
                 (FIELD(signed char, 0x66) == 1 && FLOAT(0x50) > 0.0f))) {
                FIELD(signed char, 0x66) = -FIELD(signed char, 0x66);
                ++FIELD(short, 0xD8);
            }
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
                FLOAT(0x50) = 20.0f;
                FLOAT(0x54) = 10.0f;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (FLOAT(0x50) > 10.0f) FLOAT(0x50) -= 1.0f;
            else FLOAT(0x50) = 10.0f;
            FLOAT(0x54) -= 0.6f;
            OWNER_ACTOR->SpawnEffect(804, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ClearField74();
                OWNER_ACTOR->PlaySoundAt00453D40(18);
                OWNER_ACTOR->SetCameraShakeAt00453E60(5.0f);
                for (int burstIndex807 = 0; burstIndex807 < 18; burstIndex807++) {
                    OWNER_FLOAT(0x314) = burstIndex807 * 20;
                    OWNER_FLOAT(0x318) = 17.0f;
                    OWNER_ACTOR->SpawnEffect(805, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
            }
        }
        break;

    case 808:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex808 = 0; cancelIndex808 < 15; cancelIndex808++)
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
                FLOAT(0x50) = 2.5f;
                FLOAT(0x54) = 15.0f;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            FLOAT(0x54) -= 0.45f;
            OWNER_ACTOR->SpawnEffect(804, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ClearField74();
                OWNER_ACTOR->PlaySoundAt00453D40(18);
                OWNER_ACTOR->SetCameraShakeAt00453E60(5.0f);
                for (int burstIndex808 = 0; burstIndex808 < 18; burstIndex808++) {
                    OWNER_FLOAT(0x314) = burstIndex808 * 20;
                    OWNER_FLOAT(0x318) = 17.0f;
                    OWNER_ACTOR->SpawnEffect(805, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
            }
        }
        break;

    case 809:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex809 = 0; cancelIndex809 < 10; cancelIndex809++)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 2.0f;
                FLOAT(0x20) = 2.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 810:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = RecordedRange(0, 120) - 60;
            FLOAT(0x2C) = RecordedRange(0, 120) - 60;
            FLOAT(0x30) = RecordedRange(0, 120) - 60;
            FIELD(short, 0xD8) = 0;
        }
        FLOAT(0x1C) = (0.2f - FIELD(short, 0xD8) * 0.05f * (FIELD(short, 0xD8) < 5)) + 0.005f + FLOAT(0x1C);
        FLOAT(0x20) = (0.2f - FIELD(short, 0xD8) * 0.05f * (FIELD(short, 0xD8) < 5)) + 0.005f + FLOAT(0x20);
        ++FIELD(short, 0xD8);
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 20) {
                FIELD(unsigned char, 0x11) -= 20;
                FIELD(unsigned char, 0x13) -= 20;
                FIELD(unsigned char, 0x14) -= 20;
            }
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 811:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0xD8) = 0;
            FLOAT(0x1C) = 2.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            SetPolarVelocity(FLOAT(0xC8), 10.0f);
        }
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 60) - 30;
            FIELD(short, 0xDC) = RecordedRange(0, 60) - 30;
            OWNER_ACTOR->SpawnEffect(809, FIELD(short, 0xDA) + FLOAT(0x44), FIELD(short, 0xDC) + FLOAT(0x48), FIELD(signed char, 0x66), 1);
            OWNER(unsigned int, 0x314) = FIELD(unsigned int, 0xC8);
            OWNER_ACTOR->SpawnEffect(810, FIELD(short, 0xDA) + FLOAT(0x44), FIELD(short, 0xDC) + FLOAT(0x48), FIELD(signed char, 0x66), 1);
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FLOAT(0x44) > 1480.0f || FLOAT(0x44) < -200.0f) {
            ClearField74();
            return;
        }
        else {
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                if (FIELD(short, 0xD8) < 6) {
                    ResetSecondaryCounters(1);
                    ++FIELD(short, 0xD8);
                }
                else ClearField74();
            }
        }
        break;

    case 812:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex812 = 0; cancelIndex812 < 4; cancelIndex812++)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 0.5f;
                FLOAT(0x20) = 0.5f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                FIELD(short, 0xDC) = 0;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
            }
            SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
            if (FLOAT(0xCC) > 2.0f) FLOAT(0xCC) -= 1.0f;
            if (FIELD(short, 0x62) < 2 && FLOAT(0xCC) == g_F1057_NudgeAt00657480)
                ResetSecondaryCounters(2);
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            --FIELD(short, 0xDC);
            if (FIELD(short, 0xDC) <= 0) {
                OWNER_ACTOR->SpawnEffect(813, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
                    FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
                FIELD(short, 0xDC) = 4;
            }
            if (FIELD(short, 0x64) == 0) {
                FIELD(short, 0xDA) = RecordedRange(0, 20);
                FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.5f;
                FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.5f;
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 25) {
                ResetSecondaryCounters(2);
                ++FIELD(short, 0xD8);
            }
        }
        break;

    case 813:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.8f;
            FLOAT(0x20) = 0.8f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 1;
            FLOAT(0x54) = 4.0f;
            FLOAT(0x50) = 0.0f;
        }
        FLOAT(0x54) -= 0.15f;
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        if (FIELD(unsigned char, 0x11) > 13) FIELD(unsigned char, 0x11) -= 13;
        else FIELD(unsigned char, 0x11) = 0;
        FLOAT(0x1C) *= 0.94f;
        FLOAT(0x20) *= 0.94f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 814:
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
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 815:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) != 1) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 0.0f;
            FLOAT(0x2C) = 0.0f;
            FLOAT(0x30) = 0.0f;
        }
        FLOAT(0x1C) += 0.08f;
        FLOAT(0x20) += 0.08f;
        FIELD(unsigned char, 0x11) -= 7;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 816:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) != 1) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = RecordedRange(25, 75) * 0.01f;
            FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = RecordedRange(0, 255);
            FIELD(unsigned char, 0x13) = RecordedRange(0, 255);
            FIELD(unsigned char, 0x14) = RecordedRange(0, 255);
        }
        FLOAT(0x44) -= 0.1f;
        FLOAT(0x30) += 5.0f;
        FIELD(unsigned char, 0x11) -= 7;
        FLOAT(0x1C) -= 0.01f;
        FLOAT(0x20) -= 0.01f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 817:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = RecordedRange(75, 150) * 0.01f;
            FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
            FLOAT(0x30) = RecordedRange(0, 359);
            FIELD(short, 0xDC) = static_cast<short>(AngleAt00483300(
                OPPONENT_FLOAT(0x48) + 20.0f - FLOAT(0x48),
                (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828);
            SetPolarVelocity(FIELD(short, 0xDC), 36.0f);
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FIELD(short, 0x62) < 2) {
            FLOAT(0x30) += 5.0f;
            if (AbsFloatAt00412D90(FLOAT(0x44) - OPPONENT_FLOAT(0x44)) < 60.0f &&
                AbsFloatAt00412D90(FLOAT(0x48) - OPPONENT_FLOAT(0x48) + 20.0f) < 60.0f) {
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                OWNER_ACTOR->PlaySharedSoundAt00453D60(4);
                FIELD(short, 0xD8) = static_cast<short>(FLOAT(0x44) - OPPONENT_FLOAT(0x44));
                FIELD(short, 0xDA) = static_cast<short>(FLOAT(0x48) - OPPONENT_FLOAT(0x48) + 20.0f);
                ResetSecondaryCounters(2);
            }
        }
        if (FIELD(short, 0x62) == 2 && (OWNER(short, 0x60) == 700 || OWNER(short, 0x60) == 771)) {
            if (OWNER(short, 0x62) == 23) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 60) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 140);
            }
            if (OWNER(short, 0x62) == 24) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 94) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 178);
            }
            if (OWNER(short, 0x62) == 25) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 150) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 82);
            }
            if (OWNER(short, 0x62) == 26) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 75) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 17);
            }
            if (OWNER(short, 0x62) == 27) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 30) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 10);
            }
            if (OWNER(short, 0x62) == 28) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 110) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 85);
            }
            if (OWNER(short, 0x62) == 29) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 95) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 185);
            }
            if (OWNER(short, 0x62) == 30) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 10) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 230);
            }
            if (OWNER(short, 0x62) == 31) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 54) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 160);
            }
            if (OWNER(short, 0x62) == 32) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 80) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 135);
            }
            if (OWNER(short, 0x62) > 32) {
                FLOAT(0x44) = OPPONENT_FLOAT(0x44) + FIELD(short, 0xD8) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OPPONENT_FLOAT(0x48) + (FIELD(short, 0xDA) + 70);
                if (OPPONENT(short, 0x60) == 97) {
                    ResetSecondaryCounters(3);
                    FLOAT(0x50) = RecordedRange(0, 20) - 10;
                    FLOAT(0x54) = -RecordedRange(5, 20);
                    return;
                }
            }
        }
        if (FIELD(short, 0x62) == 3) {
            FLOAT(0x54) += 0.5f;
            if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f && FLOAT(0x54) > 0.0f)
                FLOAT(0x54) = -FLOAT(0x54);
            if (FIELD(unsigned char, 0x11) > 5) FIELD(unsigned char, 0x11) -= 5;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 818:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) != 1) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 0.0f;
            FLOAT(0x2C) = 0.0f;
            FLOAT(0x30) = 0.0f;
        }
        FLOAT(0x1C) += 0.08f;
        FLOAT(0x20) += 0.08f;
        if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
        else { ClearField74(); return; }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
        break;

    case 819:
        if (OWNER(short, 0x60) != 703) ClearField74();
        if (OWNER(short, 0x60) == 703) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        ++FIELD(short, 0xDA);
        if (FIELD(short, 0xD8) == 0) {
            if (FIELD(unsigned char, 0x11) < 235) FIELD(unsigned char, 0x11) += 20;
            else {
                FIELD(unsigned char, 0x11) = 255;
                FIELD(short, 0xD8) = 1;
            }
        }
        if (FIELD(short, 0xD8) == 1 && FIELD(short, 0xDA) > 90) {
            if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
        break;

    case 820:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = RecordedRange(100, 300) * 0.01f;
            FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
            FLOAT(0x30) = RecordedRange(0, 359);
            FIELD(short, 0xDC) = static_cast<short>(AngleAt00483300(
                OPPONENT_FLOAT(0x48) + 20.0f - FLOAT(0x48),
                (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828);
            SetPolarVelocity(FIELD(short, 0xDC), 36.0f);
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FIELD(short, 0x62) < 2) {
            FLOAT(0x30) += 5.0f;
            if (AbsFloatAt00412D90(FLOAT(0x44) - OPPONENT_FLOAT(0x44)) < 80.0f &&
                AbsFloatAt00412D90(FLOAT(0x48) - OPPONENT_FLOAT(0x48) + 20.0f) < 80.0f) {
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                OWNER_ACTOR->PlaySharedSoundAt00453D60(4);
                FIELD(short, 0xD8) = static_cast<short>(FLOAT(0x44) - OPPONENT_FLOAT(0x44));
                FIELD(short, 0xDA) = static_cast<short>(FLOAT(0x48) - OPPONENT_FLOAT(0x48) + 20.0f);
                ResetSecondaryCounters(2);
            }
        }
        if (FIELD(short, 0x62) == 2 && (OWNER(short, 0x60) == 720 || OWNER(short, 0x60) == 773)) {
            if (OWNER(short, 0x62) == 23) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 60) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 140);
            }
            if (OWNER(short, 0x62) == 24) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 94) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 178);
            }
            if (OWNER(short, 0x62) == 25) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 150) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 82);
            }
            if (OWNER(short, 0x62) == 26) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 75) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 17);
            }
            if (OWNER(short, 0x62) == 27) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 30) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 10);
            }
            if (OWNER(short, 0x62) == 28) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 110) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 85);
            }
            if (OWNER(short, 0x62) == 29) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 95) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 185);
            }
            if (OWNER(short, 0x62) == 30) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 10) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 230);
            }
            if (OWNER(short, 0x62) == 31) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 54) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 160);
            }
            if (OWNER(short, 0x62) == 32) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 80) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 135);
            }
            if (OWNER(short, 0x62) > 32) {
                FLOAT(0x44) = OPPONENT_FLOAT(0x44) + FIELD(short, 0xD8) * FIELD(signed char, 0x66);
                FLOAT(0x48) = OPPONENT_FLOAT(0x48) + (FIELD(short, 0xDA) + 70);
                if (OPPONENT(short, 0x60) == 89) {
                    ResetSecondaryCounters(3);
                    FLOAT(0x50) = RecordedRange(0, 20) - 10;
                    FLOAT(0x54) = -RecordedRange(5, 20);
                    return;
                }
            }
        }
        if (FIELD(short, 0x62) == 3) {
            FLOAT(0x54) += 0.5f;
            if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f && FLOAT(0x54) > 0.0f)
                FLOAT(0x54) = -FLOAT(0x54);
            if (FIELD(unsigned char, 0x11) > 5) FIELD(unsigned char, 0x11) -= 5;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 821:
        if (OWNER(short, 0x60) != 723) ClearField74();
        if (OWNER(short, 0x60) == 723) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        ++FIELD(short, 0xDA);
        if (FIELD(short, 0xD8) == 0) {
            if (FIELD(unsigned char, 0x11) < 235) FIELD(unsigned char, 0x11) += 20;
            else {
                FIELD(unsigned char, 0x11) = 255;
                FIELD(short, 0xD8) = 1;
            }
        }
        if (FIELD(short, 0xD8) == 1 && FIELD(short, 0xDA) > 90) {
            if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
        break;

    case 822:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.0f - RecordedRange(0, 5) * 0.1f;
            FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x54) = 0.0f;
            FLOAT(0x50) = RecordedRange(0, 10) - 5;
        }
        if (FIELD(short, 0x62) == 1) {
            if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
            else {
                FIELD(unsigned char, 0x11) = 0;
                ClearField74();
            }
        }
        FLOAT(0x54) -= 0.3f;
        FLOAT(0x48) -= FLOAT(0x54);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 823:
        FIELD(signed char, 0x66) = 1;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f - RecordedRange(0, 5) * 0.1f;
            FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
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
            FIELD(short, 0xD8) = static_cast<short>(AngleAt00483300(
                OWNER_FLOAT(0x48) + 100.0f - FLOAT(0x48), OWNER_FLOAT(0x44) - FLOAT(0x44)) / g_F1211_AngleDivAt00657828);
            SetPolarVelocity(FIELD(short, 0xD8), 20.0f);
            if (FLOAT(0x44) - OWNER_FLOAT(0x44) < 20.0f && FLOAT(0x44) - OWNER_FLOAT(0x44) > -20.0f &&
                FLOAT(0x48) - OWNER_FLOAT(0x48) < 120.0f && FLOAT(0x48) - OWNER_FLOAT(0x48) > 80.0f) {
                ClearField74();
                return;
            }
        }
        FLOAT(0x44) += FLOAT(0x50);
        FLOAT(0x48) -= FLOAT(0x54);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
        break;

    case 824:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex824 = 0; cancelIndex824 < 7; cancelIndex824++)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            OWNER_ACTOR->SpawnEffect(806, FLOAT(0x44) + 10.0f - RecordedRange(0, 20),
                FLOAT(0x48) + 10.0f - RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
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
                SetPolarVelocity(FLOAT(0xC8), 30.0f);
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            if (FIELD(short, 0x62) == 1 &&
                ((FIELD(int, 0x7C) != 0 && FIELD(int, 0x7C) != 6) || FLOAT(0x48) + FLOAT(0x54) <= 0.0f)) {
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                UnknownAt0045B850(1);
                ResetSecondaryCounters(2);
                OWNER_ACTOR->SpawnEffect(827, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FLOAT(0x30) = 0.0f;
                return;
            }
            else {
                if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0)
                    OWNER_ACTOR->SpawnEffect(827, FLOAT(0x44) + 50.0f - RecordedRange(0, 100),
                        FLOAT(0x48) + 50.0f - RecordedRange(0, 100), FIELD(signed char, 0x66), 1);
                if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0)
                    OWNER_ACTOR->SpawnEffect(827, FLOAT(0x44) + 50.0f - RecordedRange(0, 100),
                        FLOAT(0x48) + 50.0f - RecordedRange(0, 100), FIELD(signed char, 0x66), 1);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                                ClearField74();
                                return;
                            }
                            else {
                    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
                }
            }
        }
        break;

    case 825:
        if (OWNER(short, 0x60) > 69 && OWNER(short, 0x60) < 150) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex825 = 0; cancelIndex825 < 15; cancelIndex825++)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(unsigned int, 0x50) = FIELD(unsigned int, 0xC8);
                FLOAT(0x54) = 10.0f;
                FIELD(short, 0xDE) = 0;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            FLOAT(0x30) += 5.0f;
            if (FIELD(short, 0x62) < 2 && OWNER(short, 0x62) == 0 &&
                (OWNER(short, 0x60) == 408 || OWNER(short, 0x60) == 414)) {
                ResetSecondaryCounters(2);
                FLOAT(0x54) = 0.0f;
                FLOAT(0x50) = 0.0f;
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0) {
                    if (FLOAT(0x50) > 2.5f) FLOAT(0x50) -= 1.0f;
                    else FLOAT(0x50) = 2.5f;
                    FLOAT(0x54) -= 0.6f;
                }
                if (FIELD(short, 0x62) == 1) {
                    --FIELD(short, 0xDE);
                    OWNER_FLOAT(0x490) = (FIELD(signed char, 0x66) * OPPONENT(signed char, 0x66)) * -6.0f *
                        (((OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66) > 0.0f) * 2 - 1);
                    if (FIELD(short, 0xDE) <= 0) {
                        OWNER_ACTOR->SpawnEffect(826, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 0);
                        FIELD(short, 0xDE) = 15;
                    }
                }
                if (FIELD(short, 0x62) == 2) {
                    FLOAT(0x1C) *= 0.85f;
                    FLOAT(0x20) *= 0.85f;
                }
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                    OWNER_ACTOR->PlaySoundAt00453D40(31);
                    FLOAT(0x50) = 0.0f;
                    FLOAT(0x54) = 0.0f;
                }
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0 && FIELD(short, 0xDA) < 45) {
                    ++FIELD(short, 0xDA);
                    ResetSecondaryCounters(1);
                }
            }
        }
        break;

    case 826:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        FLOAT(0x1C) -= 0.05f;
        FLOAT(0x20) -= 0.05f;
        if (FIELD(short, 0x64) > 5) FIELD(unsigned char, 0x11) -= 15;
        FLOAT(0x30) += 10.0f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 827:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex827 = 0; cancelIndex827 < 7; cancelIndex827++)
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
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                ClearField74();
                return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
            }
        }
        break;

    case 828:
        if (OWNER(short, 0x60) > 69 && OWNER(short, 0x60) < 150) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex828 = 0; cancelIndex828 < 15; cancelIndex828++)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            FLOAT(0x30) += 5.0f;
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(unsigned int, 0x50) = FIELD(unsigned int, 0xC8);
                FLOAT(0x54) = 10.0f;
                FIELD(short, 0xDE) = 0;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (FIELD(short, 0x62) < 2 && OWNER(short, 0x62) == 0 &&
                (OWNER(short, 0x60) == 408 || OWNER(short, 0x60) == 414)) {
                ResetSecondaryCounters(2);
                FLOAT(0x54) = 0.0f;
                FLOAT(0x50) = 0.0f;
                return;
            }
            else {
                if (FIELD(short, 0x62) == 0) {
                    if (FLOAT(0x50) > 2.5f) FLOAT(0x50) -= 1.0f;
                    else FLOAT(0x50) = 2.5f;
                    FLOAT(0x54) -= 0.6f;
                }
                if (FIELD(short, 0x62) == 1) {
                    --FIELD(short, 0xDE);
                    OWNER_FLOAT(0x490) = (FIELD(signed char, 0x66) * OPPONENT(signed char, 0x66)) * -6.0f *
                        (((OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66) > 0.0f) * 2 - 1);
                    if (FIELD(short, 0xDE) <= 0) {
                        OWNER_ACTOR->SpawnEffect(826, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 0);
                        FIELD(short, 0xDE) = 15;
                    }
                }
                if (FIELD(short, 0x62) == 2) {
                    FLOAT(0x1C) *= 0.85f;
                    FLOAT(0x20) *= 0.85f;
                }
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                    OWNER_ACTOR->PlaySoundAt00453D40(31);
                    FLOAT(0x50) = 0.0f;
                    FLOAT(0x54) = 0.0f;
                }
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0 && FIELD(short, 0xDA) < 45) {
                    ++FIELD(short, 0xDA);
                    ResetSecondaryCounters(1);
                }
            }
        }
        break;

    case 829:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex829 = 0; cancelIndex829 < 5; cancelIndex829++)
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
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0xD8) = 0;
                FLOAT(0x50) = 15.0f;
                FLOAT(0x54) = 10.0f;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            FLOAT(0x30) += 5.0f;
            FLOAT(0x54) -= 1.5f;
            if (FLOAT(0x48) + FLOAT(0x54) < 0.0f) {
                FLOAT(0x48) = 0.0f;
                FLOAT(0x54) = -FLOAT(0x54);
            }
            if (FIELD(short, 0x62) == 1 && FIELD(int, 0x7C) != 0 && FIELD(int, 0x7C) != 6) {
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                UnknownAt0045B850(1);
                ClearField74();
                OWNER_ACTOR->SpawnEffect(830, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FLOAT(0x30) = 0.0f;
                return;
            }
            else {
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                                ClearField74();
                                return;
                            }
                            else {
                    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                    FLOAT(0x48) += FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
                }
            }
        }
        break;

    case 830:
        if (FIELD(int, 0x7C) == 5) {
            ClearField74();
            return;
        }
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int cancelIndex830 = 0; cancelIndex830 < 5; cancelIndex830++)
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
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
            }
            if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                ClearField74();
                return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
            }
        }
        break;

    case 831:
        if (OWNER(short, 0x60) != 723) ClearField74();
        if (OWNER(short, 0x60) == 723) {
            FIELD(unsigned int, 0x44) = OPPONENT(unsigned int, 0x44);
            FLOAT(0x48) = OPPONENT_FLOAT(0x48) + 100.0f;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
        }
        ++FIELD(short, 0xDA);
        if (FIELD(short, 0xDA) > 90) {
            if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
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
            FIELD(short, 0xD8) = 0;
        }
        FLOAT(0x1C) = (0.2f - FIELD(short, 0xD8) * 0.02f * (FIELD(short, 0xD8) < 5)) + 0.005f + FLOAT(0x1C);
        FLOAT(0x20) = (0.2f - FIELD(short, 0xD8) * 0.02f * (FIELD(short, 0xD8) < 5)) + 0.005f + FLOAT(0x20);
        ++FIELD(short, 0xD8);
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 20) {
                FIELD(unsigned char, 0x11) -= 20;
                FIELD(unsigned char, 0x13) -= 20;
                FIELD(unsigned char, 0x14) -= 20;
            }
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 833:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x62) > 0) {
        FLOAT(0x1C) = (0.2f - FIELD(short, 0xD8) * 0.02f * (FIELD(short, 0xD8) < 5)) + 0.005f + FLOAT(0x1C);
        FLOAT(0x20) = (0.2f - FIELD(short, 0xD8) * 0.02f * (FIELD(short, 0xD8) < 5)) + 0.005f + FLOAT(0x20);
        ++FIELD(short, 0xD8);
        }
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 20) {
                FIELD(unsigned char, 0x11) -= 20;
                FIELD(unsigned char, 0x13) -= 20;
                FIELD(unsigned char, 0x14) -= 20;
            }
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
            FIELD(unsigned char, 0x11) = 255;
            for (int burstIndex833 = 0; burstIndex833 < 12; burstIndex833++) {
                OWNER_FLOAT(0x314) = RecordedRange(0, 40) - 90;
                OWNER_FLOAT(0x318) = RecordedRange(0, 22) + 5;
                OWNER_ACTOR->SpawnEffect(812, (RecordedRange(0, 200) - 100) * FIELD(signed char, 0x66) + FLOAT(0x44),
                    0.0f, FIELD(signed char, 0x66), 1);
            }
        }
        break;

    case 834:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = -80.0f;
            FIELD(short, 0xD8) = 0;
        }
        FLOAT(0x1C) = (0.3f - FIELD(short, 0xD8) * 0.05f * (FIELD(short, 0xD8) < 5)) + 0.005f + FLOAT(0x1C);
        FLOAT(0x20) = (0.3f - FIELD(short, 0xD8) * 0.05f * (FIELD(short, 0xD8) < 5)) + 0.005f + FLOAT(0x20);
        ++FIELD(short, 0xD8);
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 20) {
                FIELD(unsigned char, 0x11) -= 20;
                FIELD(unsigned char, 0x13) -= 20;
                FIELD(unsigned char, 0x14) -= 20;
            }
            else { ClearField74(); return; }
        }
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

    case 850:
        FIELD(signed char, 0x66) = OWNER(signed char, 0x66);
        if (OWNER(short, 0x60) > 149 && OWNER(short, 0x60) < 154 && FIELD(short, 0x62) == 0) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 57;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 94.0f;
        }
        if (OWNER(short, 0x60) > 153 && OWNER(short, 0x60) < 158 && FIELD(short, 0x62) == 0) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 57;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 60.0f;
        }
        if (OWNER(short, 0x60) == 158 && FIELD(short, 0x62) == 0) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 57;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        }
        if ((OWNER(short, 0x60) < 150 || OWNER(short, 0x60) > 158) && FIELD(short, 0x62) == 0) {
            ResetSecondaryCounters(1);
            OWNER(short, 0xF06) = 0;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = 50.0f;
            FIELD(short, 0xD8) = 1;
        }
        FLOAT(0x30) += 2.0f;
        if (FIELD(short, 0x62) > 0) {
            if (FIELD(unsigned char, 0x11) > 30) FIELD(unsigned char, 0x11) -= 30;
            else FIELD(unsigned char, 0x11) = 0;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(0);
        break;

    case 900:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x50) = RecordedRange(0, 30) - 15;
            FLOAT(0x54) = RecordedRange(0, 15);
        }
        if (FIELD(short, 0x62) < 3) {
            FLOAT(0x54) -= 0.6f;
            if (FLOAT(0x54) + FLOAT(0x48) <= 0.0f) {
                FLOAT(0x48) = 0.0f;
                ResetSecondaryCounters(3);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                return;
            }
        }
        if (FLOAT(0x48) > 960.0f) {
            ClearField74();
            return;
        }
        else {
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                ResetPrimaryCounters(0);
                EnableTransform(0.0f, 0.0f, 0.0f);
            }
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
            if (FIELD(short, 0x62) == 5 && FIELD(short, 0x64) == 0) FLOAT(0x54) = 24.0f;
        }
        break;

    case 901:
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 902:
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 903:
        FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
        FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 904:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = RecordedRange(0, 4) * 0.1f + 0.4f;
            FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
            FIELD(unsigned char, 0x11) = 64;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        FLOAT(0x1C) += 0.01f;
        FLOAT(0x20) += 0.01f;
        FIELD(unsigned char, 0x11) -= 1;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 905:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (RecordedRange(0, 100) < 20)
                OWNER_ACTOR->SpawnEffect(904, FLOAT(0x44) + 50.0f - RecordedRange(0, 100),
                    FLOAT(0x48) + 50.0f - RecordedRange(0, 100), FIELD(signed char, 0x66), 1);
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
                FIELD(short, 0xD8) = 100;
                FIELD(short, 0xDA) = 0;
                FIELD(short, 0xDC) = static_cast<short>(FLOAT(0xC8));
                FIELD(short, 0xDE) = 120;
                FIELD(short, 0xE0) = g_F1212_DifficultyAt006714D0 * 2 + 1;
            }
            if (OWNER(short, 0x62) < 2) {
                --FIELD(short, 0xDE);
                if (FIELD(short, 0xDE) <= 0 && OPPONENT(short, 0x324) > 0 && ScalarAt00428D20(
                    (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) +
                    (OPPONENT_FLOAT(0x48) - FLOAT(0x48)) * (OPPONENT_FLOAT(0x48) - FLOAT(0x48))) > 256 - g_F1212_DifficultyAt006714D0 * 48 &&
                    FLOAT(0x48) > 0.0f && FLOAT(0x44) > 0.0f && FLOAT(0x44) < 1280.0f) {
                    if (FIELD(short, 0xE0) > 0) {
                        OWNER_ACTOR->SpawnEffect(906, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                        OWNER_ACTOR->PlaySoundAt00453D40(28);
                        --FIELD(short, 0xE0);
                        FIELD(short, 0xDE) = 8;
                    }
                    else {
                        OWNER_ACTOR->SpawnEffect(906, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                        OWNER_ACTOR->PlaySoundAt00453D40(28);
                        FIELD(short, 0xE0) = g_F1212_DifficultyAt006714D0 * 2 + 1;
                        FIELD(short, 0xDE) = 180 - g_F1212_DifficultyAt006714D0 * 30;
                    }
                }
                FIELD(short, 0xDA) = static_cast<short>(AngleAt00483300(
                    OPPONENT_FLOAT(0x48) - FLOAT(0x48) + 100.0f,
                    (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828);
                if (FIELD(short, 0xDC) > FIELD(short, 0xDA)) {
                    if (FIELD(short, 0xDC) - FIELD(short, 0xDA) <= 180) {
                        FIELD(short, 0xDC) = FIELD(short, 0xDC) - 1;
                        if (FIELD(short, 0xDC) < -180) FIELD(short, 0xDC) = FIELD(short, 0xDC) + 360;
                    }
                    else {
                        FIELD(short, 0xDC) = FIELD(short, 0xDC) + 1;
                        if (FIELD(short, 0xDC) > 180) FIELD(short, 0xDC) = FIELD(short, 0xDC) - 360;
                    }
                }
                if (FIELD(short, 0xDC) <= FIELD(short, 0xDA)) {
                    if (FIELD(short, 0xDC) - FIELD(short, 0xDA) >= -180) {
                        FIELD(short, 0xDC) = FIELD(short, 0xDC) + 1;
                        if (FIELD(short, 0xDC) > 180) FIELD(short, 0xDC) = FIELD(short, 0xDC) - 360;
                    }
                    else {
                        FIELD(short, 0xDC) = FIELD(short, 0xDC) - 1;
                        if (FIELD(short, 0xDC) < -180) FIELD(short, 0xDC) = FIELD(short, 0xDC) + 360;
                    }
                }
            }
            if (OWNER(short, 0x62) > 1) {
                --FIELD(short, 0xDE);
                if (FIELD(short, 0xDE) <= 0 && ScalarAt00428D20(
                    (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) +
                    (OPPONENT_FLOAT(0x48) - FLOAT(0x48)) * (OPPONENT_FLOAT(0x48) - FLOAT(0x48))) > 128.0f &&
                    FLOAT(0x48) > 0.0f && FLOAT(0x44) > 0.0f && FLOAT(0x44) < 1280.0f) {
                    if (FIELD(short, 0xE0) > 0) {
                        OWNER_ACTOR->SpawnEffect(906, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                        OWNER_ACTOR->PlaySoundAt00453D40(28);
                        --FIELD(short, 0xE0);
                        FIELD(short, 0xDE) = 8;
                    }
                    else {
                        OWNER_ACTOR->SpawnEffect(906, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                        OWNER_ACTOR->PlaySoundAt00453D40(28);
                        FIELD(short, 0xE0) = 5;
                        FIELD(short, 0xDE) = 180 - g_F1212_DifficultyAt006714D0 * 30;
                    }
                }
                FIELD(short, 0xDA) = static_cast<short>(AngleAt00483300(
                    OWNER_FLOAT(0x48) - FLOAT(0x48),
                    (OWNER_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828);
                if (FIELD(short, 0xDC) > FIELD(short, 0xDA)) {
                    if (FIELD(short, 0xDC) - FIELD(short, 0xDA) <= 180) {
                        FIELD(short, 0xDC) = FIELD(short, 0xDC) - 3;
                        if (FIELD(short, 0xDC) < -180) FIELD(short, 0xDC) = FIELD(short, 0xDC) + 360;
                    }
                    else {
                        FIELD(short, 0xDC) = FIELD(short, 0xDC) + 3;
                        if (FIELD(short, 0xDC) > 180) FIELD(short, 0xDC) = FIELD(short, 0xDC) - 360;
                    }
                }
                if (FIELD(short, 0xDC) <= FIELD(short, 0xDA)) {
                    if (FIELD(short, 0xDC) - FIELD(short, 0xDA) >= -180) {
                        FIELD(short, 0xDC) = FIELD(short, 0xDC) + 3;
                        if (FIELD(short, 0xDC) > 180) FIELD(short, 0xDC) = FIELD(short, 0xDC) - 360;
                    }
                    else {
                        FIELD(short, 0xDC) = FIELD(short, 0xDC) - 3;
                        if (FIELD(short, 0xDC) < -180) FIELD(short, 0xDC) = FIELD(short, 0xDC) + 360;
                    }
                }
            }
            if (FIELD(short, 0xD8) > 50) --FIELD(short, 0xD8);
            SetPolarVelocity(FIELD(short, 0xDC), FIELD(short, 0xD8) * 0.1f);
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) -= FLOAT(0x54);
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                if (OWNER(short, 0x62) < 3) {
                    ++FIELD(short, 0xD8);
                    ResetSecondaryCounters(1);
                    return;
                }
                else { ClearField74(); return; }
            }
        }
        break;

    case 906:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 6.0f;
                FLOAT(0x20) = 6.0f;
                FIELD(unsigned char, 0x11) = 0;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0xD8) = 0;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            if (FIELD(short, 0x62) == 0) {
                if (FLOAT(0x1C) > 1.0f) {
                    FLOAT(0x1C) -= 0.2f;
                    FLOAT(0x20) -= 0.2f;
                }
                else {
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                }
                if (FIELD(unsigned char, 0x11) < 235) FIELD(unsigned char, 0x11) += 20;
                else FIELD(unsigned char, 0x11) = 255;
            }
            if (FIELD(short, 0x62) == 1 && FIELD(int, 0x7C) != 0) {
                ResetSecondaryCounters(2);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 2) {
                    FLOAT(0x1C) *= 0.85f;
                    FLOAT(0x20) *= 0.85f;
                }
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                                ClearField74();
                                return;
                            }
                            else {
                    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                        ClearField74();
                        return;
                    }
                    else if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                        SetPolarVelocity(AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                            (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828, 6.0f);
                        FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
                        FIELD(int, 0x7C) = 0;
                        FIELD(short, 0x80) = 1;
                    }
                }
            }
        }
        break;

    case 907:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
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
                FIELD(int, 0x7C) = 0;
            }
            FLOAT(0xCC) += 1.0f;
            SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC) * 0.1f);
            if (FIELD(short, 0x62) == 2) {
                FLOAT(0x1C) *= 0.85f;
                FLOAT(0x20) *= 0.85f;
            }
            if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                ClearField74();
                return;
            }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
            }
        }
        break;

    case 910:
        if (OWNER(short, 0x3A0) <= 0) {
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
            }
            if (OWNER(short, 0x60) == 761) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 140;
                FLOAT(0x48) = OWNER_FLOAT(0x48) + 35.0f;
            }
            if (OWNER(short, 0x60) != 761 || (OWNER(short, 0x60) == 761 && OWNER(short, 0x62) > 12)) {
                ClearField74();
                return;
            }
            else {
                FLOAT(0x20) *= 0.9f;
                FLOAT(0x1C) += 0.1f;
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(4);
            }
        }
        break;

    case 911:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                        EnableTransform(0.0f, 0.0f, 0.0f);
                        FLOAT(0x1C) = RecordedRange(75, 150) * 0.01f;
                        FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
                        FLOAT(0x30) = RecordedRange(0, 359);
                        FIELD(short, 0xDC) = static_cast<short>(AngleAt00483300(
                            OWNER(short, 0xF24) - FLOAT(0x48),
                            (OWNER(short, 0xF22) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828);
                        SetPolarVelocity(FIELD(short, 0xDC), 36.0f);
                    }
                    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (FIELD(short, 0x62) < 2) {
                        FLOAT(0x30) += 5.0f;
                        if (AbsFloatAt00412D90(FLOAT(0x44) - OWNER(short, 0xF22)) < 60.0f &&
                            AbsFloatAt00412D90(FLOAT(0x48) - OWNER(short, 0xF24)) < 60.0f) {
                            FLOAT(0x50) = 0.0f;
                            FLOAT(0x54) = 0.0f;
                            OWNER_ACTOR->PlaySharedSoundAt00453D60(4);
                            FIELD(short, 0xD8) = static_cast<short>(FLOAT(0x44) - OWNER(short, 0xF22));
                            FIELD(short, 0xDA) = static_cast<short>(FLOAT(0x48) - OWNER(short, 0xF24));
                            ResetSecondaryCounters(2);
                        }
                    }
                    if (FIELD(short, 0x62) == 2 && OWNER(short, 0x60) == 774) {
                        if (OWNER(short, 0x62) == 6) {
                            FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 60) * FIELD(signed char, 0x66);
                            FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 140);
                        }
                        if (OWNER(short, 0x62) == 7) {
                            FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 94) * FIELD(signed char, 0x66);
                            FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 178);
                        }
                        if (OWNER(short, 0x62) == 8) {
                            FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 150) * FIELD(signed char, 0x66);
                            FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 82);
                        }
                        if (OWNER(short, 0x62) == 9) {
                            FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 75) * FIELD(signed char, 0x66);
                            FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 17);
                        }
                        if (OWNER(short, 0x62) == 10) {
                            FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 30) * FIELD(signed char, 0x66);
                            FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 10);
                        }
                        if (OWNER(short, 0x62) == 11) {
                            FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 110) * FIELD(signed char, 0x66);
                            FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 85);
                        }
                        if (OWNER(short, 0x62) == 12) {
                            FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 95) * FIELD(signed char, 0x66);
                            FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 185);
                        }
                        if (OWNER(short, 0x62) == 13) {
                            FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) - 10) * FIELD(signed char, 0x66);
                            FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 230);
                        }
                        if (OWNER(short, 0x62) == 14) {
                            FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 54) * FIELD(signed char, 0x66);
                            FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 160);
                        }
                        if (OWNER(short, 0x62) == 15) {
                            FLOAT(0x44) = OWNER_FLOAT(0x44) + (FIELD(short, 0xD8) + 80) * FIELD(signed char, 0x66);
                            FLOAT(0x48) = OWNER_FLOAT(0x48) + (FIELD(short, 0xDA) + 135);
                        }
                        if (OWNER(short, 0x62) == 16) ResetSecondaryCounters(3);
                    }
                    if (FIELD(short, 0x62) == 3) {
                        if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -200.0f || FLOAT(0x48) > 960.0f ||
                            (OWNER(short, 0x60) == 774 && OWNER(short, 0x62) == 5)) {
                            ClearField74();
                            return;
                        }
                        FLOAT(0x44) = OWNER(short, 0xF22) + FIELD(short, 0xD8) * FIELD(signed char, 0x66);
                        FLOAT(0x48) = OWNER(short, 0xF24) + FIELD(short, 0xDA);
                        if (OWNER(short, 0xF24) <= 0) {
                            ResetSecondaryCounters(4);
                            FLOAT(0x50) = RecordedRange(0, 20) - 10;
                            FLOAT(0x54) = -RecordedRange(5, 20);
                            return;
                        }
                    }
                    if (FIELD(short, 0x62) == 4) {
                        FLOAT(0x54) += 0.5f;
                        if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f && FLOAT(0x54) > 0.0f)
                            FLOAT(0x54) = -FLOAT(0x54);
                        if (FIELD(unsigned char, 0x11) > 5) FIELD(unsigned char, 0x11) -= 5;
                        else { ClearField74(); return; }
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 912:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            OWNER(short, 0xF22) = static_cast<short>(FLOAT(0x44));
            OWNER(short, 0xF24) = static_cast<short>(FLOAT(0x48));
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 0;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
            }
            if (OWNER(short, 0x60) == 774 && OWNER(short, 0x62) > 15 && FIELD(short, 0x62) == 0) {
                FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 140;
                FLOAT(0x48) = OWNER_FLOAT(0x48) + 35.0f;
                ResetSecondaryCounters(1);
                FIELD(short, 0xDC) = static_cast<short>(AngleAt00483300(
                    OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                    (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828);
                SetPolarVelocity(FIELD(short, 0xDC), g_F1212_DifficultyAt006714D0 * 3 + 15);
            }
            if (FIELD(short, 0x62) == 1 && FLOAT(0x48) < 0.0f) {
                OWNER_ACTOR->PlaySoundAt00453D40(23);
                ClearField74();
                return;
            }
            else {
                if (FLOAT(0x44) > 1700.0f || FLOAT(0x44) < -500.0f || FLOAT(0x48) > 1280.0f) {
                    ClearField74();
                    return;
                }
                else {
                    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
                }
            }
        }
        break;

    case 913:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                FIELD(short, 0xDC) = 0;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 0.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                OWNER_ACTOR->SpawnEffect(914, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 0);
            }
            if (FIELD(short, 0xD8) < 60) ++FIELD(short, 0xD8);
            --FIELD(short, 0xDC);
            FLOAT(0x30) -= 5.0f;
            if (FIELD(short, 0x62) == 1) {
                FLOAT(0x1C) += 0.15f;
                FLOAT(0x20) += 0.15f;
                --FIELD(short, 0xDE);
            }
            if (FIELD(short, 0x62) == 2) {
                OWNER_FLOAT(0x490) = -(FIELD(short, 0xD8) * 0.1f) *
                    (FIELD(signed char, 0x66) * OPPONENT(signed char, 0x66)) *
                    (((OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66) > 0.0f) * 2 - 1);
                OWNER_ACTOR->SetCameraShakeAt00453E60(2.0f);
                if (FIELD(short, 0xDC) <= 0) {
                    OWNER_FLOAT(0x31C) = RecordedRange(0, 359);
                    SetPolarVelocity(OWNER_FLOAT(0x31C), 960.0f);
                    OWNER_ACTOR->SpawnEffect(916, FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44),
                        FLOAT(0x48) + FLOAT(0x54), FIELD(signed char, 0x66), 1);
                    OWNER_FLOAT(0x31C) = RecordedRange(0, 359);
                    SetPolarVelocity(OWNER_FLOAT(0x31C), 960.0f);
                    OWNER_ACTOR->SpawnEffect(916, FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44),
                        FLOAT(0x48) + FLOAT(0x54), FIELD(signed char, 0x66), 1);
                    FIELD(short, 0xDC) = 6 - g_F1212_DifficultyAt006714D0;
                }
            }
            if (FIELD(short, 0x62) == 4) {
                FLOAT(0x1C) *= 0.85f;
                FLOAT(0x20) *= 0.85f;
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                UnknownAt0045B850(31);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 &&
                FIELD(short, 0xDA) < g_F1212_DifficultyAt006714D0 + 2) {
                ++FIELD(short, 0xDA);
                ResetSecondaryCounters(2);
            }
        }
        break;

    case 914:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            ++FIELD(short, 0xD8);
            FLOAT(0x30) -= 6.0f;
            if (FIELD(short, 0x62) == 4) {
                FLOAT(0x1C) *= 0.85f;
                FLOAT(0x20) *= 0.85f;
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 &&
                FIELD(short, 0xDA) < g_F1212_DifficultyAt006714D0 + 2) {
                ++FIELD(short, 0xDA);
                ResetSecondaryCounters(2);
            }
        }
        break;

    case 915:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
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
                FIELD(short, 0xD8) = 0;
                FLOAT(0x50) = RecordedRange(0, 8) + 6;
            }
            if (FLOAT(0x44) > 1180.0f || FLOAT(0x44) < 100.0f) {
                ClearField74();
                OWNER_ACTOR->SpawnEffect(913, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 0);
                return;
            }
            else {
                if (FIELD(short, 0x62) == 1) {
                    FLOAT(0x1C) = RecordedRange(0, 5) * 0.1f + 0.8f;
                    FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
                }
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                    ClearField74();
                    OWNER_ACTOR->SpawnEffect(913, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 0);
                    return;
                }
            }
        }
        break;

    case 916:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
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
                SetPolarVelocity(-FLOAT(0xD0) + 180.0f, 30.0f);
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) -= FLOAT(0x54);
            if ((FIELD(int, 0x7C) != 0 || FLOAT(0xD0) <= 0.0f) && FIELD(short, 0x62) == 1) {
                ResetSecondaryCounters(2);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                return;
            }
            else {
                if (FIELD(short, 0x62) > 1) {
                    if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
                    else { ClearField74(); return; }
                }
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
                    FLOAT(0x50) = 0.0f;
                    FLOAT(0x54) = 0.0f;
                }
            }
        }
        break;

    case 918:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 99;
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 0.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            if (FIELD(short, 0x62) == 1) {
                FLOAT(0x1C) += 0.033f;
                FLOAT(0x20) += 0.033f;
                if (FLOAT(0x1C) > 1.0f) {
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                }
            }
            if (FIELD(short, 0x62) == 3) {
                FLOAT(0x1C) = RecordedRange(0, 5) * 0.025f + 0.95;
                FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) -= FLOAT(0x54);
            FLOAT(0x30) += 1.0f;
            if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f || FLOAT(0x48) > 1280.0f || FLOAT(0x48) < -380.0f) {
                ClearField74();
                return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                    ResetSecondaryCounters(3);
                    FIELD(int, 0x7C) = 0;
                    return;
                }
                else if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                    OWNER_ACTOR->PlaySoundAt00453D40(16);
                    SetPolarVelocity(AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                        (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828, 5.0f);
                }
            }
        }
        break;

    case 919:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
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
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            if (FIELD(short, 0x62) == 0) {
                if (FIELD(unsigned char, 0x11) < 220) FIELD(unsigned char, 0x11) += 35;
                else FIELD(unsigned char, 0x11) = 255;
                FLOAT(0x1C) -= 0.1f;
                FLOAT(0x20) -= 0.1f;
            }
            if (FIELD(short, 0x62) == 1) {
                if (FIELD(short, 0xD8) < 15) ++FIELD(short, 0xD8);
                SetPolarVelocity(FLOAT(0xC8), 20 - FIELD(short, 0xD8));
            }
            if (FIELD(short, 0x62) == 1 && FIELD(int, 0x7C) != 0) {
                ResetSecondaryCounters(2);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                return;
            }
            else {
                if (FIELD(short, 0x62) == 2) {
                    FLOAT(0x1C) *= 0.85f;
                    FLOAT(0x20) *= 0.85f;
                }
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -100.0f) {
                                ClearField74();
                                return;
                            }
                            else {
                    FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                    FLOAT(0x48) -= FLOAT(0x54);
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                        ClearField74();
                        return;
                    }
                    else if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                        SetPolarVelocity(FLOAT(0xC8), 20.0f);
                        FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
                    }
                }
            }
        }
        break;

    case 920:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                FIELD(short, 0xDC) = 0;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 0.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                OWNER_ACTOR->SpawnEffect(921, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 0);
            }
            if (FIELD(short, 0xD8) < g_F1212_DifficultyAt006714D0 * 8 + 10) ++FIELD(short, 0xD8);
            --FIELD(short, 0xDC);
            FLOAT(0x30) -= 5.0f;
            if (FIELD(short, 0x62) == 1) {
                FLOAT(0x1C) += 0.15f;
                FLOAT(0x20) += 0.15f;
                --FIELD(short, 0xDE);
            }
            if (FIELD(short, 0x62) == 2) {
                OWNER_FLOAT(0x490) = -(FIELD(short, 0xD8) * 0.1f) *
                    (FIELD(signed char, 0x66) * OPPONENT(signed char, 0x66)) *
                    (((OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66) > 0.0f) * 2 - 1);
                OWNER_ACTOR->SetCameraShakeAt00453E60(2.0f);

            }
            if (FIELD(short, 0x62) == 4) {
                FLOAT(0x1C) *= 0.85f;
                FLOAT(0x20) *= 0.85f;
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                UnknownAt0045B850(31);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
        }
        break;

    case 921:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            ++FIELD(short, 0xD8);
            FLOAT(0x30) -= 6.0f;
            if (FIELD(short, 0x62) == 4) {
                FLOAT(0x1C) *= 0.85f;
                FLOAT(0x20) *= 0.85f;
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
        }
        break;

    case 922:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
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
                FLOAT(0x30) = RecordedRange(0, 359);
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 923:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
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
                FIELD(short, 0xD8) = 0;
                FLOAT(0x50) = RecordedRange(0, 8) - 4;
                FLOAT(0x54) = -RecordedRange(0, 3) - 13;
            }
            if (FIELD(short, 0x64) == 0)
                OWNER_ACTOR->SpawnEffect(922, FLOAT(0x44) + 10.0f - RecordedRange(0, 20),
                    FLOAT(0x48) + 10.0f - RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
            if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
                ClearField74();
                return;
            }
            else {
                FLOAT(0x54) += 0.2f;
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x48) - FLOAT(0x54) <= 0.0f) {
                    ClearField74();
                    OWNER_ACTOR->SpawnEffect(925, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                    OWNER_ACTOR->SpawnEffect(925, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
            }
        }
        break;

    case 924:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
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
                FLOAT(0x30) = RecordedRange(0, 359);
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 925:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
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
                FIELD(short, 0xD8) = 0;
                FLOAT(0x50) = RecordedRange(0, 8) - 4;
                FLOAT(0x54) = -RecordedRange(0, 3) - 13;
            }
            if (FIELD(short, 0x64) == 0)
                OWNER_ACTOR->SpawnEffect(924, FLOAT(0x44) + 5.0f - RecordedRange(0, 10),
                    FLOAT(0x48) + 5.0f - RecordedRange(0, 10), FIELD(signed char, 0x66), 1);
            if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
                ClearField74();
                return;
            }
            else {
                FLOAT(0x54) += 0.2f;
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x48) - FLOAT(0x54) <= 0.0f) {
                    ClearField74();
                    OWNER_ACTOR->SpawnEffect(927, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                    OWNER_ACTOR->SpawnEffect(927, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
            }
        }
        break;

    case 926:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
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
                FLOAT(0x30) = RecordedRange(0, 359);
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 927:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
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
                FIELD(short, 0xD8) = 0;
                FLOAT(0x50) = RecordedRange(0, 8) - 4;
                FLOAT(0x54) = -RecordedRange(0, 3) - 13;
            }
            if (FIELD(short, 0x64) == 0)
                OWNER_ACTOR->SpawnEffect(926, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f) {
                ClearField74();
                return;
            }
            else {
                FLOAT(0x54) += 0.2f;
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x48) - FLOAT(0x54) <= 0.0f) {
                    if (FIELD(short, 0xD8) == 0) {
                        FLOAT(0x54) = -FLOAT(0x54) * 0.75f;
                        FIELD(short, 0x80) = 1;
                        FIELD(int, 0x7C) = 0;
                        ++FIELD(short, 0xD8);
                        return;
                    }
                    ClearField74();
                }
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
            }
        }
        break;

    case 928:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 99;
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 0.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            if (FIELD(short, 0x62) == 1) {
                FLOAT(0x1C) += 0.033f;
                FLOAT(0x20) += 0.033f;
                if (FLOAT(0x1C) > 1.0f) {
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                }
            }
            if (FIELD(short, 0x62) == 3) {
                FLOAT(0x1C) = RecordedRange(0, 5) * 0.025f + 0.95;
                FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) -= FLOAT(0x54);
            FLOAT(0x30) += 1.0f;
            if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f || FLOAT(0x48) > 1280.0f || FLOAT(0x48) < -380.0f) {
                ClearField74();
                return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                    ResetSecondaryCounters(3);
                    FIELD(int, 0x7C) = 0;
                    return;
                }
                else if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                    OWNER_ACTOR->PlaySoundAt00453D40(16);
                    SetPolarVelocity(AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                        (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828, 5.0f);
                }
            }
        }
        break;

    case 929:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 99;
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 0.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            if (FIELD(short, 0x62) == 1) {
                FLOAT(0x1C) += 0.033f;
                FLOAT(0x20) += 0.033f;
                if (FLOAT(0x1C) > 1.0f) {
                    FLOAT(0x1C) = 1.0f;
                    FLOAT(0x20) = 1.0f;
                }
            }
            if (FIELD(short, 0x62) == 3) {
                FLOAT(0x1C) = RecordedRange(0, 5) * 0.025f + 0.95;
                FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) -= FLOAT(0x54);
            FLOAT(0x30) += 1.0f;
            if (FLOAT(0x44) > 1800.0f || FLOAT(0x44) < -680.0f || FLOAT(0x48) > 1280.0f || FLOAT(0x48) < -380.0f) {
                ClearField74();
                return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                    ResetSecondaryCounters(3);
                    FIELD(int, 0x7C) = 0;
                    return;
                }
                else if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
                    OWNER_ACTOR->PlaySoundAt00453D40(16);
                    SetPolarVelocity(AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                        (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828, 5.0f);
                }
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
