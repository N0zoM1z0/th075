// F614: physical original complete native action0x58 inside giant fighter
// Advance(), including actual ten-projectile burst and optional guarded
// stage-one shot. NOT independent game function or exact whole CODE credit.
case 0x58: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -(reinterpret_cast<float&>(field094));
        reinterpret_cast<int&>(velocityY) = reinterpret_cast<int&>(field098);
        field05C = 0.8f;
        field07C = 0;
    }
    if (velocityY + y <= g_ThresholdAt0065782C) {
        I16(F614_COUNTER)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
        I16(F614_COUNTER+2)=static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
        ClearMotionFields();
        y = 0.0f;
        ResetPrimaryCounters(0x59);
        SetCameraShake(3.0f);
        PlaySharedSound(0x16);
        for (int burst=0;burst<10;++burst)
            SpawnDirectedAt453A70(0x3E4,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        if (reinterpret_cast<signed short&>(fieldEFA)>25) {
            reinterpret_cast<signed short&>(fieldEFA)=0;
            SpawnDirectedAt453A70(0x3E3,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        }
        break;
    }
    if (AdvanceNestedFrame()==field070)
        ResetSecondaryCounter(animationStage-1);
    if (animationStage==1 && animationFrame==0) {
#if F614_STAGE1_SPAWN
        if (fieldF0C==0) {
            fieldF0C=1;
            SpawnDirectedAt453A70(F614_PROJECTILE,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                facing,F614_SIDE);
        }
#endif
        if (velocityY != g_ThresholdAt0065782C) {
            if (*(&velocityX)==g_ThresholdAt0065782C) {
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
