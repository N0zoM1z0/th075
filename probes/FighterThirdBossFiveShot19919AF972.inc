// F972 original Japanese 004AC040 real action199/19A, each
// native physical 593B/170x86 with 19 true external PE/global fields.
// Full-source tested ordinary typed F32(0x54) owner access restores
// native ordered x87 FLD member, FMUL physical global 00657F74.
// Historical POS54=POS54*global creates two wrong original widths,
// despite identical total CODE B! No cropped exact or byte patching.
// With correct field access each state still has 91 wrong GPR roles.
// The entire original 82KB game fighter remains NONEXACT.
// F972 original Japanese 004AC040 action 0x199, five real native shot calls.
case 0x199: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=POS*g_F972_GravityAt00657F74;
        F32(0x54)=F32(0x54)*g_F972_GravityAt00657F74;
        I32(0x7C)=1;
    }
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        POS48=0.0f;
        ResetAt453E20();
        SetNativeActionAt40FAC0(0xA);
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==5 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        F32(0x314)=0.0f;
        F32(0x318)=20.0f;
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*76)+F32(0x44),
            (*(&POS48))+g_F972_YAt0065836C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*81)+F32(0x44),
            (*(&POS48))+g_F972_YAt00659474,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*86)+F32(0x44),
            (*(&POS48))+g_F972_YAt00657860,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*91)+F32(0x44),
            (*(&POS48))+g_F972_YAt00659284,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*96)+F32(0x44),
            (*(&POS48))+g_F972_YAt00659470,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0x96);
    }
    break;
}
// F972 original Japanese 004AC040 action 0x19A, five real native shot calls.
case 0x19A: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=POS*g_F972_GravityAt00657F74;
        F32(0x54)=F32(0x54)*g_F972_GravityAt00657F74;
        I32(0x7C)=1;
    }
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        POS48=0.0f;
        ResetAt453E20();
        SetNativeActionAt40FAC0(0xA);
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==5 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        F32(0x314)=-20.0f;
        F32(0x318)=20.0f;
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*98)+F32(0x44),
            (*(&POS48))+g_F972_YAt00659470,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*92)+F32(0x44),
            (*(&POS48))+g_F972_YAt00658364,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*86)+F32(0x44),
            (*(&POS48))+g_F972_YAt0065946C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44),
            (*(&POS48))+g_F972_YAt00659468,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*74)+F32(0x44),
            (*(&POS48))+g_F972_YAt00659464,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0x96);
    }
    break;
}
