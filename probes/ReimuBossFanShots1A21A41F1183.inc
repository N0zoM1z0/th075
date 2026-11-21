// Reimu Fighter::Advance native actions 0x1A2, 0x1A3 and 0x1A4.
// Five fixed-angle shots and the two difficulty-card random fan patterns.
case 0x1A2:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(2);
    if (animationStage == 5 && animationFrame == 0) {
        PlaySound(0);
        for (int shot = 0; shot < 5; ++shot) {
            field314 = static_cast<float>(65 - shot * 10);
            field318 = 10.0f;
            Fighter::SpawnTrackedEffect(0x344,
                x + static_cast<float>(facing * 0x2F),
                y + g_ReimuStormPairXBaseAt00658264,
                facing, 1, 0, 1);
        }
    }
    return;

case 0x1A3:
    if (animationStage == 0 && animationFrame == 0) field07C = 1;
    velocityY = velocityY - field05C;
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(9);
    if (animationStage == 5 && animationFrame == 0) {
        PlaySound(0);
        field314 = 0.0f;
        field318 = 10.0f;
        if (field39D == 2) {
            for (int shot = 0; shot < 5; ++shot) {
                const float yOffset = g_ReimuFiveShotYAt00657858 + static_cast<float>(RecordedRange(0, 20) + shot * 30);
                const float xOffset = static_cast<float>(RecordedRange(0, 80) + 30) * static_cast<float>(facing);
                Fighter::SpawnTrackedEffect(0x344, x + xOffset, y + yOffset, facing, 1, 0, 1);
            }
        }
        else {
            for (int shot = 0; shot < 8; ++shot) {
                const float yOffset = g_ReimuFiveShotYAt00657858 + static_cast<float>(RecordedRange(0, 20) + shot * 20);
                const float xOffset = static_cast<float>(RecordedRange(0, 100) + 20) * static_cast<float>(facing);
                Fighter::SpawnTrackedEffect(0x344, x + xOffset, y + yOffset, facing, 1, 0, 1);
            }
        }
    }
    return;

case 0x1A4:
    if (animationStage == 0 && animationFrame == 0) field07C = 1;
    velocityY = velocityY - field05C;
    if (AdvanceNestedFrame() == animationStageCount) ResetPrimaryCounters(9);
    if (animationStage == 5 && animationFrame == 0) {
        PlaySound(0);
        field314 = -30.0f;
        field318 = 10.0f;
        if (field39D == 2) {
            for (int shot = 0; shot < 5; ++shot) {
                const float yOffset = g_ReimuFiveShotYAt0065786C + static_cast<float>(RecordedRange(0, 20) + shot * 40);
                const float xOffset = static_cast<float>(RecordedRange(0, 80) + shot * 10 + 30) * static_cast<float>(facing);
                Fighter::SpawnTrackedEffect(0x344, x + xOffset, y + yOffset, facing, 1, 0, 1);
            }
        }
        else {
            for (int shot = 0; shot < 8; ++shot) {
                const float yOffset = g_ReimuFiveShotYAt0065786C + static_cast<float>(RecordedRange(0, 20) + shot * 30);
                const float xOffset = static_cast<float>(RecordedRange(0, 100) + shot * 10 + 20) * static_cast<float>(facing);
                Fighter::SpawnTrackedEffect(0x344, x + xOffset, y + yOffset, facing, 1, 0, 1);
            }
        }
    }
    return;
