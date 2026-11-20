// Original Marisa action 0x32 special handler.
action32Special: {
                if (animationStage == 0 && animationFrame == 0) {
                    velocityX = -8.0f;
                    velocityY = 0.0f;
                    field07C = 0;
                }
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX += g_JumpGroundCorrectionAt00658058;
                    if (velocityX > g_ThresholdAt0065782C)
                        velocityX = 0.0f;
                }
                if (CheckHorizontalLimits() && field3BE != 0)
                    field490 = velocityX * static_cast<float>(g_JumpReflectionAt006583E8);
                if (AdvanceNestedFrame() == field070)
                    ResetPrimaryCounters(0);
                return;

}
