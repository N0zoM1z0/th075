// Work in progress toward the complete original 00536400 (39,999 CODE B).
// The history relay and the written cases are genuine native game logic.
// Many native cases are still unwritten; this draft is NONEXACT and is not
// an executable replacement or an accepted reconstruction unit.
// See docs/OBJECT_ADVANCE_00536400_HISTORY_AND_CASES_F1211.md.
#include "ObjectAdvance536400F1211.hpp"
#include "FrameActorMotionPairsF1037.hpp"
#include "FighterAnimationPhaseBorrowedF1024.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OWNER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset)))
#define OPPONENT(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset))
#define OWNER_ACTOR reinterpret_cast<OwnerActor536400F1211*>(FIELD(void*, 0xE4))
#define HISTORY_LIST reinterpret_cast<ObjectHistoryListF1211*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + 0xFEC)

// Existing natural source for native-corresponding 817/998 uses these names.
#define SELF_FIELD FIELD
#define PARENT_FIELD OWNER
#define PARENT FIELD(void*, 0xE4)
#define SetAuxActionAt0040FB40 ResetSecondaryCounters
#define SetNativeMotionAt0040FBB0 EnableTransform
#define GetNativeActionAt0040FA30 AdvanceNestedFrame
#define NativeParentExpiredAt0045B830 ClearField74
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


void ObjectActor536400F1211::AdvanceAction()
{
    int burstIndex;
    ObjectHistoryEntryF1211* entry;
    if (OPPONENT(short, 0x3BA) != 0) return;
    if (OWNER(short, 0x3BA) != 0 && FIELD(short, 0x8A) == 0) return;

    if (FIELD(short, 0x60) < 800) {
        OWNER(short, 0xF12) = 1;
        if (OWNER(signed char, 0x39D) == 1) {
            OWNER_FLOAT(0x9C) = 0.5f;
            OWNER_ACTOR->UpdateGaugeAt0046D000(5);
            OWNER(short, 0xF10) = OWNER(short, 0x3B0);
        }
        if (OWNER(signed char, 0x39D) == 2) {
            OWNER_FLOAT(0x9C) = 0.4f;
            OWNER_ACTOR->UpdateGaugeAt0046D000(7);
            OWNER(short, 0xF10) = OWNER(short, 0x3B0);
        }
        if (OWNER(short, 0xF10) <= 0 || OWNER(short, 0x3A0) <= 0) {
            OWNER_FLOAT(0x9C) = 1.0f;
            OWNER(short, 0xF10) = 0;
            ResetPrimaryCounters(810);
            return;
        }
        FIELD(short, 0x8A) = 0;
        EnableTransform(0.0f, 0.0f, 0.0f);
        FLOAT(0x1C) = 1.0f;
        FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 128;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
        FIELD(unsigned char, 0x10) = 0x82;
        if (OWNER(short, 0x82) != 0) return;

        entry = &HISTORY_LIST->FrontAt00540220();
        if (FIELD(short, 0x60) != entry->actionAt00)
            FIELD(short, 0x80) = entry->counterAt0E;
        if (FIELD(short, 0x62) != entry->stageAt02)
            FIELD(int, 0x7C) = 0;
        ResetAnimationCountersAt0040FB00(entry->actionAt00, entry->stageAt02, 0);
        FIELD(unsigned int, 0x44) = entry->xBitsAt04;
        FIELD(unsigned int, 0x48) = entry->yBitsAt08;
        FIELD(signed char, 0x66) = entry->facingAt0C;
        return;
    }
    if (FIELD(short, 0x82) != 0) {
        --FIELD(short, 0x82);
        return;
    }
    switch (FIELD(short, 0x60)) {
    case 800:
        if (OWNER(short, 0x60) > 49 && OWNER(short, 0x60) < 150) {
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
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0)
                FIELD(short, 0xD8) = 0;
            if (FIELD(short, 0x62) == 1 && FIELD(short, 0x64) == 0) {
                OWNER_FLOAT(0x314) = FIELD(short, 0xD8);
                if (FLOAT(0xC8) == 1.0f)
                    OWNER_ACTOR->SpawnEffect(803,
                        (FIELD(short, 0xD8) * 23 - 75) * FIELD(signed char, 0x66) + FLOAT(0x44),
                        FLOAT(0x48) + 215.0f - FIELD(short, 0xD8) * 19,
                        FIELD(signed char, 0x66), 1);
                if (FLOAT(0xC8) == 2.0f)
                    OWNER_ACTOR->SpawnEffect(805,
                        FIELD(signed char, 0x66) * 100 + FLOAT(0x44),
                        FLOAT(0x48) + 200.0f - FIELD(short, 0xD8) * 25,
                        FIELD(signed char, 0x66), 1);
                if (FLOAT(0xC8) == 3.0f)
                    OWNER_ACTOR->SpawnEffect(807,
                        (FIELD(short, 0xD8) * 15 - 10) * FIELD(signed char, 0x66) + FLOAT(0x44),
                        FLOAT(0x48) + 20.0f + FIELD(short, 0xD8) * 20,
                        FIELD(signed char, 0x66), 1);
            }
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) {
                if (FIELD(short, 0xD8) < 10) {
                    ResetSecondaryCounters(1);
                    ++FIELD(short, 0xD8);
                    return;
                }
                else {
                    ClearField74();
                }
            }
        }
        break;

