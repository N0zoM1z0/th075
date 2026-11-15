#include "AliceFighter.hpp"
#include "CharacterObject.hpp"
// F572/F573/F574/F575/F576/F577/F578/F579/F580/F581/F582/F583/F585/F586/F587/F588/F590/F591/F592/F593/F596: selected natural VC7.1 source, original PE 004EBDA0.
// Original entire 33,293-byte CODE + 438 post-RET DATA now have the
// exact physical native layout and all 8,789 original x86 instruction
// offsets/lengths; all 8,789 mnemonic ordinals now match. 137 original
// non-COFF bytes in three GPR contexts still differ: NONEXACT.
// All real native action cases and the original 0040FA30 default are
// present as normal C++; three case bodies still have wrong GPR roles.
// No target ASM, injected filler, machine-byte graft or independent
// split-case CODE/DATA acceptance is claimed.
// F539 natural switch *probe*, not original fighter source or CODE credit.
// This file is regenerable from the original PE under ignored .analysis.
class ParentEffectsF572 {
public:
    void SpawnAt453A70(int kind, int x, int y, int first, int second);
    void SpawnComputedAt453A70(int kind, int x, float y, char first, int second);
    void SpawnDirectedAt453A70(int kind, int x, int y, char first, int second);
    void ModifyAt453D40(int arg);
    void SpawnMovedAt453A70(int kind, float x, int y, char first, int second);
    void SetupAt453E60(float);
};
class FighterSwitchF572_Boss004EBDA0 : public CharacterObject {
public:
    void Advance();
    void ResetAt4F4170();
    void ResetAt45B830();
    void ResetAt45B860(int kind);
    void ResetStateAt40FBB0(int,int,int);
    void MotionAt40FB70(float,float); void MotionRawAt40FB70(int,float); void MotionRawPairAt40FB70(int,int);
    void SetStateAt40FB40(int); void SetActionAt40FAC0(int); int RandomAt455580(int,int);
    short GetStateAt40FA30();
};
extern float gFloatAt00657850;
extern float gMulAt006590B4;
extern float gAddAt00659738;
extern double gMulDoubleAt00659730;
extern float gAddAt006583FC;
extern float gSubAt00659090;
extern float gSubtractAt00659728;
extern float gOffsetAt006581DC;
extern float gVelocityDragAt00659454;
extern float gMaxPositionAt0065912C;
extern float gStageOffsetAt006590AC;
extern float gScatterRateAt006578C0;
extern float gScatterBaseAt006581E0;
extern float gShrinkAt00659094;
extern float gGrowAt00657CBC;
extern float gGrowAt00657478;
extern float gCollisionAt00657888;
extern float gAngleUnitAt00657828;
extern float gTouchMaxAt00659230;
extern float gVerticalTouchMaxAt00658268;
extern double gDoubleTouchAt00659228;
extern float gNextBonusAt00657478;
extern float gLengthDivisorAt006583A0;
extern float gLengthFactorAt00659720;
extern float MagnitudeAt00428D20(float value);
extern float AngleRawAt00483300(int first, int second);
extern float AngleAt00483300(float first, float second);
extern float gCompareAt0065782C;
extern float gCompareAt0065747C;
extern float gCompareAt00657480;
extern float gCompareAt00657CF8;
extern float gCompareAt00657D14;
extern float gCompareAt00657874;
extern float gDropAt00658058;
extern float gLiftAt00657CC0;
extern float gCurveAt0065972C;
extern float gStepAt00658044;
extern float gFadeAt006583F8;
extern float gFadeAt00659428;
extern float gAbsScaleAt00659724;
extern float gStageContactAt0065786C;
extern float gParentYAt006590A8;
extern float gParentYAt006590A0;
extern signed char gGlobalActorCountAt006714D0;
extern float gParentYExtraAt00658264;
extern float gBoundRightAt00659248;
extern float gBoundLowerAt0065930C;
extern float gBoundUpperAt00658E80;
extern float gFadeAt0065825C;
extern float gMotionDecelAt00657480;
extern float gInitialClampAt00657D14;
extern float AbsFloatAt00412D90(float value);
#define I32(off) (*reinterpret_cast<int*>(RAW+(off)))
#define F32(off) (*reinterpret_cast<float*>(RAW+(off)))
#define S16(off) (*reinterpret_cast<signed short*>(RAW+(off)))
#define U8(off) (*reinterpret_cast<unsigned char*>(RAW+(off)))
#define S8(off) (*reinterpret_cast<signed char*>(RAW+(off)))
#define PARENT (*reinterpret_cast<ParentEffectsF572**>(RAW+0xE4))
#define PF32(off) (*reinterpret_cast<float*>(reinterpret_cast<char*>(PARENT)+(off)))
#define PS8(off) (*reinterpret_cast<signed char*>(reinterpret_cast<char*>(PARENT)+(off)))
#define PARENT_TARGET_S16(off) (*reinterpret_cast<signed short*>(*reinterpret_cast<char**>(reinterpret_cast<char*>(PARENT)+0x2E8)+(off)))
#define PARENT_TARGET_F32(off) (*reinterpret_cast<float*>(*reinterpret_cast<char**>(reinterpret_cast<char*>(PARENT)+0x2E8)+(off)))
#define PARENT_TARGET_S8(off) (*reinterpret_cast<signed char*>(*reinterpret_cast<char**>(reinterpret_cast<char*>(PARENT)+0x2E8)+(off)))
#define PARENT_TARGET_U8(off) (*reinterpret_cast<unsigned char*>(*reinterpret_cast<char**>(reinterpret_cast<char*>(PARENT)+0x2E8)+(off)))
#define PARENT_TARGET_I32(off) (*reinterpret_cast<int*>(*reinterpret_cast<char**>(reinterpret_cast<char*>(PARENT)+0x2E8)+(off)))
#define PARENT_TARGET_Y (*reinterpret_cast<float*>(*reinterpret_cast<char**>(reinterpret_cast<char*>(PARENT)+0x2E8)+0x48))
#define PARENT_TARGET_X (*reinterpret_cast<float*>(*reinterpret_cast<char**>(reinterpret_cast<char*>(PARENT)+0x2E8)+0x44))
#define PI32(off) (*reinterpret_cast<int*>(reinterpret_cast<char*>(PARENT)+(off)))
#define P16(off) (*reinterpret_cast<signed short*>(reinterpret_cast<char*>(PARENT)+(off)))

