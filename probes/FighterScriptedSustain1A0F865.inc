// F865 native original 1A0: 235B/67 x86/five real original PE fields.
// Meaningful float+54 lvalue needed for native FLD member/ FMUL global widths.
// Enclosing giant remains original GPR and full-parent-JMP nonexact.
case 0x1A0: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        velocityX=(velocityX)*g_F865SustainScaleAt00658348;
        velocityY=(*(&velocityY))*g_F865SustainScaleAt00658348;
    }
    if (y+velocityY<=g_ThresholdAt0065782C) {
        velocityX=0.0f;
        velocityY=0.0f;
        y=0.0f;
    }
    if ((reinterpret_cast<signed short&>(animationStage))>3)
        velocityY=velocityY-field05C;
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(9);
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0)
        field07C=1;
    return;
}
