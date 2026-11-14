#include "CharacterActionDispatch5E2310.hpp"

#define TARGET_PRIORITY(index) (static_cast<FighterSequenceInfo *>(sequenceSlots.At(index))->targetPriority)
#define ACTION_CHANGE_ALLOWED ((action > 299 && field07C != 0 && field07C != 3) || action < 300)
#define FORWARD_INPUT \
    ((aiCommand == 1 && facing == 1) || \
    (aiCommand == 2 && facing == -1) || \
    (inputD > 0 && facing * inputX == 1) || \
    (inputD == 1 && facing * inputX > 0))
#define BACKWARD_INPUT \
    ((aiCommand == 2 && facing == 1) || \
    (aiCommand == 1 && facing == -1) || \
    (inputD > 0 && facing * inputX == -1) || \
    (inputD == 1 && facing * inputX < 0))
#define NEGATIVE_VERTICAL_INPUT \
    (aiCommand == 3 || \
    (inputD > 0 && inputY == -1 && inputX == 0) || \
    (inputD == 1 && inputY < -1 && inputX == 0))
#define NEGATIVE_VERTICAL_BACK_INPUT \
    (aiCommand == 4 || \
    (inputD > 0 && inputY == -1 && facing * inputX <= -1) || \
    (inputD == 1 && inputY < -1 && facing * inputX <= -1))
#define NEGATIVE_VERTICAL_FORWARD_INPUT \
    (aiCommand == 5 || \
    (inputD > 0 && inputY == -1 && facing * inputX >= 1) || \
    (inputD == 1 && inputY < -1 && facing * inputX >= 1))
