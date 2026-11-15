// F959 original native Japanese TH075 004AC040 case 0x12E.
 // Physical 004B11E3..004B12F1 =270 original CODE B/82 x86,
 // seven real native REL32/DIR32 source external PE fields,
 // including original seven-arg sprite 0x333 at 00453B50.
 // Ordinary source is an internal handler of a still NONEXACT
 // complete 82,796-B original giant.
// Natural native 004AC040 12E original game state, source probe.
case 0x12E: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if ((field3AC)==0)
            ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(2);
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0)
        PrepareActionAt453D60(0x1D);
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnSevenAt453B50(0x333,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            facing,1,0,1);
    }
    break;
}
