// F759 real original game action 0xC8..0xCB, all under the same 00543210 giant.
// These are switch-case interiors, not individually accepted callable CODE.
case 0xC8: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (y>g_ThresholdAt0065782C && (animationStage)<7) {
        velocityY=velocityY-g_F759_C8DecelAt006593E8;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            y=0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(7);
            break;
        }
    }
    if ((animationStage)==7 && inputY<0) {
        if ((facing)*inputX>0) {
            ResetPrimaryCounters(0xCD);
            break;
        }
        ResetPrimaryCounters(0xCC);
        break;
    }
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        break;
    }
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityX=15.0f;
        velocityY=25.0f;
        field05C=2.5f;
        SpawnAt453C80(0x7D,float((facing)*80)+(x),
            (*(&y))+g_F701_VolleyYAt00658268,(facing),1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_F701_VolleyYAt00658268,(facing),1);
        SpawnRawXYAt453C80(0x81,reinterpret_cast<int&>(x),0,(facing),0);
        PlaySharedSound(31);
    }
    break;
}
case 0xC9: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (y>g_ThresholdAt0065782C && (animationStage)<6) {
        velocityY=velocityY-g_F759_C9DecelAt00658290;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            y=0.0f;
            ClearMotionFields();
            ResetSecondaryCounter(6);
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        break;
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=-25.0f;
        velocityY=40.0f;
        field05C=6.0f;
        SpawnAt453C80(0x7D,reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44-float((facing)*80),
            (*(&y))+g_F701_VolleyYAt00658268,-(facing),1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_F701_VolleyYAt00658268,-(facing),1);
        SpawnRawXYAt453C80(0x81,reinterpret_cast<int&>(x),0,-(facing),0);
        PlaySharedSound(31);
    }
    break;
}
case 0xCA: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) ClearMotionFields();
    if (y>g_ThresholdAt0065782C && (animationStage)>5) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f;
            velocityY=0.0f;
            field05C=0.0f;
            y=0.0f;
            animationFrame=0;
            ResetPrimaryCounters(0xA);
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(9);
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityX=30.0f;
        velocityY=-4.0f;
        field05C=0.6f;
        SpawnAt453C80(0x7D,float((facing)*80)+(x),
            (*(&y))+g_ContactProjectionAt00657888,(facing),1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,(facing),1);
        PlaySharedSound(31);
    }
    if ((animationStage)==6 && (animationFrame)==0) {
        velocityX=10.0f;
        velocityY=-4.0f;
    }
    break;
}
case 0xCB: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) ClearMotionFields();
    if (y>g_ThresholdAt0065782C && (animationStage)>4) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f;
            velocityY=0.0f;
            field05C=0.0f;
            y=0.0f;
            animationFrame=0;
            ResetPrimaryCounters(0xA);
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(9);
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=-30.0f;
        velocityY=2.0f;
        field05C=0.6f;
        SpawnAt453C80(0x7D,reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44-float((facing)*80),
            (*(&y))+g_ContactProjectionAt00657888,-(facing),1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,-(facing),1);
        PlaySharedSound(31);
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        velocityX=-10.0f;
        velocityY=2.0f;
    }
    break;
}
