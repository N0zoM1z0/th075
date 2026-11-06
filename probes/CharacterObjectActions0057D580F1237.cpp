// Complete research source for original 0057D580 (43,845 CODE bytes).
// All native states are written; NONEXACT and not an accepted replacement.
#include "ObjectAdvance57D580F1237.hpp"
#include "MathLookup.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OWNER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset)))
#define OPPONENT(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset))
#define OWNER_ACTOR reinterpret_cast<OwnerActor57D580F1237*>(FIELD(void*, 0xE4))

extern float g_F1211_AngleDivAt00657828;
extern signed char g_F1212_DifficultyAt006714D0;
extern unsigned int g_F1239_DwordAt0067149C;
extern unsigned char g_F1239_ByteAt006714D1;

void ObjectActor57D580F1237::AdvanceAction()
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
            for (int rewardIndex800 = 0; rewardIndex800 < 3; ++rewardIndex800)
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
            SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.2f + FLOAT(0xCC));
            if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) == 1) { ResetSecondaryCounters(2); return; }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        if (FIELD(unsigned char, 0x11) >= 25) FIELD(unsigned char, 0x11) -= 25;
                        else FIELD(unsigned char, 0x11) = 0;
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

case 801:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        else if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex801 = 0; rewardIndex801 < 3; ++rewardIndex801)
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
            SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.2f + FLOAT(0xCC));
            if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) == 1) { ResetSecondaryCounters(2); return; }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        if (FIELD(unsigned char, 0x11) >= 25) FIELD(unsigned char, 0x11) -= 25;
                        else FIELD(unsigned char, 0x11) = 0;
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

case 802:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        else if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex802 = 0; rewardIndex802 < 3; ++rewardIndex802)
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
            SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.2f + FLOAT(0xCC));
            if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) == 1) { ResetSecondaryCounters(2); return; }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        if (FIELD(unsigned char, 0x11) >= 25) FIELD(unsigned char, 0x11) -= 25;
                        else FIELD(unsigned char, 0x11) = 0;
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

case 803:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
            ClearField74(); return;
        }
        if ((OWNER(short, 0x60) != 700 || (OWNER(short, 0x60) == 700 && OWNER(short, 0x62) > 9)) && FIELD(short, 0x62) < 2)
            FLOAT(0xD0) *= 0.9f;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 3;
            FIELD(int, 0x7C) = 0;
            SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
            FIELD(short, 0xD8) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (FIELD(short, 0x62) < 2) FLOAT(0xC8) = FLOAT(0xD0) * 0.1f + FLOAT(0xC8);
        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
        FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) >= 5) FIELD(unsigned char, 0x11) -= 5;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 50) {
            ResetSecondaryCounters(1);
            FIELD(int, 0x7C) = 0;
            ++FIELD(short, 0xD8);
        }
        break;

case 804:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
        }
        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
        if (FLOAT(0xCC) > 2.0f) FLOAT(0xCC) -= 1.0f;
        if (FIELD(short, 0x62) < 2 && FLOAT(0xCC) == 2.0f) ResetSecondaryCounters(2);
        if (FIELD(short, 0x80) == 0) { ClearField74(); return; }
        else {
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) += FLOAT(0x54);
            OWNER_ACTOR->SpawnEffect(805, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
                FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
            if (FIELD(short, 0x64) == 0) {
                FIELD(short, 0xDA) = RecordedRange(0, 20);
                FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.5f;
                FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.5f;
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
            if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 45) {
                ResetSecondaryCounters(2);
                ++FIELD(short, 0xD8);
            }
        }
        break;

case 805:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.8f;
            FLOAT(0x20) = 0.8f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 1;
            FLOAT(0x54) = 8.0f;
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

case 806:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 0.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
            FLOAT(0x50) = 8.0f;
            FLOAT(0x54) = 0.0f;
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        --FIELD(short, 0xDA);
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0xDA) < 0) {
            OWNER_FLOAT(0x314) = RecordedRange(0, 40) - 90;
            OWNER_FLOAT(0x318) = RecordedRange(0, 22) + 5;
            OWNER_ACTOR->SpawnEffect(804, (100 - RecordedRange(0, 200)) * FIELD(signed char, 0x66) + FLOAT(0x44),
                FLOAT(0x48), FIELD(signed char, 0x66), 1);
            FIELD(short, 0xDA) = 2;
        }
        if (FIELD(short, 0x62) == 3) {
            if (FIELD(unsigned char, 0x11) > 13) FIELD(unsigned char, 0x11) -= 13;
            else FIELD(unsigned char, 0x11) = 0;
        }
        if (FIELD(short, 0x62) < 2) {
            FLOAT(0x1C) += 0.8f;
            FLOAT(0x20) += 0.2f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) OWNER_ACTOR->PlaySoundAt00453D40(7);
        break;

case 807:
        if (OWNER(short, 0x60) == 304) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 3;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 110.0f;
        }
        if (OWNER(short, 0x60) != 304) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (OWNER(short, 0x82) == 0 && AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 808:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0xDC) = AngleAt00483300(OPPONENT_FLOAT(0x48) + 128.0f - FLOAT(0x48),
                (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828;
            if (FIELD(short, 0xDC) < -20) FIELD(short, 0xDC) = -20;
            if (FIELD(short, 0xDC) > 20) FIELD(short, 0xDC) = 20;
        }
        if (FIELD(short, 0x62) < 3) SetPolarVelocity(FIELD(short, 0xDC), 20.0f);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FIELD(short, 0x62) < 3)
            OWNER_ACTOR->SpawnEffect(809, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
                FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
        if (FIELD(int, 0x7C) == 6) {
            ++FIELD(short, 0x80);
            FIELD(int, 0x7C) = 0;
        }
        if (FIELD(short, 0x62) == 2 && FIELD(int, 0x7C) == 1) {
            ResetSecondaryCounters(3);
            UnknownAt0045B850(9);
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            OWNER(short, 0xF0C) = 0;
            return;
        }
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(int, 0x7C) == 1) {
            for (int burstIndex808 = 0; burstIndex808 < 8; ++burstIndex808) {
                OWNER_FLOAT(0x314) = burstIndex808;
                OWNER_ACTOR->SpawnEffect(810, OPPONENT_FLOAT(0x44), OPPONENT_FLOAT(0x48) + 100.0f, 1, 1);
                ++OWNER(short, 0xF0C);
            }
        }
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.5f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
        break;

case 809:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.8f;
            FLOAT(0x20) = 0.8f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 1;
            FLOAT(0x54) = 0.0f;
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

