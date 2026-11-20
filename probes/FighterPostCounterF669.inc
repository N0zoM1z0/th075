// F669: 0x255/0x256/0x257 authentic original fighter inner case C++.
// This is source-backed original stage movement/shots in the still NONEXACT
// full giant 00543210, not independently accepted whole game functions.
// The identity float lvalue expression preserves original FLD/FADD order.
case 0x255: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnAuxEffect(0x37,x,
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }
            if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<1) {
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
            }
            break;
        }
        case 0x256: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnAuxEffect(0x37,x,
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }

            break;
        }
        case 0x257: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
            if ((animationStage)==5 && (animationFrame)==0) {
                SpawnAuxEffect(0x37,x,
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
            }
            if ((animationStage)==8 && (animationFrame)==0 && (scriptCounterF00)<1) {
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
            }
            break;
        }
