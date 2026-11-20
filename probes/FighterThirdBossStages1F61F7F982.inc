// F982 original Japanese fighter 004AC040 real 1F6 and 1F7.
// Each physical native handler is 777B/215x86/22 typed PE fields.
// Native initial motion is scaled by true DOUBLE at 006583E0
// (1F6) or 006584C8 (1F7); native stage4 F00<2 vs F00<4.
// Normal VC7.1 partial father C++ matches ordered native mnemonic/
// width geometry; original GPR mismatch count 126 per state.
// Entire 82KB game fighter remains NONEXACT, not inner-case exact.
// F982 original native 004AC040 0x1F6 double-scaled fighter action
case 0x1F6: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=(velocityX)*g_F982_Scale1F6At006583E0;
        velocityY=(velocityY)*g_F982_Scale1F6At006583E0;
        field080=99;
        field07C=0;
        field3AC=0;
        scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)>3 && (animationStage)<6) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ClearMotionFields();
            ResetSecondaryCounter(6);
            y=0.0f;
            break;
        }
    }
    if (field07C!=0) {
        ++scriptCounterF02;
        if ((scriptCounterF02)>6) {
            scriptCounterF02=0;
            field07C=0;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==2 && (animationFrame)==0) {
        field314=15.0f;
        field318=-20.0f;
        field31C=-60.0f;
        Fighter::SpawnTrackedEffect(0x32A,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        Fighter::SpawnTrackedEffect(0x329,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        field314=10.0f;
        field318=-135.0f;
        field31C=-30.0f;
        Fighter::SpawnTrackedEffect(0x32A,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        Fighter::SpawnTrackedEffect(0x329,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        PlaySound(3);
    }
    if ((animationStage)==4 && (animationFrame)==0 && (scriptCounterF00)<2) {
        ResetSecondaryCounter(2);
        ++scriptCounterF00;
    }
    if ((animationStage)==6 && (animationFrame)==0)
        ResetSecondaryCounter(5);
    break;
}
// F982 original native 004AC040 0x1F7 double-scaled fighter action
case 0x1F7: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=(velocityX)*g_F982_Scale1F7At006584C8;
        velocityY=(velocityY)*g_F982_Scale1F7At006584C8;
        field080=99;
        field07C=0;
        field3AC=0;
        scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if ((animationStage)>3 && (animationStage)<6) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ClearMotionFields();
            ResetSecondaryCounter(6);
            y=0.0f;
            break;
        }
    }
    if (field07C!=0) {
        ++scriptCounterF02;
        if ((scriptCounterF02)>6) {
            scriptCounterF02=0;
            field07C=0;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==2 && (animationFrame)==0) {
        field314=15.0f;
        field318=-20.0f;
        field31C=-60.0f;
        Fighter::SpawnTrackedEffect(0x32A,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        Fighter::SpawnTrackedEffect(0x329,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        field314=10.0f;
        field318=-135.0f;
        field31C=-30.0f;
        Fighter::SpawnTrackedEffect(0x32A,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        Fighter::SpawnTrackedEffect(0x329,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        PlaySound(3);
    }
    if ((animationStage)==4 && (animationFrame)==0 && (scriptCounterF00)<4) {
        ResetSecondaryCounter(2);
        ++scriptCounterF00;
    }
    if ((animationStage)==6 && (animationFrame)==0)
        ResetSecondaryCounter(5);
    break;
}
