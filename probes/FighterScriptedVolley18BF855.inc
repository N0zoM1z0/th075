// F855 native original 18B: 353B/99 x86/7 physical PE fields.
// Real prefix 16-bit ++, stage7 aux6 and stage6 facing*128 FILD.
// Incomplete giant register allocation remains nonnative; no case exact credit.
case 0x18B: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        velocityX=10.0f;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))>6) {
        velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(2);
    if ((reinterpret_cast<signed short&>(animationStage))==7 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(6);
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnFloatXYAt453A70(0x328,
            float((facing)*128)+(x),
            (*(&y))+g_F855ShotYAt00658400,
            (facing),1);
    }
    return;
}
