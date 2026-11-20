// Original Marisa 0x186 pre-switch branch.
        if (actionSnapshot == 0x186) {
            if (animationStage == 0 && animationFrame == 0) {
                field080 = 1;
                field07C = 0;
                field3AC = 0;
                velocityX = 12.5f;
            }
            if (animationStage > 0) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX = 0.0f;
                    field3AC = 0;
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 4 && animationFrame == 0)
                PlaySharedSound(0x1D);
            if (animationStage == 5 && animationFrame == 0) {
                SetCameraShake(2.0f);
                SpawnBattleEffect(0x325,
                    static_cast<float>(facing * 170) + x,
                    y - g_MarisaSpecialYCorrectionAt00658290, facing, 0);
            }
            return;
        }
