// F749: true complete original 00543210 native action 0x62
// physical 005459E5..00545ADE 249 original CODE B/65 original x86.
// Natural real C++ resource-facing sign plus three actual action
// transitions; an interior switch case, NOT an authored function.
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
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0x5F);
                if ((scriptCounterF00)==1) ResetPrimaryCounters(0x5D);
                if ((scriptCounterF00)==2) ResetPrimaryCounters(0x5E);
            }
            break;
        }
