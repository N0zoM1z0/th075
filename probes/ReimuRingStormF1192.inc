case 0x2DB: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0; reinterpret_cast<signed short&>(scriptCounterF02)=0; field07C=1;
        if (y==g_ThresholdAt0065782C) ResetAt453E20();
        else {
            velocityX=(velocityX)*g_ReimuAirDragAt00658348;
            velocityY=(*(&velocityY))*g_ReimuAirDragAt00658348;
        }
    }
    if (y>g_ThresholdAt0065782C) {
        if ((animationStage)<12) {
            velocityY=velocityY-g_ReimuStormFallAt00658044;
            if (y+velocityY<=g_ThresholdAt0065782C) velocityX=0.0f;
        } else {
            velocityY=velocityY-field05C;
            if (y+velocityY<=g_ThresholdAt0065782C && (animationStage)<16) {
                y=0.0f;
                ResetAt453E20();
                SetAuxActionAt40FB40(16);
                break;
            }
        }
    }
    if ((animationStage)==10 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<g_ReimuRepeatSettingAt006714D0*3+4) {
        PlaySoundAt453D40(6);
        field314=float(SelectRangeAt455580(0,359));
        if ((reinterpret_cast<signed short&>(scriptCounterF02))==0) {
            SpawnFloatXYAt453A70(0x384,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
            field314=float(SelectRangeAt455580(0,359));
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF02))==1) {
            SpawnFloatXYAt453A70(0x385,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
            field314=float(SelectRangeAt455580(0,359));
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF02))==2) {
            SpawnFloatXYAt453A70(0x386,float(facing*18)+(x),
                (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
            field314=float(SelectRangeAt455580(0,359));
        }
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        if ((reinterpret_cast<signed short&>(scriptCounterF02))>2) reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if (GetNativeActionAt40FA30()==(field070)) {
        SetNativeActionAt40FAC0(0);
        aiCardTimer=300-g_ReimuRepeatSettingAt006714D0*20;
    }
    if ((animationStage)==4 && (animationFrame)==0) {
        SpawnTrackedAt453B50(0x3B6,(*(&x))+g_ThresholdAt0065782C,
            (*(&y))+g_ReimuMeterTrailYAt0065835C,facing,1,0,1);
    }
    if ((animationStage)==12 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<30) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(10);
    }
    if ((animationStage)==15 && (animationFrame)==0 && y==g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        break;
    }
    if ((animationStage)==16 && (animationFrame)==0) SetAuxActionAt40FB40(14);
    break;
}
