// F950: independently reconstructed native Japanese TH075 004AC040
// original action0xCA, 004B04CC..004B0680 436 CODE B /123 x86.
// The ordinary C++ emits 430B/123 original x86 with ALL native
// mnemonic and GPR-role positions equal, but two native wide EBP−0x98
// integer-to-x87 spill instructions are short because the still
// PARTIAL 82KB original father uses only a 0x40 stack frame.
// The original game giant remains NONEXACT; no case-only credit.
case 0xCA: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        field05C=0.0f;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=11.0f;
        velocityY=5.0f;
        field05C=0.6f;
        SpawnAt453C80(0x7D,
            float((facing)*80)+(x),
            (*(&y))+g_F950_CAVolleyYAt00658400,
            facing,1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_F950_CAVolleyYAt00658400,
            facing,1);
        PrepareActionAt453D60(31);
    }
    if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))>1) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f;
            velocityY=0.0f;
            field05C=0.0f;
            y=0.0f;
            reinterpret_cast<signed short&>(animationFrame)=0;
            SetNativeActionAt40FAC0(0xA);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(9);
    break;
}
