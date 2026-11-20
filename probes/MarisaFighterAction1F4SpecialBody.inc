// Pre-switch special-action branch.
// Native Marisa action 0x1F4: random airborne particle, landing and launch.
action1F4Special: {
            if (animationStage == 0 && animationFrame == 0) {
                ClearMotionFields();
                field080 = 1;
                field07C = 0;
                field3AC = 0;
            }
            if (RecordedRange(0, 100) < 40 && animationStage > 3 && animationStage < 8) {
                actionSnapshot = RecordedRange(0, 0x8C);
SpawnBattleEffect(0x330,
    x + g_MarisaRandomEffectXAt00657878 - static_cast<float>(RecordedRange(0, 0x3C)),
    y + g_MarisaRandomEffectYAt00657858 + static_cast<float>(actionSnapshot), facing, 1);
            }
            if (y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    ResetSecondaryCounter(12);
                    y = 0.0f;
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0)
                PlaySound(2);
            if (animationStage == 4 && animationFrame == 0) {
                velocityX = 8.0f;
                velocityY = 14.0f;
                field05C = 0.8f;
                SpawnAuxEffect(0x7F, x, y, facing, 1);
            }
            if (animationStage == 12 && animationFrame == 0)
                ResetSecondaryCounter(10);
            return;

}
