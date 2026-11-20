// F1115: genuine original Japanese 0x386 game action at
// PE 0051B21D..0051B5AF, 914 native CODE B /195 ordered x86.
// One true state of ONE still-NONEXACT 81KB CharacterObject::Advance.
case 0x386: {
    if (x>g_F1057_RightBoundAt0065925C ||
        x<g_F1057_LeftBoundAt00659258 ||
        y>g_F1057_UpperBoundAt006583B4 ||
        y<g_F1057_LowerBoundAt00658374) {
        ClearFrameInfo();
        return;
    }
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field080=1;
        field07C=0;
        field0D8=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=3.0f;
        velocityY=0.0f;
    }
    if (animationStage==1) {
        scaleX=float(RecordedRange(0,4))*
            g_F1057_SpeedScaleAt006590B4+g_F1115_RandomDoubleAt006583B8;
        scaleY=scaleX;
        if (F1115_AbsFloatAt00412D90(x-
            owner->opponent->x)<g_F1115_DistanceAt0065786C) {
            velocityX=0.0f;
            scaleX=1.0f;
            scaleY=1.0f;
            owner->SetCameraShake(5.0f);
            ResetSecondaryCounter(2);
            return;
        }
    }
    x=float(facing)*velocityX+x;
    y=y+velocityY;
    if (AdvanceNestedFrame()==animationStageCount) {
        owner->SetCameraShake(10.0f);
        for (int shot=0;shot<12;++shot) {
            owner->SpawnBattleEffect(
                0x387,
                (*(&x))+g_F1069_ParentYSecondAt00658264-float(RecordedRange(0,80)),
                float(RecordedRange(0,320)),
                facing,1);
        }
        ClearFrameInfo();
        return;
    }
    if (animationStage==2 && animationFrame==0)
        ResetSecondaryCounter(1);
    return;
}
