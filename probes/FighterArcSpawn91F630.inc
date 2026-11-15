// F630 actual native 105-instruction action0x91 in two special giant
// fighter C++ sources. This 27-instruction stage-one projectile path
// is absent from original regular 78-instruction F629 actors.
// A full parent Advance() remains NONEXACT; this is not a new function.
case 0x91: {
    if (reinterpret_cast<signed short&>(animationStage)==0 && reinterpret_cast<signed short&>(animationFrame)==0) {
        velocityX=-10.0f;
        velocityY=14.0f;
        field05C=0.5f;
        field07C=0;
    }
    if (reinterpret_cast<signed short&>(animationStage)==1 && reinterpret_cast<signed short&>(animationFrame)==0 && reinterpret_cast<signed short&>(fieldF0C)==0) {
        reinterpret_cast<signed short&>(fieldF0C)=1;
        SpawnDirectedAt453A70(F630_PROJECTILE, reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            facing,F630_SIDE);
    }
    if (reinterpret_cast<signed short&>(animationStage)==F630_STAGE && velocityY<g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F630_EARLY);
        break;
    }
    velocityY=velocityY-field05C;
    if (velocityY+y<=g_ThresholdAt0065782C) {
        I16(F630_COUNTER)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        I16(F630_COUNTER+2)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        ResetAt453E20();
        y=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        break;
    }
    if (GetNativeActionAt40FA30()==reinterpret_cast<signed short&>(field070))
        SetAuxActionAt40FB40(F630_LATE);
    break;
}
