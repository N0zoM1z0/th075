// F1057: each of 33B/33D/33F/341/343 is 1908 ORIGINAL CODE B /402 x86
// in the ONE nonexact 0050A580 original CharacterObject Advance.
// Original PE proves the five share opcode, width, GPR, field/call policy.
// Only physical native stack scratch owners differ per independent case,
// and the native next-state sprite IDs are 33C/33E/340/342/344.
// The C++ source declares real per-case values; no fake locals/ASM.
// Original actor X/Y, target grandparent X/Y and actual native game calls.
case F1057_CASE: {
    if (x>g_F1057_RightBoundAt0065925C ||
        x<g_F1057_LeftBoundAt00659258 ||
        y>g_F1057_UpperBoundAt006583B4 ||
        y<g_F1057_LowerBoundAt00658374) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>49 &&
        owner->action<150 &&
        animationStage<2) {
        ClearFrameInfo();
        for (int shot=0;shot<3;++shot) {
            owner->SpawnBattleEffect(
                0x3E4, x,y,1,1);
        }
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            owner->SpawnBattleEffect(
                0x3E3, x,y,1,1);
        }
        return;
    }
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0,0);
        field080=3;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=10;
        field0DA=0;
        field0DE=0;
        field0DC=short(field0C8);
    }
    if (animationStage<=1) {
        field0DA=short(F1057_FloatAtan2At00483300(
            (owner->opponent->y-y)+g_F1057_YOffsetAt00657888,
            (owner->opponent->x-x)*float(facing)) /
            g_F1057_AngleDivAt00657828);
        if (field0DA>field0DC+10)
            field0DC=short(field0DC+1);
        if (field0DA<field0DC-10)
            field0DC=short(field0DC-1);
        if (field0DC>90)
            field0DC=90;
        if (field0DC<-90)
            field0DC=-90;
    }
    if (animationStage<=1) {
        SetPolarVelocity(
            float(field0DC),
            float(field0D8)*g_F1057_SpeedScaleAt006590B4+g_F1057_SpeedBaseAt00657CBC);
        owner->SpawnBattleEffect(
            F1057_NEXT_CASE, x,y,
            facing,1);
        scaleX=float(double(RecordedRange(0,4)-2)*
            g_F1057_RandomDoubleAt00658A20+g_F1057_RandomBaseAt00657D00);
        reinterpret_cast<unsigned int&>(scaleY)=reinterpret_cast<unsigned int&>(scaleX);
    }
    field0D8=short(field0D8+2);
    if (animationStage>0 && field0DA<60) {
        if ((*(&owner->opponent->y))+g_F1057_YOffsetAt00657888<y)
            field0C8=(field0C8)+g_F1057_NudgeAt00657480;
        if ((*(&owner->opponent->y))+g_F1057_YOffsetAt00657888>y)
            field0C8=(field0C8)-g_F1057_NudgeAt00657480;
        ++field0DA;
    }
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (field07C!=0 && field07C!=6 && animationStage==1) {
        if (field080==0 || field07C!=4) {
            velocityX=0.0f;
            velocityY=0.0f;
            ResetSecondaryCounter(2);
            scaleX=2.5f;
            scaleY=2.5f;
            return;
        }
        if (field080>0 && field07C==4 && field080>0)
            field07C=0;
    }
    if (animationStage>1) {
        scaleX=(scaleX)*g_F1055_FadeScaleAt006598A4;
        scaleY=(scaleY)*g_F1055_FadeScaleAt006598A4;
        if (color[0]>=25)
            color[0]-=25;
        else {
            color[0]=0;
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    if (animationStage==2 && animationFrame==0)
        ResetSecondaryCounter(1);
    return;
}
