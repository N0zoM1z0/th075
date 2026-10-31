// F1018 actual Japanese TH075 original 004AC040 state2BF.
 // Native 004BB831..004BC0A8 2167B/616 x86 with 65
 // genuine PE targets. Five native stages15/17/19/21/23
 // launch each THREE real sprites: 0x322+bool,
 // fixed0x340, and 0x341 signed-facing*640
 // FILD/FSUBR X and original Y-global0065784C
 // minus native Rand(0,400). Stage4 0x74,
 // stage13 real 0.9f Y speed, shot animation
 // only AFTER the three native calls. All native
 // positional mnemonic/width/GPR align. Previous
 // 2BE 125 GPR role debt persists, whole NONEXACT.
// F1018 real original Japanese actor 004AC040 2BF
case 0x2BF: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=0;
        ResetAt453E20();
        S16(0x80)=99;
    }
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
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==4 && S16(0x64)==0) {
        ApplyAt453E80(40);
        PrepareActionAt453D60(0x17);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x74,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*30)+F32(0x44),
            (*(&POS48))+g_F1017_StartYAt00658268,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    if (S16(0x62)==13 && S16(0x64)==0) {
        PrepareActionAt453D40(7);
        POS=0.5f;
        POS54=0.9f;
        POS5C=0.5f;
        S16(0x84)=20;
    }
    if (S16(0x62)==15 && S16(0x64)==0) {
        SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x340,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x341,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*640),
            ((*(&POS48))+g_F1018_ThirdYAt0065784C)-float(RandAt455580(0,400)),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0xC);
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==17 && S16(0x64)==0) {
        SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x340,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x341,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*640),
            ((*(&POS48))+g_F1018_ThirdYAt0065784C)-float(RandAt455580(0,400)),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0xC);
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==19 && S16(0x64)==0) {
        SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x340,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x341,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*640),
            ((*(&POS48))+g_F1018_ThirdYAt0065784C)-float(RandAt455580(0,400)),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0xC);
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==21 && S16(0x64)==0) {
        SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x340,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x341,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*640),
            ((*(&POS48))+g_F1018_ThirdYAt0065784C)-float(RandAt455580(0,400)),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0xC);
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==23 && S16(0x64)==0) {
        SpawnFloatXYAt453A70(0x322+(RandAt455580(0,100)>200),
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x340,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x341,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*640),
            ((*(&POS48))+g_F1018_ThirdYAt0065784C)-float(RandAt455580(0,400)),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0xC);
        PrepareActionAt453D40(7);
        if (S16(0xF00)<10) {
            ++S16(0xF00);
            SetAuxActionAt40FB40(15);
        }
    }
    if (S16(0x62)==34 && S16(0x64)==0)
        SetAuxActionAt40FB40(32);
    break;
}
