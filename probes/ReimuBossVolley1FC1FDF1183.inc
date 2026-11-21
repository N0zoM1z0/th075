// Reimu Fighter::Advance native actions 0x1FC and 0x1FD at 0045DD70.
// Shared stage/fade/child-burst logic; only the stage-8 horizontal launch
// differs (-60 for 1FC, +120 for 1FD).
case 0x1FC:
case 0x1FD: {
    if (animationStage == 0 && animationFrame == 0) {
        ClearMotionFields();
        field07C = 1;
        field3AC = 0;
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
    }
    if (animationStage == 6 || animationStage == 7) {
        if (color[0] < 0x15) color[0] = 0;
        else color[0] = static_cast<unsigned char>(color[0] - 0x14);
    }
    if (animationStage > 8 && animationStage < 0x0D) {
        velocityY = velocityY - field05C;
        if (color[0] < 0xEB) color[0] = static_cast<unsigned char>(color[0] + 0x14);
        else color[0] = 0xFF;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            color[0] = 0xFF;
            ClearMotionFields();
            ResetSecondaryCounter(0x0D);
            y = 0.0f;
            return;
        }
    }
    if (animationStage > 1 && animationStage < 8) {
        Fighter::SpawnTrackedEffect(0x33E,
            static_cast<float>(RecordedRange(0, 120)) + x - g_ReimuStormPairXBaseAt00658264,
            y - g_ReimuStormPairYBaseAt00657CBC + static_cast<float>(RecordedRange(0, 90)),
            1, 1, 0, 1);
    }
    if (animationStage == 9 && animationFrame == 0 && scriptCounterF00 == 0) {
        velocityX = 0.0f;
        velocityY = 0.0f;
        ++scriptCounterF00;
    }
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(0);
    if (animationStage == 6 && animationFrame == 0) {
        PlaySound(2);
        Fighter::SpawnTrackedEffect(0x338, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        Fighter::SpawnTrackedEffect(0x339, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        Fighter::SpawnTrackedEffect(0x33A, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        Fighter::SpawnTrackedEffect(0x33B, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        Fighter::SpawnTrackedEffect(0x33C, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        Fighter::SpawnTrackedEffect(0x33D, x - static_cast<float>(facing * 7), y + g_ReimuStormBurstYOffsetAt00659490, 1, 1, 0, 1);
        UpdateGaugeTimer(200);
        ResetTransform(0.0f, 0.0f, 0.0f);
        color[0] = 0xFF;
    }
    if (animationStage == 8 && animationFrame == 0 && scriptCounterF02 < 4) {
        ResetSecondaryCounter(6);
        ++scriptCounterF02;
        return;
    }
    if (animationStage == 8 && animationFrame == 0) {
        velocityX = action == 0x1FC ? -60.0f : 120.0f;
        velocityY = 3.0f;
        field05C = 0.5f;
    }
    if (animationStage == 0x0D && animationFrame == 0) {
        ResetSecondaryCounter(0x0B);
        return;
    }
    return;
}
