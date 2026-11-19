// F901 original 31C tail native 219B/63 x86/7 real PE calls.
// Actual stage12 uses state454A70(0)/452B30/Prepare17;
// stage15 short F00<8 and native aux0D, sets char3CF=1.
// Whole original fighter 46755B remains NONEXACT.
case 0x31C: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=1;
        ClearMotionFields();
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==12 && (animationFrame)==0) {
        ApplyStateAt454A70(0);
        EmitStateAt452B30();
        PlaySharedSound(0x17);
    }
    if ((animationStage)==15 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(0xD);
        reinterpret_cast<unsigned char&>(field3CF)=1;
    }
    return;
}
