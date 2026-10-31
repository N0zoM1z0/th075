// F1017 SHA-pinned Japanese original 004AC040 state 2BE:
 // real 004BB1EA..004BB831, 1607 CODE B/471 native x86,
 // 50 genuine physical PE call and global fields.
 // Stage4 signed-facing*30 FILD/FADD initial sprite0x73,
 // native Y global00658268; stage15/17/19/21/23 five
 // distinct original sprite pair 0x321+randomBoolean
 // and0x33F using Y global0065908C, signed facing*60.
 // Genuine stage13 velocity and hit counter, stage23
 // F00<6 auxiliary15 and stage34 auxiliary32.
 // Entire original-shaped PARTIAL source all native mnem
 // and width roles, 125 wrong GPR roles. Whole 82KB NONEXACT.
// F1017 real original fighter action 2BE.
case 0x2BE: {
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
        SpawnAt453C80(0x73,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*30)+F32(0x44),
            (*(&POS48))+g_F1017_StartYAt00658268,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    if (S16(0x62)==13 && S16(0x64)==0) {
        PrepareActionAt453D40(7);
        POS=0.5f;
        POS54=1.0f;
        POS5C=0.5f;
        S16(0x84)=10;
    }
    if (S16(0x62)==15 && S16(0x64)==0) {
        StartAnimationAt46D000(0xC);
        SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x33F,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==17 && S16(0x64)==0) {
        StartAnimationAt46D000(0xC);
        SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x33F,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==19 && S16(0x64)==0) {
        StartAnimationAt46D000(0xC);
        SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x33F,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==21 && S16(0x64)==0) {
        StartAnimationAt46D000(0xC);
        SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x33F,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==23 && S16(0x64)==0) {
        StartAnimationAt46D000(0xC);
        SpawnFloatXYAt453A70(0x321+(RandAt455580(0,100)>200),
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x33F,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*60)+F32(0x44),
            (*(&POS48))+g_F1017_VolleyYAt0065908C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D40(7);
        if (S16(0xF00)<6) {
            ++S16(0xF00);
            SetAuxActionAt40FB40(15);
        }
    }
    if (S16(0x62)==34 && S16(0x64)==0)
        SetAuxActionAt40FB40(32);
    break;
}
