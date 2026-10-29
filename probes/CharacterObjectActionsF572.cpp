// F572/F573/F574/F575/F576/F577/F578/F579/F580/F581/F582/F583/F585/F586/F587/F588/F590/F591: selected natural VC7.1 source, original PE 004EBDA0.
// Implements complete original actions 0x320..0x387 (excluding default aliases) in a 33,293-byte
// CharacterObject megaboss. All later cases are DIAGNOSTIC marker stores,
// not restored gameplay; this source is NOT a complete original function,
// does not earn independent native CODE or after-RET DATA exact credit.
// Original member/class names remain borrowed hypotheses. No target ASM,
// hidden padding, byte grafting or fake stack locals are present.
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
class FighterSwitchF572_Boss004EBDA0 {
public:
    void Advance();
    void ResetAt4F4170();
    void ResetAt45B830();
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
#define PARENT_TARGET_X (*reinterpret_cast<float*>(*reinterpret_cast<char**>(reinterpret_cast<char*>(PARENT)+0x2E8)+0x44))
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
            I16(0x8A) == 0)
        return;
    if (I16(0x82) != 0) {
        --I16(0x82);
        return;
    }
    switch (I16(0x60)) {
        case 0x320: ResetAt4F4170(); break;
        case 0x321: ResetAt4F4170(); break;
        case 0x322: ResetAt4F4170(); break;
        case 0x323: ResetAt4F4170(); break;
        case 0x324: ResetAt4F4170(); break;
        case 0x325: ResetAt4F4170(); break;
        case 0x326: ResetAt4F4170(); break;
        case 0x327: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && S16(0x62) < 5) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 0x19) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (I32(0x7C) == 6) {
            I32(0x7C) = 0;
            S16(0x80) = 1;
        }
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            S16(0xD8) = -30;
            S16(0xDA) = 150;
            S16(0xDC) = 0;
            ResetStateAt40FBB0(0,0,0);
            S16(0x80) = 4;
            I32(0x7C) = 0;
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0xFF;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
        }
        if (S16(0x62) == 1 && S16(0x64) == 0) {
            PARENT->SpawnComputedAt453A70(0x371, I32(0x44),
                                  F32(0x48) + gFloatAt00657850,
                                  S8(0x66), 1);
            PARENT->ModifyAt453D40(2);
        }
        if (S16(0x62) == 0) {
            MotionAt40FB70(static_cast<float>(S16(0xD8)),
                            static_cast<float>(S16(0xDA))*gMulAt006590B4);
            S16(0xDA) -= 5;
            S16(0xD8) += 3;
            F32(0x30) = F32(0x30) + gAddAt00659738;
            if (S16(0xDA) <= 0) {
                F32(0x50) = 0.0f;
                F32(0x54) = 0.0f;
                SetStateAt40FB40(1);
                F32(0x30) = 0.0f;
                break;
            }
        }
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) - *(&F32(0x54));
        if (S16(0x62) < 5 && S16(0x80) == 0) {
            SetStateAt40FB40(S16(0x62) + 4);
            break;
        }
        if (S16(0x62) > 4) {
            F32(0x1C) = static_cast<float>(F32(0x1C)*gMulDoubleAt00659730);
            F32(0x20) = F32(0x20) + gAddAt006583FC;
            if (U8(0x11) >= 10)
                U8(0x11) -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70)) {
            SetStateAt40FB40(5);
            break;
        }
        if (S16(0x64) == 0)
            I32(0x7C) = 0;
        if (S16(0x62) == 5 && S16(0x64) == 0 && S16(0xDC) < 10) {
            SetStateAt40FB40(1);
            ++S16(0xDC);
        }
    }
    break;
}
        case 0x328: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && S16(0x62) < 5) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 0x19) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (I32(0x7C) == 6) {
            I32(0x7C) = 0;
            S16(0x80) = 1;
        }
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            S16(0xD8) = 70;
            S16(0xDA) = 150;
            S16(0xDC) = 0;
            ResetStateAt40FBB0(0,0,0);
            S16(0x80) = 4;
            I32(0x7C) = 0;
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0xFF;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
        }
        if (S16(0x62) == 1 && S16(0x64) == 0) {
            PARENT->SpawnComputedAt453A70(0x371, I32(0x44),
                                  F32(0x48) + gFloatAt00657850,
                                  S8(0x66), 1);
            PARENT->ModifyAt453D40(2);
        }
        if (S16(0x62) == 0) {
            MotionAt40FB70(static_cast<float>(S16(0xD8)),
                            static_cast<float>(S16(0xDA))*gMulAt006590B4);
            S16(0xDA) -= 5;
            S16(0xD8) -= 2;
            F32(0x30) = F32(0x30) + gAddAt00659738;
            if (S16(0xDA) <= 0) {
                F32(0x50) = 0.0f;
                F32(0x54) = 0.0f;
                SetStateAt40FB40(1);
                F32(0x30) = 0.0f;
                break;
            }
        }
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) - *(&F32(0x54));
        if (S16(0x62) < 5 && S16(0x80) == 0) {
            SetStateAt40FB40(S16(0x62) + 4);
            break;
        }
        if (S16(0x62) > 4) {
            F32(0x1C) = static_cast<float>(F32(0x1C)*gMulDoubleAt00659730);
            F32(0x20) = F32(0x20) + gAddAt006583FC;
            if (U8(0x11) >= 10)
                U8(0x11) -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70)) {
            SetStateAt40FB40(5);
            break;
        }
        if (S16(0x64) == 0)
            I32(0x7C) = 0;
        if (S16(0x62) == 5 && S16(0x64) == 0 && S16(0xDC) < 10) {
            SetStateAt40FB40(1);
            ++S16(0xDC);
        }
    }
    break;
}
        case 0x329: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && S16(0x62) < 5) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 0x19) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (I32(0x7C) == 6) {
            I32(0x7C) = 0;
            S16(0x80) = 1;
        }
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            S16(0xD8) = -30;
            S16(0xDA) = 200;
            S16(0xDC) = 0;
            ResetStateAt40FBB0(0,0,0);
            S16(0x80) = 4;
            I32(0x7C) = 0;
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0xFF;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
        }
        if (S16(0x62) == 1 && S16(0x64) == 0) {
            PARENT->SpawnComputedAt453A70(0x371, I32(0x44),
                                  F32(0x48) + gFloatAt00657850,
                                  S8(0x66), 1);
            PARENT->ModifyAt453D40(2);
        }
        if (S16(0x62) == 0) {
            MotionAt40FB70(static_cast<float>(S16(0xD8)),
                            static_cast<float>(S16(0xDA))*gMulAt006590B4);
            S16(0xDA) -= 5;
            S16(0xD8) += 4;
            F32(0x30) = F32(0x30) + gAddAt00659738;
            if (S16(0xDA) <= 0) {
                F32(0x50) = 0.0f;
                F32(0x54) = 0.0f;
                SetStateAt40FB40(1);
                F32(0x30) = 0.0f;
                break;
            }
        }
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) - *(&F32(0x54));
        if (S16(0x62) < 5 && S16(0x80) == 0) {
            SetStateAt40FB40(S16(0x62) + 4);
            break;
        }
        if (S16(0x62) > 4) {
            F32(0x1C) = static_cast<float>(F32(0x1C)*gMulDoubleAt00659730);
            F32(0x20) = F32(0x20) + gAddAt006583FC;
            if (U8(0x11) >= 10)
                U8(0x11) -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70)) {
            SetStateAt40FB40(5);
            break;
        }
        if (S16(0x64) == 0)
            I32(0x7C) = 0;
        if (S16(0x62) == 5 && S16(0x64) == 0 && S16(0xDC) < 10) {
            SetStateAt40FB40(1);
            ++S16(0xDC);
        }
    }
    break;
}
        case 0x32A: {
    if (P16(0x60) > 0x31 && P16(0x60) < 0x96) {
        ResetAt45B830();
        for (int iteration=0; iteration<5; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 0x19) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (I32(0x7C) == 6) {
            I32(0x7C) = 0;
            S16(0x80) = 1;
        }
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            ResetStateAt40FBB0(0,0,0);
            S16(0x80) = 1;
            I32(0x7C) = 0;
            if (*(&F32(0xC8)) == gCompareAt0065782C) {
                F32(0x50) = 5.0f;
                F32(0x54) = 6.0f;
            }
            if (*(&F32(0xC8)) == gCompareAt0065747C) {
                F32(0x50) = 3.0f;
                F32(0x54) = 8.0f;
            }
            if (*(&F32(0xC8)) == gCompareAt00657480) {
                F32(0x50) = 1.0f;
                F32(0x54) = 10.0f;
            }
            if (*(&F32(0xC8)) == gCompareAt00657CF8) {
                F32(0x50) = -5.0f;
                F32(0x54) = 6.0f;
            }
            if (*(&F32(0xC8)) == gCompareAt00657D14) {
                F32(0x50) = -3.0f;
                F32(0x54) = 8.0f;
            }
            if (*(&F32(0xC8)) == gCompareAt00657874) {
                F32(0x50) = -1.0f;
                F32(0x54) = 10.0f;
            }
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0xFF;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
        }
        F32(0x54) = F32(0x54) - gDropAt00658058;
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (S16(0x62) < 2) {
            F32(0x30) = F32(0x30) + gLiftAt00657CC0;
            if (F32(0x48) + F32(0x54) <= gCompareAt0065782C) {
                PARENT->SpawnDirectedAt453A70(0x32B, I32(0x44), I32(0x48), S8(0x66), 1);
                PARENT->SpawnDirectedAt453A70(0x32D, I32(0x44), I32(0x48), S8(0x66), 1);
                PARENT->ModifyAt453D40(4);
                SetActionAt40FAC0(0x33B);
                F32(0x48) = 0.0f;
                F32(0x54) = 0.0f;
                F32(0x50) = 0.0f;
                F32(0x30) = 0.0f;
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70))
            SetStateAt40FB40(1);
    }
    break;
}
        case 0x32B: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        S16(0xD8) = 0;
        ResetStateAt40FBB0(0,0,0);
        S16(0x80) = 1;
        I32(0x7C) = 0;
        F32(0x54) = 0.0f;
        F32(0x50) = 0.0f;
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        I32(0x28) = 0;
        I32(0x2C) = 0;
        I32(0x30) = 0;
        PARENT->SetupAt453E60(5.0f);
    }
    F32(0x1C) = (float)(5 - S16(0x64)) * gCurveAt0065972C * (S16(0x64) < 5) + gStepAt00658044 + F32(0x1C);
    F32(0x20) = (float)(5 - S16(0x64)) * gCurveAt0065972C * (S16(0x64) < 5) + gStepAt00658044 + F32(0x20);
    if (S16(0x62) > 1) {
        if (U8(0x11) >= 10)
            U8(0x11) -= 10;
        else {
            U8(0x11) = 0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x32C: {
    if (P16(0x60) > 0x31 && P16(0x60) < 0x96) {
        ResetAt45B830();
        for (int iteration=0; iteration<5; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            ResetStateAt40FBB0(0,0,0);
            S16(0x80) = 1;
            I32(0x7C) = 0;
            MotionRawAt40FB70(I32(0xC8),15.0f);
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0xFF;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
        }
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (S16(0x62) < 2) {
            F32(0x30) = F32(0x30) + gLiftAt00657CC0;
            if (F32(0x48) + F32(0x54) <= gCompareAt0065782C) {
                PARENT->ModifyAt453D40(4);
                PARENT->SpawnDirectedAt453A70(0x32B, I32(0x44), I32(0x48), S8(0x66), 1);
                PARENT->SpawnDirectedAt453A70(0x32D, I32(0x44), I32(0x48), S8(0x66), 1);
                SetActionAt40FAC0(0x33B);
                F32(0x48) = 0.0f;
                F32(0x54) = 0.0f;
                F32(0x50) = 0.0f;
                F32(0x30) = 0.0f;
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70))
            SetStateAt40FB40(1);
    }
    break;
}
        case 0x32D: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C) = 0.4f;
        F32(0x20) = 0.4f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        S16(0x1A) = 0x4E2;
        F32(0x28) = -75.0f;
    }
    F32(0x1C) = F32(0x1C) + gFadeAt006583F8;
    F32(0x20) = F32(0x20) + gFadeAt006583F8;
    if (S16(0x62) > 1) {
        if (U8(0x11) > 20)
            U8(0x11) -= 20;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x32E: {
    if (S16(0x62) == 0 && S16(0x64) == 0 && S16(0xD8) == 1) {
        S16(0xD8) = 0;
        ResetStateAt40FBB0(0,0,0);
        S16(0x80) = 1;
        I32(0x7C) = 0;
        F32(0x54) = 0.0f;
        F32(0x50) = 0.0f;
        F32(0x1C) = 0.5f;
        F32(0x20) = 0.5f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        I32(0x28) = 0;
        I32(0x2C) = 0;
        I32(0x30) = 0;
    }
    F32(0x1C) = F32(0x1C) + gFadeAt00659428;
    F32(0x20) = F32(0x20) + gFadeAt00659428;
    U8(0x11) -= 10;
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x330: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && S16(0x62) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (I32(0x7C) == 6) {
            I32(0x7C) = 0;
            S16(0x80) = 1;
        }
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            ResetStateAt40FBB0(0,0,0);
            I32(0x7C) = 0;
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
            F32(0x50) = -4.0f;
            F32(0x54) = 6.0f;
        }
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (S16(0x62) == 0) {
            if (U8(0x11) <= 0xEB)
                U8(0x11) += 20;
            else
                U8(0x11) = 0xFF;
            F32(0x30) = F32(0x30) + gAddAt00659738;
            F32(0x54) = F32(0x54) - gAddAt006583FC;
        }
        if (S16(0x62) == 11) {
            F32(0x1C) = static_cast<float>(F32(0x1C) * gMulDoubleAt00659730);
            F32(0x20) = F32(0x20) + gAddAt006583FC;
            if (U8(0x11) >= 10)
                U8(0x11) -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70)) {
            ResetAt45B830();
            break;
        }
        if (S16(0x62) == 1 && S16(0x64) == 0) {
            F32(0x50) = 0.0f;
            F32(0x54) = 0.0f;
            F32(0x30) = 0.0f;
        }
        if (S16(0x62) == 6 && S16(0x64) == 0 && S16(0xDC) < 0) {
            SetStateAt40FB40(2);
            ++S16(0xDC);
        }
        if (S16(0x62) == 10 && S16(0x64) == 0 && S16(0xDA) < 6) {
            ++S16(0xDA);
            SetStateAt40FB40(9);
        }
        if (S16(0x62) == 9 && S16(0x64) == 0) {
            PF32(0x314) = 1200.0f;
            PF32(0x318) = static_cast<float>(RandomAt455580(0,10) - 5);
            PARENT->SpawnMovedAt453A70(0x320,
                   static_cast<float>(S8(0x66) * 10) + F32(0x44),
                   I32(0x48), U8(0x66), 1);
            PARENT->ModifyAt453D40(6);
        }
    }
    break;
}
        case 0x331: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && S16(0x62) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (I32(0x7C) == 6) {
            I32(0x7C) = 0;
            S16(0x80) = 1;
        }
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            ResetStateAt40FBB0(0,0,0);
            I32(0x7C) = 0;
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
            F32(0x50) = 3.0f;
            F32(0x54) = 16.0f;
        }
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (S16(0x62) == 0) {
            if (U8(0x11) <= 0xEB)
                U8(0x11) += 20;
            else
                U8(0x11) = 0xFF;
            F32(0x30) = F32(0x30) + gAddAt00659738;
            F32(0x54) = F32(0x54) - gSubAt00659090;
        }
        if (S16(0x62) == 11) {
            F32(0x1C) = static_cast<float>(F32(0x1C) * gMulDoubleAt00659730);
            F32(0x20) = F32(0x20) + gAddAt006583FC;
            if (U8(0x11) >= 10)
                U8(0x11) -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70)) {
            ResetAt45B830();
            break;
        }
        if (S16(0x62) == 1 && S16(0x64) == 0) {
            F32(0x50) = 0.0f;
            F32(0x54) = 0.0f;
            F32(0x30) = 0.0f;
        }
        if (S16(0x62) == 6 && S16(0x64) == 0 && S16(0xDC) < 0) {
            SetStateAt40FB40(2);
            ++S16(0xDC);
        }
        if (S16(0x62) == 10 && S16(0x64) == 0 && S16(0xDA) < 6) {
            ++S16(0xDA);
            SetStateAt40FB40(9);
        }
        if (S16(0x62) == 9 && S16(0x64) == 0) {
            PF32(0x314) = 1200.0f;
            PF32(0x318) = static_cast<float>(RandomAt455580(0,15) - 45);
            PARENT->SpawnMovedAt453A70(0x321,
                   static_cast<float>(S8(0x66) * 10) + F32(0x44),
                   I32(0x48), U8(0x66), 1);
            PARENT->ModifyAt453D40(6);
        }
    }
    break;
}
        case 0x332: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && S16(0x62) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (I32(0x7C) == 6) {
            I32(0x7C) = 0;
            S16(0x80) = 1;
        }
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            ResetStateAt40FBB0(0,0,0);
            I32(0x7C) = 0;
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
            F32(0x50) = 6.0f;
            F32(0x54) = 4.5f;
        }
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (S16(0x62) == 0) {
            if (U8(0x11) <= 0xEB)
                U8(0x11) += 20;
            else
                U8(0x11) = 0xFF;
            F32(0x30) = F32(0x30) + gAddAt00659738;
            F32(0x54) = F32(0x54) - gAddAt006583FC;
        }
        if (S16(0x62) == 11) {
            F32(0x1C) = static_cast<float>(F32(0x1C) * gMulDoubleAt00659730);
            F32(0x20) = F32(0x20) + gAddAt006583FC;
            if (U8(0x11) >= 10)
                U8(0x11) -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70)) {
            ResetAt45B830();
            break;
        }
        if (S16(0x62) == 1 && S16(0x64) == 0) {
            F32(0x50) = 0.0f;
            F32(0x54) = 0.0f;
            F32(0x30) = 0.0f;
            S8(0x66) = -S8(0x66);
        }
        if (S16(0x62) == 6 && S16(0x64) == 0 && S16(0xDC) < 0) {
            SetStateAt40FB40(2);
            ++S16(0xDC);
        }
        if (S16(0x62) == 10 && S16(0x64) == 0 && S16(0xDA) < 6) {
            ++S16(0xDA);
            SetStateAt40FB40(9);
        }
        if (S16(0x62) == 9 && S16(0x64) == 0) {
            PF32(0x314) = 1200.0f;
            PF32(0x318) = static_cast<float>(RandomAt455580(0,10) - 5);
            PARENT->SpawnMovedAt453A70(0x322,
                   static_cast<float>(S8(0x66) * 10) + F32(0x44),
                   I32(0x48), U8(0x66), 1);
            PARENT->ModifyAt453D40(6);
        }
    }
    break;
}
        case 0x335: {
    if (I32(0x7C) == 6) {
        I32(0x7C) = 0;
        S16(0x80) = 99;
    }
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 &&
            S16(0x80) > 0 && S16(0x62) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            S16(0xD8) = 0;
            S16(0xDA) = 0;
            S16(0xDC) = 0;
            I32(0x7C) = 0;
            S16(0x80) = 99;
            ResetStateAt40FBB0(0,0,0);
            I32(0x7C) = 0;
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0xFF;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
            MotionRawAt40FB70(I32(0xC8),14.0f);
        }
        if (S16(0x62) == 0) {
            F32(0x30) = F32(0x30) + gGrowAt00657CBC;
            F32(0x54) = F32(0x54) + gGrowAt00657478;
        }
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) - *(&F32(0x54));
        if (S16(0x62) == 10 && F32(0x48) - F32(0x54) <= gCollisionAt00657888) {
            F32(0x50) = 2.0f;
            F32(0x54) = 2.0f;
            SetStateAt40FB40(11);
        }
        if (S16(0x62) > 10 && S16(0xD8) > 2) {
            F32(0x50) = 0.0f;
            F32(0x54) = 0.0f;
            F32(0x1C) = static_cast<float>(F32(0x1C) * gMulDoubleAt00659730);
            F32(0x20) = F32(0x20) + gAddAt006583FC;
            if (U8(0x11) >= 10)
                U8(0x11) -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70)) {
            SetStateAt40FB40(10);
            ++S16(0xD8);
            break;
        }
        if (S16(0x62) == 1 && S16(0x64) == 0) {
            F32(0x50) = 0.0f;
            F32(0x54) = 0.0f;
            F32(0x30) = 0.0f;
        }
        if (S16(0x62) == 6 && S16(0x64) == 0 &&
                static_cast<float>(S16(0xDC)) < *(&gCompareAt0065782C) + *(&F32(0xCC))) {
            SetStateAt40FB40(2);
            ++S16(0xDC);
        }
        if (S16(0x62) == 10 && S16(0x64) == 0) {
            PARENT->ModifyAt453D40(16);
            F32(0x50) = 18.0f;
            F32(0x54) = 18.0f;
        }
    }
    break;
}
        case 0x338: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        S16(0xD8) = 0;
        ResetStateAt40FBB0(0,0,0);
        S16(0x80) = 1;
        I32(0x7C) = 0;
        F32(0x54) = 0.0f;
        F32(0x50) = 0.0f;
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        I32(0x28) = 0;
        I32(0x2C) = 0;
        I32(0x30) = 0;
        PARENT->SetupAt453E60(10.0f);
        PARENT->SpawnDirectedAt453A70(0x33A, I32(0x44), I32(0x48), S8(0x66), 1);
    }
    if (I32(0x7C) == 6) {
        I32(0x7C) = 0;
        ++S16(0x80);
    }
    F32(0x1C) = F32(0x1C) + gFadeAt00659428;
    F32(0x20) = F32(0x20) + gFadeAt00659428;
    if (S16(0x62) > 1) {
        if (U8(0x11) >= 20)
            U8(0x11) -= 20;
        else {
            U8(0x11) = 0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    if (S16(0x62) == 2 && S16(0x64) == 0)
        PARENT->SpawnDirectedAt453A70(0x339, I32(0x44), I32(0x48), S8(0x66), 1);
    break;
}
        case 0x339: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        S16(0xD8) = 0;
        ResetStateAt40FBB0(0,0,0);
        S16(0x80) = 1;
        I32(0x7C) = 0;
        F32(0x54) = 0.0f;
        F32(0x50) = 0.0f;
        F32(0x1C) = 1.3f;
        F32(0x20) = 1.3f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        I32(0x28) = 0;
        I32(0x2C) = 0;
        I32(0x30) = 0;
    }
    F32(0x1C) = F32(0x1C) + gFadeAt00659428;
    F32(0x20) = F32(0x20) + gFadeAt00659428;
    if (S16(0x62) > 1) {
        if (U8(0x11) >= 40)
            U8(0x11) -= 40;
        else {
            U8(0x11) = 0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x33A: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        S16(0x1A) = 0x4E2;
        F32(0x28) = -75.0f;
    }
    F32(0x1C) = F32(0x1C) + gAddAt006583FC;
    F32(0x20) = F32(0x20) + gAddAt006583FC;
    if (S16(0x62) > 1) {
        if (U8(0x11) > 20)
            U8(0x11) -= 20;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x33B: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        MotionAt40FB70(-(static_cast<float>(RandomAt455580(0,45))
                - gSubtractAt00659728 + gOffsetAt006581DC),18.0f);
    }
    F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
    F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
    F32(0x54) = F32(0x54) - gVelocityDragAt00659454;
    F32(0x30) = F32(0x30) + gGrowAt00657CBC;
    if (F32(0x48) < gMaxPositionAt0065912C) {
        ResetAt45B830();
        break;
    }
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x33C: {
    if (P16(0x60) == 0x2BE) {
        F32(0x44) = *(&PF32(0x44)) + static_cast<float>(S8(0x66) * 65);
        F32(0x48) = PF32(0x48) + gStageOffsetAt006590AC;
    }
    if (P16(0x60) != 0x2BE ||
            (P16(0x62) > 9 && P16(0x60) == 0x2BE)) {
        if (S16(0xD8) == 0) {
            S16(0xD8) = 1;
            break;
        }
    }
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        S16(0xD8) = 0;
        ResetStateAt40FBB0(0,0,0);
        I32(0x7C) = 0;
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
    }
    if (S16(0xD8) == 0) {
        if (U8(0x11) <= 0xE1)
            U8(0x11) += 30;
        else
            U8(0x11) = 0xFF;
    }
    if (S16(0xD8) == 1) {
        F32(0x1C) = static_cast<float>(F32(0x1C) * gMulDoubleAt00659730);
        F32(0x20) = F32(0x20) + gAddAt006583FC;
        if (U8(0x11) >= 10)
            U8(0x11) -= 10;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70)) {
        SetStateAt40FB40(1);
        break;
    }
    break;
}
        case 0x33D: {
    if (P16(0x60) == 0x2C1) {
        F32(0x44) = *(&PF32(0x44)) + static_cast<float>(S8(0x66) * 65);
        F32(0x48) = PF32(0x48) + gStageOffsetAt006590AC;
    }
    if (P16(0x60) != 0x2C1 ||
            (P16(0x62) > 9 && P16(0x60) == 0x2BE)) {
        if (S16(0xD8) == 0) {
            S16(0xD8) = 1;
            break;
        }
    }
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        S16(0xD8) = 0;
        ResetStateAt40FBB0(0,0,0);
        I32(0x7C) = 0;
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
    }
    if (S16(0xD8) == 0) {
        if (U8(0x11) <= 0xE1)
            U8(0x11) += 30;
        else
            U8(0x11) = 0xFF;
    }
    if (S16(0xD8) == 1) {
        F32(0x1C) = static_cast<float>(F32(0x1C) * gMulDoubleAt00659730);
        F32(0x20) = F32(0x20) + gAddAt006583FC;
        if (U8(0x11) >= 10)
            U8(0x11) -= 10;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70)) {
        SetStateAt40FB40(1);
        break;
    }
    break;
}
        case 0x33E: {
    if (P16(0x60) == 0x2BE) {
        F32(0x44) = *(&PF32(0x44)) + static_cast<float>(S8(0x66) * 140);
        F32(0x48) = PF32(0x48) + gStageOffsetAt006590AC;
    }
    if (P16(0x60) != 0x2BE && S16(0x62) < 7) {
        SetStateAt40FB40(7);
        break;
    }
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        S16(0x80) = 1;
        I32(0x7C) = 0;
        if (S16(0xD8) != 1) {
            ResetStateAt40FBB0(0,0,0);
            F32(0x1C) = 1.5f;
            F32(0x20) = 1.5f;
            S16(0xD8) = 0;
            U8(0x11) = 0xFF;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
            S16(0x80) = 10;
        }
    }
    if (S16(0x62) == 6)
        F32(0x20) = static_cast<float>(RandomAt455580(0,4) - 2)
                  * gScatterRateAt006578C0 + gScatterBaseAt006581E0;
    if (S16(0x62) == 7)
        F32(0x20) = F32(0x20) * gShrinkAt00659094;
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    if (S16(0x62) == 7 && S16(0x64) == 0 && S16(0xD8) < 10) {
        SetStateAt40FB40(6);
        I32(0x7C) = 0;
        ++S16(0xD8);
    }
    break;
}
        case 0x33F: {
    if (P16(0x60) == 0x2C1) {
        F32(0x44) = *(&PF32(0x44)) + static_cast<float>(S8(0x66) * 180);
        F32(0x48) = PF32(0x48) + gStageOffsetAt006590AC;
    }
    if (P16(0x60) != 0x2C1 && S16(0x62) < 17) {
        SetStateAt40FB40(17);
        break;
    }
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        I32(0x7C) = 0;
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C) = 2.0f;
        F32(0x20) = 1.5f;
        S16(0xD8) = 0;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        S16(0x80) = 25;
    }
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    if (S16(0x64) == 0)
        I32(0x7C) = 0;
    if (S16(0x62) == 13 && S16(0x64) == 0 && S16(0xD8) < 2) {
        SetStateAt40FB40(6);
        ++S16(0xD8);
    }
    break;
}
        case 0x340: {
    if (I32(0x7C) == 6) {
        I32(0x7C) = 0;
        S16(0x80) = 1;
    }
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        S16(0x80) = 1;
        I32(0x7C) = 0;
        F32(0x50) = AbsFloatAt00412D90(
            *(&PF32(0x44)) + static_cast<float>(PS8(0x66)*90) - PARENT_TARGET_X
        ) * gAbsScaleAt00659724;
        if (F32(0x50) < gInitialClampAt00657D14)
            F32(0x50) = 4.0f;
        F32(0x54) = 20.0f;
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
    }
    F32(0x54) = F32(0x54) - gMotionDecelAt00657480;
    F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
    F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
    if (S16(0x62) < 2) {
        F32(0x30) = F32(0x30) + gLiftAt00657CC0;
        if (*(&F32(0x48)) + *(&F32(0x54)) <= gCompareAt0065782C) {
            PARENT->SpawnDirectedAt453A70(0x338, I32(0x44), I32(0x48), S8(0x66), 1);
            PARENT->SpawnDirectedAt453A70(0x33A, I32(0x44), I32(0x48), S8(0x66), 1);
            PARENT->ModifyAt453D40(8);
            SetActionAt40FAC0(0x33B);
            F32(0x48) = 0.0f;
            F32(0x54) = 0.0f;
            F32(0x50) = 0.0f;
            F32(0x30) = 0.0f;
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70))
        SetStateAt40FB40(1);
    break;
}
        case 0x341: {
    if (I32(0x7C) == 6) {
        I32(0x7C) = 0;
        S16(0x80) = 1;
    }
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        S16(0x80) = 1;
        I32(0x7C) = 0;
        F32(0x50) = AbsFloatAt00412D90(
            *(&PF32(0x44)) + static_cast<float>(PS8(0x66)*90) - PARENT_TARGET_X
        ) * gAbsScaleAt00659724;
        if (F32(0x50) < gInitialClampAt00657D14)
            F32(0x50) = 4.0f;
        F32(0x54) = 20.0f;
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
    }
    F32(0x54) = F32(0x54) - gMotionDecelAt00657480;
    F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
    F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
    if (S16(0x62) < 2) {
        F32(0x30) = F32(0x30) + gLiftAt00657CC0;
        if (*(&F32(0x48)) + *(&F32(0x54)) <= gCompareAt0065782C) {
            PARENT->SpawnDirectedAt453A70(0x342, I32(0x44), I32(0x48), S8(0x66), 1);
            PARENT->SpawnDirectedAt453A70(0x344, I32(0x44), I32(0x48), S8(0x66), 1);
            PARENT->ModifyAt453D40(10);
            SetActionAt40FAC0(0x33B);
            F32(0x48) = 0.0f;
            F32(0x54) = 0.0f;
            F32(0x50) = 0.0f;
            F32(0x30) = 0.0f;
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70))
        SetStateAt40FB40(1);
    break;
}
        case 0x342: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        S16(0xD8) = 0;
        ResetStateAt40FBB0(0,0,0);
        S16(0x80) = 1;
        I32(0x7C) = 0;
        F32(0x54) = 0.0f;
        F32(0x50) = 0.0f;
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        I32(0x28) = 0;
        I32(0x2C) = 0;
        I32(0x30) = 0;
        PARENT->SetupAt453E60(10.0f);
    }
    if (I32(0x7C) == 6) {
        I32(0x7C) = 0;
        ++S16(0x80);
    }
    if (S16(0x62) == 3 && S16(0x64) == 0)
        PARENT->SpawnDirectedAt453A70(0x343, I32(0x44), I32(0x48), S8(0x66), 1);
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x343: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        S16(0xD8) = 0;
        ResetStateAt40FBB0(0,0,0);
        S16(0x80) = 1;
        I32(0x7C) = 0;
        F32(0x54) = 0.0f;
        F32(0x50) = 0.0f;
        F32(0x1C) = 1.7f;
        F32(0x20) = 1.7f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        I32(0x28) = 0;
        I32(0x2C) = 0;
        I32(0x30) = 0;
    }
    F32(0x1C) = F32(0x1C) + gFadeAt0065825C;
    F32(0x20) = F32(0x20) + gFadeAt0065825C;
    if (S16(0x62) > -1) {
        if (U8(0x11) >= 20)
            U8(0x11) -= 20;
        else {
            U8(0x11) = 0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x344: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        S16(0x1A) = 0x4E2;
        F32(0x28) = -75.0f;
    }
    F32(0x1C) = F32(0x1C) + gAddAt006583FC;
    F32(0x20) = F32(0x20) + gAddAt006583FC;
    if (S16(0x62) > 1) {
        if (U8(0x11) > 20)
            U8(0x11) -= 20;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30() == S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x345: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        S16(0xD8) = 0;
        S16(0xDA) = 0;
    }
    if (S16(0x62) > 5) {
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (F32(0x44) > gBoundRightAt00659248 ||
            F32(0x44) < gBoundLowerAt0065930C ||
            F32(0x48) < gBoundLowerAt0065930C ||
            F32(0x48) > gBoundUpperAt00658E80) {
            ResetAt45B830();
            break;
        }
        if (GetStateAt40FA30() == S16(0x70))
            SetStateAt40FB40(6);
        break;
    }
    if (S16(0x62) == 1) {
        F32(0x30) = F32(0x30) + gGrowAt00657CBC;
        if (P16(0xF12) == 1 && S16(0x62) == 1 && P16(0xF12) == 1) {
            SetStateAt40FB40(2);
            S16(0x80) = 99;
            F32(0x30) = 0.0f;
            I32(0x7C) = 0;
            break;
        }
    }
    if (P16(0xF12) == 2) {
        if (S16(0x62) < 6)
            S16(0x62) += 4;
        S16(0xDA) = 25;
        MotionAt40FB70(static_cast<float>(S16(0xD8)),
                       static_cast<float>(S16(0xDA)));
    }
    if (S16(0x62) < 6 && P16(0xF12) < 2) {
        S16(0xD8) = static_cast<short>(
            static_cast<float>(P16(0xF10)-180) + F32(0xC8));
        if (S16(0xD8) > 180) S16(0xD8) -= 360;
        if (S16(0xD8) < -180) S16(0xD8) += 360;
        MotionAt40FB70(static_cast<float>(S16(0xD8)),
                       static_cast<float>(S16(0xDA)));
        F32(0x44) = static_cast<int>(
            P16(0xF0C) + S8(0x66)*F32(0x50));
        F32(0x48) = static_cast<int>(
            P16(0xF0E) + F32(0x54));
        if (S16(0xDA) < 140) S16(0xDA) += 7;
        if (S16(0xDA) > 140) S16(0xDA) = 140;
    }
    if (GetStateAt40FA30() == S16(0x70)) SetStateAt40FB40(6);
    if (S16(0x62) == 2 && S16(0x64) == 0) SetStateAt40FB40(1);
    if (S16(0x62) == 6 && S16(0x64) == 0 && P16(0xF12) == 1) {
        SetStateAt40FB40(2);
        I32(0x7C) = 0;
    }
    break;
}
        case 0x346: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        P16(0xF10) = 0;
        F32(0x50) = 25.0f;
    }
    if (S16(0x62) < 2) {
        P16(0xF10) -= 3;
        P16(0xF0C) = static_cast<short>(F32(0x44));
        P16(0xF0E) = static_cast<short>(F32(0x48));
        F32(0x50) = F32(0x50) - gCompareAt0065747C;
        if (F32(0x50) < gCompareAt0065782C)
            F32(0x50) = 0.0f;
    }
    F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
    if (GetStateAt40FA30() == S16(0x70)) {
        ResetAt45B830();
        P16(0xF12) = 0;
    }
    if (S16(0x62) == 1 && S16(0x64) == 0)
        P16(0xF12) = 1;
    if (S16(0x62) == 2 && S16(0x64) == 0)
        P16(0xF12) = 2;
    break;
}
        case 0x347: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        S16(0xD8) = 0;
        S16(0xDA) = 0;
    }
    if (S16(0x62) > 5) {
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (F32(0x44) > gBoundRightAt00659248 ||
            F32(0x44) < gBoundLowerAt0065930C ||
            F32(0x48) < gBoundLowerAt0065930C ||
            F32(0x48) > gBoundUpperAt00658E80) {
            ResetAt45B830();
            break;
        }
        if (GetStateAt40FA30() == S16(0x70))
            SetStateAt40FB40(6);
        break;
    }
    if (S16(0x62) == 1) {
        F32(0x30) = F32(0x30) + gGrowAt00657CBC;
        if (P16(0xF12) == 1 && S16(0x62) == 1 && P16(0xF12) == 1) {
            SetStateAt40FB40(2);
            S16(0x80) = 99;
            F32(0x30) = 0.0f;
            I32(0x7C) = 0;
            break;
        }
    }
    if (P16(0xF12) == 2) {
        if (S16(0x62) < 6)
            S16(0x62) += 4;
        S16(0xDA) = 25;
        MotionAt40FB70(static_cast<float>(S16(0xD8)),
                       static_cast<float>(S16(0xDA)));
    }
    if (S16(0x62) < 6 && P16(0xF12) < 2) {
        S16(0xD8) = static_cast<short>(
            static_cast<float>(P16(0xF10)-180) + F32(0xC8));
        if (S16(0xD8) > 180) S16(0xD8) -= 360;
        if (S16(0xD8) < -180) S16(0xD8) += 360;
        MotionAt40FB70(static_cast<float>(S16(0xD8)),
                       static_cast<float>(S16(0xDA)));
        F32(0x44) = static_cast<int>(
            P16(0xF0C) + S8(0x66)*F32(0x50));
        F32(0x48) = static_cast<int>(
            P16(0xF0E) + F32(0x54));
        if (S16(0xDA) < 120) S16(0xDA) += 6;
        if (S16(0xDA) > 120) S16(0xDA) = 120;
    }
    if (GetStateAt40FA30() == S16(0x70)) SetStateAt40FB40(6);
    if (S16(0x62) == 2 && S16(0x64) == 0) SetStateAt40FB40(1);
    if (S16(0x62) == 6 && S16(0x64) == 0 && P16(0xF12) == 1) {
        SetStateAt40FB40(2);
        I32(0x7C) = 0;
    }
    break;
}
        case 0x348: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        S16(0xD8) = 0;
        S16(0xDA) = 0;
    }
    if (S16(0x62) > 5) {
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (F32(0x44) > gBoundRightAt00659248 ||
            F32(0x44) < gBoundLowerAt0065930C ||
            F32(0x48) < gBoundLowerAt0065930C ||
            F32(0x48) > gBoundUpperAt00658E80) {
            ResetAt45B830();
            break;
        }
        if (GetStateAt40FA30() == S16(0x70))
            SetStateAt40FB40(6);
        break;
    }
    if (S16(0x62) == 1) {
        F32(0x30) = F32(0x30) + gGrowAt00657CBC;
        if (P16(0xF12) == 1 && S16(0x62) == 1 && P16(0xF12) == 1) {
            SetStateAt40FB40(2);
            S16(0x80) = 99;
            F32(0x30) = 0.0f;
            I32(0x7C) = 0;
            break;
        }
    }
    if (P16(0xF12) == 2) {
        if (S16(0x62) < 6)
            S16(0x62) += 4;
        S16(0xDA) = 25;
        MotionAt40FB70(static_cast<float>(-S16(0xD8) + 180),
                       static_cast<float>(S16(0xDA)));
    }
    if (S16(0x62) < 6 && P16(0xF12) < 2) {
        S16(0xD8) = static_cast<short>(
            static_cast<float>(P16(0xF10)-180) + F32(0xC8));
        if (S16(0xD8) > 180) S16(0xD8) -= 360;
        if (S16(0xD8) < -180) S16(0xD8) += 360;
        MotionAt40FB70(static_cast<float>(-S16(0xD8)),
                       static_cast<float>(S16(0xDA)));
        F32(0x44) = static_cast<int>(
            P16(0xF0C) + S8(0x66)*F32(0x50));
        F32(0x48) = static_cast<int>(
            P16(0xF0E) + F32(0x54));
        if (S16(0xDA) < 200) S16(0xDA) += 10;
        if (S16(0xDA) > 200) S16(0xDA) = 200;
    }
    if (GetStateAt40FA30() == S16(0x70)) SetStateAt40FB40(6);
    if (S16(0x62) == 2 && S16(0x64) == 0) SetStateAt40FB40(1);
    if (S16(0x62) == 6 && S16(0x64) == 0 && P16(0xF12) == 1) {
        SetStateAt40FB40(2);
        I32(0x7C) = 0;
    }
    break;
}
        case 0x349: {
    if (S16(0x62) == 0 && S16(0x64) == 0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C) = 1.0f;
        F32(0x20) = 1.0f;
        U8(0x11) = 0xFF;
        U8(0x12) = 0xFF;
        U8(0x13) = 0xFF;
        U8(0x14) = 0xFF;
        P16(0xF10) = 0;
        F32(0x50) = 25.0f;
    }
    if (S16(0x62) < 2) {
        P16(0xF10) -= 3;
        P16(0xF0C) = static_cast<short>(F32(0x44));
        P16(0xF0E) = static_cast<short>(F32(0x48));
        F32(0x50) = F32(0x50) - gCompareAt0065747C;
        if (F32(0x50) < gCompareAt0065782C)
            F32(0x50) = 0.0f;
    }
    F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
    if (GetStateAt40FA30() == S16(0x70)) {
        ResetAt45B830();
        P16(0xF12) = 0;
    }
    if (S16(0x62) == 1 && S16(0x64) == 0)
        P16(0xF12) = 1;
    if (S16(0x62) == 2 && S16(0x64) == 0)
        P16(0xF12) = 2;
    break;
}
        case 0x34A: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && S16(0x62) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (I32(0x7C) == 6) {
            I32(0x7C) = 0;
            S16(0x80) = 1;
        }
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            ResetStateAt40FBB0(0,0,0);
            I32(0x7C) = 0;
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
            F32(0x50) = 3.0f;
            F32(0x54) = -3.0f;
        }
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (S16(0x62) == 0) {
            if (U8(0x11) <= 0xEB)
                U8(0x11) += 20;
            else
                U8(0x11) = 0xFF;
            F32(0x30) = F32(0x30) + gAddAt00659738;
            F32(0x54) = F32(0x54) - gAddAt006583FC;
            if (*(&F32(0x48)) + *(&F32(0x54)) <= gStageContactAt0065786C) {
                F32(0x48) = 20.0f;
                F32(0x54) = 0.0f;
                F32(0x50) = 0.0f;
                SetStateAt40FB40(1);
                F32(0x30) = 0.0f;
                U8(0x11) = 0xFF;
                break;
            }
        }
        if (S16(0x62) == 11) {
            F32(0x1C) = static_cast<float>(F32(0x1C) * gMulDoubleAt00659730);
            F32(0x20) = F32(0x20) + gAddAt006583FC;
            if (U8(0x11) >= 10)
                U8(0x11) -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70)) {
            ResetAt45B830();
            break;
        }
        if (S16(0x62) == 1 && S16(0x64) == 0) {
            F32(0x50) = 0.0f;
            F32(0x54) = 0.0f;
            F32(0x30) = 0.0f;
        }
        if (S16(0x62) == 6 && S16(0x64) == 0 && S16(0xDC) < 1) {
            SetStateAt40FB40(2);
            ++S16(0xDC);
        }
        if (S16(0x62) == 10 && S16(0x64) == 0 && S16(0xDA) < 6) {
            ++S16(0xDA);
            SetStateAt40FB40(9);
        }
        if (S16(0x62) == 9 && S16(0x64) == 0) {
            PF32(0x314) = 1200.0f;
            PF32(0x318) = static_cast<float>(RandomAt455580(0,60));
            PARENT->SpawnMovedAt453A70(0x323,
                   static_cast<float>(S8(0x66) * 10) + F32(0x44),
                   I32(0x48), U8(0x66), 1);
            PARENT->ModifyAt453D40(6);
        }
    }
    break;
}
        case 0x34B: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && S16(0x62) < 11) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4, I32(0x44), I32(0x48), 1, 1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3, I32(0x44), I32(0x48), 1, 1);
        }
        break;
    } else {
        if (I32(0x7C) == 6) {
            I32(0x7C) = 0;
            S16(0x80) = 1;
        }
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            ResetStateAt40FBB0(0,0,0);
            I32(0x7C) = 0;
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
            MotionRawPairAt40FB70(I32(0xCC), I32(0xC8));
        }
        F32(0x44) += static_cast<float>(S8(0x66)) * F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (S16(0x62) == 0) {
            if (U8(0x11) <= 0xEB)
                U8(0x11) += 20;
            else
                U8(0x11) = 0xFF;
            F32(0x30) = F32(0x30) + gAddAt00659738;
            F32(0x54) = F32(0x54) - gGrowAt00657478;
        }
        if (S16(0x62) == 11) {
            F32(0x1C) = static_cast<float>(F32(0x1C) * gMulDoubleAt00659730);
            F32(0x20) = F32(0x20) + gAddAt006583FC;
            if (U8(0x11) >= 10)
                U8(0x11) -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70)) {
            ResetAt45B830();
            break;
        }
        if (S16(0x62) == 1 && S16(0x64) == 0) {
            F32(0x50) = 0.0f;
            F32(0x54) = 0.0f;
            F32(0x30) = 0.0f;
        }
        if (S16(0x62) == 6 && S16(0x64) == 0 && S16(0xDC) < 0) {
            SetStateAt40FB40(2);
            ++S16(0xDC);
        }
        if (S16(0x62) == 10 && S16(0x64) == 0 && S16(0xDA) < 6) {
            ++S16(0xDA);
            SetStateAt40FB40(9);
        }
        if (S16(0x62) == 9 && S16(0x64) == 0) {
            PF32(0x314) = 1200.0f;
            PF32(0x318) = static_cast<float>(RandomAt455580(0,15) - 60);
            PARENT->SpawnMovedAt453A70(0x324,
                   static_cast<float>(S8(0x66) * 10) + F32(0x44),
                   I32(0x48), U8(0x66), 1);
            PARENT->ModifyAt453D40(6);
        }
    }
    break;
}
        case 0x34C: {
    if (P16(0x60) > 0x45 && P16(0x60) < 0x96 && S16(0x62) < 5) {
        ResetAt45B830();
        for (int iteration=0; iteration<8; ++iteration)
            PARENT->SpawnAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA) = 0;
            PARENT->SpawnAt453A70(0x3E3,I32(0x44),I32(0x48),1,1);
        }
        break;
    } else {
        if ((P16(0x60) == 0x198 && P16(0x62) < 7) ||
            (P16(0x60) == 0x19C && P16(0x62) < 5) ||
            (P16(0x60) == 0x19A && P16(0x62) < 7) ||
            (P16(0x60) == 0x19D && P16(0x62) < 5)) {
            F32(0x44) = *(&PF32(0x44)) + static_cast<float>(S8(0x66)*60);
            F32(0x48) = PF32(0x48) + gParentYAt006590A8;
            if (P16(0x60) == 0x19A)
                F32(0x48) = PF32(0x48) + gParentYExtraAt00658264;
        } else if (S16(0x62) < 5) {
            SetStateAt40FB40(5);
            break;
        }
        if (S16(0x62) == 0 && S16(0x64) == 0) {
            ResetStateAt40FBB0(0,0,0);
            I32(0x7C) = 0;
            F32(0x1C) = 1.0f;
            F32(0x20) = 1.0f;
            U8(0x11) = 0xFF;
            U8(0x12) = 0xFF;
            U8(0x13) = 0xFF;
            U8(0x14) = 0xFF;
            S16(0xDA) = 0;
        }
        if (S16(0x62) == 5) {
            F32(0x1C) = static_cast<float>(F32(0x1C)*gMulDoubleAt00659730);
            F32(0x20) = F32(0x20) + gAddAt006583FC;
            if (U8(0x11) >= 10)
                U8(0x11) -= 10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (GetStateAt40FA30() == S16(0x70)) {
            ResetAt45B830();
            break;
        }
        if (S16(0x62) == 4 && S16(0x64) == 0 && S16(0xDA) < 8) {
            ++S16(0xDA);
            SetStateAt40FB40(3);
        }
        if (S16(0x62) == 3 && S16(0x64) == 0) {
            if (P16(0x60) == 0x198) {
                PF32(0x314) = 1000.0f;
                PF32(0x318) = static_cast<float>(RandomAt455580(0,10) - 5);
                PARENT->SpawnMovedAt453A70(0x322,
                    static_cast<float>(S8(0x66)*10) + F32(0x44),
                    I32(0x48), U8(0x66),1);
                PARENT->ModifyAt453D40(6);
            }
            if (P16(0x60) == 0x19A) {
                PF32(0x314) = 1000.0f;
                PF32(0x318) = static_cast<float>(RandomAt455580(0,10) + 30);
                PARENT->SpawnMovedAt453A70(0x323,
                    static_cast<float>(S8(0x66)*10) + F32(0x44),
                    I32(0x48), U8(0x66),1);
                PARENT->ModifyAt453D40(6);
            }
            if (P16(0x60) == 0x19C) {
                PF32(0x314) = 1000.0f;
                PF32(0x318) = static_cast<float>(RandomAt455580(0,10) - 5);
                PARENT->SpawnMovedAt453A70(0x324,
                    static_cast<float>(S8(0x66)*10) + F32(0x44),
                    I32(0x48), U8(0x66),1);
                PARENT->ModifyAt453D40(6);
            }
            if (P16(0x60) == 0x19D) {
                PF32(0x314) = 1000.0f;
                PF32(0x318) = static_cast<float>(-RandomAt455580(0,10) - 30);
                PARENT->SpawnMovedAt453A70(0x325,
                    static_cast<float>(S8(0x66)*10) + F32(0x44),
                    I32(0x48), U8(0x66),1);
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
            PARENT->SpawnAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
        if (P16(0xEFA) > 25) {
            P16(0xEFA)=0;
            PARENT->SpawnAt453A70(0x3E3,I32(0x44),I32(0x48),1,1);
        }
        break;
    } else {
        if (I32(0x7C)==6) {
            I32(0x7C)=0;
            S16(0x80)=1;
        }
        if (S16(0x62)==0 && S16(0x64)==0) {
            ResetStateAt40FBB0(0,0,0);
            S16(0x80)=1;
            I32(0x7C)=0;
            I32(0x50)=I32(0xC8);
            I32(0x54)=I32(0xCC);
            F32(0x1C)=1.0f;
            F32(0x20)=1.0f;
            U8(0x11)=0xFF;
            U8(0x12)=0xFF;
            U8(0x13)=0xFF;
            U8(0x14)=0xFF;
        }
        F32(0x54) = F32(0x54) - gSubAt00659090;
        F32(0x44) += static_cast<float>(S8(0x66))*F32(0x50);
        F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
        if (S16(0x62)<2) {
            F32(0x30) = F32(0x30)+gLiftAt00657CC0;
            if (*(&F32(0x48)) + *(&F32(0x54)) <= gCompareAt0065782C) {
                PARENT->ModifyAt453D40(4);
                PARENT->SpawnDirectedAt453A70(0x32B,I32(0x44),I32(0x48),S8(0x66),1);
                PARENT->SpawnDirectedAt453A70(0x32D,I32(0x44),I32(0x48),S8(0x66),1);
                SetActionAt40FAC0(0x33B);
                F32(0x48)=0.0f;
                F32(0x54)=0.0f;
                F32(0x50)=0.0f;
                F32(0x30)=0.0f;
                break;
            }
        }
        if (GetStateAt40FA30()==S16(0x70))
            SetStateAt40FB40(1);
    }
    break;
}
        case 0x34E: {
    if (P16(0x60)>0x31 && P16(0x60)<0x96) {
        ResetAt45B830();
        for (int iteration=0;iteration<4;++iteration)
            PARENT->SpawnAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
        if (P16(0xEFA)>25) {
            P16(0xEFA)=0;
            PARENT->SpawnAt453A70(0x3E3,I32(0x44),I32(0x48),1,1);
        }
        break;
    } else {
        if (I32(0x7C)==6) {
            I32(0x7C)=0;
            S16(0x80)=1;
        }
        if (S16(0xD8)>2) {
            F32(0x1C) = static_cast<float>(F32(0x1C)*gMulDoubleAt00659730);
            F32(0x20) = F32(0x20)+gAddAt006583FC;
            if (U8(0x11)>=10)
                U8(0x11)-=10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (S16(0x62)==0 && S16(0x64)==0) {
            ResetStateAt40FBB0(0,0,0);

            F32(0x50)=20.0f;
            F32(0x54)=0.0f;
            S16(0xD8)=0;
            F32(0x1C)=1.0f;
            F32(0x20)=1.0f;
            U8(0x11)=0xFF;
            U8(0x12)=0xFF;
            U8(0x13)=0xFF;
            U8(0x14)=0xFF;
        }
        F32(0x50) = F32(0x50)-gCompareAt0065747C;
        if (F32(0x50)<gMotionDecelAt00657480)
            F32(0x50)=2.0f;
        F32(0x44) += static_cast<float>(S8(0x66))*F32(0x50);
        F32(0x48) = *(&F32(0x48))+*(&F32(0x54));
        if (GetStateAt40FA30()==S16(0x70)) {
            SetStateAt40FB40(1);
            ++S16(0xD8);
        }
    }
    break;
}
        case 0x34F: {
    if (P16(0x60)>0x31 && P16(0x60)<0x96) {
        ResetAt45B830();
        for (int iteration=0;iteration<4;++iteration)
            PARENT->SpawnAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
        if (P16(0xEFA)>25) {
            P16(0xEFA)=0;
            PARENT->SpawnAt453A70(0x3E3,I32(0x44),I32(0x48),1,1);
        }
        break;
    } else {
        if (I32(0x7C)==6) {
            I32(0x7C)=0;
            S16(0x80)=1;
        }
        if (S16(0xD8)>1) {
            F32(0x1C) = static_cast<float>(F32(0x1C)*gMulDoubleAt00659730);
            F32(0x20) = F32(0x20)+gAddAt006583FC;
            if (U8(0x11)>=10)
                U8(0x11)-=10;
            else {
                ResetAt45B830();
                break;
            }
        }
        if (S16(0x62)==0 && S16(0x64)==0) {
            ResetStateAt40FBB0(0,0,0);

            F32(0x50)=20.0f;
            F32(0x54)=0.0f;
            S16(0xD8)=0;
            I32(0x7C)=0;
            S16(0x80)=1;
            F32(0x1C)=1.0f;
            F32(0x20)=1.0f;
            U8(0x11)=0xFF;
            U8(0x12)=0xFF;
            U8(0x13)=0xFF;
            U8(0x14)=0xFF;
        }
        F32(0x50) = F32(0x50)-gCompareAt0065747C;
        if (F32(0x50)<gMotionDecelAt00657480)
            F32(0x50)=2.0f;
        F32(0x44) += static_cast<float>(S8(0x66))*F32(0x50);
        F32(0x48) = *(&F32(0x48))+*(&F32(0x54));
        if (GetStateAt40FA30()==S16(0x70)) {
            ResetAt45B830();
        }
    }
    break;
}
        case 0x370: {
    if (P16(0x60)==0x133) {
        F32(0x44) = *(&PF32(0x44)) + static_cast<float>(S8(0x66)*260);
        F32(0x48) = PF32(0x48) + gParentYAt006590A0;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C)=1.0f;
        F32(0x20)=1.0f;
        U8(0x11)=0xFF;
        U8(0x12)=0xFF;
        U8(0x13)=0xFF;
        U8(0x14)=0xFF;
    }
    F32(0x1C) = F32(0x1C) + gAddAt006583FC;
    F32(0x20) = F32(0x20) * gSubAt00659090;
    if (U8(0x11)>20)
        U8(0x11)-=20;
    else {
        ResetAt45B830();
        break;
    }
    if (GetStateAt40FA30()==S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x371: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C)=0.85f;
        F32(0x20)=0.85f;
        U8(0x11)=0xFF;
        U8(0x12)=0xFF;
        U8(0x13)=0xFF;
        U8(0x14)=0xFF;
        S16(0x1A)=0x4E2;
        F32(0x28)=-65.0f;
    }
    F32(0x30) = F32(0x30)-gSubtractAt00659728;
    if (GetStateAt40FA30()==S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x384: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C)=1.0f;
        F32(0x20)=1.0f;
        U8(0x11)=0xFF;
        U8(0x12)=0xFF;
        U8(0x13)=0xFF;
        U8(0x14)=0xFF;
        F32(0x50) = F32(0xC8)*gMulAt006590B4;
        F32(0x54) = F32(0xCC)*gMulAt006590B4;
    }
    F32(0x54) = F32(0x54)-gDropAt00658058;
    F32(0x44) += static_cast<float>(S8(0x66))*F32(0x50);
    F32(0x48) = *(&F32(0x48)) + *(&F32(0x54));
    if (S16(0x62)<2) {
        F32(0x30) = F32(0x30)+gLiftAt00657CC0;
        if (*(&F32(0x48)) + *(&F32(0x54)) <= gCompareAt0065782C) {
            PARENT->SpawnDirectedAt453A70(0x388,I32(0x44),I32(0x48),S8(0x66),0);
            PARENT->ModifyAt453D40(8);
            SetActionAt40FAC0(0x385);
            if (gGlobalActorCountAt006714D0>1)
                SetActionAt40FAC0(0x38E);
            F32(0x48)=0.0f;
            F32(0x54)=0.0f;
            F32(0x50)=0.0f;
            F32(0x30)=0.0f;
            break;
        }
    }
    if (GetStateAt40FA30()==S16(0x70))
        SetStateAt40FB40(1);
    break;
}
        case 0x385: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xD8)=0;
        ResetStateAt40FBB0(0,0,0);
        S16(0x80)=1;
        I32(0x7C)=0;
        F32(0x54)=0.0f;
        F32(0x50)=0.0f;
        F32(0x1C)=0.75f;
        F32(0x20)=0.75f;
        U8(0x11)=0xFF;
        U8(0x12)=0xFF;
        U8(0x13)=0xFF;
        U8(0x14)=0xFF;
        I32(0x28)=0;
        I32(0x2C)=0;
        I32(0x30)=0;
        PARENT->SetupAt453E60(5.0f);
        PARENT->SpawnDirectedAt453A70(0x387,I32(0x44),I32(0x48),S8(0x66),1);
    }
    if (I32(0x7C)==6) {
        I32(0x7C)=0;
        ++S16(0x80);
    }
    F32(0x1C) = F32(0x1C)+gAbsScaleAt00659724;
    F32(0x20) = F32(0x20)+gAbsScaleAt00659724;
    if (S16(0x62)>1) {
        if (U8(0x11)>=40)
            U8(0x11)-=40;
        else {
            U8(0x11)=0;
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30()==S16(0x70))
        ResetAt45B830();
    if (S16(0x62)==2 && S16(0x64)==0)
        PARENT->SpawnDirectedAt453A70(0x386,I32(0x44),I32(0x48),S8(0x66),1);
    break;
}
        case 0x386: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xD8)=0;
        ResetStateAt40FBB0(0,0,0);
        S16(0x80)=1;
        I32(0x7C)=0;
        F32(0x54)=0.0f;
        F32(0x50)=0.0f;
        F32(0x1C)=0.75f;
        F32(0x20)=0.75f;
        U8(0x11)=0xFF;
        U8(0x12)=0xFF;
        U8(0x13)=0xFF;
        U8(0x14)=0xFF;
        I32(0x28)=0;
        I32(0x2C)=0;
        I32(0x30)=0;
    }
    F32(0x1C) = F32(0x1C)+gAbsScaleAt00659724;
    F32(0x20) = F32(0x20)+gAbsScaleAt00659724;
    if (U8(0x11)>=20)
        U8(0x11)-=20;
    else {
        U8(0x11)=0;
        ResetAt45B830();
        break;
    }
    if (GetStateAt40FA30()==S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x387: {
    if (P16(0x3A0)<=0) {
        ResetAt45B830();
        break;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetStateAt40FBB0(0,0,0);
        F32(0x1C)=0.75f;
        F32(0x20)=0.75f;
        U8(0x11)=0xFF;
        U8(0x12)=0xFF;
        U8(0x13)=0xFF;
        U8(0x14)=0xFF;
        S16(0x1A)=0x4E2;
        F32(0x28)=-75.0f;
    }
    F32(0x1C) = F32(0x1C)+gFadeAt006583F8;
    F32(0x20) = F32(0x20)+gFadeAt006583F8;
    if (S16(0x62)>1) {
        if (U8(0x11)>20)
            U8(0x11)-=20;
        else {
            ResetAt45B830();
            break;
        }
    }
    if (GetStateAt40FA30()==S16(0x70))
        ResetAt45B830();
    break;
}
        case 0x388: g_FighterProbeMarker = 905; break;
        case 0x389: g_FighterProbeMarker = 906; break;
        case 0x38A: g_FighterProbeMarker = 907; break;
        case 0x38B: g_FighterProbeMarker = 908; break;
        case 0x38C: g_FighterProbeMarker = 909; break;
        case 0x38D: g_FighterProbeMarker = 910; break;
        case 0x38E: g_FighterProbeMarker = 911; break;
        case 0x3E3: g_FighterProbeMarker = 996; break;
        case 0x3E4: g_FighterProbeMarker = 997; break;
        case 0x3E5: g_FighterProbeMarker = 998; break;
        default: g_FighterProbeMarker = 0;
    }
}
#undef OWNER
#undef I16
#undef RAW
