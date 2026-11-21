// Reimu Fighter::Advance native action 0x259.
// Three-burst 0x325 cadence with the native short delay and round counter.
case 0x259:
    if (animationStage == 0 && animationFrame == 0) {
        field07C = 1;
        ClearMotionFields();
        scriptCounterF00 = 0;
        scriptCounterF02 = 0;
    }
    if (animationStage > 4) {
        if (scriptCounterF02 < 3 && scriptCounterF00 < 1) {
            ResetSecondaryCounter(0);
            field314 = static_cast<float>(scriptCounterF02 * 3 + 145);
            field318 = 10.0f;
            SpawnBattleEffect(0x325, x - static_cast<float>(facing * 100),
                y + g_ReimuSpecialVolleyYAt00659498, facing, 1);
            field314 = static_cast<float>(scriptCounterF02 * 3 + 140);
            field318 = 10.0f;
            SpawnBattleEffect(0x325, x - static_cast<float>(facing * 100),
                y + g_ReimuSpecialVolleyYAt00659498, facing, 1);
            field314 = static_cast<float>(scriptCounterF02 * 3 + 135);
            field318 = 10.0f;
            SpawnBattleEffect(0x325, x - static_cast<float>(facing * 100),
                y + g_ReimuSpecialVolleyYAt00659498, facing, 1);
            field314 = static_cast<float>(scriptCounterF02 * 3 + 130);
            field318 = 10.0f;
            SpawnBattleEffect(0x325, x - static_cast<float>(facing * 100),
                y + g_ReimuSpecialVolleyYAt00659498, facing, 1);
            field314 = static_cast<float>(scriptCounterF02 * 3 + 125);
            field318 = 10.0f;
            SpawnBattleEffect(0x325, x - static_cast<float>(facing * 100),
                y + g_ReimuSpecialVolleyYAt00659498, facing, 1);
            UpdateGaugeTimer(100);
            ++scriptCounterF02;
            scriptCounterF00 = 3;
        }
        --scriptCounterF00;
    }
    if (AdvanceNestedFrame() != animationStageCount) {
        return;
    }
    ResetPrimaryCounters(0);
    return;
