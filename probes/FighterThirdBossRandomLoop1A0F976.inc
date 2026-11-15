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
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field07C=1;
        ResetAt453E20();
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        PrepareActionAt453D40(0);
        if (field39D==2) {
            for (int shot=0;shot<5;++shot) {
                field314=0.0f;
                field318=10.0f;
                SpawnSevenFloatAt453B50(0x344,
                    float((RandAt455580(0,80)+30)*(facing))+(x),
                    ((*(&y))+g_F976_RandomYAt0065786C+shot*40)+float(RandAt455580(0,20)),
                    facing,1,0,1);
            }
        } else {
            for (int shot=0;shot<8;++shot) {
                field314=0.0f;
                field318=10.0f;
                SpawnSevenFloatAt453B50(0x344,
                    float((RandAt455580(0,100)+20)*(facing))+(x),
                    ((*(&y))+g_F976_RandomYAt0065786C+shot*30)+float(RandAt455580(0,20)),
                    facing,1,0,1);
            }
        }
    }
    break;
}
