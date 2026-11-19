// F853 selected native 18A: 250B/71x86/6 typed PE fields.
// Genuine float Y left lvalue preserves original x87 width/order.
// Incomplete giant source: original GPR and final-JMP differences remain.
case 0x18A: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
        velocityX=15.0f;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=0.0f;
        field3AC=0;
    }
    if (AdvanceNestedFrame()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==5 && (animationFrame)==0)
        SpawnFloatXYAt453A70(0x327,
            float((facing)*151)+(x),
            (*(&y))+g_F853OffsetYAt0065929C,
            (facing),1);
    return;
}
