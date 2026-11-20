// F981 native Japanese original fighter 004AC040 states 1F4 and 1F5.
// Both original game case interiors exactly 830B/232 x86 with
// 23 real typed PE/COFF external targets each. Original 1F5 stage7
// ordering sets drag AFTER raw 0x7F projectile, 1F4 sets it BEFORE.
// Four actual 0x32A/0x329 sprite shots at stage8; real x87 motion,
// 1F4 auxiliary stage10 F00<1 vs 1F5 F00<3. Natural VC7.1 source
// matches native x86 mnemonic/width geometry but 135 GPR roles each
// remain wrong in incomplete 82KB parent. No independent case exact.
// F981 true Japanese original 004AC040 action 0x1F4
case 0x1F4: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=99;
        field07C=0;
        field3AC=0;
        scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ClearMotionFields();
            ResetSecondaryCounter(0xC);
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
    if ((animationStage)==7 && (animationFrame)==0) {
        velocityX=2.0f;
        velocityY=6.5f;
        field05C=0.4f;
        SpawnAuxEffect(0x7F,x,y,
            facing,1);
        PlaySound(3);
    }
    if ((animationStage)==8 && (animationFrame)==0) {
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
    }
    if ((animationStage)==10 && (animationFrame)==0 && (scriptCounterF00)<1) {
        ResetSecondaryCounter(8);
        ++scriptCounterF00;
    }
    if ((animationStage)==12 && (animationFrame)==0)
        ResetSecondaryCounter(0xB);
    break;
}
// F981 true Japanese original 004AC040 action 0x1F5
case 0x1F5: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=99;
        field07C=0;
        field3AC=0;
        scriptCounterF00=0;
        scriptCounterF02=0;
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ClearMotionFields();
            ResetSecondaryCounter(0xC);
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
    if ((animationStage)==7 && (animationFrame)==0) {
        velocityX=8.0f;
        velocityY=13.5f;
        SpawnAuxEffect(0x7F,x,y,
            facing,1);
        field05C=0.5f;
        PlaySound(3);
    }
    if ((animationStage)==8 && (animationFrame)==0) {
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
    }
    if ((animationStage)==10 && (animationFrame)==0 && (scriptCounterF00)<3) {
        ResetSecondaryCounter(8);
        ++scriptCounterF00;
    }
    if ((animationStage)==12 && (animationFrame)==0)
        ResetSecondaryCounter(0xB);
    break;
}
