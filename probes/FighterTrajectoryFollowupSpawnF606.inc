// F606: real original 113-instruction second-switch case 0x47 or 0x48
// in the two extended fighter giants. Caller declares the true case,
// original drag, projectile kind, one-shot side and stage policy.
// Each inclusion is a naturally-typed C++ case inside whole Advance().
// These are NOT independently callable or accepted whole functions.
case F606_ACTION: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(reinterpret_cast<float&>(field094));
        reinterpret_cast<int&>(velocityY) = reinterpret_cast<int&>(field098);
        field05C = F606_DRAG;
        field07C = 0;
    }
    if (animationStage==1 && animationFrame==0 && fieldF0C==0) {
        fieldF0C=1;
        SpawnDirectedAt453A70(F606_PROJECTILE,
            reinterpret_cast<int&>(x), reinterpret_cast<int&>(y),
            facing, F606_SIDE);
    }
    if (animationStage==F606_STAGE && velocityY<g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F606_EARLY);
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= g_ThresholdAt0065782C) {
        I16(F606_COUNTER)=static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        I16(F606_COUNTER+2)=static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ResetAt453E20();
        y=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        break;
    }
    if (GetNativeActionAt40FA30()==field070)
        SetAuxActionAt40FB40(F606_LATE);
    break;
}
