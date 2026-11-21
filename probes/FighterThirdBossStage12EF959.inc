// F959 original native Japanese TH075 004AC040 case 0x12E.
 // Physical 004B11E3..004B12F1 =270 original CODE B/82 x86,
 // seven real native REL32/DIR32 source external PE fields,
 // including original seven-arg sprite 0x333 at 00453B50.
 // Ordinary source is an internal handler of a still NONEXACT
 // complete 82,796-B original giant.
// Natural native 004AC040 12E original game state, source probe.
case 0x12E: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0)
                    field080=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(2);
    if ((animationStage)==4 && (animationFrame)==0)
        PlaySharedSound(0x1D);
    if ((animationStage)==4 && (animationFrame)==0) {
        Fighter::SpawnTrackedEffect(0x333,x,y,
            facing,1,0,1);
    }
    break;
}
