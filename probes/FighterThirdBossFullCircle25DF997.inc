// F997 original Japanese 004AC040 fighter state 25D:
 // 2799B/749 native x86, 78 actual original PE external fields.
 // All original mnemonic and instruction widths align; 477
 // original 25D GPR operand roles still wrong in partial father.
 // Crucial real preceding 36-shot source restores ALL FOUR later
 // 25F/260/261/262 native GPR phases (73/73/65/65 -> 0 each).
 // Original full 82KB GAME callable remains NONEXACT.
// F997 real original Japanese 004AC040 state25D full 360-degree 36 shots
case 0x25D: {
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
        F32(0x314)=0.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=10.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=20.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=30.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=40.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=50.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=60.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=70.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=80.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=90.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=100.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=110.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=120.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=130.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=140.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=150.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=160.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=170.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=180.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=190.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=200.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=210.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=220.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=230.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=240.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=250.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=260.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=270.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=280.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=290.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=300.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=310.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=320.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=330.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=340.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=350.0f;
        F32(0x318)=7.0f;
        SpawnWithFloatAt453A70(0x327,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    break;
}
