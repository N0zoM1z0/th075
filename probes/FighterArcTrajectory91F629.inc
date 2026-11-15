// F629: genuine complete original native action0x91 arc trajectory,
// inside a huge incomplete fighter Advance(). Game case evidence,
// not an independent original CODE function or accepted match unit.
case 0x91: {
    if (reinterpret_cast<signed short&>(animationStage)==0 && reinterpret_cast<signed short&>(animationFrame)==0) {
        velocityX=-10.0f;
        velocityY=14.0f;
        field05C=0.5f;
        field07C=0;
    }
    if (reinterpret_cast<signed short&>(animationStage)==F629_STAGE && velocityY<g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F629_EARLY);
        break;
    }
    velocityY=velocityY-field05C;
    if (velocityY+y<=g_ThresholdAt0065782C) {
        I16(F629_COUNTER)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        I16(F629_COUNTER+2)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        ResetAt453E20();
        y=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        break;
    }
    if (GetNativeActionAt40FA30()==reinterpret_cast<signed short&>(field070))
        SetAuxActionAt40FB40(F629_LATE);
    break;
}
