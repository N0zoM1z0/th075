// F970 original Japanese TH075 fighter 004AC040 real actions 194/195.
 // Each original physical internal case is 644 B/168 x86, 11 real PE
 // external fields. Natural complete-partial-father VC7.1 source emits
 // matching original 168 mnemonics/widths but 118 wrong GPR roles each.
 // Real three-shot angles for 194 use -8/-4/-12; for 195 -45/-41/-49.
 // Actor raw X bit-pattern passes through as integer, genuine float Y
 // adds original global 006590AC, and stage5 movement is X=-6,Yv=9.
 // Original whole 82KB fighter and EBP temp owners still NONEXACT.
// Native original Japanese TH075 fighter 004AC040 stage 0x194, 644B/168x86.
case 0x194: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>4 && S16(0xF00)<=0 && S16(0xF02)<5) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x28);
        F32(0x314)=float(S16(0xF02)*4-8);
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x320,I32(0x44),
             (*(&POS48))+g_F970_YAt006590AC,
             *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*4-4);
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x320,I32(0x44),
             (*(&POS48))+g_F970_YAt006590AC,
             *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*4-12);
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x320,I32(0x44),
             (*(&POS48))+g_F970_YAt006590AC,
             *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
        --S16(0xF00);
    }
    POS54=POS54-POS5C;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==4 && S16(0x64)==0)
        SpawnDirectedAt453A70(0x335,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    if (S16(0x62)==5 && S16(0x64)==0) {
        POS=-6.0f;
        POS54=9.0f;
        POS5C=0.7f;
    }
    break;
}
// Native original Japanese TH075 fighter 004AC040 stage 0x195, 644B/168x86.
case 0x195: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>4 && S16(0xF00)<=0 && S16(0xF02)<5) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x28);
        F32(0x314)=float(S16(0xF02)*4-45);
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x320,I32(0x44),
             (*(&POS48))+g_F970_YAt006590AC,
             *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*4-41);
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x320,I32(0x44),
             (*(&POS48))+g_F970_YAt006590AC,
             *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*4-49);
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x320,I32(0x44),
             (*(&POS48))+g_F970_YAt006590AC,
             *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
        --S16(0xF00);
    }
    POS54=POS54-POS5C;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==4 && S16(0x64)==0)
        SpawnDirectedAt453A70(0x335,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    if (S16(0x62)==5 && S16(0x64)==0) {
        POS=-6.0f;
        POS54=9.0f;
        POS5C=0.7f;
    }
    break;
}