case 810:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
        }
        SetPolarVelocity(OWNER(short, 0xF0E) + 45.0f * FLOAT(0xC8), 140.0f);
        FLOAT(0x44) = FLOAT(0x50) + OPPONENT_FLOAT(0x44);
        FLOAT(0x48) = FLOAT(0x54) * 0.5f + OPPONENT_FLOAT(0x48) + 100.0f;
        if (FLOAT(0x54) > 0.0f) FLOAT(0x4C) = -5.0f;
        else FLOAT(0x4C) = 5.0f;
        if (FIELD(short, 0x62) < 15) {
            if (OPPONENT(short, 0x324) > 2) --OPPONENT(short, 0x324);
            if (OPPONENT(short, 0x3A0) > 0 && OPPONENT(short, 0x326) > 2) --OPPONENT(short, 0x326);
            if (FIELD(unsigned char, 0x11) < 235) FIELD(unsigned char, 0x11) += 20;
            else FIELD(unsigned char, 0x11) = 255;
        }
        if ((OPPONENT(short, 0x324) <= 0 || OWNER(short, 0x3A0) <= 0 || OWNER(short, 0x324) <= 0 || OWNER(short, 0xF0C) == 0 ||
            (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150)) && FIELD(short, 0x62) < 15) {
            ResetSecondaryCounters(FIELD(short, 0x62) + 14);
            --OWNER(short, 0xF0C);
            if (OWNER(short, 0xF0C) < 0) OWNER(short, 0xF0C) = 0;
        }
        if (FIELD(short, 0x62) > 14) {
            if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ResetSecondaryCounters(15); return; }
        if (FIELD(short, 0x62) == 15 && FIELD(short, 0x64) == 0) {
            if (FIELD(short, 0xD8) - 1 < FLOAT(0xC8) * 2) {
                ResetSecondaryCounters(1);
                ++FIELD(short, 0xD8);
            }
            else {
                --OWNER(short, 0xF0C);
                if (OWNER(short, 0xF0C) < 0) OWNER(short, 0xF0C) = 0;
            }
        }
        break;

case 812:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
        }
        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        OWNER_ACTOR->SpawnEffect(827, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
            FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
        if (FIELD(short, 0x62) == 1) {
            if (FLOAT(0x48) > OWNER_FLOAT(0x2E0) && FLOAT(0x54) < 0.0f) FIELD(short, 0xD8) = 1;
            if (FLOAT(0x48) < 0.0f && FLOAT(0x54) > 0.0f) FIELD(short, 0xD8) = 1;
            if (FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(signed char, 0x66) * FLOAT(0x50) < 0.0f) FIELD(short, 0xD8) = 1;
            if (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(signed char, 0x66) * FLOAT(0x50) > 0.0f) FIELD(short, 0xD8) = 1;
            if (FIELD(short, 0xD8) == 1) {
                OWNER_ACTOR->PlaySoundAt00453D40(0);
                for (int collisionIndex812 = 0; collisionIndex812 < 1; ++collisionIndex812) {
                    OWNER_FLOAT(0x318) = collisionIndex812 * 2 + 1;
                    OWNER_FLOAT(0x314) = AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                        (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828;
                    OWNER_ACTOR->SpawnEffect(813, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                ClearField74();
                return;
            }
        }
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.5f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 30) {
            ResetSecondaryCounters(2);
            ++FIELD(short, 0xD8);
        }
        break;


case 813:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        else if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex813 = 0; rewardIndex813 < 2; ++rewardIndex813)
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
            SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.1f + FLOAT(0xCC));
            if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) == 1) { ResetSecondaryCounters(2); return; }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        if (FIELD(unsigned char, 0x11) >= 25) FIELD(unsigned char, 0x11) -= 25;
                        else FIELD(unsigned char, 0x11) = 0;
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

case 814:
        if (OWNER(short, 0x60) == 307) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 20;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 125.0f;
        }
        if (OWNER(short, 0x60) != 307) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 2.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x1A) = 1250;
            FLOAT(0x28) = 110.0f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 815:
        if (OWNER(short, 0x60) == 301 || OWNER(short, 0x60) == 391) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        }
        if (OWNER(short, 0x60) != 301 && OWNER(short, 0x60) != 391) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x1A) = 1250;
            FLOAT(0x28) = 110.0f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 816:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
        }
        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        OWNER_ACTOR->SpawnEffect(828, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
            FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
        if (FIELD(short, 0x62) == 1) {
            if (FLOAT(0x48) > OWNER_FLOAT(0x2E0) && FLOAT(0x54) < 0.0f) FIELD(short, 0xD8) = 1;
            if (FLOAT(0x48) < 0.0f && FLOAT(0x54) > 0.0f) FIELD(short, 0xD8) = 1;
            if (FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(signed char, 0x66) * FLOAT(0x50) < 0.0f) FIELD(short, 0xD8) = 1;
            if (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(signed char, 0x66) * FLOAT(0x50) > 0.0f) FIELD(short, 0xD8) = 1;
            if (FIELD(short, 0xD8) == 1) {
                OWNER_ACTOR->PlaySoundAt00453D40(0);
                for (int collisionIndex816 = 0; collisionIndex816 < 1; ++collisionIndex816) {
                    OWNER_FLOAT(0x318) = collisionIndex816 * 2 + 1;
                    OWNER_FLOAT(0x314) = AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                        (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828;
                    OWNER_ACTOR->SpawnEffect(818, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                ClearField74();
                return;
            }
        }
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.5f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 30) {
            ResetSecondaryCounters(2);
            ++FIELD(short, 0xD8);
        }
        break;

case 817:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
        }
        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        OWNER_ACTOR->SpawnEffect(829, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
            FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
        if (FIELD(short, 0x62) == 1) {
            if (FLOAT(0x48) > OWNER_FLOAT(0x2E0) && FLOAT(0x54) < 0.0f) FIELD(short, 0xD8) = 1;
            if (FLOAT(0x48) < 0.0f && FLOAT(0x54) > 0.0f) FIELD(short, 0xD8) = 1;
            if (FLOAT(0x44) < OWNER_FLOAT(0x2D8) && FIELD(signed char, 0x66) * FLOAT(0x50) < 0.0f) FIELD(short, 0xD8) = 1;
            if (FLOAT(0x44) > OWNER_FLOAT(0x2DC) && FIELD(signed char, 0x66) * FLOAT(0x50) > 0.0f) FIELD(short, 0xD8) = 1;
            if (FIELD(short, 0xD8) == 1) {
                OWNER_ACTOR->PlaySoundAt00453D40(0);
                for (int collisionIndex817 = 0; collisionIndex817 < 1; ++collisionIndex817) {
                    OWNER_FLOAT(0x318) = collisionIndex817 * 2 + 1;
                    OWNER_FLOAT(0x314) = AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                        (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828;
                    OWNER_ACTOR->SpawnEffect(819, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
                }
                ClearField74();
                return;
            }
        }
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.5f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 30) {
            ResetSecondaryCounters(2);
            ++FIELD(short, 0xD8);
        }
        break;



case 818:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        else if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex818 = 0; rewardIndex818 < 2; ++rewardIndex818)
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
            SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.1f + FLOAT(0xCC));
            if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) == 1) { ResetSecondaryCounters(2); return; }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        if (FIELD(unsigned char, 0x11) >= 25) FIELD(unsigned char, 0x11) -= 25;
                        else FIELD(unsigned char, 0x11) = 0;
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

