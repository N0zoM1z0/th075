// Reimu Fighter::Advance native action 0x258.
// Four ordered 0x321 projectiles at stage 8; the effect Y parameter is also
// the native second effect field, followed by the 250-point gauge and reset 4.
case 0x258:
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
        SpawnBattleEffect(0x321, x + static_cast<float>(facing * 0x72),
            (y) + GeometryConstants::NinetySix, facing, 1);
        field314 = 1.0f;
        SpawnBattleEffect(0x321, x + static_cast<float>(facing * 0x72),
            (y) + GeometryConstants::NinetySix, facing, 1);
        field314 = 2.0f;
        SpawnBattleEffect(0x321, x + static_cast<float>(facing * 0x72),
            (y) + GeometryConstants::NinetySix, facing, 1);
        field314 = 3.0f;
        SpawnBattleEffect(0x321, x + static_cast<float>(facing * 0x72),
            (y) + GeometryConstants::NinetySix, facing, 1);
        UpdateGaugeTimer(0xFA);
        PlaySound(4);
    }
    return;
