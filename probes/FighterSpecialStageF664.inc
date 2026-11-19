// F664 original selected giant 00543210: full physical native action 0x200/0x201.
// Ordinary VC7.1 C++ native source interiors; enclosing whole giant remains
// NONEXACT, and SpawnRawXYAt453C80 is a provisional raw-argument ABI proxy.
// Original position +0x44/+0x48 is passed as DWORD bits, never implicit
// FLD/FSTP by-value float conversions in this source grammar.
        case 0x200: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)>7) {
                velocityX=(velocityX)-g_FallingLateDragAt00659240;
                if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
            }
            if ((animationStage)==7 && field07C==2) {
                ResetSecondaryCounter(8);
                velocityX=10.0f;
            }
            if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0) {
                PlaySound(7);
                SpawnRawXYAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1);
            }
            if ((animationStage)==7 && (animationFrame)==0) velocityX=50.0f;
            if ((animationStage)==8 && (animationFrame)==0) velocityX=10.0f;

            break;
        }
        case 0x201: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)>7) {
                velocityX=(velocityX)-g_FallingLateDragAt00659240;
                if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
            }
            if ((animationStage)==7 && field07C==2) {
                ResetSecondaryCounter(8);
                velocityX=10.0f;
            }
            if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
            if ((animationStage)==5 && (animationFrame)==0) {
                PlaySound(7);
                SpawnRawXYAt453C80(0x3C,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1);
            }
            if ((animationStage)==7 && (animationFrame)==0) velocityX=50.0f;
            if ((animationStage)==8 && (animationFrame)==0) velocityX=10.0f;
            if ((animationStage)==11 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0) {
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                ResetSecondaryCounter(2);
                field07C=0;
                field080=1;
            }
            break;
        }
