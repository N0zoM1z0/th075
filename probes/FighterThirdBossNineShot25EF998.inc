// F998 native Japanese TH075 original 004AC040 game state25E.
 // Physical original 004BA229..004BA59B 882 CODEB/236x86,
 // 24 genuine external PE targets. Stage0 float motion scaled
 // by 00657F74, native stage4 nine original sprite0x342
 // RAW 32-bit X / floating Y + native 006590AC shots;
 // fixed angles -28..28 by seven. Original instruction mnemonics
 // and widths match, 153 GPR roles still differ in PARTIAL father.
 // Genuine added state regresses following 25F/260/261/262 native
 // GPR phase from 0/0/0/0 to 73/73/65/65, but no x86 width debt.
// F998 true original Japanese game fighter 004AC040 action25E
case 0x25E: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        S16(0xF00)=0;
        S16(0xF02)=0;
        POS=POS*g_F972_GravityAt00657F74;
        F32(0x54)=F32(0x54)*g_F972_GravityAt00657F74;
    }
    if (S16(0x62)>4)
        POS54=POS54-POS5C;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==4 && S16(0x64)==0) {
        POS=-3.0f;
        POS54=9.0f;
        POS5C=0.7f;
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0xFA);
        F32(0x314)=-28.0f;
        F32(0x318)=10.0f;
        SpawnWithFloatAt453A70(0x342,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=-21.0f;
        F32(0x318)=10.0f;
        SpawnWithFloatAt453A70(0x342,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=-14.0f;
        F32(0x318)=10.0f;
        SpawnWithFloatAt453A70(0x342,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=-7.0f;
        F32(0x318)=10.0f;
        SpawnWithFloatAt453A70(0x342,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=0.0f;
        F32(0x318)=10.0f;
        SpawnWithFloatAt453A70(0x342,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=7.0f;
        F32(0x318)=10.0f;
        SpawnWithFloatAt453A70(0x342,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=14.0f;
        F32(0x318)=10.0f;
        SpawnWithFloatAt453A70(0x342,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=21.0f;
        F32(0x318)=10.0f;
        SpawnWithFloatAt453A70(0x342,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=28.0f;
        F32(0x318)=10.0f;
        SpawnWithFloatAt453A70(0x342,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    break;
}
