// F870 original native 1F8 complete 469B/143-x86/15 physical PE fields.
// Native FUCOMPP requires bare y==global, generating FLD global then FLD member.
// Actual x87 ground contact, stage3 sprite7F, stage7 sprite335, stage15 auxE.
// Full original giant remains register and two-final-JMP NONEXACT.
case 0x1F8: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        field3AC=0;
    }
    if ((velocityX)>g_ThresholdAt0065782C) {
        if (y==g_ThresholdAt0065782C) {
            velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
            if ((velocityX)<g_ThresholdAt0065782C)
                velocityX=0.0f;
        }
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(0xF);
            y=0.0f;
            return;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=8.0f;
        velocityY=12.0f;
        field05C=0.8f;
        SpawnRawAt453C80(0x7F,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==7 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnDirectedAt453A70(0x335,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PrepareActionAt453D40(4);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0xF && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(0xE);
    return;
}
