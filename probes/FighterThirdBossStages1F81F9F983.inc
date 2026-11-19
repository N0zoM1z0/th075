// F983 authentic Japanese TH075 fighter 004AC040 actions1F8/1F9.
 // Native original 1F8=1168B/339 x86 and 1F9=1167B/339 x86,
 // 28 true original PE external fields each. Typed borrowed float
 // world X at +0x44 yields genuine original IMUL/FILD/FSUBR
 // (six chains per action). Twelve original source FISUB/mnemonic
 // chains are eliminated without fake locals or byte grafting.
 // Original one CMP ECX/EAX,0xEB 6B/5B width per case still
 // differs (case-local ordinal64), with native GPR-role debts;
 // entire 82KB whole callable remains NONEXACT, not case exact.
// F983 natural source probe for real original 004AC040 1F8
case 0x1F8: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((animationStage)==6 || (animationStage)==7) {
        if ((color[0])>30)
            color[0]=(color[0])-30;
        else {
            color[0]=0;
            ResetSecondaryCounter(8);
            velocityX=60.0f;
            velocityY=10.0f;
            field05C=0.4f;
            break;
        }
    }
    if ((animationStage)==9 || (animationStage)==10) {
        velocityY=velocityY-field05C;
        if ((color[0])<235)
            color[0]=(color[0])+20;
        else
            color[0]=255;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            color[0]=255;
            ClearMotionFields();
            ResetSecondaryCounter(0xB);
            y=0.0f;
            break;
        }
    }
    if ((animationStage)<8 && (animationStage)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+(x)-g_F983_XOffsetAt00658264,
            ((*(&y))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if ((animationStage)==9 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        PlaySound(2);
        SpawnSevenFloatAt453B50(0x338,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x339,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33A,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33B,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33C,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33D,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SetMotionStateAt40FBB0(0,0.0f,0);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<4) {
        ResetSecondaryCounter(6);
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        break;
    }
    if ((animationStage)==11 && (animationFrame)==0)
        ResetSecondaryCounter(9);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
case 0x1F9: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((animationStage)==6 || (animationStage)==7) {
        if ((color[0])>30)
            color[0]=(color[0])-30;
        else {
            color[0]=0;
            ResetSecondaryCounter(8);
            velocityX=-60.0f;
            velocityY=10.0f;
            field05C=0.4f;
            break;
        }
    }
    if ((animationStage)==9 || (animationStage)==10) {
        velocityY=velocityY-field05C;
        if ((color[0])<235)
            color[0]=(color[0])+20;
        else
            color[0]=255;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            color[0]=255;
            ClearMotionFields();
            ResetSecondaryCounter(0xB);
            y=0.0f;
            break;
        }
    }
    if ((animationStage)<8 && (animationStage)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+(x)-g_F983_XOffsetAt00658264,
            ((*(&y))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if ((animationStage)==9 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        PlaySound(2);
        SpawnSevenFloatAt453B50(0x338,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x339,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33A,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33B,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33C,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33D,
            x-float((facing)*7),
            (*(&y))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SetMotionStateAt40FBB0(0,0.0f,0);
        color[0]=255;
    }
    if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<4) {
        ResetSecondaryCounter(6);
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        break;
    }
    if ((animationStage)==11 && (animationFrame)==0)
        ResetSecondaryCounter(9);
    break;
}
