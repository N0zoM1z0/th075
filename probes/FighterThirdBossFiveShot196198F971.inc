// F971: independently read original Japanese TH075 004AC040 five-shot
// actions 196/197/198, each complete internal 507B/146 native x86
// and FIFTEEN true original typed PE call/global reference fields.
// Each emits the exact native positional mnemonic/width sequence but
// 77 original GPR roles differ in the still PARTIAL 82KB father.
// Preserve original per-shot facing multipliers and global Y offsets.
// Neither case nor father is credited as a complete original game function.
// F971 original 004AC040 native 0x196 is five real projectile calls.
case 0x196: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        F32(0x314)=0.0f;
        F32(0x318)=20.0f;
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*39)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659494,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*44)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659490,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*54)+F32(0x44),
            (*(&POS48))+g_F971_YAt0065948C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*59)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659488,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0x96);
    }
    break;
}
// F971 original 004AC040 native 0x197 is five real projectile calls.
case 0x197: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        F32(0x314)=25.0f;
        F32(0x318)=20.0f;
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*85)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659484,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*91)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659480,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*97)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659498,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*103)+F32(0x44),
            (*(&POS48))+g_F971_YAt0065947C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*109)+F32(0x44),
            (*(&POS48))+g_F971_YAt00659478,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0x96);
    }
    break;
}
// F971 original 004AC040 native 0x198 is five real projectile calls.
case 0x198: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(2);
    if (S16(0x62)==6 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        F32(0x314)=0.0f;
        F32(0x318)=20.0f;
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*92)+F32(0x44),
            (*(&POS48))+g_F971_YAt0065826C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*98)+F32(0x44),
            (*(&POS48))+g_F971_YAt00658264,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*104)+F32(0x44),
            (*(&POS48))+g_F971_YAt00658294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*110)+F32(0x44),
            (*(&POS48))+g_F971_YAt00657878,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnFloatXYAt453A70(0x328,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*116)+F32(0x44),
            (*(&POS48))+g_F971_YAt00657CBC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        StartAnimationAt46D000(0x96);
    }
    break;
}
