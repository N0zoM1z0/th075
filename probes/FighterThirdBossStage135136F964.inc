// F964 real Japanese TH075 original fighter 004AC040 stages 135/136.
 // Original 135 physical 004B18B1..004B1A98, 487B/137x86/12 PE fields.
 // Compiled source 481B/137x86; two -0xA4 long EBP scratch widths
 // account for 6 missing original bytes, with 89 wrong GPR roles.
 // Original 136 physical 004B1A98..004B1C5B, 451B/134x86/11 PE fields.
 // Compiled source 451B/134x86, zero wrong mnemonic/width positions,
 // 84 wrong GPR roles. Native 136 uses FLOAT EQUALITY on +0x48
 // (FUCOMPP/TEST AH,44h) in the genuine falling-flag branch.
 // Original 136->186 physical boundary has no separate afterRET label;
 // do not invent a switch entry or accept internal code as whole exact.
// Original third-fighter native game action 135, candidate.
case 0x135: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_ApproachAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (S16(0x62)==3 || S16(0x62)==4) {
        POS54=POS54-g_AnimationDeltaAt0065747C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            POS48=0.0f;
            ResetAt453E20();
            SetAuxActionAt40FB40(5);
            SpawnAt453C80(0x80,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*150)+F32(0x44),
                POS48,*reinterpret_cast<signed char*>(RAW+0x66),1);
            break;
        }
    }
    if (S16(0x62)>4) {
        POS=POS-g_F964_LateFallAt00658048;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=15.0f;
        POS54=4.5f;
        FLAG=0;
    }
    if (S16(0x62)==5 && S16(0x64)==0)
        POS=4.0f;
    break;
}
// Original third-fighter native game action 136, candidate.
case 0x136: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=2;
        I32(0x7C)=0;
    }
    if (FLAG>0 && POS48==g_ThresholdAt0065782C) {
        POS=POS-g_ApproachAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C && S16(0x62)<12) {
            POS48=0.0f;
            ResetAt453E20();
            SetAuxActionAt40FB40(0xC);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0) {
        POS=4.0f;
        POS54=9.5f;
        POS5C=1.0f;
    }
    if (S16(0x62)==8 && S16(0x64)==0) {
        SpawnSevenAt453B50(0x337,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
    }
    if (S16(0x62)==9 && S16(0x64)==0)
        I32(0x7C)=0;
    break;
}