case 819:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        else if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex819 = 0; rewardIndex819 < 2; ++rewardIndex819)
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
            SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.1f + FLOAT(0xCC));
            if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) == 1) { ResetSecondaryCounters(2); return; }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 960.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        if (FIELD(unsigned char, 0x11) >= 25) FIELD(unsigned char, 0x11) -= 25;
                        else FIELD(unsigned char, 0x11) = 0;
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

case 820:
        if (OWNER(short, 0x60) == 390) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 146;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 80.0f;
        }
        if (OWNER(short, 0x60) != 390) { ClearField74(); return; }
        OWNER_ACTOR->SpawnEffect(805, FLOAT(0x44) - 10.0f + RecordedRange(0, 40),
            FLOAT(0x48) - 10.0f + RecordedRange(0, 40), FIELD(signed char, 0x66), 1);
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 1.5f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 1.5f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(1);
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 30) {
            ResetSecondaryCounters(2);
            ++FIELD(short, 0xD8);
        }
        break;

case 821:
        if (OWNER(short, 0x60) == 310 || OWNER(short, 0x60) == 392) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 20;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        }
        if (OWNER(short, 0x60) != 310 && OWNER(short, 0x60) != 392) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 2.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x1A) = 1250;
            FLOAT(0x28) = 140.0f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;



case 822:
        if (OWNER(short, 0x60) == 607 || OWNER(short, 0x60) == 609) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 105;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 145.0f;
        }
        if (OWNER(short, 0x60) != 607 && OWNER(short, 0x60) != 609) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.2f;
            FLOAT(0x20) = 0.2f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(int, 0x7C) == 6) FIELD(int, 0x7C) = 0;
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0xD8) == 0) {
            if (FLOAT(0x1C) < 1.0f) {
                FLOAT(0x1C) += 0.1f;
                FLOAT(0x20) += 0.1f;
            }
            else {
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                ++FIELD(short, 0xD8);
            }
        }
        if (FIELD(short, 0x62) < 4 && FIELD(short, 0xD8) > 0) {
            FLOAT(0x1C) = RecordedRange(0, 8) * 0.25f + 1.0;
            FLOAT(0x20) = FLOAT(0x1C);
        }
        if (FIELD(short, 0x62) == 4) {
            FLOAT(0x1C) *= 0.85f;
            FLOAT(0x20) = FLOAT(0x1C);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
            for (int burstIndex822 = 0; burstIndex822 < 5; ++burstIndex822) {
                OWNER_ACTOR->PlaySoundAt00453D40(2);
                OWNER_FLOAT(0x314) = 8 - burstIndex822 * 4;
                OWNER_ACTOR->SpawnEffect(823, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            }
        }
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
            OWNER_ACTOR->SpawnEffect(824, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            OWNER_ACTOR->SetCameraShakeAt00453E60(4.0f);
        }
        break;

case 823:
        if (OWNER(short, 0x60) == 607 || OWNER(short, 0x60) == 609) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 105;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 145.0f;
        }
        if (OWNER(short, 0x60) != 607 && OWNER(short, 0x60) != 609) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 0.1f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = FLOAT(0xC8);
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x62) == 1) {
            FLOAT(0x1C) += 0.2f;
            FLOAT(0x20) += 0.0025f;
        }
        if (FIELD(short, 0x62) == 2) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) *= 0.85f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) FLOAT(0x20) += 3.0f;
        break;

case 824:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x2C) = 70.0f;
            FIELD(short, 0x1A) = 1250;
            FLOAT(0x30) = RecordedRange(0, 359);
        }
        FLOAT(0x1C) += 0.2f;
        FLOAT(0x20) += 0.2f;
        if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
        else { ClearField74(); return; }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;



case 825:
        if (OWNER(short, 0x60) == 608 || OWNER(short, 0x60) == 610) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 105;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 145.0f;
        }
        if (OWNER(short, 0x60) != 608 && OWNER(short, 0x60) != 610) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.2f;
            FLOAT(0x20) = 0.2f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x80) = 3;
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(int, 0x7C) == 6) FIELD(int, 0x7C) = 0;
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0xD8) == 0) {
            if (FLOAT(0x1C) < 1.0f) {
                FLOAT(0x1C) += 0.1f;
                FLOAT(0x20) += 0.1f;
            }
            else {
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                ++FIELD(short, 0xD8);
            }
        }
        if (FIELD(short, 0x62) < 6 && FIELD(short, 0xD8) > 0) {
            FLOAT(0x1C) = RecordedRange(0, 8) * 0.25f + 1.0;
            FLOAT(0x20) = FLOAT(0x1C);
        }
        if (FIELD(short, 0x62) == 6) {
            FLOAT(0x1C) *= 0.85f;
            FLOAT(0x20) = FLOAT(0x1C);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
            for (int burstIndex825 = 0; burstIndex825 < 5; ++burstIndex825) {
                OWNER_ACTOR->PlaySoundAt00453D40(2);
                OWNER_FLOAT(0x314) = 8 - burstIndex825 * 4;
                OWNER_ACTOR->SpawnEffect(826, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            }
        }
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
            OWNER_ACTOR->SpawnEffect(824, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            OWNER_ACTOR->SetCameraShakeAt00453E60(4.0f);
            FIELD(int, 0x7C) = 0;
        }
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
            OWNER_ACTOR->SpawnEffect(824, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            OWNER_ACTOR->SetCameraShakeAt00453E60(4.0f);
            FIELD(int, 0x7C) = 0;
        }
        if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) {
            OWNER_ACTOR->SpawnEffect(824, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
            OWNER_ACTOR->SetCameraShakeAt00453E60(4.0f);
            FIELD(int, 0x7C) = 0;
        }
        break;

case 826:
        if (OWNER(short, 0x60) == 608 || OWNER(short, 0x60) == 610) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 105;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 145.0f;
        }
        if (OWNER(short, 0x60) != 608 && OWNER(short, 0x60) != 610) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 0.1f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = FLOAT(0xC8);
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x62) == 1) {
            FLOAT(0x1C) += 0.2f;
            FLOAT(0x20) += 0.0025f;
        }
        if (FIELD(short, 0x62) > 1) {
            FLOAT(0x1C) += 0.1f;
            FLOAT(0x20) *= 0.85f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) FLOAT(0x20) += 3.0f;
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) FLOAT(0x20) += 3.0f;
        if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) FLOAT(0x20) += 3.0f;
        break;




