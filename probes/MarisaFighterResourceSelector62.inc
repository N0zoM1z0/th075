// Marisa's native 0x62 input-direction selector.
// The original handler is 0x00488D0A..0x00488E03 (249 bytes).
        case 0x62: {
            if (static_cast<int>(facing) * inputX > 0
                && (static_cast<unsigned int>(inputA) > 0
                 || static_cast<unsigned int>(inputB) > 0
                 || static_cast<unsigned int>(inputC) > 0
                 || static_cast<unsigned int>(inputD) > 0))
                scriptCounterF00 = 1;
            if (static_cast<int>(facing) * inputX < 0
                && (static_cast<unsigned int>(inputA) > 0
                 || static_cast<unsigned int>(inputB) > 0
                 || static_cast<unsigned int>(inputC) > 0
                 || static_cast<unsigned int>(inputD) > 0))
                scriptCounterF00 = 2;
            if (AdvanceNestedFrame() == field070) {
                ResetPrimaryCounters(0x5F);
                if (scriptCounterF00 == 1)
                    ResetPrimaryCounters(0x5D);
                if (scriptCounterF00 == 2)
                    ResetPrimaryCounters(0x5E);
            }
            break;
        }
