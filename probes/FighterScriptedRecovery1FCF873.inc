// F873 original game 1FC: full 253B/70x86 native case, physics before stage0.
// Real height global658350, stage6 owner counters & POS15, independent game entry.
// Enclosing whole giant remains nonexact; no split-case exact CODE.
case 0x1FC: {
    if ((velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_F873GroundDropAt00658350;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        field3AC=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        field3AC=0;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0)
        velocityX=15.0f;
    return;
}