case 827:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.8f;
            FLOAT(0x20) = 0.8f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 1;
            FLOAT(0x54) = 6.0f;
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

case 828:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.8f;
            FLOAT(0x20) = 0.8f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 1;
            FLOAT(0x54) = 6.0f;
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

case 829:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.8f;
            FLOAT(0x20) = 0.8f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 1;
            FLOAT(0x54) = 6.0f;
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

case 830:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        else if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 2) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex830 = 0; rewardIndex830 < 3; ++rewardIndex830)
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
                FIELD(short, 0xD8) = 100;
            }
            --FIELD(short, 0xD8);
            if (FIELD(short, 0xD8) < 0) FIELD(short, 0xD8) = 0;
            SetPolarVelocity(0.0f, FIELD(short, 0xD8) * FLOAT(0xCC) * 0.01f);
            if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) == 1) { ResetSecondaryCounters(2); return; }
            else {
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
                    ClearField74(); return;
                }
                else {
                    if (FIELD(short, 0x62) > 1) {
                        if (FIELD(unsigned char, 0x11) >= 25) FIELD(unsigned char, 0x11) -= 25;
                        else FIELD(unsigned char, 0x11) = 0;
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;

case 831:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 4) {
            ClearField74();
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            return;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0x80) = 0;
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDC) = 0;
        }
        if (FIELD(short, 0x62) < 3) {
            SetPolarVelocity(OWNER(short, 0xF0E) * 2 + FLOAT(0xC8), FIELD(short, 0xD8));
            FIELD(short, 0xD8) = FIELD(short, 0xD8) + 10;
            if (FIELD(short, 0xD8) > 80) FIELD(short, 0xD8) = 80;
            FLOAT(0x44) = FLOAT(0x50) + FLOAT(0xCC);
            FLOAT(0x48) = FLOAT(0x54) + FLOAT(0xD0);
            if ((OWNER(short, 0x60) == 611 || OWNER(short, 0x60) == 612 || OWNER(short, 0x60) == 613) && OWNER(short, 0x62) == 0) {
                ResetSecondaryCounters(3);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                return;
            }
        }
        OWNER_ACTOR->SpawnEffect(827, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
            FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.5f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
            if (FIELD(short, 0xDC) < 5) {
                ResetSecondaryCounters(1);
                ++FIELD(short, 0xDC);
            }
            else FIELD(short, 0xDC) = 0;
        }
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
            if (FIELD(short, 0xDC) < 15) {
                ++FIELD(short, 0xDC);
                ResetSecondaryCounters(2);
                return;
            }
            else { ClearField74(); return; }
        }
        break;



case 832:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
            ClearField74(); return;
        }
        if ((OWNER(short, 0x60) != 704 || (OWNER(short, 0x60) == 704 && OWNER(short, 0x62) > 9)) && FIELD(short, 0x62) < 2)
            FLOAT(0xD0) *= 0.9f;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 3;
            FIELD(int, 0x7C) = 0;
            SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
            FIELD(short, 0xD8) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (FIELD(short, 0x62) < 2) FLOAT(0xC8) = FLOAT(0xD0) * 0.1f + FLOAT(0xC8);
        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
        FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) >= 5) FIELD(unsigned char, 0x11) -= 5;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 50) {
            ResetSecondaryCounters(1);
            FIELD(int, 0x7C) = 0;
            ++FIELD(short, 0xD8);
        }
        break;

case 833:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) {
            ClearField74(); return;
        }
        if ((OWNER(short, 0x60) != 704 || (OWNER(short, 0x60) == 704 && OWNER(short, 0x62) > 9)) && FIELD(short, 0x62) < 2)
            FLOAT(0xD0) *= 0.75f;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 3;
            FIELD(int, 0x7C) = 0;
            SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
            FIELD(short, 0xD8) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (FIELD(short, 0x62) < 2) FLOAT(0xC8) = FLOAT(0xD0) * 0.1f + FLOAT(0xC8);
        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
        FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) >= 5) FIELD(unsigned char, 0x11) -= 5;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 50) {
            ResetSecondaryCounters(1);
            FIELD(int, 0x7C) = 0;
            ++FIELD(short, 0xD8);
        }
        break;

case 834:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        else if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 38) {
            ClearField74();
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            for (int rewardIndex834 = 0; rewardIndex834 < 3; ++rewardIndex834)
                OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 2;
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
            if (FIELD(short, 0x62) < 38) SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.1f + FLOAT(0xCC));
            if (FIELD(int, 0x7C) == 4 && FIELD(short, 0x80) > 0) FIELD(int, 0x7C) = 0;
            if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) < 38) {
                ResetSecondaryCounters(38);
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
                    if (FIELD(short, 0x62) > 37) {
                        if (FIELD(unsigned char, 0x11) >= 15) {
                            FIELD(unsigned char, 0x11) -= 15;
                            FLOAT(0x1C) *= 0.9f;
                            FLOAT(0x20) = FLOAT(0x1C);
                        }
                        else { ClearField74(); return; }
                    }
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        if (FIELD(short, 0x62) == 38 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(21);
        break;

case 835:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 40.0f;
            FLOAT(0x2C) = FIELD(signed char, 0x66) * -40;
            FLOAT(0x30) = RecordedRange(0, 359);
        }
        FLOAT(0x1C) += 0.05f;
        FLOAT(0x20) += 0.05f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 836:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 3) ResetSecondaryCounters(3);
        if (OWNER(short, 0x60) == 706 && OWNER(short, 0x62) == 0 && FIELD(short, 0x62) < 3) ResetSecondaryCounters(3);
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 0.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        --FIELD(short, 0xDA);
        if (FIELD(short, 0x62) == 2) {
            FLOAT(0x50) = 0.0f;
            if (OPPONENT_FLOAT(0x44) + 40.0f < FLOAT(0x44)) FLOAT(0x50) = FIELD(signed char, 0x66) * -2;
            if (OPPONENT_FLOAT(0x44) - 40.0f > FLOAT(0x44)) FLOAT(0x50) = FIELD(signed char, 0x66) * 2;
        }
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0xDA) < 0) {
            OWNER_FLOAT(0x314) = -RecordedRange(0, 80) - 50;
            OWNER_FLOAT(0x318) = RecordedRange(0, 18) + 15;
            OWNER_ACTOR->SpawnEffect(837, (100 - RecordedRange(0, 200)) * FIELD(signed char, 0x66) + FLOAT(0x44),
                FLOAT(0x48), FIELD(signed char, 0x66), 1);
            FIELD(short, 0xDA) = 1;
        }
        if (FIELD(short, 0x62) == 3) {
            if (FIELD(unsigned char, 0x11) > 13) FIELD(unsigned char, 0x11) -= 13;
            else FIELD(unsigned char, 0x11) = 0;
        }
        if (FIELD(short, 0x62) < 2) {
            FLOAT(0x1C) += 0.8f;
            FLOAT(0x20) += 0.1f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) OWNER_ACTOR->PlaySoundAt00453D40(7);
        break;

