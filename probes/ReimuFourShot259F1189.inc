// Reimu Fighter::Advance native action 0x259.
// Four ordered 0x322 projectiles at stage 8; this sibling differs by effect ID.
case 0x259:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetPrimaryCounters(0);
    }
    if (animationStage == 8 && animationFrame == 0) {
        field314 = 0.0f;
        field318 = (y) + GeometryConstants::NinetySix;
        SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
            (y) + GeometryConstants::NinetySix, facing, 1);
        field314 = 1.0f;
        SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
            (y) + GeometryConstants::NinetySix, facing, 1);
        field314 = 2.0f;
        SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
            (y) + GeometryConstants::NinetySix, facing, 1);
        field314 = 3.0f;
        SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
            (y) + GeometryConstants::NinetySix, facing, 1);
        UpdateGaugeTimer(0xFA);
        PlaySound(4);
    }
    return;
