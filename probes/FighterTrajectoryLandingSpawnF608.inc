// F608: original native 118-instruction indexed action0x49 in two
// special spawning fighter giants. Original whole boss remains NONEXACT.
case 0x49: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(reinterpret_cast<float&>(field094));
        reinterpret_cast<int&>(velocityY) = reinterpret_cast<int&>(field098);
        field05C = 0.8f;
        field07C = 0;
    }
    if (velocityY + y <= g_ThresholdAt0065782C) {
        I16(F608_COUNTER)=static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        I16(F608_COUNTER+2)=static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (GetNativeActionAt40FA30()==field070)
        SetAuxActionAt40FB40(animationStage-1);
    if (animationStage==1 && animationFrame==0) {
        // Actual 118-x86 native case has a once-only projectile branch
        // before its two original x87 equality tests. Keep it inside
        // the already established stage-one/frame-zero guard.
        if (fieldF0C==0) {
            fieldF0C=1;
            SpawnDirectedAt453A70(F608_PROJECTILE,
                reinterpret_cast<int&>(x), reinterpret_cast<int&>(y),
                facing, F608_SIDE);
        }
        if (velocityY != g_ThresholdAt0065782C) {
        // Real VC7.1 left lvalue preserves original FLD global; FLD member.
        // Both branches exit this native case, not merely the nested if.
        if (*(&velocityX) == g_ThresholdAt0065782C) {
            SetAuxActionAt40FB40(3);
            break;
        } else {
            SetAuxActionAt40FB40(2);
            break;
        }
        }
    }
    break;
}