case 837:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
        }
        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
        if (FIELD(short, 0x62) < 2 && FLOAT(0xCC) == 2.0f) ResetSecondaryCounters(2);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        OWNER_ACTOR->SpawnEffect(805, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
            FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.5f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 30) {
            ResetSecondaryCounters(2);
            ++FIELD(short, 0xD8);
        }
        break;

case 838:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 4) {
            ClearField74();
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            OWNER_ACTOR->SpawnEffect(996, FLOAT(0x44), FLOAT(0x48), 1, 1);
            if (OWNER(short, 0xEFA) > 25) {
                OWNER(short, 0xEFA) = 0;
                OWNER_ACTOR->SpawnEffect(995, FLOAT(0x44), FLOAT(0x48), 1, 1);
            }
            return;
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            if (OWNER(short, 0x60) == 613) FIELD(short, 0x80) = 1;
            else FIELD(short, 0x80) = 0;
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDC) = 0;
        }
        if (FIELD(short, 0x62) < 3) {
            SetPolarVelocity(OWNER(short, 0xF0E) * 2 + FLOAT(0xC8), FIELD(short, 0xD8));
            FIELD(short, 0xD8) = FIELD(short, 0xD8) + 10;
            if (FIELD(short, 0xD8) > 120) FIELD(short, 0xD8) = 120;
            FLOAT(0x44) = FLOAT(0x50) + FLOAT(0xCC);
            FLOAT(0x48) = FLOAT(0x54) + FLOAT(0xD0);
            if ((FIELD(short, 0x80) == 0 && OWNER(short, 0x60) != 611 && OWNER(short, 0x60) != 612) ||
                ((OWNER(short, 0x60) == 611 || OWNER(short, 0x60) == 612 || OWNER(short, 0x60) == 613) && OWNER(short, 0x62) == 0)) {
                ResetSecondaryCounters(3);
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                return;
            }
        }
        OWNER_ACTOR->SpawnEffect(827, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
            FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.5f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
            if (FIELD(short, 0xDC) < 5) {
                ResetSecondaryCounters(1);
                ++FIELD(short, 0xDC);
            }
            else FIELD(short, 0xDC) = 0;
        }
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) {
            if (FIELD(short, 0xDC) < 40) {
                ++FIELD(short, 0xDC);
                ResetSecondaryCounters(2);
                return;
            }
            else { ClearField74(); return; }
        }
        break;

case 839:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 4) {
            ClearField74();
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
            SetPolarVelocity(RecordedRange(0, 60) - 30, 4.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
        }
        if (FIELD(int, 0x7C) != 0) { ClearField74(); return; }
        if (OPPONENT_FLOAT(0x48) + 100.0f < FLOAT(0x48)) FLOAT(0x54) -= 0.02f;
        if (OPPONENT_FLOAT(0x48) + 100.0f >= FLOAT(0x48)) FLOAT(0x54) += 0.02f;
        FLOAT(0x50) += 0.05f;
        if (FIELD(short, 0xD8) <= 0) {
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0xD8) = 10;
        }
        --FIELD(short, 0xD8);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        if (FIELD(short, 0x64) == 0)
            OWNER_ACTOR->SpawnEffect(840, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
                FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.9f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.9f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            if (FIELD(short, 0xDC) < 60 && FIELD(short, 0x80) > 0) {
                ResetSecondaryCounters(1);
                ++FIELD(short, 0xDC);
            }
            else ClearField74();
        }
        break;



case 840:
        FIELD(unsigned char, 0x66) = OWNER(unsigned char, 0x66);
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
        FLOAT(0x54) -= 0.1f;
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        if (FIELD(unsigned char, 0x11) > 13) FIELD(unsigned char, 0x11) -= 13;
        else FIELD(unsigned char, 0x11) = 0;
        FLOAT(0x1C) *= 0.94f;
        FLOAT(0x20) *= 0.94f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;






case 841:
        if (OWNER(short, 0x60) == 309) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 20;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 40.0f;
        }
        if (OWNER(short, 0x60) != 309) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 2.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x1A) = 1250;
            FLOAT(0x28) = -70.0f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 842:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
        }
        SetPolarVelocity(OWNER(short, 0xF0E) + 45.0f * FLOAT(0xC8), 140.0f);
        FLOAT(0x44) = FLOAT(0x50) + OPPONENT_FLOAT(0x44);
        FLOAT(0x48) = FLOAT(0x54) * 0.5f + OPPONENT_FLOAT(0x48) + 100.0f;
        if (FLOAT(0x54) > 0.0f) FLOAT(0x4C) = -5.0f;
        else FLOAT(0x4C) = 5.0f;
        if (FIELD(short, 0x62) < 21) {
            if (OPPONENT(short, 0x324) > 2) OPPONENT(short, 0x324) = OPPONENT(short, 0x324) - 1;
            if (OPPONENT(short, 0x3A0) > 0 && OPPONENT(short, 0x326) > 2) OPPONENT(short, 0x326) = OPPONENT(short, 0x326) - 1;
            if (FIELD(unsigned char, 0x11) < 235) FIELD(unsigned char, 0x11) += 20;
            else FIELD(unsigned char, 0x11) = 255;
        }
        if ((OPPONENT(short, 0x324) <= 0 || OWNER(short, 0x3A0) <= 0 || OWNER(short, 0x324) <= 0 || OWNER(short, 0xF0C) == 0 ||
            (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150)) && FIELD(short, 0x62) < 21) {
            ResetSecondaryCounters(FIELD(short, 0x62) + 20);
            --OWNER(short, 0xF0C);
            if (OWNER(short, 0xF0C) < 0) OWNER(short, 0xF0C) = 0;
        }
        if (FIELD(short, 0x62) > 20) {
            if (FIELD(unsigned char, 0x11) > 10) FIELD(unsigned char, 0x11) -= 10;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) { ResetSecondaryCounters(21); return; }
        if (FIELD(short, 0x62) == 21 && FIELD(short, 0x64) == 0) {
            if (FIELD(short, 0xD8) - 1 < FLOAT(0xC8) * 5.0f) {
                ResetSecondaryCounters(1);
                ++FIELD(short, 0xD8);
            }
            else {
                --OWNER(short, 0xF0C);
                if (OWNER(short, 0xF0C) < 0) OWNER(short, 0xF0C) = 0;
            }
        }
        break;

