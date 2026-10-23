#include "CharacterActionDispatch4E2F20.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(this) + offset))
#define FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<u8 *>(this) + offset)
#define RECORD(type, receiver, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(FIELD(void *, receiver)) + offset))
#define TARGET_PRIORITY(index) (*reinterpret_cast<short *>(reinterpret_cast<u8 *>(reinterpret_cast<ActionSequenceSlots *>(reinterpret_cast<u8 *>(this) + 0x468)->At(index)) + 0x10))
#define ACTION_CHANGE_ALLOWED ((FIELD(short, 0x60) > 299 && FIELD(int, 0x7C) != 0 && FIELD(int, 0x7C) != 3) || FIELD(short, 0x60) < 300)
#define FORWARD_INPUT \
    ((FIELD(u8, 0x511) == 1 && FIELD(signed char, 0x66) == 1) || \
    (FIELD(u8, 0x511) == 2 && FIELD(signed char, 0x66) == -1) || \
    (FIELD(unsigned long, 0x4F4) > 0 && FIELD(signed char, 0x66) * FIELD(int, 0x4DC) == 1) || \
    (FIELD(unsigned long, 0x4F4) == 1 && FIELD(signed char, 0x66) * FIELD(int, 0x4DC) > 0))
#define BACKWARD_INPUT \
    ((FIELD(u8, 0x511) == 2 && FIELD(signed char, 0x66) == 1) || \
    (FIELD(u8, 0x511) == 1 && FIELD(signed char, 0x66) == -1) || \
    (FIELD(unsigned long, 0x4F4) > 0 && FIELD(signed char, 0x66) * FIELD(int, 0x4DC) == -1) || \
    (FIELD(unsigned long, 0x4F4) == 1 && FIELD(signed char, 0x66) * FIELD(int, 0x4DC) < 0))
#define NEGATIVE_VERTICAL_INPUT \
    (FIELD(u8, 0x511) == 3 || \
    (FIELD(unsigned long, 0x4F4) > 0 && FIELD(int, 0x4E0) == -1 && FIELD(int, 0x4DC) == 0) || \
    (FIELD(unsigned long, 0x4F4) == 1 && FIELD(int, 0x4E0) < -1 && FIELD(int, 0x4DC) == 0))
#define NEGATIVE_VERTICAL_BACK_INPUT \
    (FIELD(u8, 0x511) == 4 || \
    (FIELD(unsigned long, 0x4F4) > 0 && FIELD(int, 0x4E0) == -1 && FIELD(signed char, 0x66) * FIELD(int, 0x4DC) <= -1) || \
    (FIELD(unsigned long, 0x4F4) == 1 && FIELD(int, 0x4E0) < -1 && FIELD(signed char, 0x66) * FIELD(int, 0x4DC) <= -1))
#define NEGATIVE_VERTICAL_FORWARD_INPUT \
    (FIELD(u8, 0x511) == 5 || \
    (FIELD(unsigned long, 0x4F4) > 0 && FIELD(int, 0x4E0) == -1 && FIELD(signed char, 0x66) * FIELD(int, 0x4DC) >= 1) || \
    (FIELD(unsigned long, 0x4F4) == 1 && FIELD(int, 0x4E0) < -1 && FIELD(signed char, 0x66) * FIELD(int, 0x4DC) >= 1))
