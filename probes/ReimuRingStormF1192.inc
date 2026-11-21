case 0x2DB: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0; scriptCounterF02=0; field07C=1;
        if (y==g_ThresholdAt0065782C) ClearMotionFields();
        else {
            velocityX=(velocityX)*g_ReimuAirDragAt00658348;
            velocityY=(*(&velocityY))*g_ReimuAirDragAt00658348;
        }
    }
    if (y>g_ThresholdAt0065782C) {
        if ((animationStage)<12) {
            velocityY=velocityY-g_ReimuStormFallAt00658044;
            if (y+velocityY<g_ThresholdAt0065782C) velocityX=0.0f;
        } else {
            velocityY=velocityY-field05C;
            if (y+velocityY<g_ThresholdAt0065782C && (animationStage)<16) {
                y=0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(16);
                break;
            }
        }
    }
    if ((animationStage)==10 && (animationFrame)==0 && (scriptCounterF00)<g_ReimuRepeatSettingAt006714D0*3+4) {
        PlaySound(6);
        field314=float(RecordedRange(0,359));
        if ((scriptCounterF02)==0) {
            SpawnBattleEffect(0x384,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,facing,1);
            field314=float(RecordedRange(0,359));
        }
        if ((scriptCounterF02)==1) {
            SpawnBattleEffect(0x385,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,facing,1);
            field314=float(RecordedRange(0,359));
        }
        if ((scriptCounterF02)==2) {
            SpawnBattleEffect(0x386,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,facing,1);
            field314=float(RecordedRange(0,359));
        }
        ++scriptCounterF02;
        if ((scriptCounterF02)>2) scriptCounterF02=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=300-g_ReimuRepeatSettingAt006714D0*20;
    }
    if ((animationStage)==4 && (animationFrame)==0) {
        Fighter::SpawnTrackedEffect(0x3B6,(*(&x))+g_ThresholdAt0065782C,
            (*(&y))+g_ReimuMeterTrailYAt0065835C,facing,1,0,1);
    }
    if ((animationStage)==12 && (animationFrame)==0 && (scriptCounterF00)<30) {
        ++scriptCounterF00;
        ResetSecondaryCounter(10);
    }
    if ((animationStage)==15 && (animationFrame)==0 && y==g_ThresholdAt0065782C) {
        ResetPrimaryCounters(10);
        break;
    }
    if ((animationStage)==16 && (animationFrame)==0) ResetSecondaryCounter(14);
    break;
}
