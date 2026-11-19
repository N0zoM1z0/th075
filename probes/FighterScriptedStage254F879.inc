// F879 actual real game 0x254, whole original PE switch entry.
// Native true BYTE decrement (not MOVZX dword), stage5 floatY sprite37, owner+EFA reset.
// 252/253 include native +3B6/+7C guard; 254 does not. Incomplete whole GPR phase.
case 0x254: {
    if ((animationStage)==0 && (animationFrame)==0) {
        --reinterpret_cast<unsigned char&>(field366);
        ClearMotionFields();
        field080=1;
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }

    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnMixedAt453C80(0x37,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            (facing),1);
        PlaySharedSound(0x21);
        reinterpret_cast<signed short&>(opponent->fieldEFA)=0;
    }
    return;
}
