// F606: real original 113-instruction second-switch case 0x47 or 0x48
// in the two extended fighter giants. Caller declares the true case,
// original drag, projectile kind, one-shot side and stage policy.
// Each inclusion is a naturally-typed C++ case inside whole Advance().
// These are NOT independently callable or accepted whole functions.
case F606_ACTION: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(field094);
        velocityY = field098;
        field05C = F606_DRAG;
        field07C = 0;
    }
    if (animationStage==1 && animationFrame==0 && fieldF0C==0) {
        fieldF0C=1;
        SpawnBattleEffect(F606_PROJECTILE,x,y,
            facing, F606_SIDE);
    }
    if (animationStage==F606_STAGE && velocityY<g_StopThresholdAt00657480) {
        ResetSecondaryCounter(F606_EARLY);
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= g_ThresholdAt0065782C) {
        I16(F606_COUNTER)=static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
        I16(F606_COUNTER+2)=static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
        ClearMotionFields();
        y=0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame()==field070)
        ResetSecondaryCounter(F606_LATE);
    break;
}