#define PRIORITY_OR_SPECIAL_RANK(index) (RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(index) || RECORD(short, 0x78, 0x12) == 99 || RECORD(short, 0x78, 0x12) == 49)
#define PRIORITY_OR_MOVEMENT_RANK(index) (RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(index) || RECORD(short, 0x78, 0x12) == 99 || RECORD(short, 0x78, 0x12) == 49 || RECORD(short, 0x78, 0x12) == 39)
#define ATTACK_A (FIELD(unsigned long, 0x4E8) == 1 || FIELD(unsigned long, 0x500) > 0)
#define ATTACK_B (FIELD(unsigned long, 0x4EC) == 1 || FIELD(unsigned long, 0x504) > 0)
#define ATTACK_C (FIELD(unsigned long, 0x4F0) == 1 || FIELD(unsigned long, 0x508) > 0)
#define FORWARD_MOTION (FIELD(signed char, 0x66) * FIELD(int, 0x4DC) > 0 || FIELD(signed char, 0x66) * FIELD(int, 0x4F8) > 0)
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<u8 *>(FIELD(void *, 0x2E8)) + offset)
#define DISTANT_FROM_OPPONENT(upper, lower) (FLOAT(0x44) - OPPONENT_FLOAT(0x44) > upper || FLOAT(0x44) - OPPONENT_FLOAT(0x44) < lower)
void CharacterAction4E2F20::DispatchActions()
{
    if (FIELD(u8, 0x511) == 205 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(720)) {
        PackDirectionBits();
        ResetPrimaryCounters(720);
        return;
    }
    if (FIELD(u8, 0x511) == 220 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(751)) {
        PackDirectionBits();
        ResetPrimaryCounters(751);
        return;
    }
    if (FIELD(u8, 0x511) == 210 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(741)) {
        PackDirectionBits();
        ResetPrimaryCounters(741);
        return;
    }
    if (FIELD(u8, 0x511) == 200 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(731)) {
        PackDirectionBits();
        ResetPrimaryCounters(731);
        return;
    }
    if (FIELD(u8, 0x511) == 201 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(732)) {
        PackDirectionBits();
        ResetPrimaryCounters(732);
        return;
    }
    if (FIELD(u8, 0x511) == 202 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(733)) {
        PackDirectionBits();
        ResetPrimaryCounters(733);
        return;
    }
    if (FIELD(u8, 0x511) == 103 &&
        FLOAT(0x48) == 0.0f &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(u8, 0x39C) == 0 &&
        FIELD(short, 0x3A0) <= 0 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(795) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(795);
        return;
    }
    if (FIELD(signed char, 0x366) > 0 && FLOAT(0x48) == 0.0f &&
        FIELD(u8, 0x511) == 102 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(594) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        if (FLOAT(0x48) == 0.0f) {
            if (FIELD(short, 0x60) > 299) {
                ResetPrimaryCounters(595);
                return;
            }
            ResetPrimaryCounters(594);
            return;
        }
        if (FLOAT(0x48) > 0.0f) {
            if (FIELD(short, 0x60) > 149 && FIELD(short, 0x60) < 159) {
                ResetPrimaryCounters(599);
                return;
            }
            if (FIELD(short, 0x60) > 299) {
                ResetPrimaryCounters(598);
                return;
            }
            ResetPrimaryCounters(597);
            return;
        }
    }
    if (FIELD(signed char, 0x366) >= 1 && FLOAT(0x48) == 0.0f &&
        FIELD(u8, 0x511) == 102 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(596) && FIELD(short, 0x60) < 300) {
        PackDirectionBits();
        if (FLOAT(0x48) == 0.0f) {
            ResetPrimaryCounters(596);
            return;
        }
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(u8, 0x511) == 13 &&
        FLOAT(0x48) == 0.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 0 &&
        FIELD(signed char, 0x39D) == 1 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(703) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(703);
        return;
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(short, 0xF12) == 0 &&
        FIELD(u8, 0x511) == 13 &&
        FLOAT(0x48) == 0.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 1 &&
        FIELD(signed char, 0x39D) == 1 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(704) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(704);
        return;
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(u8, 0x511) == 13 &&
        FLOAT(0x48) == 0.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 2 &&
        FIELD(signed char, 0x39D) == 1 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(705) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(705);
        return;
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(u8, 0x511) == 13 &&
        FLOAT(0x48) == 0.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x398) == 0 &&
        FIELD(signed char, 0x39D) == 2 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(700) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(700);
        return;
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(short, 0xF12) == 0 &&
        FIELD(u8, 0x511) == 13 &&
        FLOAT(0x48) == 0.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x398) == 1 &&
        FIELD(signed char, 0x39D) == 2 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(701) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(701);
        return;
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(u8, 0x511) == 13 &&
        FLOAT(0x48) == 0.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x398) == 2 &&
        FIELD(signed char, 0x39D) == 2 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(702) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(702);
        return;
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(u8, 0x511) == 22 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FIELD(short, 0x3B0) > 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(608) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(608);
        return;
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(u8, 0x511) == 21 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FIELD(short, 0x3B0) > 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(607) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(607);
        return;
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(u8, 0x511) == 20 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FIELD(short, 0x3B0) > 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(606) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(606);
        return;
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(u8, 0x511) == 31 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(613) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(613);
        return;
    }
    if (FIELD(short, 0x3B0) > 0 &&
        FIELD(u8, 0x511) == 30 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(612) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(612);
        return;
    }
    if (FIELD(u8, 0x511) == 12 &&
        FIELD(short, 0x3B0) > 0 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FLOAT(0x48) == 0.0f &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(602) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(602);
        return;
    }
    if (FIELD(u8, 0x511) == 11 &&
        FIELD(short, 0x3B0) > 0 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FLOAT(0x48) == 0.0f &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(601) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(601);
        return;
    }
    if (FIELD(u8, 0x511) == 10 &&
        FIELD(short, 0x3B0) > 0 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FLOAT(0x48) == 0.0f &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(600) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(600);
        return;
    }
    if (FIELD(u8, 0x511) == 101 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FLOAT(0x48) == 0.0f &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(309) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(309);
        return;
    }
    if (FIELD(u8, 0x511) == 100 &&
        FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(310) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(310);
        return;
    }
    if (FORWARD_INPUT && FLOAT(0x48) == 0.0f && FIELD(short, 0x60) != 207 &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(200) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(200);
        return;
    }
    if (FORWARD_INPUT && FLOAT(0x48) > 0.0f &&
        !(FLOAT(0x48) < 60.0f && FLOAT(0x54) > 0.0f) &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FIELD(signed char, 0x3AD) < 2 && PRIORITY_OR_MOVEMENT_RANK(202) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ++FIELD(signed char, 0x3AD);
        ResetPrimaryCounters(202);
        return;
    }
    if (BACKWARD_INPUT && FLOAT(0x48) == 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(201) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(201);
        return;
    }
    if (BACKWARD_INPUT && FLOAT(0x48) > 0.0f &&
        (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FIELD(signed char, 0x3AD) < 2 && PRIORITY_OR_MOVEMENT_RANK(203) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ++FIELD(signed char, 0x3AD);
        ResetPrimaryCounters(203);
        return;
    }
    if (NEGATIVE_VERTICAL_INPUT && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FLOAT(0x48) == 0.0f && PRIORITY_OR_MOVEMENT_RANK(204) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(204);
        return;
    }
    if (NEGATIVE_VERTICAL_BACK_INPUT && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FLOAT(0x48) == 0.0f && PRIORITY_OR_MOVEMENT_RANK(206) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(206);
        return;
    }
    if (NEGATIVE_VERTICAL_FORWARD_INPUT && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
        FLOAT(0x48) == 0.0f && PRIORITY_OR_MOVEMENT_RANK(205) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(205);
        return;
    }
    if (FLOAT(0x48) == 0.0f && (FIELD(int, 0x4E0) > 0 || FIELD(int, 0x4FC) > 0)) {
        if (ATTACK_A && FORWARD_MOTION && FIELD(short, 0x60) == 200 &&
            (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0) {
            ResetPrimaryCounters(392);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_A) {
            if (FIELD(short, 0x3B0) > 0 && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(460.0f, -460.0f) &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(410) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(410);
                ClearAuxiliaryInput();
                return;
            }
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(302) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(302);
                ClearAuxiliaryInput();
                return;
            }
        }
        if ((FIELD(unsigned long, 0x4EC) == 1 || FIELD(unsigned long, 0x500) > 0) &&
            FORWARD_MOTION && FIELD(short, 0x60) == 200 &&
            (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0) {
            ResetPrimaryCounters(393);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_B) {
            if (FIELD(short, 0x3B0) > 0 && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(416) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(416);
                ClearAuxiliaryInput();
                return;
            }
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(303) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(303);
                ClearAuxiliaryInput();
                return;
            }
        }
        if (ATTACK_C && FIELD(short, 0x3B0) > 0 &&
            (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
            RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(402) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(402);
            ClearAuxiliaryInput();
            return;
        }
    }
    if (FLOAT(0x48) == 0.0f && FIELD(int, 0x4E0) == 0) {
        if (ATTACK_A && FIELD(int, 0x4E0) == 0 && FORWARD_MOTION &&
            FIELD(short, 0x60) == 200 && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0) {
            ResetPrimaryCounters(390);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_A && FIELD(int, 0x4E0) == 0 && FORWARD_MOTION) {
            if (FIELD(short, 0x3B0) > 0 && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(480.0f, -480.0f) &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(408) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(408);
                ClearAuxiliaryInput();
                return;
            }
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(307) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(307);
                ClearAuxiliaryInput();
                return;
            }
        }
        if (ATTACK_A) {
            if (FIELD(short, 0x3B0) > 0 && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(480.0f, -480.0f) &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(408) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(408);
                ClearAuxiliaryInput();
                return;
            }
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(300) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(300);
                ClearAuxiliaryInput();
                return;
            }
        }
        if ((FIELD(unsigned long, 0x4EC) == 1 || FIELD(unsigned long, 0x500) > 0) &&
            FIELD(int, 0x4E0) == 0 && FORWARD_MOTION && FIELD(short, 0x60) == 200 &&
            (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0) {
            ResetPrimaryCounters(391);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_B && FIELD(int, 0x4E0) == 0 && FORWARD_MOTION) {
            if (FIELD(short, 0x3B0) > 0 && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(415) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(415);
                ClearAuxiliaryInput();
                return;
            }
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(308) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(308);
                ClearAuxiliaryInput();
                return;
            }
        }
        if (ATTACK_B) {
            if (FIELD(short, 0x3B0) > 0 && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(414) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(414);
                ClearAuxiliaryInput();
                return;
            }
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                (RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(301) || FIELD(short, 0x60) == 301) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(301);
                ClearAuxiliaryInput();
                return;
            }
        }
        if (ATTACK_C && FIELD(int, 0x4E0) == 0 && FORWARD_MOTION &&
            (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 && FIELD(short, 0x3B0) > 0 &&
            RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(401) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(401);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_C && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
            FIELD(short, 0x3B0) > 0 &&
            RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(400) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(400);
            ClearAuxiliaryInput();
            return;
        }
    }
    if (FLOAT(0x48) > 0.0f) {
        if (ATTACK_A) {
            if (FIELD(short, 0x3B0) > 0 && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(520.0f, -520.0f) &&
                (FIELD(int, 0x4E0) > 0 || FIELD(int, 0x4FC) > 0) &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(413) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(413);
                ClearAuxiliaryInput();
                return;
            }
            if (FIELD(short, 0x3B0) > 0 && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(520.0f, -520.0f) &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(412) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(412);
                ClearAuxiliaryInput();
                return;
            }
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(304) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(304);
                ClearAuxiliaryInput();
                return;
            }
        }
        if (ATTACK_B) {
            if (FIELD(short, 0x3B0) > 0 && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(400.0f, -400.0f) &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(418) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(418);
                ClearAuxiliaryInput();
                return;
            }
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(305) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(305);
                ClearAuxiliaryInput();
                return;
            }
        }
        if (ATTACK_C && (FIELD(int, 0x4E0) > 0 || FIELD(int, 0x4FC) > 0) &&
            (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 && FIELD(short, 0x3B0) > 0 &&
            RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(404) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(404);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_C && (RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
            FIELD(short, 0x3B0) > 0 &&
            RECORD(short, 0x78, 0x12) <= TARGET_PRIORITY(407) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(407);
            ClearAuxiliaryInput();
            return;
        }
        if (FIELD(unsigned long, 0x4F4) > 0 || FIELD(unsigned long, 0x50C) > 0) {
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                FIELD(signed char, 0x3AD) < 2 &&
                FIELD(signed char, 0x66) * FIELD(int, 0x4DC) == 1 &&
                !(FLOAT(0x48) < 60.0f && FLOAT(0x54) > 0.0f) &&
                PRIORITY_OR_SPECIAL_RANK(202) && ACTION_CHANGE_ALLOWED) {
                PackDirectionBits();
                ++FIELD(signed char, 0x3AD);
                ResetPrimaryCounters(202);
                return;
            }
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                FIELD(signed char, 0x3AD) < 2 &&
                FIELD(signed char, 0x66) * FIELD(int, 0x4DC) == -1 &&
                PRIORITY_OR_SPECIAL_RANK(203) && ACTION_CHANGE_ALLOWED) {
                PackDirectionBits();
                ++FIELD(signed char, 0x3AD);
                ResetPrimaryCounters(203);
                return;
            }
        }
        if (FIELD(unsigned long, 0x4F4) == 1 || FIELD(unsigned long, 0x50C) == 1) {
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                FIELD(signed char, 0x3AD) < 2 &&
                FIELD(signed char, 0x66) * FIELD(int, 0x4DC) > 0 &&
                !(FLOAT(0x48) < 60.0f && FLOAT(0x54) > 0.0f) &&
                PRIORITY_OR_SPECIAL_RANK(202) && ACTION_CHANGE_ALLOWED) {
                PackDirectionBits();
                ++FIELD(signed char, 0x3AD);
                ResetPrimaryCounters(202);
                return;
            }
            if ((RECORD(unsigned long, 0x74, 0x3C) & 0x20) != 0 &&
                FIELD(signed char, 0x3AD) < 2 &&
                FIELD(signed char, 0x66) * FIELD(int, 0x4DC) < 0 &&
                PRIORITY_OR_SPECIAL_RANK(203) && ACTION_CHANGE_ALLOWED) {
                PackDirectionBits();
                ++FIELD(signed char, 0x3AD);
                ResetPrimaryCounters(203);
                return;
            }
        }
    }
}
