// Pre-switch special-action branch.
// Native Marisa action 0x2C2: card resource setup and terminal effect.
action2C2Special: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 0;
                field080 = 6;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                field36C -= g_ContactProjectionAt00657888;
                SpawnAuxEffect(0x74, x,
                    y + g_MarisaSpecialProjectileYAt00658400, facing, 1);
            }
            if (animationStage == 6 && animationFrame == 0) {
                SpawnBattleEffect(0x343, x, y, facing, 1);
                UpdateGaugeTimer(0x1F4);
                fieldF14 = 6;
                fieldF16 = 6;
                fieldF18 = 0x1A4;
                PlaySound(0x0D);
            }
            return;

}
