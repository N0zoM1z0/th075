// F969 original Japanese TH075 fighter 004AC040 true state 0x192.
 // Native 004B2611..004B28ED, 732B/177x86/11 real external PE fields.
 // C++ naturally emits ALL 177 matching mnemonics and original widths:
 // three FLOAT X=FILD(count-dependent facing product)+member X, three
 // FLOAT Y=member Y+original-global+integer FIADD(count*20), and
 // three frame/angle FILD values. Real temp stack slots remain
 // nonnative EBP-0x84..-0xA4 instead of actual -0xD8..-0xF8;
 // 121 true native GPR-role mismatches still prevent whole exactness.
 // Original 82KB father still incomplete, no independent case credit.
// F969 genuine original Japanese 004AC040 0x192 stage3 three-shot trial.
case 0x192: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>4 && S16(0xF00)<=0 && S16(0xF02)<5) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x28);
        F32(0x314)=float(S16(0xF02)*4+45);
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x320,
          float((47-S16(0xF02)*10)*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
          (*(&POS48))+g_F969_RoundY192At00658264+S16(0xF02)*20,
          *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*4+49);
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x320,
          float((47-S16(0xF02)*10)*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
          (*(&POS48))+g_F969_RoundY192At00658264+S16(0xF02)*20,
          *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*4+41);
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x320,
          float((47-S16(0xF02)*10)*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
          (*(&POS48))+g_F969_RoundY192At00658264+S16(0xF02)*20,
          *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
        --S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(2);
    break;
}
