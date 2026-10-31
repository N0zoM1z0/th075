// F976 genuine Japanese TH075 original fighter 004AC040
// 1A0 physical 004B4097..004B42D1, 570 CODE B/148 x86,
// 12 original genuine PE call/global fields. Real 5/8 shot loops,
// native random number and FIADD/FILD source order. The original
// right-to-left argument evaluation must calculate native Y base
// BEFORE calling RandAt455580(0,20); the opposite source grammar
// changes 72 native ordered mnemonics. With correct natural C++
// all original 148 positional mnemonics+widths align, 66 native
// GPR roles still wrong in the incomplete 82KB parent. No exact credit.
// F976 original 004AC040 real action 1A0 natural random 5/8 loop.
case 0x1A0: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
    }
    --S16(0xF00);
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        PrepareActionAt453D40(0);
        if (*reinterpret_cast<signed char*>(RAW+0x39D)==2) {
            for (int shot=0;shot<5;++shot) {
                F32(0x314)=0.0f;
                F32(0x318)=10.0f;
                SpawnSevenFloatAt453B50(0x344,
                    float((RandAt455580(0,80)+30)*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
                    ((*(&POS48))+g_F976_RandomYAt0065786C+shot*40)+float(RandAt455580(0,20)),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
        } else {
            for (int shot=0;shot<8;++shot) {
                F32(0x314)=0.0f;
                F32(0x318)=10.0f;
                SpawnSevenFloatAt453B50(0x344,
                    float((RandAt455580(0,100)+20)*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
                    ((*(&POS48))+g_F976_RandomYAt0065786C+shot*30)+float(RandAt455580(0,20)),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
        }
    }
    break;
}
