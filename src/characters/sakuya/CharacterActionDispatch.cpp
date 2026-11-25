#include "characters/sakuya/CharacterActionDispatch.hpp"
#include "battle/FighterFrameFlags.hpp"

#define TARGET_PRIORITY(index) (sequenceSlots.at(index)->targetPriority)
#define ACTION_CHANGE_ALLOWED ((action > 299 && collisionResult != 0 && collisionResult != 3) || action < 300)
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
void SakuyaFighter::DispatchActions()
{
    if (aiCommand == 221 &&
        y == 0.0f &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(752)) {
        PackDirectionBits();
        ResetPrimaryCounters(771);
        return;
    }
    if (aiCommand == 220 &&
        y == 0.0f &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(751)) {
        PackDirectionBits();
        ResetPrimaryCounters(770);
        return;
    }
    if (aiCommand == 211 &&
        y == 0.0f &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(763)) {
        PackDirectionBits();
        ResetPrimaryCounters(763);
        return;
    }
    if (aiCommand == 210 &&
        y == 0.0f &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(762)) {
        PackDirectionBits();
        ResetPrimaryCounters(762);
        return;
    }
    if (aiCommand == 201 &&
        y == 0.0f &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(742)) {
        PackDirectionBits();
        ResetPrimaryCounters(742);
        return;
    }
    if (aiCommand == 200 &&
        y == 0.0f &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(741)) {
        PackDirectionBits();
        ResetPrimaryCounters(741);
        return;
    }
    if (aiCommand == 103 &&
        y == 0.0f &&
        spellPower >= 100.0f &&
        spellDeclarationExpired == 0 &&
        spellTimer <= 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(795) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(795);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 0 &&
        roundsRemaining == 1 &&
        fieldF14 == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(701) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(701);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 23 &&
        y == 0.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 1 &&
        roundsRemaining == 1 &&
        fieldF10 <= 0 && fieldF0C == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(707) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(707);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 1 &&
        roundsRemaining == 1 &&
        fieldF10 <= 0 && fieldF0C == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(706) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(706);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[1] == 2 &&
        roundsRemaining == 1 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
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
        selectedSpellCards[0] == 0 &&
        roundsRemaining == 2 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(700) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(700);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 23 &&
        y == 0.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[0] == 1 &&
        roundsRemaining == 2 &&
        fieldF10 <= 0 && fieldF0C == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(705) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(705);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 13 &&
        y == 0.0f &&
        spellTimer > 0 &&
        spellPower >= 100.0f &&
        selectedSpellCards[0] == 1 &&
        roundsRemaining == 2 &&
        fieldF10 <= 0 && fieldF0C == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
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
        selectedSpellCards[0] == 2 &&
        roundsRemaining == 2 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(702) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(702);
        return;
    }
    if (bombCount > 0 && y == 0.0f &&
        aiCommand == 102 && fieldF12 == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(594) &&
        ACTION_CHANGE_ALLOWED) {
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
        aiCommand == 102 && fieldF12 == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(596) &&
        action < 300) {
        PackDirectionBits();
        if (y == 0.0f) {
            ResetPrimaryCounters(596);
            return;
        }
    }
    if (aiCommand == 42 &&
        y == 0.0f &&
        spirit > 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(504) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(506);
        if (y > 0.0f) ResetPrimaryCounters(509);
        return;
    }
    if (aiCommand == 41 &&
        y == 0.0f &&
        spirit > 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(504) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(504);
        if (y > 0.0f) ResetPrimaryCounters(508);
        return;
    }
    if (aiCommand == 40 &&
        y == 0.0f &&
        spirit > 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(504) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(505);
        if (y > 0.0f) ResetPrimaryCounters(507);
        return;
    }
    if (aiCommand == 31 &&
        fieldF12 == 0 &&
        spirit > 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        fieldF12 == 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(501) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(501);
        if (y > 0.0f) ResetPrimaryCounters(503);
        return;
    }
    if (spirit > 0 &&
        aiCommand == 30 &&
        fieldF12 == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(500) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(500);
        if (y > 0.0f) ResetPrimaryCounters(502);
        return;
    }
    if (aiCommand == 12 &&
        fieldF12 == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        spirit > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(604) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(604);
        if (y > 0.0f) ResetPrimaryCounters(606);
        return;
    }
    if (aiCommand == 11 &&
        fieldF12 == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        spirit > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(608) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(608);
        if (y > 0.0f) ResetPrimaryCounters(610);
        return;
    }
    if (aiCommand == 10 &&
        fieldF12 == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        spirit > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(607) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(607);
        if (y > 0.0f) ResetPrimaryCounters(609);
        return;
    }
    if (aiCommand == 21 &&
        y == 0.0f &&
        fieldF12 == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        spirit > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(601) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(601);
        if (y > 0.0f) ResetPrimaryCounters(603);
        return;
    }
    if (aiCommand == 20 &&
        y == 0.0f &&
        fieldF12 == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        spirit > 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(600) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(600);
        if (y > 0.0f) ResetPrimaryCounters(602);
        return;
    }
    if (aiCommand == 101 &&
        fieldF12 == 0 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        y == 0.0f &&
        sequenceInfo->priority <= TARGET_PRIORITY(309) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(309);
        return;
    }
    if (aiCommand == 100 &&
        fieldF12 == 0 &&
        y == 0.0f &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(310) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(310);
        return;
    }
    if (FORWARD_INPUT && y == 0.0f && action != 207 &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(200) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(200);
        return;
    }
    if (FORWARD_INPUT && y > 0.0f &&
        !(y < 60.0f && velocityY > 0.0f) &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        field3AD < 2 && PRIORITY_OR_SPECIAL_RANK(202) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ++field3AD;
        ResetPrimaryCounters(202);
        return;
    }
    if (BACKWARD_INPUT && y == 0.0f &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        sequenceInfo->priority <= TARGET_PRIORITY(201) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(201);
        return;
    }
    if (BACKWARD_INPUT && y > 0.0f &&
        (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        field3AD < 2 && PRIORITY_OR_SPECIAL_RANK(203) &&
        ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ++field3AD;
        ResetPrimaryCounters(203);
        return;
    }
    if (NEGATIVE_VERTICAL_INPUT && (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        y == 0.0f && PRIORITY_OR_SPECIAL_RANK(204) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(204);
        return;
    }
    if (NEGATIVE_VERTICAL_BACK_INPUT && (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        y == 0.0f && PRIORITY_OR_SPECIAL_RANK(206) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(206);
        return;
    }
    if (NEGATIVE_VERTICAL_FORWARD_INPUT && (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
        y == 0.0f && PRIORITY_OR_SPECIAL_RANK(205) && ACTION_CHANGE_ALLOWED) {
        PackDirectionBits();
        ResetPrimaryCounters(205);
        return;
    }
    if (y == 0.0f && (inputY > 0 || bufferedY > 0)) {
        if (ATTACK_A && FORWARD_MOTION && action == 200 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0) {
            ResetPrimaryCounters(392);
            if (fieldF12 != 0) ResetPrimaryCounters(418);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_A && spirit > 0 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
            sequenceInfo->priority <= TARGET_PRIORITY(408) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(408);
            if (fieldF12 != 0) ResetPrimaryCounters(418);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_A && (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(302) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(302);
            if (fieldF12 != 0) ResetPrimaryCounters(418);
            ClearAuxiliaryWords();
            return;
        }
        if ((static_cast<unsigned long>(inputB) == 1 || bufferedA > 0) &&
            FORWARD_MOTION && action == 200 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0) {
            ResetPrimaryCounters(393);
            if (fieldF12 != 0) ResetPrimaryCounters(418);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B && spirit > 0 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
            sequenceInfo->priority <= TARGET_PRIORITY(413) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(413);
            if (fieldF12 != 0) ResetPrimaryCounters(418);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B && (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(303) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(303);
            if (fieldF12 != 0) ResetPrimaryCounters(418);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_C && (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            spirit > 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(402) && ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(402);
            if (fieldF12 != 0) ResetPrimaryCounters(418);
            ClearAuxiliaryWords();
            return;
        }
    }
    if (y == 0.0f && inputY == 0) {
        if (ATTACK_A &&
            inputY == 0 &&
            FORWARD_MOTION &&
            action == 200 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0) {
            ResetPrimaryCounters(390);
            if (fieldF12 != 0) ResetPrimaryCounters(417);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_A &&
            spirit > 0 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
            FORWARD_MOTION &&
            sequenceInfo->priority <= TARGET_PRIORITY(407) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(407);
            if (fieldF12 != 0) ResetPrimaryCounters(417);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_A &&
            spirit > 0 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
            sequenceInfo->priority <= TARGET_PRIORITY(406) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(406);
            if (fieldF12 != 0) ResetPrimaryCounters(416);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_A &&
            inputY == 0 &&
            FORWARD_MOTION &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(307) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(307);
            if (fieldF12 != 0) ResetPrimaryCounters(417);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_A &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            (sequenceInfo->priority <= TARGET_PRIORITY(300) || action == 300) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(300);
            if (fieldF12 != 0) ResetPrimaryCounters(416);
            ClearAuxiliaryWords();
            return;
        }
        if ((static_cast<unsigned long>(inputB) == 1 || bufferedA > 0) &&
            inputY == 0 &&
            FORWARD_MOTION &&
            action == 200 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0) {
            ResetPrimaryCounters(391);
            if (fieldF12 != 0) ResetPrimaryCounters(417);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B &&
            inputY == 0 &&
            FORWARD_MOTION &&
            spirit > 0 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
            sequenceInfo->priority <= TARGET_PRIORITY(412) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(412);
            if (fieldF12 != 0) ResetPrimaryCounters(417);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B &&
            spirit > 0 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            DISTANT_FROM_OPPONENT(320.0f, -320.0f) &&
            sequenceInfo->priority <= TARGET_PRIORITY(411) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(411);
            if (fieldF12 != 0) ResetPrimaryCounters(416);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B &&
            inputY == 0 &&
            FORWARD_MOTION &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(308) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(308);
            if (fieldF12 != 0) ResetPrimaryCounters(417);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(301) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(301);
            if (fieldF12 != 0) ResetPrimaryCounters(416);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_C &&
            inputY == 0 &&
            FORWARD_MOTION &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            spirit > 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(401) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(401);
            if (fieldF12 != 0) ResetPrimaryCounters(417);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_C &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            spirit > 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(400) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(400);
            if (fieldF12 != 0) ResetPrimaryCounters(416);
            ClearAuxiliaryWords();
            return;
        }
    }
    if (y > 0.0f) {
        if (ATTACK_A &&
            spirit > 0 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            DISTANT_FROM_OPPONENT(400.0f, -400.0f) &&
            (inputY > 0 || bufferedY > 0) &&
            sequenceInfo->priority <= TARGET_PRIORITY(410) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(410);
            if (fieldF12 != 0) ResetPrimaryCounters(420);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_A &&
            spirit > 0 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            DISTANT_FROM_OPPONENT(400.0f, -400.0f) &&
            sequenceInfo->priority <= TARGET_PRIORITY(409) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(409);
            if (fieldF12 != 0) ResetPrimaryCounters(419);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_A &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(304) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(304);
            if (fieldF12 != 0) ResetPrimaryCounters(419);
            if (fieldF12 != 0 && (inputY > 0 || bufferedY > 0)) ResetPrimaryCounters(420);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B &&
            spirit > 0 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            DISTANT_FROM_OPPONENT(480.0f, -480.0f) &&
            (inputY > 0 || bufferedY > 0) &&
            sequenceInfo->priority <= TARGET_PRIORITY(415) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(415);
            if (fieldF12 != 0) ResetPrimaryCounters(420);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B &&
            spirit > 0 &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            DISTANT_FROM_OPPONENT(480.0f, -480.0f) &&
            sequenceInfo->priority <= TARGET_PRIORITY(414) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(414);
            if (fieldF12 != 0) ResetPrimaryCounters(419);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_B &&
            (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
            sequenceInfo->priority <= TARGET_PRIORITY(305) &&
            ACTION_CHANGE_ALLOWED) {
            ResetPrimaryCounters(305);
            if (fieldF12 != 0) ResetPrimaryCounters(419);
            if (fieldF12 != 0 && (inputY > 0 || bufferedY > 0)) ResetPrimaryCounters(420);
            ClearAuxiliaryWords();
            return;
        }
        if (ATTACK_C) {
            if (inputY > 0 &&
                (frameInfo->flags & FrameFlags::CanCancel) != 0 &&
                spirit > 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(405) &&
                ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(405);
                if (fieldF12 != 0) ResetPrimaryCounters(420);
                ClearAuxiliaryWords();
                return;
            }
            if ((frameInfo->flags & FrameFlags::CanCancel) != 0 &&
                spirit > 0 &&
                sequenceInfo->priority <= TARGET_PRIORITY(404) &&
                ACTION_CHANGE_ALLOWED) {
                ResetPrimaryCounters(404);
                if (fieldF12 != 0) ResetPrimaryCounters(419);
                ClearAuxiliaryWords();
                return;
            }
        }
        if (inputD > 0 || bufferedD > 0) {
            if ((frameInfo->flags & FrameFlags::CanCancel) != 0 &&
                field3AD < 2 &&
                facing * inputX == 1 &&
                !(y < 60.0f && velocityY > 0.0f) &&
                PRIORITY_OR_SPECIAL_RANK(202) && ACTION_CHANGE_ALLOWED) {
                PackDirectionBits();
                ++field3AD;
                ResetPrimaryCounters(202);
                return;
            }
            if ((frameInfo->flags & FrameFlags::CanCancel) != 0 &&
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
            if ((frameInfo->flags & FrameFlags::CanCancel) != 0 &&
                field3AD < 2 &&
                facing * inputX > 0 &&
                !(y < 60.0f && velocityY > 0.0f) &&
                PRIORITY_OR_SPECIAL_RANK(202) && ACTION_CHANGE_ALLOWED) {
                PackDirectionBits();
                ++field3AD;
                ResetPrimaryCounters(202);
                return;
            }
            if ((frameInfo->flags & FrameFlags::CanCancel) != 0 &&
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