case 843:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0xDC) = AngleAt00483300(OPPONENT_FLOAT(0x48) + 128.0f - FLOAT(0x48),
                (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828;
            if (FIELD(short, 0xDC) < -40) FIELD(short, 0xDC) = -40;
            if (FIELD(short, 0xDC) > 40) FIELD(short, 0xDC) = 40;
        }
        if (FIELD(short, 0x62) < 3) SetPolarVelocity(FIELD(short, 0xDC), 20.0f);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FIELD(short, 0x62) < 3)
            OWNER_ACTOR->SpawnEffect(809, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
                FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
        if (FIELD(int, 0x7C) == 6) {
            ++FIELD(short, 0x80);
            FIELD(int, 0x7C) = 0;
        }
        if (FIELD(short, 0x62) == 2 && FIELD(int, 0x7C) == 1) {
            UnknownAt0045B850(14);
            ResetSecondaryCounters(3);
            FLOAT(0x50) = 0.0f;
            FLOAT(0x54) = 0.0f;
            OWNER(short, 0xF0C) = 0;
            return;
        }
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(int, 0x7C) == 1) {
            for (int burstIndex843 = 0; burstIndex843 < 8; ++burstIndex843) {
                OWNER_FLOAT(0x314) = burstIndex843;
                OWNER_ACTOR->SpawnEffect(842, OPPONENT_FLOAT(0x44), OPPONENT_FLOAT(0x48) + 100.0f, 1, 1);
                ++OWNER(short, 0xF0C);
            }
        }
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 0.5f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
        break;

case 844:
        if (OWNER(short, 0x60) == 300) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48);
        }
        if (OWNER(short, 0x60) != 300) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (OWNER(short, 0x82) == 0 && AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        return;

case 845:
        if (OWNER(short, 0x60) == 302) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48);
        }
        if (OWNER(short, 0x60) != 302 || (OWNER(short, 0x60) == 302 && OWNER(short, 0x62) == 0)) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (OWNER(short, 0x82) == 0 && AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        return;


case 846:
        if (OWNER(short, 0x60) == 305) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48);
        }
        if (OWNER(short, 0x60) != 305) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (OWNER(short, 0x82) == 0 && AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        return;

case 847:
        if ((OWNER(short, 0x60) == 303 || OWNER(short, 0x60) == 393)) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48);
        }
        if ((OWNER(short, 0x60) != 303 && OWNER(short, 0x60) != 393)) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (OWNER(short, 0x82) == 0 && AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        return;


case 899:
        FIELD(unsigned char, 0x66) = OWNER(unsigned char, 0x66);
        if (OWNER(short, 0x60) > 149 && OWNER(short, 0x60) < 154 && FIELD(short, 0x62) == 0) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + float(FIELD(signed char, 0x66) * 57);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 94.0f;
        }
        if (OWNER(short, 0x60) > 153 && OWNER(short, 0x60) < 158 && FIELD(short, 0x62) == 0) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + float(FIELD(signed char, 0x66) * 57);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 60.0f;
        }
        if (OWNER(short, 0x60) == 158 && FIELD(short, 0x62) == 0) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + float(FIELD(signed char, 0x66) * 57);
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        }
        if ((OWNER(short, 0x60) < 150 || OWNER(short, 0x60) > 158) && FIELD(short, 0x62) == 0) {
            ResetSecondaryCounters(1);
            OWNER(short, 0xF0A) = 0;
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
        return;

case 900:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 3;
            FIELD(int, 0x7C) = 0;
            SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
            FIELD(short, 0xDC) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
        FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
        if (FIELD(short, 0xD8) == 0) {
            FLOAT(0xCC) -= 0.2f;
            if (FLOAT(0xCC) < 1.0) {
                FLOAT(0xCC) = 1.0f;
                FIELD(short, 0xD8) = 1;
                ResetSecondaryCounters(2);
            }
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FIELD(short, 0x62) > 2) {
            if (FIELD(unsigned char, 0x11) >= 5) FIELD(unsigned char, 0x11) -= 5;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
            FIELD(int, 0x7C) = 0;
            ResetSecondaryCounters(1);
        }
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < g_F1212_DifficultyAt006714D0 * 2) {
            ResetSecondaryCounters(2);
            FIELD(int, 0x7C) = 0;
            ++FIELD(short, 0xD8);
        }
        break;

case 902:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 0.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
        }
        --FIELD(short, 0xDA);
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0xDA) < 0) {
            OWNER_FLOAT(0x314) = -RecordedRange(0, 40) - 70;
            OWNER_FLOAT(0x318) = RecordedRange(0, 6) + 15;
            OWNER_ACTOR->SpawnEffect(903, (10 - RecordedRange(0, 20)) * FIELD(signed char, 0x66) + FLOAT(0x44),
                FLOAT(0x48), FIELD(signed char, 0x66), 1);
            if (g_F1212_DifficultyAt006714D0 == 3 && RecordedRange(0, 100) < 20)
                OWNER_ACTOR->SpawnEffect(904, (10 - RecordedRange(0, 20)) * FIELD(signed char, 0x66) + FLOAT(0x44),
                    FLOAT(0x48), FIELD(signed char, 0x66), 1);
            FIELD(short, 0xDA) = 3;
        }
        if (FIELD(short, 0x62) == 3) {
            if (FIELD(unsigned char, 0x11) > 13) FIELD(unsigned char, 0x11) -= 13;
            else FIELD(unsigned char, 0x11) = 0;
        }
        if (FIELD(short, 0x62) < 2 && FIELD(short, 0x64) < 10) {
            FLOAT(0x1C) += 0.4f;
            FLOAT(0x20) += 0.1f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) OWNER_ACTOR->PlaySoundAt00453D40(7);
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 0) {
            ResetSecondaryCounters(2);
            ++FIELD(short, 0xD8);
        }
        break;

