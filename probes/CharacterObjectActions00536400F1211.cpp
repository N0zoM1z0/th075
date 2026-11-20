// Work in progress toward the complete original 00536400 (39,999 CODE B).
// The typed owner history relay and the written cases are native game logic.
// All native states are written; this draft remains NONEXACT and is not
// an executable replacement or an accepted reconstruction unit.
// See docs/OBJECT_ADVANCE_00536400_HISTORY_AND_CASES_F1211.md.
#include "CharacterObject.hpp"
#include "YoumuFighter.hpp"
#include "YoumuObjectHistoryF1211.hpp"
#include "FighterAnimationPhaseBorrowedF1024.hpp"



extern float g_F1069_ParentYFirstAt00659138;
extern float g_F1069_ParentYSecondAt00658264;
extern float g_F1057_YOffsetAt00657888;
extern float g_F1057_NudgeAt00657480;
extern float g_F1057_SpeedBaseAt006590BC;
extern float g_F1051_ScaleCeilingAt0065747C;
extern float g_F1211_SplitAltitudeAt006599EC;
extern float g_F1211_HalfSpreadAt00657878;
extern float g_F1211_RightBoundAt00659424;
extern float g_F1211_LowerBoundAt006595EC;
extern float g_F1211_UpperBoundAt006583B4;
extern float g_F1211_AngleDivAt00657828;
extern signed char g_F1212_DifficultyAt006714D0;


