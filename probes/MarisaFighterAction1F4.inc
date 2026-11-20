// Native Marisa action 0x1F4: random airborne particle, landing and launch.
        case 0x1F4: {
            if (animationStage == 0 && animationFrame == 0) {
                ClearMotionFields();
                field080 = 1;
                field07C = 0;
                field3AC = 0;
            }
            if (RecordedRange(0, 100) < 40 && animationStage > 3 && animationStage < 8) {
                const float effectY = y + g_MarisaRandomEffectYAt00657858;
                const float spawnY = static_cast<float>(RecordedRange(0, 0x8C)) + effectY;
                const float effectX = x + g_MarisaRandomEffectXAt00657878;
                const float spawnX = effectX - static_cast<float>(RecordedRange(0, 0x3C));
                SpawnBattleEffect(0x330, spawnX, spawnY, facing, 1);
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
            if (AdvanceNestedFrame() == field070)
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
