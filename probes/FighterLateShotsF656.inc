// F656: true original native 0x133..0x136 stage-specific movement and shots.
        case 0x133: {
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=0.0f;
                velocityY=0.0f;
                field05C=0.0f;
                field080=1;
                field07C=0;
            }
            if ((velocityX)>g_ThresholdAt0065782C)
                velocityX=(velocityX)-g_NewDragAt006581E0;
            if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
            if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                PlaySharedSound(0x1C);
                SpawnDirectedAt453A70(0x341,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1);
            }
            if ((animationStage)==6 && (animationFrame)==0) velocityX=15.0f;
            if ((animationStage)==8 && (animationFrame)==0) {
                PlaySharedSound(0x1C);
                field080=1;
                field07C=0;
                SpawnDirectedAt453A70(0x342,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1);
            }
            break;
        }
        case 0x134: {
            if ((animationStage)==0 && (animationFrame)==0) {
                if ((field3AC)==0) ClearMotionFields();
                field080=1;
                field07C=0;
            }
            if ((field3AC)>0) {
                velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
                if ((velocityX)<g_ThresholdAt0065782C) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0);
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)==1 && (animationFrame)==0) PlaySharedSound(0x1D);
            break;
        }
        case 0x135: {
            if ((animationStage)==0 && (animationFrame)==0) {
                if ((field3AC)==0) ClearMotionFields();
                field080=1;
                field07C=0;
            }
            if ((field3AC)>0) {
                velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
                if ((velocityX)<g_ThresholdAt0065782C) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if ((animationStage)==10 || (animationStage)==11) {
                velocityX=(velocityX)-g_SubtractAt00657478;
                if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0);
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)==7 && (animationFrame)==0) velocityX=20.0f;
            if ((animationStage)==10 && (animationFrame)==0)
                SpawnDirectedAt453A70(0x33F,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1);
            break;
        }
        case 0x136: {
            if ((animationStage)==0 && (animationFrame)==0) {
                if ((field3AC)==0) ClearMotionFields();
                field080=1;
                field07C=0;
            }
            if ((field3AC)>0) {
                velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
                if ((velocityX)<g_ThresholdAt0065782C) {
                    velocityX=0.0f;
                    field3AC=0;
                }
            }
            if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0)
                SpawnDirectedAt453A70(0x33E,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1);
            if ((animationStage)==6 && (animationFrame)==0) PlaySharedSound(0x1D);
            break;
        }
