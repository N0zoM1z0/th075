// F608: original native 118-instruction indexed action0x49 in two
// special spawning fighter giants. Original whole boss remains NONEXACT.
case 0x49: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(field094);
        velocityY = field098;
        field05C = 0.8f;
        field07C = 0;
    }
    if (velocityY + y <= FloatConstants::Zero) {
        scriptCounterF00=static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        scriptCounterF02=static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y=0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(animationStage-1);
    if (animationStage==1 && animationFrame==0) {
        // Actual 118-x86 native case has a once-only projectile branch
        // before its two original x87 equality tests. Keep it inside
        // the already established stage-one/frame-zero guard.
        if (fieldF0C==0) {
            fieldF0C=1;
            SpawnBattleEffect(F608_PROJECTILE,x,y,
                facing, F608_SIDE);
        }
        if (velocityY != FloatConstants::Zero) {
        // Real VC7.1 left lvalue preserves original FLD global; FLD member.
        // Both branches exit this native case, not merely the nested if.
        if (*(&velocityX) == FloatConstants::Zero) {
            ResetSecondaryCounter(3);
            break;
        } else {
            ResetSecondaryCounter(2);
            break;
        }
        }
    }
    break;
}
