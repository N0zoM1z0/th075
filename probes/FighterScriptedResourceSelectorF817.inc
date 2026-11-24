// Youmu's resource-state selector in action 0x62, at 0x00523BA4.
        case 0x62: {
            if (static_cast<int>(facing) * inputX>0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(inputD)>0))
                scriptCounterF00=1;
            if (static_cast<int>(facing) * inputX<0
                && (static_cast<unsigned int>(inputA)>0
                 || static_cast<unsigned int>(inputB)>0
                 || static_cast<unsigned int>(inputC)>0
                 || static_cast<unsigned int>(inputD)>0))
                scriptCounterF00=2;
            else if (inputA == 0 && inputB == 0 && inputC == 0 && inputD == 0) {
                // Keep the previous selection until another attack input.
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0x5F);
                if ((scriptCounterF00)==1) ResetPrimaryCounters(0x5D);
                if ((scriptCounterF00)==2) ResetPrimaryCounters(0x5E);
            }
            return;
        }