extern unsigned int g_FighterProbeMarker;
#define RAW reinterpret_cast<char*>(this)
#define I16(off) *reinterpret_cast<signed short*>(RAW+(off))
#define OWNER (*reinterpret_cast<char**>(RAW+0x2E8))
void FighterSwitchF572_Boss004EBDA0::Advance() {
    if (*reinterpret_cast<signed short*>(
            *reinterpret_cast<char**>(
                *reinterpret_cast<char**>(RAW+0xE4)+0x2E8)+0x3BA) != 0)
        return;
    if (*reinterpret_cast<signed short*>(
            *reinterpret_cast<char**>(RAW+0xE4)+0x3BA) != 0 &&
            reinterpret_cast<signed short&>(field08A) == 0)
        return;
    if (reinterpret_cast<signed short&>(field082) != 0) {
        --reinterpret_cast<signed short&>(field082);
        return;
    }
    switch (reinterpret_cast<signed short&>(action)) {
        case 0x320: ResetAt4F4170(); break;
        case 0x321: ResetAt4F4170(); break;
        case 0x322: ResetAt4F4170(); break;
        case 0x323: ResetAt4F4170(); break;
        case 0x324: ResetAt4F4170(); break;
        case 0x325: ResetAt4F4170(); break;
        case 0x326: ResetAt4F4170(); break;
        case 0x327: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && (reinterpret_cast<signed short&>(animationStage)) < 5) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 0x19) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            reinterpret_cast<signed short&>(field080) = 1;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            reinterpret_cast<signed short&>(field0D8) = -30;
            reinterpret_cast<signed short&>(field0DA) = 150;
            reinterpret_cast<signed short&>(field0DC) = 0;
            ResetStateAt40FBB0(0,0,0);
            reinterpret_cast<signed short&>(field080) = 4;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            PARENT->SpawnComputedAt453A70(0x371, reinterpret_cast<int&>(x),
                                  (y) + gFloatAt00657850,
                                  facing, 1);
            PARENT->ModifyAt453D40(2);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0) {
            MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),
                            static_cast<float>(reinterpret_cast<signed short&>(field0DA))*gMulAt006590B4);
            reinterpret_cast<signed short&>(field0DA) -= 5;
            reinterpret_cast<signed short&>(field0D8) += 3;
            rotationZ = (rotationZ) + gAddAt00659738;
            if ((reinterpret_cast<signed short&>(field0DA)) <= 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                SetStateAt40FB40(1);
                rotationZ = 0.0f;
                break;
            }
        }
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) - *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) < 5 && (reinterpret_cast<signed short&>(field080)) == 0) {
            SetStateAt40FB40((reinterpret_cast<signed short&>(animationStage)) + 4);
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) > 4) {
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
            SetStateAt40FB40(5);
            break;
        }
        if ((reinterpret_cast<signed short&>(animationFrame)) == 0)
            field07C = 0;
        if ((reinterpret_cast<signed short&>(animationStage)) == 5 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DC)) < 10) {
            SetStateAt40FB40(1);
            ++reinterpret_cast<signed short&>(field0DC);
        }
    }
    break;
}
        case 0x328: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && (reinterpret_cast<signed short&>(animationStage)) < 5) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 0x19) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            reinterpret_cast<signed short&>(field080) = 1;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            reinterpret_cast<signed short&>(field0D8) = 70;
            reinterpret_cast<signed short&>(field0DA) = 150;
            reinterpret_cast<signed short&>(field0DC) = 0;
            ResetStateAt40FBB0(0,0,0);
            reinterpret_cast<signed short&>(field080) = 4;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            PARENT->SpawnComputedAt453A70(0x371, reinterpret_cast<int&>(x),
                                  (y) + gFloatAt00657850,
                                  facing, 1);
            PARENT->ModifyAt453D40(2);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0) {
            MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),
                            static_cast<float>(reinterpret_cast<signed short&>(field0DA))*gMulAt006590B4);
            reinterpret_cast<signed short&>(field0DA) -= 5;
            reinterpret_cast<signed short&>(field0D8) -= 2;
            rotationZ = (rotationZ) + gAddAt00659738;
            if ((reinterpret_cast<signed short&>(field0DA)) <= 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                SetStateAt40FB40(1);
                rotationZ = 0.0f;
                break;
            }
        }
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) - *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) < 5 && (reinterpret_cast<signed short&>(field080)) == 0) {
            SetStateAt40FB40((reinterpret_cast<signed short&>(animationStage)) + 4);
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) > 4) {
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
            SetStateAt40FB40(5);
            break;
        }
        if ((reinterpret_cast<signed short&>(animationFrame)) == 0)
            field07C = 0;
        if ((reinterpret_cast<signed short&>(animationStage)) == 5 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DC)) < 10) {
            SetStateAt40FB40(1);
            ++reinterpret_cast<signed short&>(field0DC);
        }
    }
    break;
}
        case 0x329: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && (reinterpret_cast<signed short&>(animationStage)) < 5) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 0x19) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            reinterpret_cast<signed short&>(field080) = 1;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            reinterpret_cast<signed short&>(field0D8) = -30;
            reinterpret_cast<signed short&>(field0DA) = 200;
            reinterpret_cast<signed short&>(field0DC) = 0;
            ResetStateAt40FBB0(0,0,0);
            reinterpret_cast<signed short&>(field080) = 4;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            PARENT->SpawnComputedAt453A70(0x371, reinterpret_cast<int&>(x),
                                  (y) + gFloatAt00657850,
                                  facing, 1);
            PARENT->ModifyAt453D40(2);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0) {
            MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),
                            static_cast<float>(reinterpret_cast<signed short&>(field0DA))*gMulAt006590B4);
            reinterpret_cast<signed short&>(field0DA) -= 5;
            reinterpret_cast<signed short&>(field0D8) += 4;
            rotationZ = (rotationZ) + gAddAt00659738;
            if ((reinterpret_cast<signed short&>(field0DA)) <= 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                SetStateAt40FB40(1);
                rotationZ = 0.0f;
                break;
            }
        }
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) - *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) < 5 && (reinterpret_cast<signed short&>(field080)) == 0) {
            SetStateAt40FB40((reinterpret_cast<signed short&>(animationStage)) + 4);
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) > 4) {
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
            SetStateAt40FB40(5);
            break;
        }
        if ((reinterpret_cast<signed short&>(animationFrame)) == 0)
            field07C = 0;
        if ((reinterpret_cast<signed short&>(animationStage)) == 5 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DC)) < 10) {
            SetStateAt40FB40(1);
            ++reinterpret_cast<signed short&>(field0DC);
        }
    }
    break;
}
        case 0x32A: {
    if (P16(0x60) > 0x31 && P16(0x60) < 0x96) {
        ResetAt45B830();
        for (int iteration=0; iteration<5; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 0x19) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            reinterpret_cast<signed short&>(field080) = 1;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            ResetStateAt40FBB0(0,0,0);
            reinterpret_cast<signed short&>(field080) = 1;
            field07C = 0;
            if (*(&field0C8) == gCompareAt0065782C) {
                velocityX = 5.0f;
                velocityY = 6.0f;
            }
            if (*(&field0C8) == gCompareAt0065747C) {
                velocityX = 3.0f;
                velocityY = 8.0f;
            }
            if (*(&field0C8) == gCompareAt00657480) {
                velocityX = 1.0f;
                velocityY = 10.0f;
            }
            if (*(&field0C8) == gCompareAt00657CF8) {
                velocityX = -5.0f;
                velocityY = 6.0f;
            }
            if (*(&field0C8) == gCompareAt00657D14) {
                velocityX = -3.0f;
                velocityY = 8.0f;
            }
            if (*(&field0C8) == gCompareAt00657874) {
                velocityX = -1.0f;
                velocityY = 10.0f;
            }
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        velocityY = (velocityY) - gDropAt00658058;
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) + *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) < 2) {
            rotationZ = (rotationZ) + gLiftAt00657CC0;
            if (*(&y) + *(&velocityY) <= gCompareAt0065782C) {
                PARENT->SpawnDirectedAt453A70(0x32B, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
                PARENT->SpawnDirectedAt453A70(0x32D, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
                PARENT->ModifyAt453D40(4);
                SetActionAt40FAC0(0x33B);
                y = 0.0f;
                velocityY = 0.0f;
                velocityX = 0.0f;
                rotationZ = 0.0f;
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
            SetStateAt40FB40(1);
    }
    break;
}
        case 0x32B: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        reinterpret_cast<signed short&>(field0D8) = 0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080) = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<int&>(rotationX) = 0;
        reinterpret_cast<int&>(rotationY) = 0;
        reinterpret_cast<int&>(rotationZ) = 0;
        PARENT->SetupAt453E60(5.0f);
    }
    scaleX = (float)(5 - (reinterpret_cast<signed short&>(animationFrame))) * gCurveAt0065972C * ((reinterpret_cast<signed short&>(animationFrame)) < 5) + gStepAt00658044 + (scaleX);
    scaleY = (float)(5 - (reinterpret_cast<signed short&>(animationFrame))) * gCurveAt0065972C * ((reinterpret_cast<signed short&>(animationFrame)) < 5) + gStepAt00658044 + (scaleY);
    if ((reinterpret_cast<signed short&>(animationStage)) > 1) {
        if ((color[0]) >= 10)
            color[0] -= 10;
        else {
            color[0] = 0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x32C: {
    if (P16(0x60) > 0x31 && P16(0x60) < 0x96) {
        ResetAt45B830();
        for (int iteration=0; iteration<5; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            ResetStateAt40FBB0(0,0,0);
            reinterpret_cast<signed short&>(field080) = 1;
            field07C = 0;
            MotionRawAt40FB70(reinterpret_cast<int&>(field0C8),15.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) + *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) < 2) {
            rotationZ = (rotationZ) + gLiftAt00657CC0;
            if (*(&y) + *(&velocityY) <= gCompareAt0065782C) {
                PARENT->ModifyAt453D40(4);
                PARENT->SpawnDirectedAt453A70(0x32B, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
                PARENT->SpawnDirectedAt453A70(0x32D, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
                SetActionAt40FAC0(0x33B);
                y = 0.0f;
                velocityY = 0.0f;
                velocityX = 0.0f;
                rotationZ = 0.0f;
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
            SetStateAt40FB40(1);
    }
    break;
}
        case 0x32D: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX = 0.4f;
        scaleY = 0.4f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<signed short&>(field01A) = 0x4E2;
        rotationX = -75.0f;
    }
    scaleX = (scaleX) + gFadeAt006583F8;
    scaleY = (scaleY) + gFadeAt006583F8;
    if ((reinterpret_cast<signed short&>(animationStage)) > 1) {
        if ((color[0]) > 20)
            color[0] -= 20;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x32E: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0D8)) == 1) {
        reinterpret_cast<signed short&>(field0D8) = 0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080) = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 0.5f;
        scaleY = 0.5f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<int&>(rotationX) = 0;
        reinterpret_cast<int&>(rotationY) = 0;
        reinterpret_cast<int&>(rotationZ) = 0;
    }
    scaleX = (scaleX) + gFadeAt00659428;
    scaleY = (scaleY) + gFadeAt00659428;
    color[0] -= 10;
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x330: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && (reinterpret_cast<signed short&>(animationStage)) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            reinterpret_cast<signed short&>(field080) = 1;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            ResetStateAt40FBB0(0,0,0);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = -4.0f;
            velocityY = 6.0f;
        }
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) + *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + gAddAt00659738;
            velocityY = (velocityY) - gAddAt006583FC;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 11) {
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
            ResetAt45B830();
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 6 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DC)) < 0) {
            SetStateAt40FB40(2);
            ++reinterpret_cast<signed short&>(field0DC);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 10 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DA)) < 6) {
            ++reinterpret_cast<signed short&>(field0DA);
            SetStateAt40FB40(9);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 9 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            PF32(0x314) = 1200.0f;
            PF32(0x318) = static_cast<float>(RandomAt455580(0,10) - 5);
            PARENT->SpawnMovedAt453A70(0x320,
                   static_cast<float>((facing) * 10) + (x),
                   reinterpret_cast<int&>(y), reinterpret_cast<unsigned char&>(facing), 1);
            PARENT->ModifyAt453D40(6);
        }
    }
    break;
}
        case 0x331: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && (reinterpret_cast<signed short&>(animationStage)) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            reinterpret_cast<signed short&>(field080) = 1;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            ResetStateAt40FBB0(0,0,0);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 3.0f;
            velocityY = 16.0f;
        }
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) + *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + gAddAt00659738;
            velocityY = (velocityY) - gSubAt00659090;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 11) {
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
            ResetAt45B830();
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 6 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DC)) < 0) {
            SetStateAt40FB40(2);
            ++reinterpret_cast<signed short&>(field0DC);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 10 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DA)) < 6) {
            ++reinterpret_cast<signed short&>(field0DA);
            SetStateAt40FB40(9);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 9 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            PF32(0x314) = 1200.0f;
            PF32(0x318) = static_cast<float>(RandomAt455580(0,15) - 45);
            PARENT->SpawnMovedAt453A70(0x321,
                   static_cast<float>((facing) * 10) + (x),
                   reinterpret_cast<int&>(y), reinterpret_cast<unsigned char&>(facing), 1);
            PARENT->ModifyAt453D40(6);
        }
    }
    break;
}
        case 0x332: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && (reinterpret_cast<signed short&>(animationStage)) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            reinterpret_cast<signed short&>(field080) = 1;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            ResetStateAt40FBB0(0,0,0);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 6.0f;
            velocityY = 4.5f;
        }
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) + *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + gAddAt00659738;
            velocityY = (velocityY) - gAddAt006583FC;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 11) {
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
            ResetAt45B830();
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
            facing = -(facing);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 6 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DC)) < 0) {
            SetStateAt40FB40(2);
            ++reinterpret_cast<signed short&>(field0DC);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 10 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DA)) < 6) {
            ++reinterpret_cast<signed short&>(field0DA);
            SetStateAt40FB40(9);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 9 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            PF32(0x314) = 1200.0f;
            PF32(0x318) = static_cast<float>(RandomAt455580(0,10) - 5);
            PARENT->SpawnMovedAt453A70(0x322,
                   static_cast<float>((facing) * 10) + (x),
                   reinterpret_cast<int&>(y), reinterpret_cast<unsigned char&>(facing), 1);
            PARENT->ModifyAt453D40(6);
        }
    }
    break;
}
        case 0x335: {
    if ((field07C) == 6) {
        field07C = 0;
        reinterpret_cast<signed short&>(field080) = 99;
    }
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 &&
            (reinterpret_cast<signed short&>(field080)) > 0 && (reinterpret_cast<signed short&>(animationStage)) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            reinterpret_cast<signed short&>(field0D8) = 0;
            reinterpret_cast<signed short&>(field0DA) = 0;
            reinterpret_cast<signed short&>(field0DC) = 0;
            field07C = 0;
            reinterpret_cast<signed short&>(field080) = 99;
            ResetStateAt40FBB0(0,0,0);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            MotionRawAt40FB70(reinterpret_cast<int&>(field0C8),14.0f);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0) {
            rotationZ = (rotationZ) + gGrowAt00657CBC;
            velocityY = (velocityY) + gGrowAt00657478;
        }
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) - *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) == 10 && *(&y) - *(&velocityY) <= gCollisionAt00657888) {
            velocityX = 2.0f;
            velocityY = 2.0f;
            SetStateAt40FB40(11);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) > 10 && (reinterpret_cast<signed short&>(field0D8)) > 2) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
            SetStateAt40FB40(10);
            ++reinterpret_cast<signed short&>(field0D8);
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 6 && (reinterpret_cast<signed short&>(animationFrame)) == 0 &&
                static_cast<float>(reinterpret_cast<signed short&>(field0DC)) < *(&gCompareAt0065782C) + *(&field0CC)) {
            SetStateAt40FB40(2);
            ++reinterpret_cast<signed short&>(field0DC);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 10 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            PARENT->ModifyAt453D40(16);
            velocityX = 18.0f;
            velocityY = 18.0f;
        }
    }
    break;
}
        case 0x338: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        reinterpret_cast<signed short&>(field0D8) = 0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080) = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<int&>(rotationX) = 0;
        reinterpret_cast<int&>(rotationY) = 0;
        reinterpret_cast<int&>(rotationZ) = 0;
        PARENT->SetupAt453E60(10.0f);
        PARENT->SpawnDirectedAt453A70(0x33A, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
    }
    if ((field07C) == 6) {
        field07C = 0;
        ++reinterpret_cast<signed short&>(field080);
    }
    scaleX = (scaleX) + gFadeAt00659428;
    scaleY = (scaleY) + gFadeAt00659428;
    if ((reinterpret_cast<signed short&>(animationStage)) > 1) {
        if ((color[0]) >= 20)
            color[0] -= 20;
        else {
            color[0] = 0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    if ((reinterpret_cast<signed short&>(animationStage)) == 2 && (reinterpret_cast<signed short&>(animationFrame)) == 0)
        PARENT->SpawnDirectedAt453A70(0x339, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
    break;
}
        case 0x339: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        reinterpret_cast<signed short&>(field0D8) = 0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080) = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 1.3f;
        scaleY = 1.3f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<int&>(rotationX) = 0;
        reinterpret_cast<int&>(rotationY) = 0;
        reinterpret_cast<int&>(rotationZ) = 0;
    }
    scaleX = (scaleX) + gFadeAt00659428;
    scaleY = (scaleY) + gFadeAt00659428;
    if ((reinterpret_cast<signed short&>(animationStage)) > 1) {
        if ((color[0]) >= 40)
            color[0] -= 40;
        else {
            color[0] = 0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x33A: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<signed short&>(field01A) = 0x4E2;
        rotationX = -75.0f;
    }
    scaleX = (scaleX) + gAddAt006583FC;
    scaleY = (scaleY) + gAddAt006583FC;
    if ((reinterpret_cast<signed short&>(animationStage)) > 1) {
        if ((color[0]) > 20)
            color[0] -= 20;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x33B: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        MotionAt40FB70(-(static_cast<float>(RandomAt455580(0,45))
                - gSubtractAt00659728 + gOffsetAt006581DC),18.0f);
    }
    x += static_cast<float>(facing) * (velocityX);
    y = *(&y) + *(&velocityY);
    velocityY = (velocityY) - gVelocityDragAt00659454;
    rotationZ = (rotationZ) + gGrowAt00657CBC;
    if ((y) < gMaxPositionAt0065912C) {
        ResetAt45B830();
        break;
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x33C: {
    if (P16(0x60) == 0x2BE) {
        x = *(&PF32(0x44)) + static_cast<float>((facing) * 65);
        y = PF32(0x48) + gStageOffsetAt006590AC;
    }
    if (P16(0x60) != 0x2BE ||
            (P16(0x62) > 9 && P16(0x60) == 0x2BE)) {
        if ((reinterpret_cast<signed short&>(field0D8)) == 0) {
            reinterpret_cast<signed short&>(field0D8) = 1;
            break;
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        reinterpret_cast<signed short&>(field0D8) = 0;
        ResetStateAt40FBB0(0,0,0);
        field07C = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    if ((reinterpret_cast<signed short&>(field0D8)) == 0) {
        if ((color[0]) <= 0xE1)
            color[0] += 30;
        else
            color[0] = 0xFF;
    }
    if ((reinterpret_cast<signed short&>(field0D8)) == 1) {
        scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
        scaleY = (scaleY) + gAddAt006583FC;
        if ((color[0]) >= 10)
            color[0] -= 10;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
        SetStateAt40FB40(1);
        break;
    }
    break;
}
        case 0x33D: {
    if (P16(0x60) == 0x2C1) {
        x = *(&PF32(0x44)) + static_cast<float>((facing) * 65);
        y = PF32(0x48) + gStageOffsetAt006590AC;
    }
    if (P16(0x60) != 0x2C1 ||
            (P16(0x62) > 9 && P16(0x60) == 0x2BE)) {
        if ((reinterpret_cast<signed short&>(field0D8)) == 0) {
            reinterpret_cast<signed short&>(field0D8) = 1;
            break;
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        reinterpret_cast<signed short&>(field0D8) = 0;
        ResetStateAt40FBB0(0,0,0);
        field07C = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    if ((reinterpret_cast<signed short&>(field0D8)) == 0) {
        if ((color[0]) <= 0xE1)
            color[0] += 30;
        else
            color[0] = 0xFF;
    }
    if ((reinterpret_cast<signed short&>(field0D8)) == 1) {
        scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
        scaleY = (scaleY) + gAddAt006583FC;
        if ((color[0]) >= 10)
            color[0] -= 10;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
        SetStateAt40FB40(1);
        break;
    }
    break;
}
        case 0x33E: {
    if (P16(0x60) == 0x2BE) {
        x = *(&PF32(0x44)) + static_cast<float>((facing) * 140);
        y = PF32(0x48) + gStageOffsetAt006590AC;
    }
    if (P16(0x60) != 0x2BE && (reinterpret_cast<signed short&>(animationStage)) < 7) {
        SetStateAt40FB40(7);
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        reinterpret_cast<signed short&>(field080) = 1;
        field07C = 0;
        if ((reinterpret_cast<signed short&>(field0D8)) != 1) {
            ResetStateAt40FBB0(0,0,0);
            scaleX = 1.5f;
            scaleY = 1.5f;
            reinterpret_cast<signed short&>(field0D8) = 0;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            reinterpret_cast<signed short&>(field080) = 10;
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 6)
        scaleY = static_cast<float>(RandomAt455580(0,4) - 2)
                  * gScatterRateAt006578C0 + gScatterBaseAt006581E0;
    if ((reinterpret_cast<signed short&>(animationStage)) == 7)
        scaleY = (scaleY) * gShrinkAt00659094;
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    if ((reinterpret_cast<signed short&>(animationStage)) == 7 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0D8)) < 10) {
        SetStateAt40FB40(6);
        field07C = 0;
        ++reinterpret_cast<signed short&>(field0D8);
    }
    break;
}
        case 0x33F: {
    if (P16(0x60) == 0x2C1) {
        x = *(&PF32(0x44)) + static_cast<float>((facing) * 180);
        y = PF32(0x48) + gStageOffsetAt006590AC;
    }
    if (P16(0x60) != 0x2C1 && (reinterpret_cast<signed short&>(animationStage)) < 17) {
        SetStateAt40FB40(17);
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        field07C = 0;
        ResetStateAt40FBB0(0,0,0);
        scaleX = 2.0f;
        scaleY = 1.5f;
        reinterpret_cast<signed short&>(field0D8) = 0;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<signed short&>(field080) = 25;
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    if ((reinterpret_cast<signed short&>(animationFrame)) == 0)
        field07C = 0;
    if ((reinterpret_cast<signed short&>(animationStage)) == 13 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0D8)) < 2) {
        SetStateAt40FB40(6);
        ++reinterpret_cast<signed short&>(field0D8);
    }
    break;
}
        case 0x340: {
    if ((field07C) == 6) {
        field07C = 0;
        reinterpret_cast<signed short&>(field080) = 1;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080) = 1;
        field07C = 0;
        velocityX = AbsFloatAt00412D90(
            *(&PF32(0x44)) + static_cast<float>(PS8(0x66)*90) - PARENT_TARGET_X
        ) * gAbsScaleAt00659724;
        if ((velocityX) < gInitialClampAt00657D14)
            velocityX = 4.0f;
        velocityY = 20.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    velocityY = (velocityY) - gMotionDecelAt00657480;
    x += static_cast<float>(facing) * (velocityX);
    y = *(&y) + *(&velocityY);
    if ((reinterpret_cast<signed short&>(animationStage)) < 2) {
        rotationZ = (rotationZ) + gLiftAt00657CC0;
        if (*(&y) + *(&velocityY) <= gCompareAt0065782C) {
            PARENT->SpawnDirectedAt453A70(0x338, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
            PARENT->SpawnDirectedAt453A70(0x33A, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
            PARENT->ModifyAt453D40(8);
            SetActionAt40FAC0(0x33B);
            y = 0.0f;
            velocityY = 0.0f;
            velocityX = 0.0f;
            rotationZ = 0.0f;
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        SetStateAt40FB40(1);
    break;
}
        case 0x341: {
    if ((field07C) == 6) {
        field07C = 0;
        reinterpret_cast<signed short&>(field080) = 1;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080) = 1;
        field07C = 0;
        velocityX = AbsFloatAt00412D90(
            *(&PF32(0x44)) + static_cast<float>(PS8(0x66)*90) - PARENT_TARGET_X
        ) * gAbsScaleAt00659724;
        if ((velocityX) < gInitialClampAt00657D14)
            velocityX = 4.0f;
        velocityY = 20.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    velocityY = (velocityY) - gMotionDecelAt00657480;
    x += static_cast<float>(facing) * (velocityX);
    y = *(&y) + *(&velocityY);
    if ((reinterpret_cast<signed short&>(animationStage)) < 2) {
        rotationZ = (rotationZ) + gLiftAt00657CC0;
        if (*(&y) + *(&velocityY) <= gCompareAt0065782C) {
            PARENT->SpawnDirectedAt453A70(0x342, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
            PARENT->SpawnDirectedAt453A70(0x344, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
            PARENT->ModifyAt453D40(10);
            SetActionAt40FAC0(0x33B);
            y = 0.0f;
            velocityY = 0.0f;
            velocityX = 0.0f;
            rotationZ = 0.0f;
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        SetStateAt40FB40(1);
    break;
}
        case 0x342: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        reinterpret_cast<signed short&>(field0D8) = 0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080) = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<int&>(rotationX) = 0;
        reinterpret_cast<int&>(rotationY) = 0;
        reinterpret_cast<int&>(rotationZ) = 0;
        PARENT->SetupAt453E60(10.0f);
    }
    if ((field07C) == 6) {
        field07C = 0;
        ++reinterpret_cast<signed short&>(field080);
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 3 && (reinterpret_cast<signed short&>(animationFrame)) == 0)
        PARENT->SpawnDirectedAt453A70(0x343, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), facing, 1);
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x343: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        reinterpret_cast<signed short&>(field0D8) = 0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080) = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 1.7f;
        scaleY = 1.7f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<int&>(rotationX) = 0;
        reinterpret_cast<int&>(rotationY) = 0;
        reinterpret_cast<int&>(rotationZ) = 0;
    }
    scaleX = (scaleX) + gFadeAt0065825C;
    scaleY = (scaleY) + gFadeAt0065825C;
    if ((reinterpret_cast<signed short&>(animationStage)) > -1) {
        if ((color[0]) >= 20)
            color[0] -= 20;
        else {
            color[0] = 0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x344: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<signed short&>(field01A) = 0x4E2;
        rotationX = -75.0f;
    }
    scaleX = (scaleX) + gAddAt006583FC;
    scaleY = (scaleY) + gAddAt006583FC;
    if ((reinterpret_cast<signed short&>(animationStage)) > 1) {
        if ((color[0]) > 20)
            color[0] -= 20;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x345: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<signed short&>(field0D8) = 0;
        reinterpret_cast<signed short&>(field0DA) = 0;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) > 5) {
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) + *(&velocityY);
        if ((x) > gBoundRightAt00659248 ||
            (x) < gBoundLowerAt0065930C ||
            (y) < gBoundLowerAt0065930C ||
            (y) > gBoundUpperAt00658E80) {
            ResetAt45B830();
            break;
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
            SetStateAt40FB40(6);
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 1) {
        rotationZ = (rotationZ) + gGrowAt00657CBC;
        if (P16(0xF12) == 1 && (reinterpret_cast<signed short&>(animationStage)) == 1 && P16(0xF12) == 1) {
            SetStateAt40FB40(2);
            reinterpret_cast<signed short&>(field080) = 99;
            rotationZ = 0.0f;
            field07C = 0;
            break;
        }
    }
    if (P16(0xF12) == 2) {
        if ((reinterpret_cast<signed short&>(animationStage)) < 6)
            reinterpret_cast<signed short&>(animationStage) += 4;
        reinterpret_cast<signed short&>(field0DA) = 25;
        MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),
                       static_cast<float>(reinterpret_cast<signed short&>(field0DA)));
    }
    if ((reinterpret_cast<signed short&>(animationStage)) < 6 && P16(0xF12) < 2) {
        reinterpret_cast<signed short&>(field0D8) = static_cast<short>(
            static_cast<float>(P16(0xF10)-180) + (field0C8));
        if ((reinterpret_cast<signed short&>(field0D8)) > 180) reinterpret_cast<signed short&>(field0D8) -= 360;
        if ((reinterpret_cast<signed short&>(field0D8)) < -180) reinterpret_cast<signed short&>(field0D8) += 360;
        MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),
                       static_cast<float>(reinterpret_cast<signed short&>(field0DA)));
        x = static_cast<int>(
            P16(0xF0C) + (facing)*(velocityX));
        y = static_cast<int>(
            P16(0xF0E) + (velocityY));
        if ((reinterpret_cast<signed short&>(field0DA)) < 140) reinterpret_cast<signed short&>(field0DA) += 7;
        if ((reinterpret_cast<signed short&>(field0DA)) > 140) reinterpret_cast<signed short&>(field0DA) = 140;
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) SetStateAt40FB40(6);
    if ((reinterpret_cast<signed short&>(animationStage)) == 2 && (reinterpret_cast<signed short&>(animationFrame)) == 0) SetStateAt40FB40(1);
    if ((reinterpret_cast<signed short&>(animationStage)) == 6 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && P16(0xF12) == 1) {
        SetStateAt40FB40(2);
        field07C = 0;
    }
    break;
}
        case 0x346: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        P16(0xF10) = 0;
        velocityX = 25.0f;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) < 2) {
        P16(0xF10) -= 3;
        P16(0xF0C) = static_cast<short>(x);
        P16(0xF0E) = static_cast<short>(y);
        velocityX = (velocityX) - gCompareAt0065747C;
        if ((velocityX) < gCompareAt0065782C)
            velocityX = 0.0f;
    }
    x += static_cast<float>(facing) * (velocityX);
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
        ResetAt45B830();
        P16(0xF12) = 0;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0)
        P16(0xF12) = 1;
    if ((reinterpret_cast<signed short&>(animationStage)) == 2 && (reinterpret_cast<signed short&>(animationFrame)) == 0)
        P16(0xF12) = 2;
    break;
}
        case 0x347: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<signed short&>(field0D8) = 0;
        reinterpret_cast<signed short&>(field0DA) = 0;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) > 5) {
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) + *(&velocityY);
        if ((x) > gBoundRightAt00659248 ||
            (x) < gBoundLowerAt0065930C ||
            (y) < gBoundLowerAt0065930C ||
            (y) > gBoundUpperAt00658E80) {
            ResetAt45B830();
            break;
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
            SetStateAt40FB40(6);
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 1) {
        rotationZ = (rotationZ) + gGrowAt00657CBC;
        if (P16(0xF12) == 1 && (reinterpret_cast<signed short&>(animationStage)) == 1 && P16(0xF12) == 1) {
            SetStateAt40FB40(2);
            reinterpret_cast<signed short&>(field080) = 99;
            rotationZ = 0.0f;
            field07C = 0;
            break;
        }
    }
    if (P16(0xF12) == 2) {
        if ((reinterpret_cast<signed short&>(animationStage)) < 6)
            reinterpret_cast<signed short&>(animationStage) += 4;
        reinterpret_cast<signed short&>(field0DA) = 25;
        MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),
                       static_cast<float>(reinterpret_cast<signed short&>(field0DA)));
    }
    if ((reinterpret_cast<signed short&>(animationStage)) < 6 && P16(0xF12) < 2) {
        reinterpret_cast<signed short&>(field0D8) = static_cast<short>(
            static_cast<float>(P16(0xF10)-180) + (field0C8));
        if ((reinterpret_cast<signed short&>(field0D8)) > 180) reinterpret_cast<signed short&>(field0D8) -= 360;
        if ((reinterpret_cast<signed short&>(field0D8)) < -180) reinterpret_cast<signed short&>(field0D8) += 360;
        MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),
                       static_cast<float>(reinterpret_cast<signed short&>(field0DA)));
        x = static_cast<int>(
            P16(0xF0C) + (facing)*(velocityX));
        y = static_cast<int>(
            P16(0xF0E) + (velocityY));
        if ((reinterpret_cast<signed short&>(field0DA)) < 120) reinterpret_cast<signed short&>(field0DA) += 6;
        if ((reinterpret_cast<signed short&>(field0DA)) > 120) reinterpret_cast<signed short&>(field0DA) = 120;
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) SetStateAt40FB40(6);
    if ((reinterpret_cast<signed short&>(animationStage)) == 2 && (reinterpret_cast<signed short&>(animationFrame)) == 0) SetStateAt40FB40(1);
    if ((reinterpret_cast<signed short&>(animationStage)) == 6 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && P16(0xF12) == 1) {
        SetStateAt40FB40(2);
        field07C = 0;
    }
    break;
}
        case 0x348: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        reinterpret_cast<signed short&>(field0D8) = 0;
        reinterpret_cast<signed short&>(field0DA) = 0;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) > 5) {
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) + *(&velocityY);
        if ((x) > gBoundRightAt00659248 ||
            (x) < gBoundLowerAt0065930C ||
            (y) < gBoundLowerAt0065930C ||
            (y) > gBoundUpperAt00658E80) {
            ResetAt45B830();
            break;
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070)))
            SetStateAt40FB40(6);
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 1) {
        rotationZ = (rotationZ) + gGrowAt00657CBC;
        if (P16(0xF12) == 1 && (reinterpret_cast<signed short&>(animationStage)) == 1 && P16(0xF12) == 1) {
            SetStateAt40FB40(2);
            reinterpret_cast<signed short&>(field080) = 99;
            rotationZ = 0.0f;
            field07C = 0;
            break;
        }
    }
    if (P16(0xF12) == 2) {
        if ((reinterpret_cast<signed short&>(animationStage)) < 6)
            reinterpret_cast<signed short&>(animationStage) += 4;
        reinterpret_cast<signed short&>(field0DA) = 25;
        MotionAt40FB70(static_cast<float>(-(reinterpret_cast<signed short&>(field0D8)) + 180),
                       static_cast<float>(reinterpret_cast<signed short&>(field0DA)));
    }
    if ((reinterpret_cast<signed short&>(animationStage)) < 6 && P16(0xF12) < 2) {
        reinterpret_cast<signed short&>(field0D8) = static_cast<short>(
            static_cast<float>(P16(0xF10)-180) + (field0C8));
        if ((reinterpret_cast<signed short&>(field0D8)) > 180) reinterpret_cast<signed short&>(field0D8) -= 360;
        if ((reinterpret_cast<signed short&>(field0D8)) < -180) reinterpret_cast<signed short&>(field0D8) += 360;
        MotionAt40FB70(static_cast<float>(-(reinterpret_cast<signed short&>(field0D8))),
                       static_cast<float>(reinterpret_cast<signed short&>(field0DA)));
        x = static_cast<int>(
            P16(0xF0C) + (facing)*(velocityX));
        y = static_cast<int>(
            P16(0xF0E) + (velocityY));
        if ((reinterpret_cast<signed short&>(field0DA)) < 200) reinterpret_cast<signed short&>(field0DA) += 10;
        if ((reinterpret_cast<signed short&>(field0DA)) > 200) reinterpret_cast<signed short&>(field0DA) = 200;
    }
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) SetStateAt40FB40(6);
    if ((reinterpret_cast<signed short&>(animationStage)) == 2 && (reinterpret_cast<signed short&>(animationFrame)) == 0) SetStateAt40FB40(1);
    if ((reinterpret_cast<signed short&>(animationStage)) == 6 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && P16(0xF12) == 1) {
        SetStateAt40FB40(2);
        field07C = 0;
    }
    break;
}
        case 0x349: {
    if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        P16(0xF10) = 0;
        velocityX = 25.0f;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) < 2) {
        P16(0xF10) -= 3;
        P16(0xF0C) = static_cast<short>(x);
        P16(0xF0E) = static_cast<short>(y);
        velocityX = (velocityX) - gCompareAt0065747C;
        if ((velocityX) < gCompareAt0065782C)
            velocityX = 0.0f;
    }
    x += static_cast<float>(facing) * (velocityX);
    if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
        ResetAt45B830();
        P16(0xF12) = 0;
    }
    if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0)
        P16(0xF12) = 1;
    if ((reinterpret_cast<signed short&>(animationStage)) == 2 && (reinterpret_cast<signed short&>(animationFrame)) == 0)
        P16(0xF12) = 2;
    break;
}
        case 0x34A: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && (reinterpret_cast<signed short&>(animationStage)) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            reinterpret_cast<signed short&>(field080) = 1;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            ResetStateAt40FBB0(0,0,0);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 3.0f;
            velocityY = -3.0f;
        }
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) + *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + gAddAt00659738;
            velocityY = (velocityY) - gAddAt006583FC;
            if (*(&y) + *(&velocityY) <= gStageContactAt0065786C) {
                y = 20.0f;
                velocityY = 0.0f;
                velocityX = 0.0f;
                SetStateAt40FB40(1);
                rotationZ = 0.0f;
                color[0] = 0xFF;
                break;
            }
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 11) {
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
            ResetAt45B830();
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 6 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DC)) < 1) {
            SetStateAt40FB40(2);
            ++reinterpret_cast<signed short&>(field0DC);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 10 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DA)) < 6) {
            ++reinterpret_cast<signed short&>(field0DA);
            SetStateAt40FB40(9);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 9 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            PF32(0x314) = 1200.0f;
            PF32(0x318) = static_cast<float>(RandomAt455580(0,60));
            PARENT->SpawnMovedAt453A70(0x323,
                   static_cast<float>((facing) * 10) + (x),
                   reinterpret_cast<int&>(y), reinterpret_cast<unsigned char&>(facing), 1);
            PARENT->ModifyAt453D40(6);
        }
    }
    break;
}
        case 0x34B: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && (reinterpret_cast<signed short&>(animationStage)) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, reinterpret_cast<int&>(x), reinterpret_cast<int&>(y), 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            reinterpret_cast<signed short&>(field080) = 1;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            ResetStateAt40FBB0(0,0,0);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            MotionRawPairAt40FB70(reinterpret_cast<int&>(field0CC), reinterpret_cast<int&>(field0C8));
        }
        x += static_cast<float>(facing) * (velocityX);
        y = *(&y) + *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage)) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + gAddAt00659738;
            velocityY = (velocityY) - gGrowAt00657478;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 11) {
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
            ResetAt45B830();
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 1 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 6 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DC)) < 0) {
            SetStateAt40FB40(2);
            ++reinterpret_cast<signed short&>(field0DC);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 10 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DA)) < 6) {
            ++reinterpret_cast<signed short&>(field0DA);
            SetStateAt40FB40(9);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 9 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            PF32(0x314) = 1200.0f;
            PF32(0x318) = static_cast<float>(RandomAt455580(0,15) - 60);
            PARENT->SpawnMovedAt453A70(0x324,
                   static_cast<float>((facing) * 10) + (x),
                   reinterpret_cast<int&>(y), reinterpret_cast<unsigned char&>(facing), 1);
            PARENT->ModifyAt453D40(6);
        }
    }
    break;
}
        case 0x34C: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && (reinterpret_cast<signed short&>(animationStage)) < 5) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        }
        break;
    } else {
        if ((P16(0x60) == 0x198 && P16(0x62) < 7) ||
            (P16(0x60) == 0x19C && P16(0x62) < 5) ||
            (P16(0x60) == 0x19A && P16(0x62) < 7) ||
            (P16(0x60) == 0x19D && P16(0x62) < 5)) {
            x = *(&PF32(0x44)) + static_cast<float>((facing)*60);
            y = PF32(0x48) + gParentYAt006590A8;
            if (P16(0x60) == 0x19A)
                y = PF32(0x48) + gParentYExtraAt00658264;
        } else if ((reinterpret_cast<signed short&>(animationStage)) < 5) {
            SetStateAt40FB40(5);
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 0 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            ResetStateAt40FBB0(0,0,0);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            reinterpret_cast<signed short&>(field0DA) = 0;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 5) {
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == (reinterpret_cast<signed short&>(field070))) {
            ResetAt45B830();
            break;
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 4 && (reinterpret_cast<signed short&>(animationFrame)) == 0 && (reinterpret_cast<signed short&>(field0DA)) < 8) {
            ++reinterpret_cast<signed short&>(field0DA);
            SetStateAt40FB40(3);
        }
        if ((reinterpret_cast<signed short&>(animationStage)) == 3 && (reinterpret_cast<signed short&>(animationFrame)) == 0) {
            if (P16(0x60) == 0x198) {
                PF32(0x314) = 1000.0f;
                PF32(0x318) = static_cast<float>(RandomAt455580(0,10) - 5);
                PARENT->SpawnMovedAt453A70(0x322,
                    static_cast<float>((facing)*10) + (x),
                    reinterpret_cast<int&>(y), reinterpret_cast<unsigned char&>(facing),1);
                PARENT->ModifyAt453D40(6);
            }
            if (P16(0x60) == 0x19A) {
                PF32(0x314) = 1000.0f;
                PF32(0x318) = static_cast<float>(RandomAt455580(0,10) + 30);
                PARENT->SpawnMovedAt453A70(0x323,
                    static_cast<float>((facing)*10) + (x),
                    reinterpret_cast<int&>(y), reinterpret_cast<unsigned char&>(facing),1);
                PARENT->ModifyAt453D40(6);
            }
            if (P16(0x60) == 0x19C) {
                PF32(0x314) = 1000.0f;
                PF32(0x318) = static_cast<float>(RandomAt455580(0,10) - 5);
                PARENT->SpawnMovedAt453A70(0x324,
                    static_cast<float>((facing)*10) + (x),
                    reinterpret_cast<int&>(y), reinterpret_cast<unsigned char&>(facing),1);
                PARENT->ModifyAt453D40(6);
            }
            if (P16(0x60) == 0x19D) {
                PF32(0x314) = 1000.0f;
                PF32(0x318) = static_cast<float>(-RandomAt455580(0,10) - 30);
                PARENT->SpawnMovedAt453A70(0x325,
                    static_cast<float>((facing)*10) + (x),
                    reinterpret_cast<int&>(y), reinterpret_cast<unsigned char&>(facing),1);
                PARENT->ModifyAt453D40(6);
            }
        }
    }
    break;
}
        case 0x34D: {
    if (P16(0x60) > 0x31 && P16(0x60) < 0x96) {
        ResetAt45B830();
        for (int iteration=0; iteration<5; ++iteration)
            PARENT->SpawnAt453A70(0x3E4,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA)=0;
            PARENT->SpawnAt453A70(0x3E3,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        }
        break;
    } else {
        if ((field07C)==6) {
            field07C=0;
            reinterpret_cast<signed short&>(field080)=1;
        }
        if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
            ResetStateAt40FBB0(0,0,0);
            reinterpret_cast<signed short&>(field080)=1;
            field07C=0;
            reinterpret_cast<int&>(velocityX)=reinterpret_cast<int&>(field0C8);
            reinterpret_cast<int&>(velocityY)=reinterpret_cast<int&>(field0CC);
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
            color[1]=0xFF;
            color[2]=0xFF;
            color[3]=0xFF;
        }
        velocityY = (velocityY) - gSubAt00659090;
        x += static_cast<float>(facing)*(velocityX);
        y = *(&y) + *(&velocityY);
        if ((reinterpret_cast<signed short&>(animationStage))<2) {
            rotationZ = (rotationZ)+gLiftAt00657CC0;
            if (*(&y) + *(&velocityY) <= gCompareAt0065782C) {
                PARENT->ModifyAt453D40(4);
                PARENT->SpawnDirectedAt453A70(0x32B,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),facing,1);
                PARENT->SpawnDirectedAt453A70(0x32D,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),facing,1);
                SetActionAt40FAC0(0x33B);
                y=0.0f;
                velocityY=0.0f;
                velocityX=0.0f;
                rotationZ=0.0f;
                break;
            }
        }
        if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
            SetStateAt40FB40(1);
    }
    break;
}
        case 0x34E: {
    if (P16(0x60)>0x31 && P16(0x60)<0x96) {
        ResetAt45B830();
        for (int iteration=0;iteration<4;++iteration)
            PARENT->SpawnAt453A70(0x3E4,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        if (P16(0xEFA)>25) {
            P16(0xEFA)=0;
            PARENT->SpawnAt453A70(0x3E3,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        }
        break;
    } else {
        if ((field07C)==6) {
            field07C=0;
            reinterpret_cast<signed short&>(field080)=1;
        }
        if ((reinterpret_cast<signed short&>(field0D8))>2) {
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY)+gAddAt006583FC;
            if ((color[0])>=10)
                color[0]-=10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
            ResetStateAt40FBB0(0,0,0);

            velocityX=20.0f;
            velocityY=0.0f;
            reinterpret_cast<signed short&>(field0D8)=0;
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
            color[1]=0xFF;
            color[2]=0xFF;
            color[3]=0xFF;
        }
        velocityX = (velocityX)-gCompareAt0065747C;
        if ((velocityX)<gMotionDecelAt00657480)
            velocityX=2.0f;
        x += static_cast<float>(facing)*(velocityX);
        y = *(&y)+*(&velocityY);
        if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
            SetStateAt40FB40(1);
            ++reinterpret_cast<signed short&>(field0D8);
        }
    }
    break;
}
        case 0x34F: {
    if (P16(0x60)>0x31 && P16(0x60)<0x96) {
        ResetAt45B830();
        for (int iteration=0;iteration<4;++iteration)
            PARENT->SpawnAt453A70(0x3E4,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        if (P16(0xEFA)>25) {
            P16(0xEFA)=0;
            PARENT->SpawnAt453A70(0x3E3,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        }
        break;
    } else {
        if ((field07C)==6) {
            field07C=0;
            reinterpret_cast<signed short&>(field080)=1;
        }
        if ((reinterpret_cast<signed short&>(field0D8))>1) {
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY)+gAddAt006583FC;
            if ((color[0])>=10)
                color[0]-=10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
            ResetStateAt40FBB0(0,0,0);

            velocityX=20.0f;
            velocityY=0.0f;
            reinterpret_cast<signed short&>(field0D8)=0;
            field07C=0;
            reinterpret_cast<signed short&>(field080)=1;
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
            color[1]=0xFF;
            color[2]=0xFF;
            color[3]=0xFF;
        }
        velocityX = (velocityX)-gCompareAt0065747C;
        if ((velocityX)<gMotionDecelAt00657480)
            velocityX=2.0f;
        x += static_cast<float>(facing)*(velocityX);
        y = *(&y)+*(&velocityY);
        if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
            ResetAt45B830();
        }
    }
    break;
}
        case 0x370: {
    if (P16(0x60)==0x133) {
        x = *(&PF32(0x44)) + static_cast<float>((facing)*260);
        y = PF32(0x48) + gParentYAt006590A0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
    }
    scaleX = (scaleX) + gAddAt006583FC;
    scaleY = (scaleY) * gSubAt00659090;
    if ((color[0])>20)
        color[0]-=20;
    else {
        ResetAt45B830();
        break;
    }
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x371: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX=0.85f;
        scaleY=0.85f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field01A)=0x4E2;
        rotationX=-65.0f;
    }
    rotationZ = (rotationZ)-gSubtractAt00659728;
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x384: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX = (field0C8)*gMulAt006590B4;
        velocityY = (field0CC)*gMulAt006590B4;
    }
    velocityY = (velocityY)-gDropAt00658058;
    x += static_cast<float>(facing)*(velocityX);
    y = *(&y) + *(&velocityY);
    if ((reinterpret_cast<signed short&>(animationStage))<2) {
        rotationZ = (rotationZ)+gLiftAt00657CC0;
        if (*(&y) + *(&velocityY) <= gCompareAt0065782C) {
            PARENT->SpawnDirectedAt453A70(0x388,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),facing,0);
            PARENT->ModifyAt453D40(8);
            SetActionAt40FAC0(0x385);
            if (gGlobalActorCountAt006714D0>1)
                SetActionAt40FAC0(0x38E);
            y=0.0f;
            velocityY=0.0f;
            velocityX=0.0f;
            rotationZ=0.0f;
            break;
        }
    }
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetStateAt40FB40(1);
    break;
}
        case 0x385: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field0D8)=0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        velocityY=0.0f;
        velocityX=0.0f;
        scaleX=0.75f;
        scaleY=0.75f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<int&>(rotationX)=0;
        reinterpret_cast<int&>(rotationY)=0;
        reinterpret_cast<int&>(rotationZ)=0;
        PARENT->SetupAt453E60(5.0f);
        PARENT->SpawnDirectedAt453A70(0x387,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),facing,1);
    }
    if ((field07C)==6) {
        field07C=0;
        ++reinterpret_cast<signed short&>(field080);
    }
    scaleX = (scaleX)+gAbsScaleAt00659724;
    scaleY = (scaleY)+gAbsScaleAt00659724;
    if ((reinterpret_cast<signed short&>(animationStage))>1) {
        if ((color[0])>=40)
            color[0]-=40;
        else {
            color[0]=0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0)
        PARENT->SpawnDirectedAt453A70(0x386,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),facing,1);
    break;
}
        case 0x386: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field0D8)=0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        velocityY=0.0f;
        velocityX=0.0f;
        scaleX=0.75f;
        scaleY=0.75f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<int&>(rotationX)=0;
        reinterpret_cast<int&>(rotationY)=0;
        reinterpret_cast<int&>(rotationZ)=0;
    }
    scaleX = (scaleX)+gAbsScaleAt00659724;
    scaleY = (scaleY)+gAbsScaleAt00659724;
    if ((color[0])>=20)
        color[0]-=20;
    else {
        color[0]=0;
        ResetAt45B830();
        break;
    }
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x387: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX=0.75f;
        scaleY=0.75f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field01A)=0x4E2;
        rotationX=-75.0f;
    }
    scaleX = (scaleX)+gFadeAt006583F8;
    scaleY = (scaleY)+gFadeAt006583F8;
    if ((reinterpret_cast<signed short&>(animationStage))>1) {
        if ((color[0])>20)
            color[0]-=20;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x388: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        MotionAt40FB70(-(static_cast<float>(RandomAt455580(0,45))
             - gSubtractAt00659728 + gOffsetAt006581DC),18.0f);
    }
    x += static_cast<float>(facing)*(velocityX);
    y = *(&y)+*(&velocityY);
    velocityY = (velocityY)-gVelocityDragAt00659454;
    rotationZ = (rotationZ)+gGrowAt00657CBC;
    if ((y)<gMaxPositionAt0065912C) {
        ResetAt45B830();
        break;
    }
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x389: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if ((field07C)==6) {
        field07C=0;
        reinterpret_cast<signed short&>(field080)=1;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field0D8)=-30;
        reinterpret_cast<signed short&>(field0DA)=150;
        reinterpret_cast<signed short&>(field0DC)=0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        PARENT->SpawnComputedAt453A70(0x371,reinterpret_cast<int&>(x),
                    (y)+gFloatAt00657850,facing,1);
        PARENT->ModifyAt453D40(2);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0) {
        if ((color[0])<225)
            color[0]+=30;
        else
            color[0]=0xFF;
    }
    if ((reinterpret_cast<signed short&>(animationStage))<8 && (reinterpret_cast<signed short&>(field080))==0) {
        SetStateAt40FB40((reinterpret_cast<signed short&>(animationStage))+4);
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))>7) {
        scaleX=static_cast<float>((scaleX)*gMulDoubleAt00659730);
        scaleY=(scaleY)+gAddAt006583FC;
        if ((color[0])>=10)
            color[0]-=10;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetStateAt40FB40(8);
        break;
    }
    if ((reinterpret_cast<signed short&>(animationFrame))==0)
        field07C=0;
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(field0DC))<5) {
        SetStateAt40FB40(4);
        ++reinterpret_cast<signed short&>(field0DC);
    }
    break;
}
        case 0x38A: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field0D8)=10;
        reinterpret_cast<signed short&>(field0DA)=0;
        reinterpret_cast<signed short&>(field0DE)=0;
        reinterpret_cast<signed short&>(field0DC)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==1 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        PARENT->SpawnDirectedAt453A70(0x389,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),facing,1);
    }
    if ((reinterpret_cast<signed short&>(animationStage))>0) {
        reinterpret_cast<signed short&>(field0DA) = static_cast<short>(AngleAt00483300(
            *(&PARENT_TARGET_Y) - *(&y) + gCollisionAt00657888,
            (*(&PARENT_TARGET_X) - *(&x)) * (facing)) / gAngleUnitAt00657828);
        if ((reinterpret_cast<signed short&>(field0DC))>(reinterpret_cast<signed short&>(field0DA))) {
            if ((reinterpret_cast<signed short&>(field0DC))-(reinterpret_cast<signed short&>(field0DA))<=180) {
                reinterpret_cast<signed short&>(field0DC)-=2;
                if ((reinterpret_cast<signed short&>(field0DC))<-180) reinterpret_cast<signed short&>(field0DC)+=360;
            } else {
                reinterpret_cast<signed short&>(field0DC)+=2;
                if ((reinterpret_cast<signed short&>(field0DC))>180) reinterpret_cast<signed short&>(field0DC)-=360;
            }
        }
        if ((reinterpret_cast<signed short&>(field0DC))<=(reinterpret_cast<signed short&>(field0DA))) {
            if ((reinterpret_cast<signed short&>(field0DC))-(reinterpret_cast<signed short&>(field0DA))>=-180) {
                reinterpret_cast<signed short&>(field0DC)+=2;
                if ((reinterpret_cast<signed short&>(field0DC))>180) reinterpret_cast<signed short&>(field0DC)-=360;
            } else {
                reinterpret_cast<signed short&>(field0DC)-=2;
                if ((reinterpret_cast<signed short&>(field0DC))<-180) reinterpret_cast<signed short&>(field0DC)+=360;
            }
        }
    }
    MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0DC)),4.0f);
    x += static_cast<float>(facing)*(velocityX);
    y = *(&y) - *(&velocityY);
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        if ((reinterpret_cast<signed short&>(field0D8))<gGlobalActorCountAt006714D0*5+10) {
            ++reinterpret_cast<signed short&>(field0D8);
            SetStateAt40FB40(1);
            break;
        }
        ResetAt45B830();
        break;
    }
    break;
}
        case 0x38B: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=(field0C8)*gMulAt006590B4;
        velocityY=(field0CC)*gMulAt006590B4;
        reinterpret_cast<signed short&>(field0D8)=static_cast<short>(RandomAt455580(-480,960));
    }
    x += static_cast<float>(facing)*(velocityX);
    y = *(&y)+*(&velocityY);
    if ((reinterpret_cast<signed short&>(animationStage))==0) {
        if ((color[0])<=235)
            color[0]+=20;
        else
            color[0]=0xFF;
        rotationZ=(rotationZ)+gAddAt00659738;
        velocityY=(velocityY)-gDropAt00658058;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==12) {
        scaleX=static_cast<float>((scaleX)*gMulDoubleAt00659730);
        scaleY=(scaleY)+gAddAt006583FC;
        if ((color[0])>=10)
            color[0]-=10;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        ResetAt45B830();
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==1 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        rotationZ=0.0f;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(field0DC))<0) {
        SetStateAt40FB40(2);
        ++reinterpret_cast<signed short&>(field0DC);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        PF32(0x314)=static_cast<float>(reinterpret_cast<signed short&>(field0D8));
        PI32(0x318)=reinterpret_cast<int&>(x);
        PI32(0x31C)=reinterpret_cast<int&>(y);
        PARENT->SpawnDirectedAt453A70(0x38C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),facing,1);
        PARENT->ModifyAt453D40(15);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==10 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(field0DA))<6) {
        ++reinterpret_cast<signed short&>(field0DA);
        SetStateAt40FB40(9);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        PARENT->SpawnMovedAt453A70(0x38D,
            static_cast<float>((reinterpret_cast<signed short&>(field0D8))*(facing)) + (x),
            0,facing,1);
        PARENT->ModifyAt453D40(8);
    }
    break;
}
        case 0x38C: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX = MagnitudeAt00428D20(
            *(&field0C8)* *(&field0C8) + *(&field0D0)* *(&field0D0))
            / gLengthDivisorAt006583A0 * gLengthFactorAt00659720;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ = AngleRawAt00483300(reinterpret_cast<int&>(field0D0),reinterpret_cast<int&>(field0C8)) / gAngleUnitAt00657828;
    }
    scaleY=static_cast<float>((scaleY)*gMulDoubleAt00659730);
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x38D: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field0D8)=0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        velocityY=0.0f;
        velocityX=0.0f;
        scaleX=0.25f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<int&>(rotationX)=0;
        reinterpret_cast<int&>(rotationY)=0;
        reinterpret_cast<int&>(rotationZ)=0;
        PARENT->SetupAt453E60(10.0f);
    }
    if ((field07C)==6) {
        field07C=0;
        ++reinterpret_cast<signed short&>(field080);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0)
        PARENT->SpawnDirectedAt453A70(0x343,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),facing,1);
    if ((reinterpret_cast<signed short&>(animationStage))<3) {
        scaleX=(scaleX)+gFadeAt00659428;
        scaleY=(scaleY)+gFadeAt00659428;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==4) {
        scaleX=(scaleX)*gSubAt00659090;
        if ((color[0])>=20) {
            color[0]-=20;
            color[1]-=20;
            color[2]-=20;
        } else {
            color[0]=0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(field0D8))<5) {
        ++reinterpret_cast<signed short&>(field0D8);
        SetStateAt40FB40(3);
    }
    break;
}
        case 0x38E: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field0D8)=0;
        ResetStateAt40FBB0(0,0,0);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        velocityY=0.0f;
        velocityX=0.0f;
        scaleX=0.75f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<int&>(rotationX)=0;
        reinterpret_cast<int&>(rotationY)=0;
        reinterpret_cast<int&>(rotationZ)=0;
        PARENT->SetupAt453E60(5.0f);
        PARENT->SpawnDirectedAt453A70(0x387,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),facing,1);
    }
    if ((field07C)==6) {
        field07C=0;
        ++reinterpret_cast<signed short&>(field080);
    }
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        ResetAt45B830();
    break;
}
        case 0x3E3: {
    facing=1;
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=0.0f;
        velocityY=-1.0f;
        reinterpret_cast<signed short&>(field0D8)=static_cast<short>(RandomAt455580(0,360)-180);
        reinterpret_cast<signed short&>(field0DA)=15;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0) {
        --reinterpret_cast<signed short&>(field0DA);
        if ((reinterpret_cast<signed short&>(field0DA))<3) reinterpret_cast<signed short&>(field0DA)=3;
        MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),
                       static_cast<float>(reinterpret_cast<signed short&>(field0DA))*gSubAt00659090);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==1) {
        reinterpret_cast<signed short&>(field0D8)=static_cast<short>(AngleAt00483300(
            PARENT_TARGET_Y + *(&gCollisionAt00657888) - (y),
            *(&PARENT_TARGET_X)-*(&x)) / gAngleUnitAt00657828);
        MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),20.0f);
        if ((*(&x) - *(&PARENT_TARGET_X) < gStageContactAt0065786C) &&
            (*(&x) - *(&PARENT_TARGET_X) > gTouchMaxAt00659230) &&
            (*(&y) - *(&PARENT_TARGET_Y) < gParentYAt006590A8) &&
            (*(&y) - *(&PARENT_TARGET_Y) > gVerticalTouchMaxAt00658268)) {
            ResetAt45B830();
            if (PARENT_TARGET_S8(0x366)<2)
                ++PARENT_TARGET_U8(0x366);
            else
                PARENT_TARGET_I32(0x2D0)+=20000;
            ResetAt45B860(0x2E);
            break;
        }
    }
    x=*(&x)+*(&velocityX);
    y=*(&y)-*(&velocityY);
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetStateAt40FB40(1);
    break;
}
        case 0x3E4: {
    facing=1;
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=0.0f;
        velocityY=-1.0f;
        reinterpret_cast<signed short&>(field0D8)=static_cast<short>(RandomAt455580(0,360)-180);
        reinterpret_cast<signed short&>(field0DA)=15;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0) {
        --reinterpret_cast<signed short&>(field0DA);
        if ((reinterpret_cast<signed short&>(field0DA))<3) reinterpret_cast<signed short&>(field0DA)=3;
        MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),
                       static_cast<float>(reinterpret_cast<signed short&>(field0DA))*gSubAt00659090);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==1) {
        reinterpret_cast<signed short&>(field0D8)=static_cast<short>(AngleAt00483300(
            PARENT_TARGET_Y + *(&gCollisionAt00657888) - (y),
            *(&PARENT_TARGET_X)-*(&x)) / gAngleUnitAt00657828);
        MotionAt40FB70(static_cast<float>(reinterpret_cast<signed short&>(field0D8)),20.0f);
        if ((*(&x) - *(&PARENT_TARGET_X) < gStageContactAt0065786C) &&
            (*(&x) - *(&PARENT_TARGET_X) > gTouchMaxAt00659230) &&
            (*(&y) - *(&PARENT_TARGET_Y) < gParentYAt006590A8) &&
            (*(&y) - *(&PARENT_TARGET_Y) > gVerticalTouchMaxAt00658268)) {
            ++P16(0xEFA);
            ResetAt45B860(0x2E);
            ResetAt45B830();
            if (PARENT_TARGET_S16(0x3B6)>0) {
                if (PARENT_TARGET_S16(0x3B6)>5)
                    PARENT_TARGET_S16(0x3B6)-=5;
                else {
                    PARENT_TARGET_S16(0x3B6)=0;
                    PARENT_TARGET_S16(0x3B0)=1000;
                }
                break;
            }
            if (PARENT_TARGET_S16(0x3B0)<990)
                PARENT_TARGET_S16(0x3B0)+=10;
            else {
                PARENT_TARGET_S16(0x3B0)=1000;
                if (PARENT_TARGET_U8(0x39C)==0) {
                    if (PARENT_TARGET_F32(0x36C)<gDoubleTouchAt00659228)
                        PARENT_TARGET_F32(0x36C)=PARENT_TARGET_F32(0x36C)+gNextBonusAt00657478;
                    else
                        PARENT_TARGET_F32(0x36C)=900.0f;
                }
            }
            break;
        }
    }
    x=*(&x)+*(&velocityX);
    y=*(&y)-*(&velocityY);
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetStateAt40FB40(1);
    break;
}
        case 0x3E5: {
    reinterpret_cast<int&>(x)=*reinterpret_cast<int*>(reinterpret_cast<char*>(PARENT)+0x44);
    reinterpret_cast<int&>(y)=0;
    reinterpret_cast<signed short&>(field08A)=1;
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetStateAt40FBB0(0,0,0);
        scaleX=3.0f;
        scaleY=3.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field01A)=0x4E2;
        reinterpret_cast<int&>(rotationY)=0;
        reinterpret_cast<int&>(rotationZ)=0;
        rotationX=-80.0f;
        reinterpret_cast<signed short&>(field0D8)=P16(0x3A0);
    }
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    scaleX=static_cast<float>(P16(0x3A0))/(reinterpret_cast<signed short&>(field0D8))*2.0f;
    scaleY=static_cast<float>(P16(0x3A0))/(reinterpret_cast<signed short&>(field0D8))*2.0f;
    rotationZ=(rotationZ)+gCompareAt0065747C;
    if (GetStateAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetStateAt40FB40(9);
        break;
    }
    break;
}
        default: GetStateAt40FA30();
    }
}
#undef OWNER
#undef I16
#undef RAW