void YoumuObject::Advance()
{
    int burstIndex;
    ObjectHistoryEntryF1211* entry;
    if (owner->opponent->field3BA != 0) return;
    if (owner->field3BA != 0 && field08A == 0) return;

    if (action < 800) {
        static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
        if (owner->field39D == 1) {
            owner->field09C = 0.5f;
            owner->UpdateGaugeTimer(5);
            static_cast<YoumuFighter*>(owner)->fieldF10 = owner->spirit;
        }
        if (owner->field39D == 2) {
            owner->field09C = 0.4f;
            owner->UpdateGaugeTimer(7);
            static_cast<YoumuFighter*>(owner)->fieldF10 = owner->spirit;
        }
        if (static_cast<YoumuFighter*>(owner)->fieldF10 <= 0 || owner->field3A0 <= 0) {
            owner->field09C = 1.0f;
            static_cast<YoumuFighter*>(owner)->fieldF10 = 0;
            ResetPrimaryCounters(810);
            return;
        }
        field08A = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 128;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field010 = 0x82;
        if (owner->field082 != 0) return;

        entry = &static_cast<YoumuFighter*>(owner)->historyQueue.front();
        if (action != entry->actionAt00)
            field080 = entry->counterAt0E;
        if (animationStage != entry->stageAt02)
            field07C = 0;
        SetThreeCounters(entry->actionAt00, entry->stageAt02, 0);
        x = entry->xAt04;
        y = entry->yAt08;
        facing = entry->facingAt0C;
        return;
    }
    if (field082 != 0) {
        --field082;
        return;
    }
    switch (action) {
    case 800:
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0)
                field0D8 = 0;
            if (animationStage == 1 && animationFrame == 0) {
                owner->field314 = field0D8;
                if (field0C8 == 1.0f)
                    owner->SpawnBattleEffect(803,
                        (field0D8 * 23 - 75) * facing + x,
                        y + 215.0f - field0D8 * 19,
                        facing, 1);
                if (field0C8 == 2.0f)
                    owner->SpawnBattleEffect(805,
                        facing * 100 + x,
                        y + 200.0f - field0D8 * 25,
                        facing, 1);
                if (field0C8 == 3.0f)
                    owner->SpawnBattleEffect(807,
                        (field0D8 * 15 - 10) * facing + x,
                        y + 20.0f + field0D8 * 20,
                        facing, 1);
            }
            if (AdvanceNestedFrame() == field070) {
                if (field0D8 < 10) {
                    ResetSecondaryCounter(1);
                    ++field0D8;
                    return;
                }
                else {
                    ClearFrameInfo();
                }
            }
        }
        break;

    case 801:
        if (owner->action == 402 && field0D8 == 0) {
            x = owner->x + facing * 99;
            y = owner->y + 66.0f;
        }
        if (owner->action != 402) field0D8 = 1;
        if (field07C == 6) {
            field07C = 0;
            field080 = 1;
        }
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                ResetTransform(-20.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
        scaleX += 0.1f;
        scaleY *= 0.85f;
        if (animationStage > 1 && color[0] > 0)
            color[0] -= 3;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 802:
        if (owner->action == 404 && field0D8 == 0) {
            x = owner->x + facing * 83;
            y = owner->y + 114.0f;
        }
        if (owner->action != 404) field0D8 = 1;
        if (field07C == 6) {
            field07C = 0;
            field080 = 1;
        }
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                ResetTransform(-20.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
        scaleX += 0.1f;
        scaleY *= 0.85f;
        if (animationStage > 1 && color[0] > 0)
            color[0] -= 3;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 803:
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                owner->PlaySharedSound(42);
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 2.5f;
                scaleY = 2.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (animationStage == 2 && animationFrame == 0) {
                owner->field314 = field0D8;
                if (field0DA != 1)
                    owner->SpawnBattleEffect(804, x, y, facing, 1);
            }
            scaleX *= 0.95f;
            scaleY *= 0.95f;
            if (animationStage == 2 && color[0] > 10)
                color[0] -= 10;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 804:
        if (field07C == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0DA = 1000.0f - field0C8 * 60.0f;
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                field0DC = AngleAt00483300(
                    owner->opponent->y + 100.0f - y,
                    (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828;
                if (field0DC < -20) field0DC = 10;
                if (field0DC > 20) field0DC = -10;
                SetPolarVelocity(field0DC, field0DA * 0.01f);
                scaleX = 1.5f;
                scaleY = 1.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            if ((field07C == 1 || field07C == 2 || field07C == 4) && animationStage < 2) {
                ResetSecondaryCounter(2);
                return;
            }
            else {
                if (field0DA < 800) field0DA = 800;
                SetPolarVelocity(field0DC, field0DA * 0.01f);
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > g_F1211_RightBoundAt00659424 ||
                    x < g_F1211_LowerBoundAt006595EC ||
                    y > g_F1211_UpperBoundAt006583B4 ||
                    y < g_F1211_LowerBoundAt006595EC) {
                    ClearFrameInfo();
                    return;
                }
                else {
                    if (color[0] > 20 && animationStage == 2)
                        color[0] -= 20;
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

    case 805:
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                owner->PlaySharedSound(42);
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 2.5f;
                scaleY = 2.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (animationStage == 2 && animationFrame == 0) {
                owner->field314 = field0D8;
                if (field0DA != 1)
                    owner->SpawnBattleEffect(806, x, y, facing, 1);
            }
            scaleX *= 0.95f;
            scaleY *= 0.95f;
            if (animationStage == 2 && color[0] > 10)
                color[0] -= 10;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 806:
        if (field07C == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0DA = 1000.0f - field0C8 * 60.0f;
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                field0DC = AngleAt00483300(
                    owner->opponent->y + 100.0f - y,
                    (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828;
                if (field0DC < -65) field0DC = -55;
                if (field0DC > -25) field0DC = -15;
                SetPolarVelocity(field0DC, field0DA * 0.01f);
                scaleX = 1.5f;
                scaleY = 1.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            if ((field07C == 1 || field07C == 2 || field07C == 4) && animationStage < 2) {
                ResetSecondaryCounter(2);
                return;
            }
            else {
                if (field0DA < 800) field0DA = 800;
                SetPolarVelocity(field0DC, field0DA * 0.01f);
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > g_F1211_RightBoundAt00659424 ||
                    x < g_F1211_LowerBoundAt006595EC ||
                    y > g_F1211_UpperBoundAt006583B4 ||
                    y < g_F1211_LowerBoundAt006595EC) {
                    ClearFrameInfo();
                    return;
                }
                else {
                    if (color[0] > 20 && animationStage == 2)
                        color[0] -= 20;
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

    case 807:
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                owner->PlaySharedSound(42);
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 2.5f;
                scaleY = 2.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (animationStage == 2 && animationFrame == 0) {
                owner->field314 = field0D8;
                if (field0DA != 1)
                    owner->SpawnBattleEffect(808, x, y, facing, 1);
            }
            scaleX *= 0.95f;
            scaleY *= 0.95f;
            if (animationStage == 2 && color[0] > 10)
                color[0] -= 10;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 808:
        if (field07C == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0DA = 1000.0f - field0C8 * 60.0f;
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                field0DC = AngleAt00483300(
                    owner->opponent->y + 100.0f - y,
                    (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828;
                if (field0DC < 25) field0DC = 35;
                if (field0DC > 65) field0DC = 55;
                SetPolarVelocity(field0DC, field0DA * 0.01f);
                scaleX = 1.5f;
                scaleY = 1.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            if ((field07C == 1 || field07C == 2 || field07C == 4) && animationStage < 2) {
                ResetSecondaryCounter(2);
                return;
            }
            else {
                if (field0DA < 800) field0DA = 800;
                SetPolarVelocity(field0DC, field0DA * 0.01f);
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > g_F1211_RightBoundAt00659424 ||
                    x < g_F1211_LowerBoundAt006595EC ||
                    y > g_F1211_UpperBoundAt006583B4 ||
                    y < g_F1211_LowerBoundAt006595EC) {
                    ClearFrameInfo();
                    return;
                }
                else {
                    if (color[0] > 20 && animationStage == 2)
                        color[0] -= 20;
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

    case 809:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.8f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = -field0C8;
        }
        if (animationStage == 1 && owner->animationStage > 8) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            if (animationStage == 2) {
                scaleX += 0.2f;
                scaleY *= 0.9f;
                if (color[0] > 9) color[0] -= 9;
                else color[0] = 0;
            }
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 810:
        static_cast<YoumuFighter*>(owner)->fieldF12 = 0;
        if (owner->action == 704 || owner->action == 705) field08A = 1;
        else field08A = 0;
        if (static_cast<YoumuFighter*>(owner)->fieldF10 > 0) {
            ClearFrameInfo();
            owner->SpawnTrackedEffect(0, owner->x, owner->y, facing, 0, 0, 1);
            return;
        }
        else {
            facing = owner->facing;
            if (owner->action == 796 && owner->animationStage == 17 &&
                (owner->field370[owner->field39D]) == 2) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetPrimaryCounters(911);
                return;
            }
            else if (owner->action == 796 && owner->animationStage == 17 &&
                (owner->field370[owner->field39D]) == 0) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                field0C8 = 0.0f;
                ResetPrimaryCounters(905);
                if (g_F1212_DifficultyAt006714D0 == 3) {
                    owner->field314 = 1.0f;
                    owner->SpawnBattleEffect(905, x, y, facing, 1);
                }
                return;
            }
            else if (owner->action == 412 && owner->animationStage == 3) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetPrimaryCounters(836);
                owner->PlaySound(12);
                return;
            }
            else if (owner->action == 414 && owner->animationStage == 3) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetPrimaryCounters(846);
                owner->PlaySound(12);
                return;
            }
            else if (owner->action == 416 && owner->animationStage == 3) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetPrimaryCounters(847);
                owner->PlaySound(12);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    field0D8 = 1;
                }
                if (facing == 1)
                    velocityX = (owner->x - (owner->action != 706) * 100 - x +
                        (owner->action == 704 || owner->action == 705) * 100) * 0.05f;
                if (facing == -1)
                    velocityX = -((owner->x + (owner->action != 706) * 100 - x -
                        (owner->action == 704 || owner->action == 705) * 100) * 0.05f);
                velocityY = (owner->y + 200.0f - (owner->action == 706) * 100 - y -
                    (owner->action == 704 || owner->action == 705) * 100) * 0.05f;
                x = facing * velocityX + x;
                y += velocityY;
                if (field08A == 0)
                    owner->SpawnBattleEffect(811, x - 10.0f + RecordedRange(0, 20),
                        y - 10.0f + RecordedRange(0, 20), facing, 1);
                if (field08A != 0)
                    owner->SpawnTrackedEffect(811, x - 10.0f + RecordedRange(0, 20),
                        y - 10.0f + RecordedRange(0, 20), facing, 1, 0, 1);
                if (animationFrame == 0) {
                    field0DA = RecordedRange(0, 20);
                    scaleX = field0DA * 0.01f + 0.9f;
                    scaleY = field0DA * 0.01f + 0.9f;
                }
                if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(0);
            }
        }
        break;

    case 811:
        facing = owner->facing;
        if (owner->action == 704 || owner->action == 705) field08A = 1;
        else field08A = 0;
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.8f;
            scaleY = 0.8f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            velocityY = 4.0f;
            velocityX = 0.0f;
        }
        velocityY -= 0.1f;
        x = facing * velocityX + x;
        y += velocityY;
        if (color[0] > 13) color[0] -= 13;
        else color[0] = 0;
        scaleX *= 0.94f;
        scaleY *= 0.94f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 0x331: {
    facing = owner->facing;
    if (owner->action>0x95 &&
        owner->action<0x9A &&
        animationStage==0) {
        x=owner->x+
            float(facing*57);
        y=(*(&owner->y))+
            g_F1069_ParentYFirstAt00659138;
    }
    if (owner->action>0x99 &&
        owner->action<0x9E &&
        animationStage==0) {
        x=owner->x+
            float(facing*57);
        y=(*(&owner->y))+
            g_F1069_ParentYSecondAt00658264;
    }
    if (owner->action==0x9E &&
        animationStage==0) {
        x=owner->x+
            float(facing*57);
        y=(*(&owner->y))+
            g_F1057_YOffsetAt00657888;
    }
    if ((owner->action<0x96 ||
         owner->action>0x9E) &&
        animationStage==0) {
        ResetSecondaryCounter(1);
        owner->fieldF0A=0;
    }
    if (animationStage==0 &&
        animationFrame==0 &&
        field0D8==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationY=50.0f;
        field0D8=1;
    }
    rotationZ=(rotationZ)+g_F1057_NudgeAt00657480;
    if (animationStage>0) {
        if (color[0]>30)
            color[0]-=30;
        else
            color[0]=0;
    }
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    if (animationStage==1 && animationFrame==0)
        ResetSecondaryCounter(0);
    return;
}

    case 820:
        if (owner->action == 308) {
            x = owner->x;
            y = owner->y;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 821:
        if (owner->action == 504) {
            x = owner->x;
            y = owner->y;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 822:
        if (owner->action == 502 || owner->action == 513) {
            x = owner->x;
            y = owner->y;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 823:
        if (owner->action == 503) {
            x = owner->x;
            y = owner->y;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 824:
        if (owner->action == 500 || owner->action == 501) {
            x = owner->x;
            y = owner->y;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 825:
        if (owner->action == 309) {
            x = owner->x;
            y = owner->y;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 826:
        if (owner->action == 310) {
            x = owner->x;
            y = owner->y;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 827:
        if (owner->action == 501) {
            x = owner->x;
            y = owner->y;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 828:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(30.0f, 60.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (animationStage < 14 && animationStage > 5) {
        scaleX += 0.004f;
        scaleY += 0.004f;
    }
    if (animationStage < 14 && owner->animationStage > 3) {
        ResetSecondaryCounter(14);
        ResetTransform(0.0f, 0.0f, 0.0f);
        return;
    }
    else {
        if (animationStage > 27) {
            scaleX = 1.0f;
            scaleY = 1.0f;
        }
        if (owner->action == 702) {
            x = owner->x;
            y = owner->y;
        }
        else {
            ClearFrameInfo();
            return;
        }
        if (owner->field082 == 0) {
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            if (animationStage == 14 && animationFrame == 0 && owner->animationStage < 4)
            ResetSecondaryCounter(6);
            if (animationStage == 28 && animationFrame == 0)
            ResetTransform(55.0f, 2.0f, 0.0f);
        }
    }
    break;

    case 829:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(40.0f, 75.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (animationStage < 14 && animationStage > 5) {
        scaleX += 0.004f;
        scaleY += 0.004f;
    }
    if (animationStage < 14 && owner->animationStage > 3) {
        ResetSecondaryCounter(14);
        ResetTransform(0.0f, 0.0f, 0.0f);
        return;
    }
    else if (owner->action == 703) {
        x = owner->x;
        y = owner->y;
    }
    else {
        ClearFrameInfo();
        return;
    }
    if (owner->field082 == 0) {
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 14 && animationFrame == 0 && owner->animationStage < 4)
        ResetSecondaryCounter(6);
        if (animationStage == 28 && animationFrame == 0)
        ResetTransform(55.0f, 2.0f, 0.0f);
    }
    break;

    case 832:
        if (owner->action > 49 && owner->action < 150 && animationStage < 7) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
            owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
            owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
            owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
            owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
            owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
            owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
            owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
            owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
            owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(3.0f, 137.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationX = facing * -30;
                rotationY = 60.0f;
                field080 = 999;
                field0D8 = 0;
            }
            rotationZ += 10.0f;
            if (field07C == 5) {
                PlaySharedSound(37);
                owner->SpawnBattleEffect(839, field08C, field090, facing, 1);
                owner->SpawnBattleEffect(839, field08C, field090, facing, 1);
                owner->SpawnBattleEffect(839, field08C, field090, facing, 1);
                field07C = 0;
            }
            if (field07C != 0) field07C = 0;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            if (animationStage == 7 && animationFrame == 0 && field0D8 < 30) {
                ++field0D8;
                ResetSecondaryCounter(6);
            }
        }
        break;

    case 833:
        if (owner->action == 390) {
            x = owner->x;
            y = owner->y;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 834:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->action > 49 && owner->action < 150) {
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        ResetPrimaryCounters(810);
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            if (field0D8 == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 1;
                field0DC = 0;
                velocityX = 7.0f;
                velocityY = 8.0f;
            }
            owner->field314 = 1000.0f;
            owner->field318 = -45.0f;
            owner->SpawnBattleEffect(835, x, y, facing, 1);
            owner->UpdateGaugeTimer(20);
            owner->PlaySharedSound(42);
        }
        velocityY -= 0.4f;
        if (velocityY <= -0.5f) velocityY = -0.5f;
        x = facing * velocityX + x;
        y += velocityY;
        owner->SpawnBattleEffect(811, x - 10.0f + RecordedRange(0, 20),
        y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.9f;
            scaleY = field0DA * 0.01f + 0.9f;
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(0);
            ++field0DC;
            if (field0DC > 15) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetPrimaryCounters(810);
                return;
            }
        }
    }
    break;

    case 835:
        if (field07C == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            ClearFrameInfo();
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0DA = field0C8;
                field0DC = field0CC;
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                SetPolarVelocity(field0DC, field0DA * 0.01f);
                scaleX = 1.5f;
                scaleY = 1.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            if ((field07C == 1 || field07C == 2 || field07C == 4 || field07C == 6) && animationStage < 2) {
                ResetSecondaryCounter(2);
                return;
            }
            else {
                SetPolarVelocity(field0DC, field0DA * 0.01f);
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > g_F1211_RightBoundAt00659424 ||
                    x < g_F1211_LowerBoundAt006595EC ||
                    y > g_F1211_UpperBoundAt006583B4 ||
                    y < g_F1211_LowerBoundAt006595EC) {
                    ClearFrameInfo();
                    return;
                }
                else {
                    if (color[0] > 20 && animationStage == 2)
                        color[0] -= 20;
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

    case 836:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->action > 49 && owner->action < 150) {
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        ResetPrimaryCounters(810);
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            field0DA = 0;
            field0DC = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            owner->field314 = 1000.0f;
            owner->field318 = field0DC * 3 - 30;
            owner->UpdateGaugeTimer(20);
            owner->SpawnBattleEffect(835, x, y, facing, 1);
            owner->PlaySharedSound(42);
            ++field0DC;
        }
        x = facing * velocityX + x;
        y += velocityY;
        owner->SpawnBattleEffect(811, x - 10.0f + RecordedRange(0, 20),
        y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.9f;
            scaleY = field0DA * 0.01f + 0.9f;
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(1);
            if (field0DC > 5) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetPrimaryCounters(810);
                return;
            }
        }
    }
    break;

    case 837:
        x = owner->x;
        y = owner->y + 100.0f;
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0DA = static_cast<YoumuFighter*>(owner)->fieldF10;
        }
        scaleX = static_cast<float>(static_cast<YoumuFighter*>(owner)->fieldF10) / field0DA * 2;
        scaleY = static_cast<float>(static_cast<YoumuFighter*>(owner)->fieldF10) / field0DA * 2;
        if (animationStage == 1 && static_cast<YoumuFighter*>(owner)->fieldF10 > 0) {
            if (color[0] < 245) color[0] += 10;
            else color[0] = 255;
        }
        if (static_cast<YoumuFighter*>(owner)->fieldF10 <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            rotationZ += 1.0f;
            if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(1);
        }
        break;

    case 838:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.3f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 839:
        if (field07C == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0DA = field0C8;
                field0DC = field0CC;
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                SetPolarVelocity(30 - RecordedRange(0, 60), RecordedRange(0, 10) + 10);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            if ((field07C == 1 || field07C == 2 || field07C == 4) && animationStage < 2) {
                ResetSecondaryCounter(2);
                return;
            }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > g_F1211_RightBoundAt00659424 ||
                    x < g_F1211_LowerBoundAt006595EC ||
                    y > g_F1211_UpperBoundAt006583B4 ||
                    y < g_F1211_LowerBoundAt006595EC) {
                    ClearFrameInfo();
                    return;
                }
                else {
                    if (color[0] > 20 && animationStage == 2)
                        color[0] -= 20;
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

    case 840:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(50.0f, 20.0f, 0.0f);
            scaleX = 1.01f;
            scaleY = 1.01f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX += 0.001f;
        scaleY += 0.0015f;
        if (color[0] > 10) {
            color[0] -= 10;
        }
        else {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 841:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(55.0f, 2.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.1f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX += 0.01f;
        scaleY += 0.02f;
        if (color[0] > 10) {
            color[0] -= 10;
        }
        else {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 842:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationZ = field0C8;
        SetPolarVelocity(field0C8, 30.0f);
    }
    if (animationStage == 1) {
        scaleX += 0.2f;
        scaleY -= 0.19f;
    }
    if (animationStage == 2) scaleX += 0.2f;
    x = facing * velocityX + x;
    y += velocityY;
    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
    break;

    case 843:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
        field07C = 0;
        field080 = 1;
        field0D8 = RecordedRange(0, 100);
        ResetSecondaryCounter(4);
        if (field0D8 < 75) ResetSecondaryCounter(3);
        if (field0D8 < 50) ResetSecondaryCounter(2);
        if (field0D8 < 25) ResetSecondaryCounter(1);
    }
    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
    if (animationFrame == 0) ClearFrameInfo();
    break;

    case 844:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.8f;
            scaleY = 4.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = 90.0f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 845:
    if (owner->action > 49 && owner->action < 150 && animationStage < 7) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
        owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
        owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
        owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
        owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
        owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
        owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
        owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
        owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
        owner->SpawnBattleEffect(996, x, y + 100.0f, 1, 1);
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(3.0f, 137.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = facing * -30;
            rotationY = 60.0f;
            field080 = 999;
            field0D8 = 0;
        }
        rotationZ += 10.0f;
        if (field07C == 5) {
            PlaySharedSound(37);
            owner->SpawnBattleEffect(839, field08C, field090, facing, 1);
            owner->SpawnBattleEffect(839, field08C, field090, facing, 1);
            owner->SpawnBattleEffect(839, field08C, field090, facing, 1);
            field07C = 0;
        }
        if (field07C != 0) field07C = 0;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 7 && animationFrame == 0 && field0D8 < 40) {
            ++field0D8;
            ResetSecondaryCounter(6);
        }
    }
    break;

    case 846:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->action > 49 && owner->action < 150) {
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        ResetPrimaryCounters(810);
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            field0DA = 0;
            field0DC = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            owner->field314 = 1000.0f;
            owner->field318 = field0DC * 3 + 10;
            owner->UpdateGaugeTimer(20);
            owner->SpawnBattleEffect(835, x, y, facing, 1);
            owner->PlaySharedSound(42);
            ++field0DC;
        }
        x = facing * velocityX + x;
        y += velocityY;
        owner->SpawnBattleEffect(811, x - 10.0f + RecordedRange(0, 20),
        y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.9f;
            scaleY = field0DA * 0.01f + 0.9f;
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(1);
            if (field0DC > 5) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetPrimaryCounters(810);
                return;
            }
        }
    }
    break;

    case 847:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->action > 49 && owner->action < 150) {
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        ResetPrimaryCounters(810);
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            field0DA = 0;
            field0DC = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            owner->field314 = 1000.0f;
            owner->field318 = field0DC * 3 - 50;
            owner->UpdateGaugeTimer(20);
            owner->SpawnBattleEffect(835, x, y, facing, 1);
            owner->PlaySharedSound(42);
            ++field0DC;
        }
        x = facing * velocityX + x;
        y += velocityY;
        owner->SpawnBattleEffect(811, x - 10.0f + RecordedRange(0, 20),
        y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.9f;
            scaleY = field0DA * 0.01f + 0.9f;
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(1);
            if (field0DC > 5) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetPrimaryCounters(810);
                return;
            }
        }
    }
    break;

    case 848:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->action > 49 && owner->action < 150) {
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        ResetPrimaryCounters(810);
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            field0DA = 0;
            field0DC = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            owner->field314 = 1000.0f;
            owner->field318 = field0DC * 3 - 30;
            owner->UpdateGaugeTimer(20);
            owner->SpawnBattleEffect(835, x, y, facing, 1);
            owner->PlaySharedSound(42);
            ++field0DC;
        }
        x = facing * velocityX + x;
        y += velocityY;
        owner->SpawnBattleEffect(811, x - 10.0f + RecordedRange(0, 20),
        y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.9f;
            scaleY = field0DA * 0.01f + 0.9f;
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(1);
            if (field0DC > 8) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetPrimaryCounters(810);
                return;
            }
        }
    }
    break;

    case 849:
    if (field07C == 5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 20;
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (field07C != 0 || field0D8 > 0) {
            if (field07C == 6) {
                field07C = 0;
                ++field080;
            }
            else {
                if (color[0] > 20) {
                    color[0] -= 20;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            field07C = 1;
        }
        --field0DA;
        if (field0DA < 5) field0DA = 5;
        SetPolarVelocity(20.0f, field0DA);
        x = facing * velocityX + x;
        y -= velocityY;
        if (x > g_F1211_RightBoundAt00659424 ||
        x < g_F1211_LowerBoundAt006595EC ||
        y > g_F1211_UpperBoundAt006583B4 ||
        y < g_F1211_LowerBoundAt006595EC) {
            ClearFrameInfo();
            return;
        }
        else {
            if (AdvanceNestedFrame() == field070) {
                ResetSecondaryCounter(1);
                ++field0D8;
            }
        }
    }
    break;

    case 850:
    if (field07C == 5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 20;
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (field07C != 0 || field0D8 > 0) {
            if (field07C == 6) {
                field07C = 0;
                ++field080;
            }
            else {
                if (color[0] > 20) {
                    color[0] -= 20;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            field07C = 1;
        }
        --field0DA;
        if (field0DA < 5) field0DA = 5;
        SetPolarVelocity(-30.0f, field0DA);
        x = facing * velocityX + x;
        y -= velocityY;
        if (x > g_F1211_RightBoundAt00659424 ||
        x < g_F1211_LowerBoundAt006595EC ||
        y > g_F1211_UpperBoundAt006583B4 ||
        y < g_F1211_LowerBoundAt006595EC) {
            ClearFrameInfo();
            return;
        }
        else {
            if (AdvanceNestedFrame() == field070) {
                ResetSecondaryCounter(1);
                ++field0D8;
            }
        }
    }
    break;

    case 851:
    if (field07C == 5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 20;
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (field07C != 0 || field0D8 > 0) {
            if (field07C == 6) {
                field07C = 0;
                ++field080;
            }
            else {
                if (color[0] > 20) {
                    color[0] -= 20;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            field07C = 1;
        }
        --field0DA;
        if (field0DA < 5) field0DA = 5;
        SetPolarVelocity(0.0f, field0DA);
        x = facing * velocityX + x;
        y -= velocityY;
        if (x > g_F1211_RightBoundAt00659424 ||
        x < g_F1211_LowerBoundAt006595EC ||
        y > g_F1211_UpperBoundAt006583B4 ||
        y < g_F1211_LowerBoundAt006595EC) {
            ClearFrameInfo();
            return;
        }
        else {
            if (AdvanceNestedFrame() == field070) {
                ResetSecondaryCounter(1);
                ++field0D8;
            }
        }
    }
    break;

    case 900:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->field3A0 <= 0) {
        ResetPrimaryCounters(810);
        static_cast<YoumuFighter*>(owner)->fieldF12 = 0;
        if (field0DE == 1) ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && g_F1212_DifficultyAt006714D0 == 0) {
        ResetPrimaryCounters(916);
        field0D8 = 0;
        field0DA = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 128;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field07C = 0;
        field080 = 1;
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    if (animationStage > 1 && animationStage < 10 &&
    AbsFloatAt00412D90(owner->opponent->x - x) < 320.0f) {
        ResetSecondaryCounter(10);
        return;
    }
    else {
        if (animationStage > 15) {
            velocityX -= 0.25f;
            if (velocityX < 0.0f) velocityX = 0.0f;
        }
        x = facing * velocityX + x;
        y += velocityY;
        if (x < 30.0f) {
            velocityX = 0.0f;
            x = 30.0f;
        }
        if (x > 1250.0f) {
            velocityX = 0.0f;
            x = 1250.0f;
        }
        if (AdvanceNestedFrame() == field070) ResetPrimaryCounters(903);
        if (animationStage == 2 && animationFrame == 0) velocityX = 12.5f;
        if (animationStage == 10 && animationFrame == 0 && field0D8 < 1) {
            ++field0D8;
            ResetSecondaryCounter(2);
        }
        if (animationStage == 15 && animationFrame == 0) {
            owner->SpawnAuxEffect(128, facing * 100 + x,
            y, facing, 1);
            owner->SpawnBattleEffect(822, x, y, facing, 1);
            owner->PlaySound(2);
        }
        if (animationStage == 16 && animationFrame == 0) velocityX = 17.5f;
    }
    break;

    case 901:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->field3A0 <= 0) {
        ResetPrimaryCounters(810);
        static_cast<YoumuFighter*>(owner)->fieldF12 = 0;
        if (field0DE == 1) ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && g_F1212_DifficultyAt006714D0 == 0) {
        ResetPrimaryCounters(916);
        field0D8 = 0;
        field0DA = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 128;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
    }
    if (animationStage == 2 && animationFrame == 0) {
        field07C = 0;
        field080 = 1;
        velocityX = 10.0f;
        velocityY = 0.0f;
        owner->SpawnBattleEffect(827, x, y, facing, 1);
        owner->PlaySound(1);
    }
    if (animationStage == 13 && animationFrame == 0) {
        owner->SpawnBattleEffect(824, x, y, facing, 1);
        owner->PlaySound(1);
    }
    if (velocityX > 0.0f) {
        velocityX -= 0.5f;
        if (velocityX < 0.0f) velocityX = 0.0f;
    }
    if (y > 0.0f && animationStage < 24) {
        velocityY -= 0.65f;
        if (y + velocityY <= 0.0f) {
            ResetSecondaryCounter(24);
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
            return;
        }
    }
    x = facing * velocityX + x;
    y += velocityY;
    if (x < 30.0f) {
        velocityX = 0.0f;
        x = 30.0f;
    }
    if (x > 1250.0f) {
        velocityX = 0.0f;
        x = 1250.0f;
    }
    if (AdvanceNestedFrame() == field070) ResetPrimaryCounters(903);
    if (animationStage == 13 && animationFrame == 0 && field0D8 < 1) {
        ++field0D8;
        ResetSecondaryCounter(2);
    }
    if (animationStage == 15 && animationFrame == 0) {
        velocityX = 12.5f;
        velocityY = 15.0f;
        field07C = 0;
        field080 = 1;
    }
    if (animationStage == 24 && animationFrame == 0) ResetSecondaryCounter(22);
    break;

    case 902:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->field3A0 <= 0) {
        ResetPrimaryCounters(810);
        static_cast<YoumuFighter*>(owner)->fieldF12 = 0;
        if (field0DE == 1) ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && g_F1212_DifficultyAt006714D0 == 0) {
        ResetPrimaryCounters(916);
        field0D8 = 0;
        field0DA = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 128;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        velocityX = 0.0f;
        velocityY = 0.0f;
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
    }
    if (animationStage == 2 && animationFrame == 0) {
        field07C = 0;
        field080 = 1;
        velocityX = 10.0f;
        velocityY = 0.0f;
    }
    if (y > 0.0f && animationStage < 26) {
        velocityY -= 0.8f;
        if (y + velocityY <= 0.0f) {
            ResetSecondaryCounter(26);
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
            return;
        }
    }
    x = facing * velocityX + x;
    y += velocityY;
    if (x < 30.0f) {
        velocityX = 0.0f;
        x = 30.0f;
    }
    if (x > 1250.0f) {
        velocityX = 0.0f;
        x = 1250.0f;
    }
    if (AdvanceNestedFrame() == field070) ResetPrimaryCounters(903);
    if (animationStage == 3 && animationFrame == 0) {
        owner->SpawnAuxEffect(127, x, y, facing, 1);
        velocityX = RecordedRange(0, 6) + 7.5f;
        velocityY = 16.0f;
        field07C = 0;
        field080 = 1;
    }
    if (animationStage == 18 && animationFrame == 0) {
        owner->SpawnBattleEffect(821, x, y, facing, 1);
        owner->PlaySound(4);
    }
    if (animationStage == 26 && animationFrame == 0) ResetSecondaryCounter(24);
    break;

    case 903:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->action > 49 && owner->action < 150 && g_F1212_DifficultyAt006714D0 == 0) {
        ResetPrimaryCounters(916);
        field0D8 = 0;
        field0DA = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        return;
    }
    if (owner->field3A0 <= 0) {
        ResetPrimaryCounters(810);
        static_cast<YoumuFighter*>(owner)->fieldF12 = 0;
        if (field0DE == 1) ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 128;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field0D8 = RecordedRange(0, 30) + 90 - g_F1212_DifficultyAt006714D0 * 30;
        field0DA = 0;
        field0DC = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    --field0D8;
    if (field0D8 <= 0) {
        if (RecordedRange(0, 100) < 25) ResetPrimaryCounters(904);
        if (AbsFloatAt00412D90(owner->opponent->x - x) < 320.0f && RecordedRange(0, 100) < 50) {
            ResetPrimaryCounters(901);
            return;
        }
        if (AbsFloatAt00412D90(owner->opponent->x - x) > 320.0f && RecordedRange(0, 100) < 50) {
            if (RecordedRange(0, 100) < 50) {
                ResetPrimaryCounters(900);
                return;
            }
            else {
                ResetPrimaryCounters(902);
                return;
            }
        }
        field0DA = RecordedRange(0, 100);
        if (field0DA < 25) { ResetPrimaryCounters(900); return; }
        if (field0DA < 50) { ResetPrimaryCounters(901); return; }
        if (field0DA < 75) { ResetPrimaryCounters(902); return; }
        if (field0DA < 999) { ResetPrimaryCounters(904); return; }
    }
    if (owner->opponent->x > x) facing = 1;
    else facing = -1;
    x = facing * velocityX + x;
    y += velocityY;
    if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(1);
    break;

    case 904:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->action > 49 && owner->action < 150 && g_F1212_DifficultyAt006714D0 == 0) {
        ResetPrimaryCounters(916);
        field0D8 = 0;
        field0DA = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        return;
    }
    if (owner->field3A0 <= 0) {
        ResetPrimaryCounters(810);
        static_cast<YoumuFighter*>(owner)->fieldF12 = 0;
        if (field0DE == 1) ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 128;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field0D8 = RecordedRange(0, 120) - 60;
        field0DC = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    if (field0D8 < 0) {
        ++field0D8;
        velocityX = 3.0f;
        if (x < 30.0f) {
            velocityX = 0.0f;
            x = 30.0f;
        }
        if (x > 1250.0f) {
            velocityX = 0.0f;
            x = 1250.0f;
        }
    }
    if (field0D8 > 0) {
        --field0D8;
        velocityX = -3.0f;
        if (x < 30.0f) {
            velocityX = 0.0f;
            x = 30.0f;
        }
        if (x > 1250.0f) {
            velocityX = 0.0f;
            x = 1250.0f;
        }
    }
    if (field0D8 == 0) {
        if (owner->opponent->x > x) facing = 1;
        else facing = -1;
        ResetPrimaryCounters(903);
        return;
    }
    else {
        x = facing * velocityX + x;
        y += velocityY;
        if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(1);
    }
    break;

    case 905:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 128;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        velocityX = -3.0f;
        velocityY = 0.0f;
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
        field0DE = field0C8;
    }
    if (owner->field3A0 <= 0) {
        ResetPrimaryCounters(810);
        static_cast<YoumuFighter*>(owner)->fieldF12 = 0;
        if (field0DE == 1) ClearFrameInfo();
        return;
    }
    if (y > 0.0f && animationStage < 7) {
        velocityY -= 0.6f;
        if (y + velocityY <= 0.0f) {
            ResetSecondaryCounter(7);
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
            return;
        }
    }
    x = facing * velocityX + x;
    y += velocityY;
    if (x < 30.0f) {
        velocityX = 0.0f;
        x = 30.0f;
    }
    if (x > 1250.0f) {
        velocityX = 0.0f;
        x = 1250.0f;
    }
    if (AdvanceNestedFrame() == field070) ResetPrimaryCounters(903);
    if (animationStage == 7 && animationFrame == 0) ResetSecondaryCounter(5);
    break;

    case 906:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(40.0f, 75.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (animationStage < 14 && animationStage > 5) {
        scaleX += 0.004f;
        scaleY += 0.004f;
    }
    if (animationStage < 14 && owner->animationStage > 3) {
        ResetSecondaryCounter(14);
        ResetTransform(0.0f, 0.0f, 0.0f);
        return;
    }
    else {
        if (owner->action >= 700) {
            x = owner->x;
            y = owner->y;
        }
        if (animationStage > 5) {
            if (color[0] > 20) color[0] -= 20;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(6);
    }
    break;

    case 907:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(40.0f, 75.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (owner->action > 700) {
        x = owner->x;
        y = owner->y;
    }
    else {
        ClearFrameInfo();
        return;
    }
    if (owner->field082 == 0)
    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
    break;

    case 908:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(40.0f, 75.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (owner->action > 700) {
        x = owner->x;
        y = owner->y;
    }
    else {
        ClearFrameInfo();
        return;
    }
    if (owner->field082 == 0)
    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
    break;

    case 909:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 2.5f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
    }
    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
    break;

    case 910:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field01A = 1250;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
    }
    scaleX += 0.025f;
    scaleY += 0.025f;
    if (owner->action == 741) {
        x = owner->x;
        y = owner->y + 100.0f;
        rotationZ = -45.0f;
    }
    if (owner->action == 742) {
        x = owner->x;
        y = owner->y + 100.0f;
        rotationX = -200.0f;
        rotationZ = 0.0f;
    }
    if (owner->action == 743) {
        x = owner->x;
        y = owner->y + 50.0f;
        rotationX = -100.0f;
        rotationZ = 0.0f;
    }
    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
    break;

    case 911:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->field3A0 <= 0) {
        ResetPrimaryCounters(810);
        static_cast<YoumuFighter*>(owner)->fieldF12 = 0;
        return;
    }
    else {
        facing = owner->facing;
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            field0DA = 0;
            field0DC = 0;
        }
        if (owner->action == 752 && owner->animationStage == 5 && owner->opponent->health > 0) {
            --field0DC;
            if (field0DC <= 0) {
                owner->PlaySound(0);
                owner->SpawnBattleEffect(912, x, y, facing, 1);
                field0DC = 14 - g_F1212_DifficultyAt006714D0 * 2;
            }
        }
        if (facing == 1)
        velocityX = (owner->x - x) * 0.05f;
        if (facing == -1)
        velocityX = -((owner->x - x) * 0.05f);
        velocityY = ((380 - (owner->action == 706) * 100 - y) -
        (owner->action == 704 || owner->action == 705) * 100) * 0.05f;
        x = facing * velocityX + x;
        y += velocityY;
        owner->SpawnBattleEffect(811, x - 10.0f + RecordedRange(0, 20),
        y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.9f;
            scaleY = field0DA * 0.01f + 0.9f;
        }
        if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(0);
    }
    break;

    case 912:
        if (owner->field3A0 <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                SetPolarVelocity(-RecordedRange(0, 120), 5.0f);
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            if ((field07C == 6 || field07C == 1 ||
                 field07C == 2 || field07C == 4) && animationStage < 3) {
                ResetSecondaryCounter(3);
                return;
            }
            else {
                if (scaleX < 1.0f) {
                    scaleX += 0.05f;
                    scaleY += 0.05f;
                    if (scaleX > 1.0f) {
                        scaleX = 1.0f;
                        scaleY = 1.0f;
                    }
                }
                if (animationStage == 2 && owner->action == 752 &&
                    owner->animationStage == 8 && y < g_F1211_SplitAltitudeAt006599EC) {
                    ClearFrameInfo();
                    field0D8 = RecordedRange(0, 3) + 3;
                    for (burstIndex = 0; burstIndex < field0D8; burstIndex++) {
                        owner->SpawnBattleEffect(913,
                            (RecordedRange(0, 60) + x) - g_F1211_HalfSpreadAt00657878,
                            (RecordedRange(0, 60) + y) - g_F1211_HalfSpreadAt00657878,
                            owner->facing, 1);
                    }
                }
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > g_F1211_RightBoundAt00659424 ||
                    x < g_F1211_LowerBoundAt006595EC ||
                    y > g_F1211_UpperBoundAt006583B4 ||
                    y < g_F1211_LowerBoundAt006595EC) {
                    ClearFrameInfo();
                    return;
                }
                else {
                    if (color[0] > 20 && animationStage == 3)
                        color[0] -= 20;
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;
    case 913:
    if (owner->field3A0 <= 0) {
        ClearFrameInfo();
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            scaleX = RecordedRange(0, 3) * 0.1f + 0.8f;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = RecordedRange(0, 30);
            field0DA = 1;
            field0DC = RecordedRange(0, 5);
        }
        if (animationStage < 2) {
            ++field0DA;
            SetPolarVelocity(field0D8 - 15,
            field0DC * 0.2f + field0DA * 0.1f);
            rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
        }
        if (field07C != 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            velocityX = 0.0f;
            velocityY = 0.0f;
            return;
        }
        else {
            x = facing * velocityX + x;
            y -= velocityY;
            if (x > g_F1211_RightBoundAt00659424 ||
            x < g_F1211_LowerBoundAt006595EC ||
            y > g_F1211_UpperBoundAt006583B4 ||
            y < g_F1211_LowerBoundAt006595EC) {
                ClearFrameInfo();
                return;
            }
            else {
                if (color[0] > 20 && animationStage == 2)
                color[0] -= 20;
                if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            }
        }
    }
    break;

    case 914:
    if (owner->field3A0 <= 0) {
        ClearFrameInfo();
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 359);
            field0D8 = RecordedRange(0, 359);
            field0DA = RecordedRange(0, 80) + 100;
        }
        if (animationStage == 0) {
            scaleX += 0.015f;
            scaleY += 0.015f;
        }
        SetPolarVelocity(field0D8, field0DA * 0.1f);
        rotationZ += 4.0f;
        velocityX += 0.05f;
        x = facing * velocityX + x;
        y -= velocityY;
        field0DA -= 5;
        if (field0DA < 20) field0DA = 20;
        if (color[0] > 5) color[0] -= 5;
        else { ClearFrameInfo(); return; }
        if (x > g_F1211_RightBoundAt00659424 ||
        x < g_F1211_LowerBoundAt006595EC ||
        y > g_F1211_UpperBoundAt006583B4 ||
        y < g_F1211_LowerBoundAt006595EC) {
            ClearFrameInfo();
            return;
        }
        else {
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
    }
    break;

    case 915:
    if (owner->field3A0 <= 0) {
        ClearFrameInfo();
        return;
    }
    else {
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.0f;
            field080 = 255;
            field07C = 0;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        if (animationStage == 0) {
            scaleX += 0.05f;
            scaleY += 0.05f;
            if (scaleX > 1.0f) {
                scaleX = 1.0f;
                scaleY = 1.0f;
            }
        }
        velocityX += 0.2f;
        x = facing * velocityX + x;
        y -= velocityY;
        if (x > 1600.0f ||
        x < -360.0f ||
        y > g_F1211_UpperBoundAt006583B4 ||
        y < g_F1211_LowerBoundAt006595EC) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 2 && animationFrame == 0) {
                ResetSecondaryCounter(1);
                field07C = 0;
            }
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
    }
    break;

    case 916:
    static_cast<YoumuFighter*>(owner)->fieldF12 = 1;
    if (owner->field3A0 <= 0) {
        ResetPrimaryCounters(810);
        static_cast<YoumuFighter*>(owner)->fieldF12 = 0;
        return;
    }
    else {
        facing = owner->facing;
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            velocityX = -10.0f;
            velocityY = 10.0f;
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            field0DA = 0;
            field0DC = 0;
        }
        if (velocityX < -2.0f) velocityX += 0.6f;
        else velocityX = -2.0f;
        if (velocityY > 0.0f) velocityY -= 0.6f;
        else velocityY = 0.0f;
        if (velocityX == g_F1057_NudgeAt00657480) ++field0DA;
        if (x < 30.0f) {
            velocityX = 0.0f;
            x = 30.0f;
        }
        if (x > 1250.0f) {
            velocityX = 0.0f;
            x = 1250.0f;
        }
        if ((field0DA > 120 && owner->action > 149) || owner->action < 50) {
            ResetPrimaryCounters(905);
            field0D8 = 0;
            field0DA = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
            return;
        }
        else {
            x = facing * velocityX + x;
            y += velocityY;
            owner->SpawnBattleEffect(811, x - 10.0f + RecordedRange(0, 20),
            y - 10.0f + RecordedRange(0, 20), facing, 1);
            if (animationFrame == 0) {
                field0DA = RecordedRange(0, 20);
                scaleX = field0DA * 0.01f + 0.9f;
                scaleY = field0DA * 0.01f + 0.9f;
            }
            if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(0);
        }
    }
    break;

    case 990:
        if (static_cast<YoumuFighter*>(owner)->fieldF14 == 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            x = owner->x;
            y = owner->y + 100.0f;
            field08A = 1;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 2.0f;
                scaleY = 2.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            rotationZ += 1.0f;
            if (animationStage == 0) {
                if (color[0] < 180) {
                    color[0] += 25;
                }
                else {
                    color[0] = 180;
                }
                if (static_cast<YoumuFighter*>(owner)->fieldF14 >= 120) {
                    ResetSecondaryCounter(1);
                    color[0] = 180;
                    return;
                }
            }
            if (animationStage == 2) {
                if (color[0] >= 30) {
                    color[0] -= 30;
                }
                else {
                    color[0] = 0;
                }
                if (color[0] == 0) {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == field070) {
                ClearFrameInfo();
                return;
            }
        }
        break;

    case 991:
        if (static_cast<YoumuFighter*>(owner)->fieldF14 == 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            x = owner->x;
            y = owner->y + 100.0f;
            field08A = 1;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            scaleX = static_cast<YoumuFighter*>(owner)->fieldF14 / 75.0f;
            scaleY = scaleX;
            if (animationStage == 0) {
                if (color[0] < 230) {
                    color[0] += 25;
                }
                else {
                    color[0] = 255;
                }
                if (static_cast<YoumuFighter*>(owner)->fieldF14 >= 150) {
                    ResetSecondaryCounter(1);
                    color[0] = 255;
                    return;
                }
            }
            if (animationStage == 2) {
                if (color[0] >= 10) {
                    color[0] -= 10;
                }
                else {
                    color[0] = 0;
                }
                if (color[0] == 0) {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == field070) {
                ClearFrameInfo();
                return;
            }
        }
        break;

    case 995:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = RecordedRange(0, 360) - 180;
            field0DA = 15;
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) field0DA = 3;
            SetPolarVelocity(field0D8, field0DA * 0.8f);
        }
        if (animationStage == 1) {
            field0D8 = AngleAt00483300(owner->opponent->y + 100.0f - y, owner->opponent->x - x) / 0.017453288659453392f;
            SetPolarVelocity(field0D8, 20.0f);
            if (x - owner->opponent->x < 20.0f && x - owner->opponent->x > -20.0f && y - owner->opponent->y < 120.0f && y - owner->opponent->y > 80.0f) {
                ClearFrameInfo();
                if (owner->opponent->field366 < 2) {
                    ++owner->opponent->field366;
                }
                else {
                    owner->opponent->score += 20000;
                }
                PlaySharedSound(46);
                return;
            }
        }
        x += velocityX;
        y -= velocityY;
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(1);
        }
        break;

    case 996:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = RecordedRange(0, 360) - 180;
            field0DA = 15;
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) field0DA = 3;
            SetPolarVelocity(field0D8, field0DA * 0.8f);
        }
        if (animationStage == 1) {
            field0D8 = AngleAt00483300(owner->opponent->y + 100.0f - y, owner->opponent->x - x) / 0.017453288659453392f;
            SetPolarVelocity(field0D8, 20.0f);
            if (x - owner->opponent->x < 20.0f && x - owner->opponent->x > -20.0f && y - owner->opponent->y < 120.0f && y - owner->opponent->y > 80.0f) {
                ++owner->fieldEFA;
                PlaySharedSound(46);
                ClearFrameInfo();
                if (owner->opponent->spiritCooldown > 0) {
                    if (owner->opponent->spiritCooldown > 5) {
                        owner->opponent->spiritCooldown -= 5;
                    }
                    else {
                        owner->opponent->spiritCooldown = 0;
                        owner->opponent->spirit = 1000;
                    }
                    return;
                }
                else if (owner->opponent->spirit < 990) {
                    owner->opponent->spirit += 10;
                }
                else {
                    owner->opponent->spirit = 1000;
                    if (owner->opponent->field39C == 0) {
                        if (owner->opponent->field36C < 998.9) {
                            owner->opponent->field36C += 0.5f;
                        }
                        else {
                            owner->opponent->field36C = 900.0f;
                        }
                    }
                }
                return;
            }
        }
        x += velocityX;
        y -= velocityY;
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(1);
        }
        break;

    case 997:
        x = owner->x;
        y = 2.0f;
        field08A = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.0f;
            scaleY = 3.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field01A = 1250;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            rotationX = -80.0f;
            field0D8 = owner->field3A0;
            field0DA = 0;
        }
        if (owner->field3A0 <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            scaleX = static_cast<float>(owner->field3A0) / field0D8 * 2 + 1.0f;
            scaleY = static_cast<float>(owner->field3A0) / field0D8 * 2 + 1.0f;
            rotationZ += 1.0f;
            if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(9);
        }
        break;

case 0x3E6: {
    if (owner->action!=0xD1 &&
        owner->action!=0xD2 &&
        animationStage<2) {
        ResetSecondaryCounter(2);
        return;
    }
    x = owner->x;
    y=(*(&owner->y))+g_F1057_YOffsetAt00657888;
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationX=0.0f;
        rotationY=0.0f;
        rotationZ=0.0f;
    }
    scaleX=(scaleX)-g_F1057_SpeedBaseAt006590BC;
    scaleY=(scaleY)-g_F1057_SpeedBaseAt006590BC;
    rotationZ=(rotationZ)+g_F1051_ScaleCeilingAt0065747C;
    if (animationStage==2)
        color[0]=unsigned char(color[0]-12);
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    if (animationStage==2 && animationFrame==0)
        ResetSecondaryCounter(1);
    return;
}

    default:
        AdvanceNestedFrame();
        break;
    }
}