case 903:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
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
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
        }
        SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
        if (FIELD(short, 0x62) < 2 && FLOAT(0xCC) == 2.0f) ResetSecondaryCounters(2);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        --FIELD(short, 0xDA);
        if (FIELD(short, 0xDA) <= 0) {
            OWNER_ACTOR->SpawnEffect(805, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
                FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
            FIELD(short, 0xDA) = 4;
        }
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.01f + 1.0f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.01f + 1.0f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 30) {
            ResetSecondaryCounters(2);
            ++FIELD(short, 0xD8);
        }
        break;

case 904:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
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
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0xC8) = -RecordedRange(0, 90) - 30;
            FLOAT(0xCC) = RecordedRange(0, 9) + 8;
            SetPolarVelocity(FLOAT(0xC8), FLOAT(0xCC));
            FLOAT(0x50) = RecordedRange(0, 10) - 3;
            FLOAT(0x54) = RecordedRange(0, 10) + 5;
        }
        if (FIELD(short, 0x62) == 2) {
            FLOAT(0x54) -= 0.4f;
            if (FLOAT(0x54) < -4.0f) FLOAT(0x54) = -4.0f;
            if (FLOAT(0x48) + FLOAT(0x54) <= 0.0f) {
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
                ResetSecondaryCounters(3);
            }
        }
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) += FLOAT(0x54);
        --FIELD(short, 0xDC);
        if (FIELD(short, 0xDC) <= 0) {
            OWNER_ACTOR->SpawnEffect(805, FLOAT(0x44) - 10.0f + RecordedRange(0, 20),
                FLOAT(0x48) - 10.0f + RecordedRange(0, 20), FIELD(signed char, 0x66), 1);
            FIELD(short, 0xDC) = 2;
        }
        if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) == 2) { ResetSecondaryCounters(3); return; }
        if (FIELD(short, 0x64) == 0) {
            FIELD(short, 0xDA) = RecordedRange(0, 20);
            FLOAT(0x1C) = FIELD(short, 0xDA) * 0.02f + 0.9f;
            FLOAT(0x20) = FIELD(short, 0xDA) * 0.02f + 0.9f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 15) {
            ++FIELD(short, 0xD8);
            ResetSecondaryCounters(1);
        }
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
        break;





case 905:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.5f;
            FLOAT(0x20) = 0.5f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
            UnknownAt0045B850(6);
            if (g_F1212_DifficultyAt006714D0 <= 1 && FIELD(short, 0xD8) < 5)
                OWNER_ACTOR->SpawnEffect(902, FIELD(short, 0xD8) * 300 + RecordedRange(0, 50),
                    0.0f, FIELD(signed char, 0x66), 1);
            if (g_F1212_DifficultyAt006714D0 == 2 && FIELD(short, 0xD8) < 5)
                OWNER_ACTOR->SpawnEffect(902, FIELD(short, 0xD8) * 270 + RecordedRange(0, 50),
                    0.0f, FIELD(signed char, 0x66), 1);
            if (g_F1212_DifficultyAt006714D0 == 3 && FIELD(short, 0xD8) < 6)
                OWNER_ACTOR->SpawnEffect(902, FIELD(short, 0xD8) * 240 + RecordedRange(0, 50),
                    0.0f, FIELD(signed char, 0x66), 1);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) < 13) {
            ++FIELD(short, 0xD8);
            ResetSecondaryCounters(1);
        }
        break;

case 906:
        if (FIELD(short, 0x62) < 3) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48);
        }
        if (OWNER(short, 0x60) != 760 && OWNER(short, 0x60) != 761 && FIELD(short, 0x62) < 3) { ResetSecondaryCounters(3); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 150.0f, 0.0f);
            FLOAT(0x1C) = 0.0f;
            FLOAT(0x20) = 0.05f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x62) == 0) {
            FLOAT(0x1C) += 0.1f;
            if (FLOAT(0x1C) > 1.0f) FLOAT(0x1C) = 1.0f;
        }
        if (FIELD(short, 0x62) == 0) {
            g_F1239_DwordAt0067149C = 0xFFFFFF;
            if (FIELD(short, 0xD8) == 0) {
                g_F1239_ByteAt006714D1 = 255;
                FIELD(short, 0xD8) = 1;
            }
            if (FIELD(short, 0xD8) == 1) {
                if (g_F1239_ByteAt006714D1 > 15) g_F1239_ByteAt006714D1 -= 15;
                else {
                    g_F1239_ByteAt006714D1 = 0;
                    FIELD(short, 0xD8) = 2;
                }
            }
        }
        if (FIELD(short, 0x62) == 1) {
            FLOAT(0x20) += 0.1f;
            if (FLOAT(0x20) > 1.0f) FLOAT(0x20) = 1.0f;
        }
        if (FIELD(short, 0x62) == 3) {
            if (FIELD(unsigned char, 0x11) > 25) FIELD(unsigned char, 0x11) -= 25;
            else { ClearField74(); return; }
        }
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
            ResetSecondaryCounters(2);
            OWNER_ACTOR->SpawnEffect(907, FLOAT(0x44), FLOAT(0x48), 1, 0);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) OWNER(short, 0xF04) = 1;
        if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
        break;

case 907:
        if (FIELD(short, 0x62) < 3) {
            FLOAT(0x44) = OWNER_FLOAT(0x44);
            FLOAT(0x48) = OWNER_FLOAT(0x48);
        }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 150.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (FIELD(short, 0x62) == 0) {
            FLOAT(0x1C) += 0.01f;
            FLOAT(0x20) += 0.01f;
            if (FIELD(unsigned char, 0x11) > 25) FIELD(unsigned char, 0x11) -= 25;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 908:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = FLOAT(0xC8);
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 256;
            FIELD(int, 0x7C) = 0;
            SetPolarVelocity(FIELD(short, 0xDA), FIELD(short, 0xD8) * 0.1f + 5.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (FIELD(int, 0x7C) == 6) {
            FIELD(int, 0x7C) = 0;
            ++FIELD(short, 0x80);
        }
        ++FIELD(short, 0xD8);
        SetPolarVelocity(FIELD(short, 0xDA), FIELD(short, 0xD8) * 0.1f + 5.0f);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f || FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) { ClearField74(); return; }
        if (FIELD(unsigned char, 0x11) > 20 && FIELD(short, 0x62) == 2) FIELD(unsigned char, 0x11) -= 20;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ResetSecondaryCounters(1);
            FIELD(int, 0x7C) = 0;
            return;
        }
        break;

