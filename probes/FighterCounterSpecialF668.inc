// F668: 00543210 original native physical 252/253/254 consecutive stages.
// Complete ordinary C++ inner cases in STILL-NONEXACT original fighter giant.
// The explicit identity lvalue (*(&y)) preserves original x87
// FLD [object+0x48] BEFORE FADD [PE global 0x00657888], unlike
// a commuted standalone float expression in pinned VC7.1.
// This branch uses the inherited Fighter::SpawnAuxEffect(float,float) ABI.
case 0x252: {
            if ((animationStage)==0 && (animationFrame)==0) {
                --field366;
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if ((spiritCooldown)==0 && field07C==1) spirit=1000;
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==4 && (animationFrame)==0) {
                SpawnAuxEffect(0x37,x,
                    (*(&y))+GeometryConstants::Hundred,
                    facing,1);
                PlaySharedSound(0x21);
                opponent->fieldEFA=0;
            }
            break;
        }
        case 0x253: {
            if ((animationStage)==0 && (animationFrame)==0) {
                --field366;
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if ((spiritCooldown)==0 && field07C==1) spirit=1000;
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==4 && (animationFrame)==0) {
                SpawnAuxEffect(0x37,x,
                    (*(&y))+GeometryConstants::Hundred,
                    facing,1);
                PlaySharedSound(0x21);
                opponent->fieldEFA=0;
            }
            break;
        }

        case 0x254: {
            if ((animationStage)==0 && (animationFrame)==0) {
                --field366;
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            if ((animationStage)==4 && (animationFrame)==0) {
                SpawnAuxEffect(0x37,x,
                    (*(&y))+GeometryConstants::Hundred,
                    facing,1);
                PlaySharedSound(0x21);
                opponent->fieldEFA=0;
            }
            break;
        }