#define PRIORITY_OR_SPECIAL_RANK(index) (sequenceInfo->priority <= TARGET_PRIORITY(index) || sequenceInfo->priority == 99 || sequenceInfo->priority == 49)
#define ATTACK_A (reinterpret_cast<unsigned long&>(inputA) == 1 || bufferedA > 0)
#define ATTACK_B (reinterpret_cast<unsigned long&>(inputB) == 1 || bufferedB > 0)
#define ATTACK_C (reinterpret_cast<unsigned long&>(inputC) == 1 || bufferedC > 0)
#define FORWARD_MOTION (facing * inputX > 0 || facing * bufferedX > 0)
#define DISTANT_FROM_OPPONENT(upper, lower) (x - opponent->x > upper || x - opponent->x < lower)
void CharacterAction5E2310::DispatchActions()
{
    if (aiCommand == 103 &&
        y == 0.0f &&
        field36C >= 100.0f &&
        field39C == 0 &&
        field3A0 <= 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(795) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(795);
        return;
    }
    if (aiCommand == 13 &&
        y == 0.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[1] == 0 &&
        field39D == 1 &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(701) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(701);
        return;
    }
    if (aiCommand == 13 &&
        y == 0.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[1] == 1 &&
        field39D == 1 &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(703) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(703);
        return;
    }
    if (meter > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[1] == 2 &&
        field39D == 1 &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(706) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(706);
        return;
    }
    if (aiCommand == 13 &&
        y == 0.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[0] == 0 &&
        field39D == 2 &&
        (frameInfo->flags & 0x20) != 0 &&
        meter > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(700) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(700);
        if (y > 0.0f) ResetPrimaryCounters(706);
        return;
    }
    if (aiCommand == 13 &&
        y == 0.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[0] == 1 &&
        field39D == 2 &&
        (frameInfo->flags & 0x20) != 0 &&
        meter > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(702) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(702);
        return;
    }
    if (aiCommand == 13 &&
        y == 0.0f &&
        field3A0 > 0 &&
        field36C >= 100.0f &&
        aiSelectors[0] == 2 &&
        field39D == 2 &&
        (frameInfo->flags & 0x20) != 0 &&
        meter > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(704) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(704);
        return;
    }
    if (field366 > 0 && y == 0.0f &&
        aiCommand == 102 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(594) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        if (y == 0.0f) {
            if (action > 299) {
                ResetPrimaryCounters(595);
                return;
            }
            ResetPrimaryCounters(594);
            return;
        }
        if (y > 0.0f) {
            if (action > 149 && action < 159) {
                ResetPrimaryCounters(599);
                return;
            }
            if (action > 299) {
                ResetPrimaryCounters(598);
                return;
            }
            ResetPrimaryCounters(597);
            return;
        }
    }
    if (field366 > 0 && y == 0.0f &&
        aiCommand == 102 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(596) && action < 300) {
        PackDirectionBits();
        if (y == 0.0f) {
            ResetPrimaryCounters(596);
            return;
        }
    }
    if (aiCommand == 41 &&
        y == 0.0f &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(509) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(509);
        return;
    }
    if (aiCommand == 40 &&
        y == 0.0f &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(508) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(508);
        return;
    }
    if (aiCommand == 31 &&
        y == 0.0f &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(507) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(507);
        return;
    }
    if (aiCommand == 30 &&
        y == 0.0f &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(506) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(506);
        return;
    }
    if (aiCommand == 11 &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        meter > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(501) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(501);
        return;
    }
    if (aiCommand == 10 &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        meter > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(500) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(500);
        return;
    }
    if (aiCommand == 21 &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        meter > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(603) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(603);
        return;
    }
    if (aiCommand == 20 &&
        meter > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        meter > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(602) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(602);
        return;
    }
    if (aiCommand == 101 &&
        (frameInfo->flags & 0x20) != 0 &&
        action < 320 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(309) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(309);
        return;
    }
    if (aiCommand == 100 &&
        (frameInfo->flags & 0x20) != 0 &&
        action < 320 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(310) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(310);
        return;
    }
    if (FORWARD_INPUT && y == 0.0f && action != 207 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(200) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(200);
        return;
    }
    if (FORWARD_INPUT && y > 0.0f &&
        !(y < 60.0f && velocityY > 0.0f) &&
        (frameInfo->flags & 0x20) != 0 &&
        field3AD < 2 && PRIORITY_OR_SPECIAL_RANK(202) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ++field3AD;
        ResetPrimaryCounters(202);
        return;
    }
    if (BACKWARD_INPUT && y == 0.0f &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(201) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(201);
        return;
    }
    if (BACKWARD_INPUT && y > 0.0f &&
        (frameInfo->flags & 0x20) != 0 &&
        field3AD < 2 && PRIORITY_OR_SPECIAL_RANK(203) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ++field3AD;
        ResetPrimaryCounters(203);
        return;
    }
    if (NEGATIVE_VERTICAL_INPUT && (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f && PRIORITY_OR_SPECIAL_RANK(204) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(204);
        return;
    }
    if (NEGATIVE_VERTICAL_BACK_INPUT && (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f && PRIORITY_OR_SPECIAL_RANK(206) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(206);
        return;
    }
    if (NEGATIVE_VERTICAL_FORWARD_INPUT && (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f && PRIORITY_OR_SPECIAL_RANK(205) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(205);
        return;
    }
    if (y == 0.0f && (inputY > 0 || bufferedY > 0)) {
        if (ATTACK_A && FORWARD_MOTION && action == 200 &&
            (frameInfo->flags & 0x20) != 0) {
            ResetPrimaryCounters(392);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_A && meter > 0 &&
            (frameInfo->flags & 0x20) != 0 &&
            DISTANT_FROM_OPPONENT(360.0f, -360.0f) &&
            sequenceInfo->priority <= TARGET_PRIORITY(408) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(408);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_A && (frameInfo->flags & 0x20) != 0 &&
            ((action < 320 && sequenceInfo->priority <= TARGET_PRIORITY(303)) ||
             action == 303) && ACTION_CHANGE_ALLOWED) {
            ClearAuxiliaryInput();
            ResetPrimaryCounters(303);
            return;
        }
        if ((reinterpret_cast<unsigned long&>(inputB) == 1 || bufferedA > 0) &&
            FORWARD_MOTION && action == 200 &&
            (frameInfo->flags & 0x20) != 0) {
            ResetPrimaryCounters(393);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_B && meter > 0 &&
            (frameInfo->flags & 0x20) != 0 &&
            DISTANT_FROM_OPPONENT(240.0f, -240.0f) &&
            sequenceInfo->priority <= TARGET_PRIORITY(414) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(414);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_B && (frameInfo->flags & 0x20) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(304) && ACTION_CHANGE_ALLOWED) {
            ClearAuxiliaryInput();
            if (action == 300) return;
            if (action == 303) return;
            if (action == 322) {
                ResetPrimaryCounters(326);
                return;
            }
            if (action < 320) {
                ResetPrimaryCounters(304);
                return;
            }
            return;
        }
        if (ATTACK_C && meter > 0 &&
            (frameInfo->flags & 0x20) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(402) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(402);
            ClearAuxiliaryInput();
            return;
        }
    }
    if (y == 0.0f && inputY == 0) {
        if (ATTACK_A && inputY == 0 && FORWARD_MOTION &&
            action == 200 && (frameInfo->flags & 0x20) != 0) {
            ResetPrimaryCounters(390);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_A && inputY == 0 && FORWARD_MOTION) {
            if (meter > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(407) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(407);
                ClearAuxiliaryInput();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 && action < 320 &&
                sequenceInfo->priority <= TARGET_PRIORITY(308) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(308);
                ClearAuxiliaryInput();
                return;
            }
        }
        if (ATTACK_A) {
            if (meter > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(406) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(406);
                ClearAuxiliaryInput();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(300) && ACTION_CHANGE_ALLOWED) {
                ClearAuxiliaryInput();
                if (action == 322) {
                    ResetPrimaryCounters(324);
                    return;
                }
                if (action == 320) {
                    ResetPrimaryCounters(322);
                    return;
                }
                if (action == 300 || action == 303) {
                    ResetPrimaryCounters(320);
                    return;
                }
                if (action < 320) {
                    ResetPrimaryCounters(300);
                    return;
                }
            }
        }
        if ((reinterpret_cast<unsigned long&>(inputB) == 1 || bufferedA > 0) &&
            inputY == 0 && FORWARD_MOTION && action == 200 &&
            (frameInfo->flags & 0x20) != 0) {
            ResetPrimaryCounters(391);
            ClearAuxiliaryInput();
            return;
        }
        if (ATTACK_B && inputY == 0 && FORWARD_MOTION) {
            if (meter > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(240.0f, -240.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(412) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(412);
                ClearAuxiliaryInput();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 && action < 320 &&
                sequenceInfo->priority <= TARGET_PRIORITY(307) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(307);
                ClearAuxiliaryInput();
                return;
            }
        }
        if (ATTACK_B) {
            if (meter > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(240.0f, -240.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(412) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(412);
                ClearAuxiliaryInput();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(301) && ACTION_CHANGE_ALLOWED) {
                ClearAuxiliaryInput();
                if (action == 300) {
                    ResetPrimaryCounters(321);
                    return;
                }
                if (action == 303) return;
                if (action == 320) {
                    ResetPrimaryCounters(323);
                    return;
                }
                if (action == 322) {
                    ResetPrimaryCounters(325);
                    return;
                }
                if (action < 320) {
                    ResetPrimaryCounters(301);
                    return;
                }
            }
        }
        if (ATTACK_C && (frameInfo->flags & 0x20) != 0 &&
            meter > 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(400) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(400);
            ClearAuxiliaryInput();
            return;
        }
    }
    if (y > 0.0f) {
        if (ATTACK_A) {
            if (FORWARD_MOTION && meter > 0 &&
                (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(360.0f, -360.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(411) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(411);
                ClearAuxiliaryInput();
                return;
            }
            if (meter > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(360.0f, -360.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(410) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(410);
                ClearAuxiliaryInput();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(305) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(305);
                ClearAuxiliaryInput();
                return;
            }
        }
        if (ATTACK_B) {
            if ((inputY > 0 || bufferedY > 0) &&
                meter > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(360.0f, -360.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(416) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(416);
                ClearAuxiliaryInput();
                return;
            }
            if (meter > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(360.0f, -360.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(416) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(416);
                ClearAuxiliaryInput();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(306) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(306);
                ClearAuxiliaryInput();
                return;
            }
        }
        if (ATTACK_C && meter > 0 &&
            (frameInfo->flags & 0x20) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(404) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(404);
            ClearAuxiliaryInput();
            return;
        }
        if (inputD > 0 || bufferedD > 0) {
            if ((frameInfo->flags & 0x20) != 0 &&
                field3AD < 2 &&
                facing * inputX == 1 &&
                !(y < 60.0f && velocityY > 0.0f) &&
                PRIORITY_OR_SPECIAL_RANK(202) && ACTION_CHANGE_ALLOWED) {
                PackDirectionBits();
                ++field3AD;
                ResetPrimaryCounters(202);
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                field3AD < 2 &&
                facing * inputX == -1 &&
                PRIORITY_OR_SPECIAL_RANK(203) && ACTION_CHANGE_ALLOWED) {
                PackDirectionBits();
                ++field3AD;
                ResetPrimaryCounters(203);
                return;
            }
        }
        if (inputD == 1 || bufferedD == 1) {
            if ((frameInfo->flags & 0x20) != 0 &&
                field3AD < 2 &&
                facing * inputX > 0 &&
                !(y < 60.0f && velocityY > 0.0f) &&
                PRIORITY_OR_SPECIAL_RANK(202) && ACTION_CHANGE_ALLOWED) {
                PackDirectionBits();
                ++field3AD;
                ResetPrimaryCounters(202);
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                field3AD < 2 &&
                facing * inputX < 0 &&
                PRIORITY_OR_SPECIAL_RANK(203) && ACTION_CHANGE_ALLOWED) {
                PackDirectionBits();
                ++field3AD;
                ResetPrimaryCounters(203);
                return;
            }
        }
    }
}