case 909:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = FLOAT(0xC8);
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            SetPolarVelocity(FLOAT(0xC8), 1.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (FIELD(short, 0x62) < 2) FLOAT(0xC8) += 1.0f;
        ++FIELD(short, 0xD8);
        SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.05f);
        if (FIELD(short, 0x62) == 1) SetPolarVelocity(FLOAT(0xC8), 1.0f);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
        if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f || FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) { ClearField74(); return; }
        if (FIELD(int, 0x7C) != 0 && FIELD(short, 0x62) < 3) { ResetSecondaryCounters(3); return; }
        if (FIELD(unsigned char, 0x11) > 20 && FIELD(short, 0x62) == 3) FIELD(unsigned char, 0x11) -= 20;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0) {
            FIELD(int, 0x7C) = 0;
            FIELD(short, 0xD8) = 0;
            FLOAT(0xC8) = AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828;
        }
        break;

case 910:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x30) = FLOAT(0xCC);
            if (FLOAT(0xCC) > 0.0f && FLOAT(0xCC) < 180.0f)
                FLOAT(0x1C) = FLOAT(0x48) / MathLookup::ReadPhaseTable(FLOAT(0xCC)) / 256.0f * 1.1f;
            else FLOAT(0x1C) = 6.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xD8) = 0;
        }
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 5 && FLOAT(0xCC) > 0.0f && FLOAT(0xCC) < 180.0f)
            OWNER_ACTOR->SpawnEffect(911, MathLookup::ReadRatio(90.0f - FLOAT(0xCC)) * FLOAT(0x48) + 640.0f, 0.0f, 1, 1);
        FLOAT(0x20) *= 0.85;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 911:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x54) = 0.0f;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 0.0f;
            FLOAT(0x2C) = 0.0f;
            FLOAT(0x30) = 0.0f;
        }
        if (FIELD(int, 0x7C) == 6) {
            FIELD(int, 0x7C) = 0;
            ++FIELD(short, 0x80);
        }
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0)
            OWNER_ACTOR->SpawnEffect(912, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
        if (FIELD(short, 0x62) < 3) {
            FLOAT(0x1C) += 0.07f;
            FLOAT(0x20) += 0.07f;
        }
        if (FIELD(short, 0x62) == 4) {
            FLOAT(0x1C) *= 0.85f;
            if (FIELD(unsigned char, 0x11) >= 15) FIELD(unsigned char, 0x11) -= 15;
            else { FIELD(unsigned char, 0x11) = 0; ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;








case 912:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x1A) = 1250;
            FLOAT(0x28) = -75.0f;
        }
        FLOAT(0x1C) += 0.15f;
        FLOAT(0x20) += 0.15f;
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 913:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x30) = FLOAT(0xCC);
            if (FLOAT(0xCC) > 0.0f && FLOAT(0xCC) < 180.0f)
                FLOAT(0x1C) = FLOAT(0x48) / MathLookup::ReadPhaseTable(FLOAT(0xCC)) / 256.0f * 1.1f;
            else FLOAT(0x1C) = 6.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 5 && FLOAT(0xCC) > 0.0f && FLOAT(0xCC) < 180.0f)
            OWNER_ACTOR->SpawnEffect(914, MathLookup::ReadRatio(90.0f - FLOAT(0xCC)) * FLOAT(0x48) + 640.0f, 0.0f, 1, 1);
        FLOAT(0x20) *= 0.85;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 914:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
            FLOAT(0x54) = 0.0f;
            FLOAT(0x50) = 0.0f;
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 0.0f;
            FLOAT(0x2C) = 0.0f;
            FLOAT(0x30) = 0.0f;
        }
        if (FIELD(int, 0x7C) == 6) {
            FIELD(int, 0x7C) = 0;
            ++FIELD(short, 0x80);
        }
        if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0)
            OWNER_ACTOR->SpawnEffect(915, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 1);
        if (FIELD(short, 0x62) < 3) {
            FLOAT(0x1C) += 0.07f;
            FLOAT(0x20) += 0.07f;
        }
        if (FIELD(short, 0x62) == 4) {
            FLOAT(0x1C) *= 0.85f;
            if (FIELD(unsigned char, 0x11) >= 15) FIELD(unsigned char, 0x11) -= 15;
            else { FIELD(unsigned char, 0x11) = 0; ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;



case 915:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.25f;
            FLOAT(0x20) = 0.25f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x1A) = 1250;
            FLOAT(0x28) = -75.0f;
        }
        FLOAT(0x1C) += 0.15f;
        FLOAT(0x20) += 0.15f;
        if (FIELD(short, 0x62) > 1) {
            if (FIELD(unsigned char, 0x11) > 20) FIELD(unsigned char, 0x11) -= 20;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 916:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
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
        }
        ++FIELD(short, 0xD8);
        FLOAT(0xC8) += FLOAT(0xD0);
        SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.2f + FLOAT(0xCC));
        FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) { ClearField74(); return; }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 917:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
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
        }
        ++FIELD(short, 0xD8);
        FLOAT(0xC8) += FLOAT(0xD0);
        SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.2f + FLOAT(0xCC));
        FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) { ClearField74(); return; }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 918:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
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
        }
        ++FIELD(short, 0xD8);
        FLOAT(0xC8) += FLOAT(0xD0);
        SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.2f + FLOAT(0xCC));
        FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        FLOAT(0x48) -= FLOAT(0x54);
        if (FLOAT(0x44) > 1380.0f || FLOAT(0x44) < -100.0f || FLOAT(0x48) > 640.0f || FLOAT(0x48) < -120.0f) { ClearField74(); return; }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

case 919:
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(short, 0xD8) = 0;
            FIELD(short, 0xDA) = 0;
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            if (FIELD(short, 0xD8) < 2 - g_F1212_DifficultyAt006714D0) ++FIELD(short, 0xD8);
            else {
                OWNER_ACTOR->SpawnEffect(904, RecordedRange(0, 1200) + 60, RecordedRange(0, 120) + 700,
                    1 - (RecordedRange(0, 100) < 50) * 2, 1);
                FIELD(short, 0xD8) = 0;
            }
            ResetSecondaryCounters(2);
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
                ResetSecondaryCounters(9);
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
