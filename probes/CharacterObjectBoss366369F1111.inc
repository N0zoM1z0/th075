// F1111: authentic Japanese 0x366..0x369, each 2,214 original CODE B
// /452 x86 in the ONE still-NONEXACT 81KB CharacterObject boss.
// Four native distinct physical game cases, with original spawned IDs
// 0x33E/0x340/0x342/0x344. Original 0x365 source is tracked separately.
case F1111_CASE: {
    if (x>g_F1057_RightBoundAt0065925C ||
        x<g_F1057_LeftBoundAt00659258 ||
        y>g_F1057_UpperBoundAt006583B4 ||
        y<g_F1057_LowerBoundAt00658374) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<2) {
        ClearFrameInfo();
        for (int shot=0;shot<2;++shot)
            owner->SpawnBattleEffect(
                0x3E4,x,y,1,1);
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            owner->SpawnBattleEffect(
                0x3E3,x,y,1,1);
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
        field0DC=0;
    }
    if (animationStage>0) {
        field0D8=short(field0D8+2);
        field0DA=short(F1057_FloatAtan2At00483300(
            (owner->opponent->y-y)+g_F1057_YOffsetAt00657888,
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
        // The native PE independently checks the mutated +DC angle again.
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
    if (animationStage<=1) {
        SetPolarVelocity(float(field0DC),
            float(field0D8)*g_F1110_NativeSpeedAt006578C0+g_F1110_NativeBaseAt00657CF8);
        owner->SpawnBattleEffect(
            F1111_NEXT_ACTION,x,y,
            facing,1);
        scaleX=float(double(RandomBoundaryAt00455580(0,4)-2)*
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
