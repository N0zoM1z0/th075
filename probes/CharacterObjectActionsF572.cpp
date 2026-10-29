// F572/F573/F574/F575: selected natural VC7.1 source, original PE 004EBDA0.
// Implements complete original actions 0x320..0x32E in a 33,293-byte
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
    void SetupAt453E60(float);
};
class FighterSwitchF572_Boss004EBDA0 {
public:
    void Advance();
    void ResetAt4F4170();
    void ResetAt45B830();
    void ResetStateAt40FBB0(int,int,int);
    void MotionAt40FB70(float,float); void MotionRawAt40FB70(int,float);
    void SetStateAt40FB40(int); void SetActionAt40FAC0(int);
    short GetStateAt40FA30();
};
extern float gFloatAt00657850;
extern float gMulAt006590B4;
extern float gAddAt00659738;
extern double gMulDoubleAt00659730;
extern float gAddAt006583FC;
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
#define I32(off) (*reinterpret_cast<int*>(RAW+(off)))
#define F32(off) (*reinterpret_cast<float*>(RAW+(off)))
#define S16(off) (*reinterpret_cast<signed short*>(RAW+(off)))
#define U8(off) (*reinterpret_cast<unsigned char*>(RAW+(off)))
#define S8(off) (*reinterpret_cast<signed char*>(RAW+(off)))
#define PARENT (*reinterpret_cast<ParentEffectsF572**>(RAW+0xE4))
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
        case 0x330: g_FighterProbeMarker = 817; break;
        case 0x331: g_FighterProbeMarker = 818; break;
        case 0x332: g_FighterProbeMarker = 819; break;
        case 0x335: g_FighterProbeMarker = 822; break;
        case 0x338: g_FighterProbeMarker = 825; break;
        case 0x339: g_FighterProbeMarker = 826; break;
        case 0x33A: g_FighterProbeMarker = 827; break;
        case 0x33B: g_FighterProbeMarker = 828; break;
        case 0x33C: g_FighterProbeMarker = 829; break;
        case 0x33D: g_FighterProbeMarker = 830; break;
        case 0x33E: g_FighterProbeMarker = 831; break;
        case 0x33F: g_FighterProbeMarker = 832; break;
        case 0x340: g_FighterProbeMarker = 833; break;
        case 0x341: g_FighterProbeMarker = 834; break;
        case 0x342: g_FighterProbeMarker = 835; break;
        case 0x343: g_FighterProbeMarker = 836; break;
        case 0x344: g_FighterProbeMarker = 837; break;
        case 0x345: g_FighterProbeMarker = 838; break;
        case 0x346: g_FighterProbeMarker = 839; break;
        case 0x347: g_FighterProbeMarker = 840; break;
        case 0x348: g_FighterProbeMarker = 841; break;
        case 0x349: g_FighterProbeMarker = 842; break;
        case 0x34A: g_FighterProbeMarker = 843; break;
        case 0x34B: g_FighterProbeMarker = 844; break;
        case 0x34C: g_FighterProbeMarker = 845; break;
        case 0x34D: g_FighterProbeMarker = 846; break;
        case 0x34E: g_FighterProbeMarker = 847; break;
        case 0x34F: g_FighterProbeMarker = 848; break;
        case 0x370: g_FighterProbeMarker = 881; break;
        case 0x371: g_FighterProbeMarker = 882; break;
        case 0x384: g_FighterProbeMarker = 901; break;
        case 0x385: g_FighterProbeMarker = 902; break;
        case 0x386: g_FighterProbeMarker = 903; break;
        case 0x387: g_FighterProbeMarker = 904; break;
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
