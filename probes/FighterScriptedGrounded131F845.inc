// F845 genuine original 0x131 202B/58 x86, actual native stage3 animation 0x1D.
// F844 original selected 005214B0 native stage0x130 202B/58 x86.
// Native x87 position/grounded drag and two entire-parent returns.
// Physical PE shows prepare stage3, animation1C, action9.
// Not independently callable whole original game CODE.
case 0x131: {
    velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(0xA);
        y=0.0f;
        field05C=0.0f;
        velocityY=0.0f;
        return;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        field080=1;
        field07C=0;
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(9);
    if ((animationStage)==3 && (animationFrame)==0)
        PlaySharedSound(0x1D);
    return;
}
