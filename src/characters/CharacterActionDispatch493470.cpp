#include "engine/GameSharedState.hpp"
#include "characters/CharacterActionDispatch493470.hpp"

#define TARGET_PRIORITY(index) (sequenceSlots.at(index)->targetPriority)
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
#define ATTACK_A (static_cast<unsigned long>(inputA) == 1 || bufferedA > 0)
#define ATTACK_B (static_cast<unsigned long>(inputB) == 1 || bufferedB > 0)
#define ATTACK_C (static_cast<unsigned long>(inputC) == 1 || bufferedC > 0)
#define FORWARD_MOTION (facing * inputX > 0 || facing * bufferedX > 0)
#define DISTANT_FROM_OPPONENT(upper, lower) (x - opponent->x > upper || x - opponent->x < lower)
void MarisaFighter::DispatchActions()
{
    if (aiCommand == 103 &&
        y == 0.0f &&
        spellPower >= 100.0f &&
        spellDeclarationExpired == 0 &&
        spellTimer <= 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(795) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(795);
        return;
    }
    if (aiCommand == 230 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(760) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(760);
        return;
    }
    if (aiCommand == 221 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(752) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(752);
        return;
    }
    if (aiCommand == 220 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(751) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(751);
        return;
    }
    if (aiCommand == 225 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(754) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(754);
        return;
    }
    if (aiCommand == 200 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(731) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(731);
        return;
    }
    if (aiCommand == 210 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(741) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(741);
        return;
    }
    if (aiCommand == 211 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(742) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(742);
        if (g_OptionsModeAt006714D0 == 0) ResetPrimaryCounters(743);
        return;
    }
    if (bombCount > 0 && y == 0.0f &&
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
    if (bombCount > 0 && y == 0.0f &&
        aiCommand == 102 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(596) && action < 300) {
        PackDirectionBits();
        if (y == 0.0f) {
            ResetPrimaryCounters(596);
            return;
        }
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 0 &&
        field39D == 1 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(712) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(712);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 1 &&
        field39D == 1 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(704) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(704);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 2 &&
        field39D == 1 &&
        fieldF14 == 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(706) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(706);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        fieldF14 == 6 &&
        fieldF12 == 1 &&
        selectedSpellCards[1] == 2 &&
        field39D == 1 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(715) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(715);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 23 &&
        y == 0.0f &&
        fieldF12 == 1 &&
        fieldF14 == 6 &&
        selectedSpellCards[1] == 2 &&
        field39D == 1 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(714) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(714);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[0] == 0 &&
        field39D == 2 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(700) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(700);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[0] == 1 &&
        field39D == 2 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(703) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(703);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[0] == 2 &&
        field39D == 2 &&
        fieldF14 == 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(705) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(705);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        fieldF14 == 4 &&
        fieldF12 == 1 &&
        selectedSpellCards[0] == 2 &&
        field39D == 2 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(708) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(708);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 23 &&
        y == 0.0f &&
        fieldF12 == 1 &&
        fieldF14 == 4 &&
        selectedSpellCards[0] == 2 &&
        field39D == 2 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(707) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(707);
        return;
    }
    if (aiCommand == 51 &&
        y == 0.0f &&
        (frameInfo->flags & 0x20) != 0 &&
        spirit > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(625) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(625);
        return;
    }
    if (aiCommand == 50 &&
        y == 0.0f &&
        (frameInfo->flags & 0x20) != 0 &&
        spirit > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(624) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(624);
        return;
    }
    if (aiCommand == 31 &&
        y == 0.0f &&
        spirit > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(501) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(501);
        return;
    }
    if (aiCommand == 30 &&
        y == 0.0f &&
        spirit > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(500) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(500);
        return;
    }
    if (aiCommand == 21 &&
        spirit > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        action != 526 &&
        sequenceInfo->priority <= TARGET_PRIORITY(525) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(525);
        if (y > 0.0f) ResetPrimaryCounters(523);
        return;
    }
    if (aiCommand == 20 &&
        spirit > 0 &&
        (frameInfo->flags & 0x20) != 0 &&
        action != 526 &&
        sequenceInfo->priority <= TARGET_PRIORITY(524) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(524);
        if (y > 0.0f) ResetPrimaryCounters(522);
        return;
    }
    if (aiCommand == 101 &&
        (frameInfo->flags & 0x20) != 0 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(309) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(309);
        return;
    }
    if (aiCommand == 100 &&
        y == 0.0f &&
        (frameInfo->flags & 0x20) != 0 &&
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
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_A) {
            if (spirit > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(402) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(402);
                ClearAuxiliaryWords();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                (sequenceInfo->priority <= TARGET_PRIORITY(302) ||
                action == 300 || action == 302) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(302);
                ClearAuxiliaryWords();
                return;
            }
        }
        if ((static_cast<unsigned long>(inputB) == 1 || bufferedA > 0) &&
            FORWARD_MOTION && action == 200 &&
            (frameInfo->flags & 0x20) != 0) {
            ResetPrimaryCounters(393);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B) {
            if (spirit > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(415) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(415);
                ClearAuxiliaryWords();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(303) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(303);
                ClearAuxiliaryWords();
                return;
            }
        }
        if (ATTACK_C && spirit > 0 &&
            (frameInfo->flags & 0x20) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(409) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(409);
            ClearAuxiliaryWords();
            return;
        }
    }
    if (y == 0.0f && inputY == 0) {
        if (ATTACK_A && inputY == 0 && FORWARD_MOTION &&
            action == 200 && (frameInfo->flags & 0x20) != 0) {
            ResetPrimaryCounters(390);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_A && inputY == 0 && FORWARD_MOTION) {
            if (spirit > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(360.0f, -360.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(400) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(400);
                ClearAuxiliaryWords();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(307) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(307);
                ClearAuxiliaryWords();
                return;
            }
        }
        if (ATTACK_A) {
            if (spirit > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(400) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(400);
                ClearAuxiliaryWords();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                (sequenceInfo->priority <= TARGET_PRIORITY(300) || action == 300 || action == 302) &&
                ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(300);
                ClearAuxiliaryWords();
                return;
            }
        }
        if ((static_cast<unsigned long>(inputB) == 1 || bufferedA > 0) &&
            inputY == 0 && FORWARD_MOTION && action == 200 &&
            (frameInfo->flags & 0x20) != 0) {
            ResetPrimaryCounters(391);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B && inputY == 0 && FORWARD_MOTION) {
            if (spirit > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(413) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(413);
                ClearAuxiliaryWords();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(308) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(308);
                ClearAuxiliaryWords();
                return;
            }
        }
        if (ATTACK_B) {
            if (spirit > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(412) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(412);
                ClearAuxiliaryWords();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(301) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(301);
                ClearAuxiliaryWords();
                return;
            }
        }
        if (ATTACK_C && inputY == 0 && FORWARD_MOTION &&
            (frameInfo->flags & 0x20) != 0 && spirit > 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(407) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(407);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_C && (frameInfo->flags & 0x20) != 0 &&
            spirit > 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(406) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(406);
            ClearAuxiliaryWords();
            return;
        }
    }
    if (y > 0.0f) {
        if (ATTACK_A) {
            if (spirit > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(400.0f, -400.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(404) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(404);
                ClearAuxiliaryWords();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(304) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(304);
                ClearAuxiliaryWords();
                return;
            }
        }
        if (ATTACK_B) {
            if ((inputY > 0 || bufferedY > 0) &&
                spirit > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(360.0f, -360.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(417) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(417);
                ClearAuxiliaryWords();
                return;
            }
            if (spirit > 0 && (frameInfo->flags & 0x20) != 0 &&
                DISTANT_FROM_OPPONENT(360.0f, -360.0f) &&
                sequenceInfo->priority <= TARGET_PRIORITY(416) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(416);
                ClearAuxiliaryWords();
                return;
            }
            if ((frameInfo->flags & 0x20) != 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(305) && ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(305);
                ClearAuxiliaryWords();
                return;
            }
        }
        if (ATTACK_C && (inputY > 0 || bufferedY > 0) &&
            (frameInfo->flags & 0x20) != 0 && spirit > 100 &&
            sequenceInfo->priority <= TARGET_PRIORITY(411) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(411);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_C && (frameInfo->flags & 0x20) != 0 &&
            spirit > 100 &&
            sequenceInfo->priority <= TARGET_PRIORITY(410) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(410);
            ClearAuxiliaryWords();
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
