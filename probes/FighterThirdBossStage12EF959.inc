// F959 original native Japanese TH075 004AC040 case 0x12E.
 // Physical 004B11E3..004B12F1 =270 original CODE B/82 x86,
 // seven real native REL32/DIR32 source external PE fields,
 // including original seven-arg sprite 0x333 at 00453B50.
 // Ordinary source is an internal handler of a still NONEXACT
 // complete 82,796-B original giant.
// Natural native 004AC040 12E original game state, source probe.
case 0x12E: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0)
            ResetAt453E20();
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
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(2);
    if (S16(0x62)==4 && S16(0x64)==0)
        PrepareActionAt453D60(0x1D);
    if (S16(0x62)==4 && S16(0x64)==0) {
        SpawnSevenAt453B50(0x333,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
    }
    break;
}
