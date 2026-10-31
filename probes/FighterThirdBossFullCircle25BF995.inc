// F995 pinned Japanese original 004AC040 25B native 3693 B/957 x86.
 // Exactly THIRTY-SIX real independent sprite0x327 calls at angles
 // 0,10,...,350, each genuine signed facing*49 integer FILD/FADD
 // native X and Y+physical global00659294. Original real COFF
 // has 77 typed external PE fields, including 36 global Y and
 // 36 projectile calls; compile all original mnemonics/widths.
 // GPR original roles remain nonnative; full 82KB fighter NONEXACT.
// F995 original Japanese game fighter 004AC040 action25B:
 // thirty-six native separate 0x327 projectile calls
case 0x25B: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    --S16(0xF00);
    if (S16(0x62)>5 && S16(0xF00)<=0 && S16(0xF02)<1) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0xFA);
        F32(0x314)=0.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=10.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=20.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=30.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=40.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=50.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=60.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=70.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=80.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=90.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=100.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=110.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=120.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=130.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=140.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=150.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=160.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=170.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=180.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=190.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=200.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=210.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=220.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=230.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=240.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=250.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=260.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=270.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=280.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=290.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=300.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=310.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=320.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=330.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=340.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=350.0f;
        F32(0x318)=7.0f;
        SpawnFloatXYAt453A70(0x327,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
            (*(&POS48))+g_F968_RoundY190At00659294,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
}
