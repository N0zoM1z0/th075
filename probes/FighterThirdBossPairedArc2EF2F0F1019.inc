// F1019 real Japanese original 004AC040 actions 2EF and 2F0.
 // Each physical PE 2229 native CODE B/573 x86/80 actual PE
 // fields. Both normal whole PARTIAL father source interiors
 // have ZERO native positional mnemonic, width and GPR errors.
 // 2EF fall global00658044 vs 2F0 global00658354,
 // stage13 vertical1.5f vs3.5f, first random angle
 // minus70 vs four following −50. Last stage23 F04
 // counter condition must be NESTED within stage23.
 // Original 0040FB70 receives raw 32-bit float angle
 // bits (one MOV and PUSH), not C++ FP FLD/FSTP.
 // Borrowed CONST actor velocity+0x50 yields original
 // FLD global00658264 / FADD actor+0x50, then FIMUL
 // signed facing, unlike mutable raw-pointer alternatives.
 // Whole original 82KB parent remains NONEXACT: one extra
 // native original-sized slot in our generated father,
 // CODE +6 B, frame0x724 vs native0x720, prior 2BE GPR
 // roles and original physical whole offsets still differ.
// F1019 original Japanese TH075 native state0x2EF.
case 0x2EF: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        I32(0x7C)=0;
        ResetAt453E20();
        S16(0x80)=99;
    }
    if (POS48>=g_ThresholdAt0065782C && S16(0x62)<22)
        POS54=POS54-g_F747_BounceYAt00658044;
    if (POS48>=g_ThresholdAt0065782C && S16(0x62)>23) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C && S16(0x62)<34) {
            SetAuxActionAt40FB40(34);
            ResetAt453E20();
            POS48=0.0f;
            break;
        }
    }
    if (S16(0x64)==0)
        I32(0x7C)=0;
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=static_cast<short>(RandAt455580(60,120));
    }
    if (S16(0x62)==13 && S16(0x64)==0) {
        PrepareActionAt453D40(7);
        POS=float(RandAt455580(0,6)-3);
        POS54=1.5f;
        POS5C=0.5f;
    }
    if (S16(0x62)==15 && S16(0x64)==0) {
        S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        S16(0xF02)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
        F32(0x314)=float(RandAt455580(0,100)-70);
        F32(0x318)=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(I32(0x314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                *reinterpret_cast<const float*>(RAW+0x50))*
                (*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            ((*(&POS48))+g_F1019_VolleyYAt0065908C)-POS54,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==17 && S16(0x64)==0) {
        S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        S16(0xF02)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
        F32(0x314)=float(RandAt455580(0,100)-70);
        F32(0x318)=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(I32(0x314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                *reinterpret_cast<const float*>(RAW+0x50))*
                (*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            ((*(&POS48))+g_F1019_VolleyYAt0065908C)-POS54,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==19 && S16(0x64)==0) {
        S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        S16(0xF02)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
        F32(0x314)=float(RandAt455580(0,100)-70);
        F32(0x318)=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(I32(0x314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                *reinterpret_cast<const float*>(RAW+0x50))*
                (*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            ((*(&POS48))+g_F1019_VolleyYAt0065908C)-POS54,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==21 && S16(0x64)==0) {
        S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        S16(0xF02)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
        F32(0x314)=float(RandAt455580(0,100)-70);
        F32(0x318)=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(I32(0x314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                *reinterpret_cast<const float*>(RAW+0x50))*
                (*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            ((*(&POS48))+g_F1019_VolleyYAt0065908C)-POS54,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==23 && S16(0x64)==0) {
        S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        S16(0xF02)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
        F32(0x314)=float(RandAt455580(0,100)-70);
        F32(0x318)=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(I32(0x314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                *reinterpret_cast<const float*>(RAW+0x50))*
                (*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            ((*(&POS48))+g_F1019_VolleyYAt0065908C)-POS54,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
        if (S16(0xF04)<g_F1004_ModeAt006714D0*2+8) {
            ++S16(0xF04);
            SetAuxActionAt40FB40(15);
        }
    }
    if (S16(0x62)==34 && S16(0x64)==0)
        SetAuxActionAt40FB40(32);
    break;
}

// F1019 original Japanese TH075 native state0x2F0.
case 0x2F0: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        I32(0x7C)=0;
        ResetAt453E20();
        S16(0x80)=99;
    }
    if (POS48>=g_ThresholdAt0065782C && S16(0x62)<22)
        POS54=POS54-g_F1019_FallAt00658354;
    if (POS48>=g_ThresholdAt0065782C && S16(0x62)>23) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C && S16(0x62)<34) {
            SetAuxActionAt40FB40(34);
            ResetAt453E20();
            POS48=0.0f;
            break;
        }
    }
    if (S16(0x64)==0)
        I32(0x7C)=0;
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=static_cast<short>(RandAt455580(60,120));
    }
    if (S16(0x62)==13 && S16(0x64)==0) {
        PrepareActionAt453D40(7);
        POS=float(RandAt455580(0,6)-3);
        POS54=3.5f;
        POS5C=0.5f;
    }
    if (S16(0x62)==15 && S16(0x64)==0) {
        S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        S16(0xF02)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
        F32(0x314)=float(RandAt455580(0,100)-50);
        F32(0x318)=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(I32(0x314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                *reinterpret_cast<const float*>(RAW+0x50))*
                (*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            ((*(&POS48))+g_F1019_VolleyYAt0065908C)-POS54,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==17 && S16(0x64)==0) {
        S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        S16(0xF02)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
        F32(0x314)=float(RandAt455580(0,100)-50);
        F32(0x318)=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(I32(0x314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                *reinterpret_cast<const float*>(RAW+0x50))*
                (*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            ((*(&POS48))+g_F1019_VolleyYAt0065908C)-POS54,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==19 && S16(0x64)==0) {
        S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        S16(0xF02)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
        F32(0x314)=float(RandAt455580(0,100)-50);
        F32(0x318)=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(I32(0x314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                *reinterpret_cast<const float*>(RAW+0x50))*
                (*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            ((*(&POS48))+g_F1019_VolleyYAt0065908C)-POS54,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==21 && S16(0x64)==0) {
        S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        S16(0xF02)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
        F32(0x314)=float(RandAt455580(0,100)-50);
        F32(0x318)=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(I32(0x314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                *reinterpret_cast<const float*>(RAW+0x50))*
                (*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            ((*(&POS48))+g_F1019_VolleyYAt0065908C)-POS54,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==23 && S16(0x64)==0) {
        S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        S16(0xF02)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
        F32(0x314)=float(RandAt455580(0,100)-50);
        F32(0x318)=float(RandAt455580(0,10)+5);
        SetAngleBitsAt40FB70(I32(0x314),100.0f);
        SpawnFloatXYAt453A70(0x38F,
            ((g_F983_XOffsetAt00658264+
                *reinterpret_cast<const float*>(RAW+0x50))*
                (*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            ((*(&POS48))+g_F1019_VolleyYAt0065908C)-POS54,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        PrepareActionAt453D40(7);
        if (S16(0xF04)<g_F1004_ModeAt006714D0*2+8) {
            ++S16(0xF04);
            SetAuxActionAt40FB40(15);
        }
    }
    if (S16(0x62)==34 && S16(0x64)==0)
        SetAuxActionAt40FB40(32);
    break;
}
