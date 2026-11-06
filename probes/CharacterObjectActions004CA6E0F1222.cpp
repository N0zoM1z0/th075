// Incomplete research toward original 004CA6E0 (42,511 CODE bytes).
// Only reviewed states are present; this is NONEXACT and not a replacement.
#include "ObjectAdvance4CA6E0F1222.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OWNER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset)))
#define OPPONENT(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset))
#define OWNER_ACTOR reinterpret_cast<OwnerActor4CA6E0F1222*>(FIELD(void*, 0xE4))

extern float g_F1211_AngleDivAt00657828;

void ObjectActor4CA6E0F1222::AdvanceAction()
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
        else if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150 && FIELD(short, 0x62) < 5) {
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
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0x80) = 1;
                FLOAT(0x50) = 0.0f;
                FLOAT(0x54) = 0.0f;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) -= FLOAT(0x54);
            ++FIELD(short, 0xD8);
            if (FIELD(short, 0x62) < 4) {
                SetPolarVelocity(FLOAT(0xC8), FIELD(short, 0xD8) * 0.5f + FLOAT(0xCC));
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
                OWNER_FLOAT(0x310) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
                OWNER(unsigned char, 0x2F0) = 0;
                OWNER(short, 0x2F6) = 0;
                OWNER(short, 0x2F8) = 0;
                OWNER(short, 0x2FA) = 0;
                OWNER_FLOAT(0x2FC) = 1.0f;
                OWNER_FLOAT(0x300) = 1.0f;
                OWNER(unsigned char, 0x2F1) = 255;
                OWNER(unsigned char, 0x2F2) = 255;
                OWNER(unsigned char, 0x2F3) = 255;
                OWNER(unsigned char, 0x2F4) = 255;
                OWNER_FLOAT(0x308) = 0.0f;
                OWNER_FLOAT(0x30C) = 0.0f;
                OWNER_ACTOR->SpawnTrackedEffectAt00453AC0(813, FLOAT(0x44), FLOAT(0x48), FIELD(signed char, 0x66), 0, 1);
            }
            if ((FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4) && FIELD(short, 0x62) == 0) {
                ResetSecondaryCounters(6);
                return;
            }
            else if (FLOAT(0x44) > 1400.0f || FLOAT(0x44) < -160.0f || FLOAT(0x48) > 1000.0f || FLOAT(0x48) < -160.0f) {
                ClearField74();
                return;
            }
            else {
                if (FIELD(short, 0x62) == 6 && FIELD(short, 0x64) == 0) {
                    FLOAT(0x50) = -FLOAT(0x50) * 0.25;
                    FLOAT(0x54) = -14.0f;
                }
                if (FIELD(short, 0x62) == 6) {
                    FLOAT(0x54) += 0.5f;
                    FLOAT(0x30) += 40.0f;
                }
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                if (FIELD(short, 0x62) == 4 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(0);
                if (FIELD(short, 0x62) == 7 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(6);
            }
        }
        break;

    case 801:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = RecordedRange(0, 7) * 0.1f + 1.0f;
            FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = RecordedRange(0, 50) + 30 + (RecordedRange(0, 100) < 50) * 180;
            FLOAT(0x30) = RecordedRange(0, 60);
            FLOAT(0x2C) = (RecordedRange(0, 90) - 25) * FIELD(signed char, 0x66);
            FIELD(short, 0xDA) = RecordedRange(0, 2);
        }
        FLOAT(0x44) = FIELD(short, 0xDA) * 6.0f * FIELD(signed char, 0x66) + FLOAT(0x44);
        FLOAT(0x1C) += 0.1f;
        FLOAT(0x20) += 0.02f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 802:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            FIELD(short, 0xD8) = 0;
            EnableTransform(0.0f, 0.0f, 0.0f);
            FIELD(int, 0x7C) = 0;
            FLOAT(0x1C) = RecordedRange(0, 9) * 0.1f + 1.7f;
            FIELD(unsigned int, 0x20) = FIELD(unsigned int, 0x1C);
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = RecordedRange(0, 50) + 30 + (RecordedRange(0, 100) < 50) * 180;
            FLOAT(0x30) = RecordedRange(0, 60);
            FLOAT(0x2C) = (RecordedRange(0, 90) - 25) * FIELD(signed char, 0x66);
        }
        FLOAT(0x1C) += 0.02f;
        FLOAT(0x1C) += 0.5f;
        FLOAT(0x20) += 0.02f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 803:
        if (FIELD(int, 0x7C) == 5) { ClearField74(); return; }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                FIELD(short, 0xD8) = 0;
                FIELD(short, 0xDA) = 0;
                FIELD(short, 0xDC) = 0;
                EnableTransform(0.0f, 0.0f, 0.0f);
                FLOAT(0x1C) = 1.0f;
                FLOAT(0x20) = 1.0f;
                FIELD(unsigned char, 0x11) = 0;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
            }
            if (FIELD(short, 0x62) == 2 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FIELD(short, 0xDC) = static_cast<short>(AngleAt00483300(OPPONENT_FLOAT(0x48) + 100.0f - FLOAT(0x48),
                    (OPPONENT_FLOAT(0x44) - FLOAT(0x44)) * FIELD(signed char, 0x66)) / g_F1211_AngleDivAt00657828);
                ++FIELD(short, 0xD8);
            }
            if (FIELD(short, 0x62) < 2) {
                FLOAT(0x30) += 15.0f;
                SetPolarVelocity(FLOAT(0xC8), 4.5f);
            }
            if (FIELD(short, 0x62) > 1) {
                ++FIELD(short, 0xDA);
                SetPolarVelocity(FIELD(short, 0xDC), FIELD(short, 0xDA));
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
                FLOAT(0x1C) += 0.5f;
            }
            FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
            FLOAT(0x48) -= FLOAT(0x54);
            if (FLOAT(0x44) > 1600.0f || FLOAT(0x44) < -400.0f || FLOAT(0x48) > 1400.0f || FLOAT(0x48) < -400.0f) {
                ClearField74();
                return;
            }
            else {
                if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(2);
                if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) FIELD(unsigned char, 0x11) = 255;
            }
        }
        break;

    case 804:
        if (OWNER(short, 0x60) == 307 || OWNER(short, 0x60) == 390) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 60;
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

    case 812:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = FLOAT(0xCC) * 0.2f + 0.25f;
            FLOAT(0x20) = 1.0f;
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

    case 813:
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

    case 814:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.3f;
            FLOAT(0x20) = 1.3f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (OWNER(short, 0xF0C) > 0) {
            if (FIELD(unsigned char, 0x11) < 245) FIELD(unsigned char, 0x11) += 10;
            else FIELD(unsigned char, 0x11) = 255;
        }
        if (OWNER(short, 0xF0C) <= 0) {
            if (FIELD(unsigned char, 0x11) > 5) FIELD(unsigned char, 0x11) -= 5;
            else { ClearField74(); return; }
        }
        FLOAT(0x30) += 0.25f;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
        break;

    case 815:
        FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 2.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xDA) = OWNER(short, 0xF0C);
        }
        FLOAT(0x1C) = static_cast<float>(OWNER(short, 0xF0C)) / FIELD(short, 0xDA) * 2;
        FLOAT(0x20) = static_cast<float>(OWNER(short, 0xF0C)) / FIELD(short, 0xDA) * 2;
        if (FIELD(short, 0x62) == 1 && OWNER(short, 0xF0C) > 0) {
            if (FIELD(unsigned char, 0x11) < 245) FIELD(unsigned char, 0x11) += 10;
            else {
                FIELD(unsigned char, 0x11) = 255;
                ResetSecondaryCounters(2);
                return;
            }
        }
        if (FIELD(short, 0x62) == 2 && OWNER(short, 0xF0C) <= 0) {
            ResetSecondaryCounters(3);
            return;
        }
        else if (FIELD(short, 0x62) == 3) { ClearField74(); return; }
        else {
            FLOAT(0x30) += 1.0f;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(3);
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
        }
        break;

    case 816:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.5f;
            FLOAT(0x20) = 1.5f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        if (OWNER(short, 0xF10) > 0) {
            if (FIELD(unsigned char, 0x11) < 245) FIELD(unsigned char, 0x11) += 10;
            else FIELD(unsigned char, 0x11) = 255;
        }
        if (OWNER(short, 0xF10) <= 0) {
            if (FIELD(unsigned char, 0x11) > 5) FIELD(unsigned char, 0x11) -= 5;
            else { ClearField74(); return; }
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(1);
        break;

    case 817:
        FIELD(signed char, 0x66) = OWNER(signed char, 0x66);
        if (OWNER(short, 0x60) > 149 && OWNER(short, 0x60) < 154) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 30;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 94.0f;
        }
        if (OWNER(short, 0x60) > 153 && OWNER(short, 0x60) < 158) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 70;
            FLOAT(0x48) = OWNER_FLOAT(0x48) + 60.0f;
        }
        if (OWNER(short, 0x60) == 158) {
            FLOAT(0x44) = OWNER_FLOAT(0x44) + FIELD(signed char, 0x66) * 57;
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
            FIELD(short, 0xD8) = 1;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
            ClearField74();
            OWNER(short, 0xF0A) = 0;
        }
        break;

    case 818:
        FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
        FLOAT(0x48) = OWNER_FLOAT(0x48) + 100.0f;
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0 && FIELD(short, 0xD8) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 2.0f;
            FLOAT(0x20) = 2.0f;
            FIELD(unsigned char, 0x11) = 0;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FIELD(short, 0xDA) = OWNER(short, 0xF10);
        }
        FLOAT(0x1C) = static_cast<float>(OWNER(short, 0xF10)) / FIELD(short, 0xDA) * 2;
        FLOAT(0x20) = static_cast<float>(OWNER(short, 0xF10)) / FIELD(short, 0xDA) * 2;
        if (FIELD(short, 0x62) == 1 && OWNER(short, 0xF10) > 0) {
            if (FIELD(unsigned char, 0x11) < 245) FIELD(unsigned char, 0x11) += 10;
            else {
                FIELD(unsigned char, 0x11) = 255;
                ResetSecondaryCounters(2);
                return;
            }
        }
        if (FIELD(short, 0x62) == 2 && OWNER(short, 0xF10) <= 0) {
            ResetSecondaryCounters(3);
            return;
        }
        else if (FIELD(short, 0x62) == 3) { ClearField74(); return; }
        else {
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(3);
            if (FIELD(short, 0x62) == 3 && FIELD(short, 0x64) == 0) ResetSecondaryCounters(2);
        }
        break;

    case 819:
        if (OWNER(short, 0x60) == 302) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (OWNER(short, 0x60) != 302) { ClearField74(); return; }
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
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 820:
        if (OWNER(short, 0x60) == 304) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (OWNER(short, 0x60) != 304) { ClearField74(); return; }
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
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 821:
        if (OWNER(short, 0x60) == 404 || OWNER(short, 0x60) == 405) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (OWNER(short, 0x60) != 404 && OWNER(short, 0x60) != 405) { ClearField74(); return; }
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
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 822:
        if (OWNER(short, 0x60) == 308) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (OWNER(short, 0x60) != 308) { ClearField74(); return; }
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
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
        break;

    case 823:
        if (OWNER(short, 0x60) == 310) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (OWNER(short, 0x60) != 310) { ClearField74(); return; }
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
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        }
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
            FLOAT(0x30) = RecordedRange(0, 90) - 45;
            FIELD(short, 0xD8) = RecordedRange(0, 10);
            FIELD(short, 0xDA) = RecordedRange(0, 10);
            FIELD(short, 0xDC) = RecordedRange(0, 10);
            FIELD(short, 0xDE) = RecordedRange(0, 5);
            FIELD(short, 0xE0) = RecordedRange(0, 5);
            FLOAT(0x50) = RecordedRange(0, 6) - 3;
            FLOAT(0x54) = -RecordedRange(0, 2);
        }
        FLOAT(0x54) -= 0.2f;
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        if (FIELD(short, 0xD8) < 5) FLOAT(0x30) = FIELD(short, 0xDE) + FLOAT(0x30);
        if (FIELD(short, 0xD8) > 4) FLOAT(0x30) -= FIELD(short, 0xDE);
        if (FIELD(short, 0xDA) < 5) FLOAT(0x28) = FIELD(short, 0xE0) + FLOAT(0x28);
        if (FIELD(short, 0xDA) > 4) FLOAT(0x28) -= FIELD(short, 0xE0);
        if (FIELD(short, 0xDC) < 5) FLOAT(0x2C) = FIELD(short, 0xE0) + FLOAT(0x2C);
        if (FIELD(short, 0xDC) > 4) FLOAT(0x2C) -= FIELD(short, 0xE0);
        FIELD(unsigned char, 0x11) -= 8;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 825:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 90) - 45;
            FIELD(short, 0xD8) = RecordedRange(0, 10);
            FIELD(short, 0xDA) = RecordedRange(0, 10);
            FIELD(short, 0xDC) = RecordedRange(0, 10);
            FIELD(short, 0xDE) = RecordedRange(0, 5);
            FIELD(short, 0xE0) = RecordedRange(0, 5);
            FLOAT(0x50) = RecordedRange(0, 6) - 3;
            FLOAT(0x54) = -RecordedRange(0, 2);
        }
        FLOAT(0x54) -= 0.2f;
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        if (FIELD(short, 0xD8) < 5) FLOAT(0x30) = FIELD(short, 0xDE) + FLOAT(0x30);
        if (FIELD(short, 0xD8) > 4) FLOAT(0x30) -= FIELD(short, 0xDE);
        if (FIELD(short, 0xDA) < 5) FLOAT(0x28) = FIELD(short, 0xE0) + FLOAT(0x28);
        if (FIELD(short, 0xDA) > 4) FLOAT(0x28) -= FIELD(short, 0xE0);
        if (FIELD(short, 0xDC) < 5) FLOAT(0x2C) = FIELD(short, 0xE0) + FLOAT(0x2C);
        if (FIELD(short, 0xDC) > 4) FLOAT(0x2C) -= FIELD(short, 0xE0);
        FIELD(unsigned char, 0x11) -= 8;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
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
            FLOAT(0x30) = RecordedRange(0, 90) - 45;
            FIELD(short, 0xD8) = RecordedRange(0, 10);
            FIELD(short, 0xDA) = RecordedRange(0, 10);
            FIELD(short, 0xDC) = RecordedRange(0, 10);
            FIELD(short, 0xDE) = RecordedRange(0, 5);
            FIELD(short, 0xE0) = RecordedRange(0, 5);
            FLOAT(0x50) = RecordedRange(0, 6) - 3;
            FLOAT(0x54) = -RecordedRange(0, 2);
        }
        FLOAT(0x54) -= 0.2f;
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        if (FIELD(short, 0xD8) < 5) FLOAT(0x30) = FIELD(short, 0xDE) + FLOAT(0x30);
        if (FIELD(short, 0xD8) > 4) FLOAT(0x30) -= FIELD(short, 0xDE);
        if (FIELD(short, 0xDA) < 5) FLOAT(0x28) = FIELD(short, 0xE0) + FLOAT(0x28);
        if (FIELD(short, 0xDA) > 4) FLOAT(0x28) -= FIELD(short, 0xE0);
        if (FIELD(short, 0xDC) < 5) FLOAT(0x2C) = FIELD(short, 0xE0) + FLOAT(0x2C);
        if (FIELD(short, 0xDC) > 4) FLOAT(0x2C) -= FIELD(short, 0xE0);
        FIELD(unsigned char, 0x11) -= 8;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 827:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 90) - 45;
            FIELD(short, 0xD8) = RecordedRange(0, 10);
            FIELD(short, 0xDA) = RecordedRange(0, 10);
            FIELD(short, 0xDC) = RecordedRange(0, 10);
            FIELD(short, 0xDE) = RecordedRange(0, 5);
            FIELD(short, 0xE0) = RecordedRange(0, 5);
            FLOAT(0x50) = RecordedRange(0, 6) - 3;
            FLOAT(0x54) = -RecordedRange(0, 2);
        }
        FLOAT(0x54) -= 0.2f;
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        if (FIELD(short, 0xD8) < 5) FLOAT(0x30) = FIELD(short, 0xDE) + FLOAT(0x30);
        if (FIELD(short, 0xD8) > 4) FLOAT(0x30) -= FIELD(short, 0xDE);
        if (FIELD(short, 0xDA) < 5) FLOAT(0x28) = FIELD(short, 0xE0) + FLOAT(0x28);
        if (FIELD(short, 0xDA) > 4) FLOAT(0x28) -= FIELD(short, 0xE0);
        if (FIELD(short, 0xDC) < 5) FLOAT(0x2C) = FIELD(short, 0xE0) + FLOAT(0x2C);
        if (FIELD(short, 0xDC) > 4) FLOAT(0x2C) -= FIELD(short, 0xE0);
        FIELD(unsigned char, 0x11) -= 8;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 828:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 90) - 45;
            FIELD(short, 0xD8) = RecordedRange(0, 10);
            FIELD(short, 0xDA) = RecordedRange(0, 10);
            FIELD(short, 0xDC) = RecordedRange(0, 10);
            FIELD(short, 0xDE) = RecordedRange(0, 5);
            FIELD(short, 0xE0) = RecordedRange(0, 5);
            FLOAT(0x50) = RecordedRange(0, 6) - 3;
            FLOAT(0x54) = -RecordedRange(0, 2);
        }
        FLOAT(0x54) -= 0.2f;
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        if (FIELD(short, 0xD8) < 5) FLOAT(0x30) = FIELD(short, 0xDE) + FLOAT(0x30);
        if (FIELD(short, 0xD8) > 4) FLOAT(0x30) -= FIELD(short, 0xDE);
        if (FIELD(short, 0xDA) < 5) FLOAT(0x28) = FIELD(short, 0xE0) + FLOAT(0x28);
        if (FIELD(short, 0xDA) > 4) FLOAT(0x28) -= FIELD(short, 0xE0);
        if (FIELD(short, 0xDC) < 5) FLOAT(0x2C) = FIELD(short, 0xE0) + FLOAT(0x2C);
        if (FIELD(short, 0xDC) > 4) FLOAT(0x2C) -= FIELD(short, 0xE0);
        FIELD(unsigned char, 0x11) -= 8;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 829:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = RecordedRange(0, 90) - 45;
            FIELD(short, 0xD8) = RecordedRange(0, 10);
            FIELD(short, 0xDA) = RecordedRange(0, 10);
            FIELD(short, 0xDC) = RecordedRange(0, 10);
            FIELD(short, 0xDE) = RecordedRange(0, 5);
            FIELD(short, 0xE0) = RecordedRange(0, 5);
            FLOAT(0x50) = RecordedRange(0, 10) - 5;
            FLOAT(0x54) = -RecordedRange(0, 2);
        }
        FLOAT(0x54) -= 0.2f;
        FLOAT(0x48) += FLOAT(0x54);
        FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
        if (FIELD(short, 0xD8) < 5) FLOAT(0x30) = FIELD(short, 0xDE) + FLOAT(0x30);
        if (FIELD(short, 0xD8) > 4) FLOAT(0x30) -= FIELD(short, 0xDE);
        if (FIELD(short, 0xDA) < 5) FLOAT(0x28) = FIELD(short, 0xE0) + FLOAT(0x28);
        if (FIELD(short, 0xDA) > 4) FLOAT(0x28) -= FIELD(short, 0xE0);
        if (FIELD(short, 0xDC) < 5) FLOAT(0x2C) = FIELD(short, 0xE0) + FLOAT(0x2C);
        if (FIELD(short, 0xDC) > 4) FLOAT(0x2C) -= FIELD(short, 0xE0);
        FIELD(unsigned char, 0x11) -= 8;
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 990:
        if (OWNER(short, 0xF16) == 0 && FIELD(short, 0x62) < 2) {
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
                if (OWNER(short, 0xF16) >= 120) {
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
        if (OWNER(short, 0xF16) == 0 && FIELD(short, 0x62) < 2) {
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
            FLOAT(0x1C) = OWNER(short, 0xF16) / 60.0f;
            FLOAT(0x20) = FLOAT(0x1C);
            if (FIELD(short, 0x62) == 0) {
                if (FIELD(unsigned char, 0x11) < 230) {
                    FIELD(unsigned char, 0x11) += 25;
                }
                else {
                    FIELD(unsigned char, 0x11) = 255;
                }
                if (OWNER(short, 0xF16) >= 120) {
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
        FLOAT(0x48) = OWNER_FLOAT(0x48) * 0.0f + 20.0f;
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
            FLOAT(0x28) = 0.0f;
            FLOAT(0x2C) = 0.0f;
            FLOAT(0x30) = 0.0f;
            FLOAT(0x28) = -80.0f;
            FIELD(short, 0xD8) = OWNER(short, 0x3A0);
        }
        if (OWNER(short, 0x3A0) <= 0) { ClearField74(); return; }
        else {
            FLOAT(0x1C) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2;
            FLOAT(0x20) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2;
            FLOAT(0x30) += 1.0f;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(40);
            if (FIELD(short, 0x62) == 40 && FIELD(short, 0x64) == 0) FIELD(unsigned char, 0x11) = 255;
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
