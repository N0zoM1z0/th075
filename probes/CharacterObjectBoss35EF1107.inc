// F1107 native original Japanese 0x35E at 00516646..00516CE4:
// 1694 original CODE B/350 x86 inside ONE still-NONEXACT 81KB Boss.
case 0x35E: {
    if (x>g_F1057_RightBoundAt0065925C ||
        x<g_F1057_LeftBoundAt00659258 ||
        y>g_F1057_UpperBoundAt006583B4 ||
        y<g_F1057_LowerBoundAt00658374) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96) {
        ClearFrameInfo();
        for (int shot=0;shot<2;++shot)
            reinterpret_cast<F1051Grandparent*>(owner)->SpawnObjectAt00453A70(
                0x3E4,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            reinterpret_cast<F1051Grandparent*>(owner)->SpawnObjectAt00453A70(
                0x3E3,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        return;
    }
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field080=1;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=60;
        field0DA=0;
        field0DE=0;
        field0DC=short(field0C8);
        rotationZ=F1057_FloatAtan2At00483300(
            velocityY,velocityX)/g_F1057_AngleDivAt00657828;
        SetPolarVelocity(float(field0DC),
            float(field0D8)*g_F1057_SpeedScaleAt006590B4);
    }
    if (animationStage>0) {
        if (field080==0) {
            ClearFrameInfo();
            owner->PlaySound(1);
            reinterpret_cast<F1051Grandparent*>(owner)->SpawnObjectAt00453A70(
                0x35F,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
                facing,1);
            return;
        }
        field0D8=short(field0D8+2);
        rotationZ=F1057_FloatAtan2At00483300(
            velocityY,velocityX)/g_F1057_AngleDivAt00657828;
        field0DA=short(F1057_FloatAtan2At00483300(
            owner->opponent->y-y+g_F1057_YOffsetAt00657888,
            (owner->opponent->x-x)*int(facing)) /
            g_F1057_AngleDivAt00657828);
        if (field0DC>field0DA) {
            if (field0DC-field0DA<=180) {
                field0DC=short(field0DC-2);
                if (field0DC<-180)
                    field0DC=short(field0DC+360);
            } else {
                field0DC=short(field0DC+2);
                if (field0DC>180)
                    field0DC=short(field0DC-360);
            }
        }
        // Original PE independently checks the UPDATED angle against the
        // target after the greater-than case, not an exclusive else.
        if (field0DC<=field0DA) {
            if (field0DC-field0DA>=-180) {
                field0DC=short(field0DC+2);
                if (field0DC>180)
                    field0DC=short(field0DC-360);
            } else {
                field0DC=short(field0DC-2);
                if (field0DC<-180)
                    field0DC=short(field0DC+360);
            }
        }
    }
    SetPolarVelocity(float(field0DC),
        float(field0D8)*g_F1057_SpeedScaleAt006590B4);
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (AdvanceNestedFrame()==field070)
        ResetSecondaryCounter(1);
    return;
}