case 0x331: {
    SELF_FIELD(unsigned char,0x66)=PARENT_FIELD(unsigned char,0x66);
    if (PARENT_FIELD(signed short,0x60)>0x95 &&
        PARENT_FIELD(signed short,0x60)<0x9A &&
        F1024_PHASE(this).stageAt62==0) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(SELF_FIELD(signed char,0x66)*57);
        F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+
            g_F1069_ParentYFirstAt00659138;
    }
    if (PARENT_FIELD(signed short,0x60)>0x99 &&
        PARENT_FIELD(signed short,0x60)<0x9E &&
        F1024_PHASE(this).stageAt62==0) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(SELF_FIELD(signed char,0x66)*57);
        F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+
            g_F1069_ParentYSecondAt00658264;
    }
    if (PARENT_FIELD(signed short,0x60)==0x9E &&
        F1024_PHASE(this).stageAt62==0) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(SELF_FIELD(signed char,0x66)*57);
        F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+
            g_F1057_YOffsetAt00657888;
    }
    if ((PARENT_FIELD(signed short,0x60)<0x96 ||
         PARENT_FIELD(signed short,0x60)>0x9E) &&
        F1024_PHASE(this).stageAt62==0) {
        SetAuxActionAt0040FB40(1);
        PARENT_FIELD(signed short,0xF0A)=0;
    }
    if (F1024_PHASE(this).stageAt62==0 &&
        F1024_PHASE(this).frameAt64==0 &&
        SELF_FIELD(signed short,0xD8)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(float,0x2C)=50.0f;
        SELF_FIELD(signed short,0xD8)=1;
    }
    SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1057_NudgeAt00657480;
    if (F1024_PHASE(this).stageAt62>0) {
        if (SELF_FIELD(unsigned char,0x11)>30)
            SELF_FIELD(unsigned char,0x11)-=30;
        else
            SELF_FIELD(unsigned char,0x11)=0;
    }
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==1 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(0);
    return;
}

    case 820:
        if (OWNER(short, 0x60) == 308) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 821:
        if (OWNER(short, 0x60) == 504) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 822:
        if (OWNER(short, 0x60) == 502 || OWNER(short, 0x60) == 513) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 823:
        if (OWNER(short, 0x60) == 503) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 824:
        if (OWNER(short, 0x60) == 500 || OWNER(short, 0x60) == 501) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 825:
        if (OWNER(short, 0x60) == 309) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 826:
        if (OWNER(short, 0x60) == 310) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 827:
        if (OWNER(short, 0x60) == 501) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 833:
        if (OWNER(short, 0x60) == 390) {
            FIELD(unsigned int, 0x44) = OWNER(unsigned int, 0x44);
            FIELD(unsigned int, 0x48) = OWNER(unsigned int, 0x48);
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 838:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 1.3f;
            FLOAT(0x20) = 1.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x28) = 0.0f;
            FLOAT(0x2C) = 0.0f;
            FLOAT(0x30) = 0.0f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 840:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(50.0f, 20.0f, 0.0f);
            FLOAT(0x1C) = 1.01f;
            FLOAT(0x20) = 1.01f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        FLOAT(0x1C) += 0.001f;
        FLOAT(0x20) += 0.0015f;
        if (FIELD(unsigned char, 0x11) > 10) {
            FIELD(unsigned char, 0x11) -= 10;
        }
        else {
            ClearField74();
            return;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 841:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(55.0f, 2.0f, 0.0f);
            FLOAT(0x1C) = 1.0f;
            FLOAT(0x20) = 1.1f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
        }
        FLOAT(0x1C) += 0.01f;
        FLOAT(0x20) += 0.02f;
        if (FIELD(unsigned char, 0x11) > 10) {
            FIELD(unsigned char, 0x11) -= 10;
        }
        else {
            ClearField74();
            return;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 844:
        if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
            EnableTransform(0.0f, 0.0f, 0.0f);
            FLOAT(0x1C) = 0.8f;
            FLOAT(0x20) = 4.0f;
            FIELD(unsigned char, 0x11) = 255;
            FIELD(unsigned char, 0x12) = 255;
            FIELD(unsigned char, 0x13) = 255;
            FIELD(unsigned char, 0x14) = 255;
            FLOAT(0x30) = 90.0f;
        }
        if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
        break;

    case 912:
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            if (FIELD(short, 0x62) == 0 && FIELD(short, 0x64) == 0) {
                EnableTransform(0.0f, 0.0f, 0.0f);
                FIELD(short, 0x80) = 1;
                FIELD(int, 0x7C) = 0;
                FLOAT(0x1C) = 0.0f;
                FLOAT(0x20) = 0.0f;
                FIELD(unsigned char, 0x11) = 255;
                FIELD(unsigned char, 0x12) = 255;
                FIELD(unsigned char, 0x13) = 255;
                FIELD(unsigned char, 0x14) = 255;
                SetPolarVelocity(-RecordedRange(0, 120), 5.0f);
                FLOAT(0x30) = AngleAt00483300(FLOAT(0x54), FLOAT(0x50)) / g_F1211_AngleDivAt00657828;
            }
            if ((FIELD(int, 0x7C) == 6 || FIELD(int, 0x7C) == 1 ||
                 FIELD(int, 0x7C) == 2 || FIELD(int, 0x7C) == 4) && FIELD(short, 0x62) < 3) {
                ResetSecondaryCounters(3);
                return;
            }
            else {
                if (FLOAT(0x1C) < 1.0f) {
                    FLOAT(0x1C) += 0.05f;
                    FLOAT(0x20) += 0.05f;
                    if (FLOAT(0x1C) > 1.0f) {
                        FLOAT(0x1C) = 1.0f;
                        FLOAT(0x20) = 1.0f;
                    }
                }
                if (FIELD(short, 0x62) == 2 && OWNER(short, 0x60) == 752 &&
                    OWNER(short, 0x62) == 8 && FLOAT(0x48) < g_F1211_SplitAltitudeAt006599EC) {
                    ClearField74();
                    FIELD(short, 0xD8) = RecordedRange(0, 3) + 3;
                    for (burstIndex = 0; burstIndex < FIELD(short, 0xD8); burstIndex++) {
                        OWNER_ACTOR->SpawnEffect(913,
                            (RecordedRange(0, 60) + FLOAT(0x44)) - g_F1211_HalfSpreadAt00657878,
                            (RecordedRange(0, 60) + FLOAT(0x48)) - g_F1211_HalfSpreadAt00657878,
                            OWNER(signed char, 0x66), 1);
                    }
                }
                FLOAT(0x44) = FIELD(signed char, 0x66) * FLOAT(0x50) + FLOAT(0x44);
                FLOAT(0x48) -= FLOAT(0x54);
                if (FLOAT(0x44) > g_F1211_RightBoundAt00659424 ||
                    FLOAT(0x44) < g_F1211_LowerBoundAt006595EC ||
                    FLOAT(0x48) > g_F1211_UpperBoundAt006583B4 ||
                    FLOAT(0x48) < g_F1211_LowerBoundAt006595EC) {
                    ClearField74();
                    return;
                }
                else {
                    if (FIELD(unsigned char, 0x11) > 20 && FIELD(short, 0x62) == 3)
                        FIELD(unsigned char, 0x11) -= 20;
                    if (AdvanceNestedFrame() == FIELD(short, 0x70)) ClearField74();
                }
            }
        }
        break;
    case 990:
        if (OWNER(short, 0xF14) == 0 && FIELD(short, 0x62) < 2) {
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
                if (OWNER(short, 0xF14) >= 120) {
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
        if (OWNER(short, 0xF14) == 0 && FIELD(short, 0x62) < 2) {
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
            FLOAT(0x1C) = OWNER(short, 0xF14) / 75.0f;
            FLOAT(0x20) = FLOAT(0x1C);
            if (FIELD(short, 0x62) == 0) {
                if (FIELD(unsigned char, 0x11) < 230) {
                    FIELD(unsigned char, 0x11) += 25;
                }
                else {
                    FIELD(unsigned char, 0x11) = 255;
                }
                if (OWNER(short, 0xF14) >= 150) {
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
        if (OWNER(short, 0x3A0) <= 0) {
            ClearField74();
            return;
        }
        else {
            FLOAT(0x1C) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2 + 1.0f;
            FLOAT(0x20) = static_cast<float>(OWNER(short, 0x3A0)) / FIELD(short, 0xD8) * 2 + 1.0f;
            FLOAT(0x30) += 1.0f;
            if (AdvanceNestedFrame() == FIELD(short, 0x70)) ResetSecondaryCounters(9);
        }
        break;

case 0x3E6: {
    if (PARENT_FIELD(signed short,0x60)!=0xD1 &&
        PARENT_FIELD(signed short,0x60)!=0xD2 &&
        F1024_PHASE(this).stageAt62<2) {
        SetAuxActionAt0040FB40(2);
        return;
    }
    SELF_FIELD(unsigned int,0x44)=PARENT_FIELD(unsigned int,0x44);
    F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+g_F1057_YOffsetAt00657888;
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(float,0x28)=0.0f;
        SELF_FIELD(float,0x2C)=0.0f;
        SELF_FIELD(float,0x30)=0.0f;
    }
    SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)-g_F1057_SpeedBaseAt006590BC;
    SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)-g_F1057_SpeedBaseAt006590BC;
    SELF_FIELD(float,0x30)=SELF_FIELD(float,0x30)+g_F1051_ScaleCeilingAt0065747C;
    if (F1024_PHASE(this).stageAt62==2)
        SELF_FIELD(unsigned char,0x11)=unsigned char(SELF_FIELD(unsigned char,0x11)-12);
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    return;
}

    // Further independently reviewed states are inserted in native order.
    default:
        AdvanceNestedFrame();
        break;
    }
}

#undef NativeParentExpiredAt0045B830
#undef GetNativeActionAt0040FA30
#undef SetNativeMotionAt0040FBB0
#undef SetAuxActionAt0040FB40
#undef PARENT
#undef PARENT_FIELD
#undef SELF_FIELD
#undef HISTORY_LIST
#undef OWNER_ACTOR
#undef OPPONENT_FLOAT
#undef OWNER_FLOAT
#undef OPPONENT
#undef OWNER
#undef FLOAT
#undef FIELD
