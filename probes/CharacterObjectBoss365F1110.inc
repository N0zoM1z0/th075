// F1110: actual original game action 0x365 at 00517FBF..00518865:
// 2214 native CODE B /452 x86. This is ONE inner case of a still
// NONEXACT single 81KB original CharacterObject Advance callable.
case 0x365: {
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        F1024_PHASE(this).stageAt62<2) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<2;++shot)
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        return;
    }
    if (field07C==5) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
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
    if (F1024_PHASE(this).stageAt62>0) {
        field0D8=short(field0D8+2);
        field0DA=short(F1057_FloatAtan2At00483300(
            F1037_POSITION(PARENT_GRANDPARENT).yPosition-F1037_POSITION(this).yPosition+g_F1057_YOffsetAt00657888,
            (F1037_POSITION(PARENT_GRANDPARENT).xPosition-F1037_POSITION(this).xPosition)*int(facing)) /
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
    if (F1024_PHASE(this).stageAt62<=1) {
        SetNativeTwoFloatsAt0040FB70(
            float(field0DC),
            float(field0D8)*g_F1110_NativeSpeedAt006578C0+g_F1110_NativeBaseAt00657CF8);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x33C,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1);
        scaleX=float(double(RandomBoundaryAt00455580(0,4)-2)*
            g_F1057_RandomDoubleAt00658A20+g_F1057_RandomBaseAt00657D00);
        reinterpret_cast<unsigned int&>(scaleY)=reinterpret_cast<unsigned int&>(scaleX);
    }
    field0D8=short(field0D8+2);
    if (F1024_PHASE(this).stageAt62>0 && field0DA<60) {
        if ((*(&F1037_POSITION(PARENT_GRANDPARENT).yPosition))+g_F1057_YOffsetAt00657888<F1037_POSITION(this).yPosition)
            field0C8=(field0C8)+g_F1057_NudgeAt00657480;
        if ((*(&F1037_POSITION(PARENT_GRANDPARENT).yPosition))+g_F1057_YOffsetAt00657888>F1037_POSITION(this).yPosition)
            field0C8=(field0C8)-g_F1057_NudgeAt00657480;
        ++field0DA;
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (field07C!=0 && field07C!=6 && F1024_PHASE(this).stageAt62==1) {
        if (field080==0 || field07C!=4) {
            F1037_MOTION(this).xMotion=0.0f;
            F1037_MOTION(this).yMotion=0.0f;
            SetAuxActionAt0040FB40(2);
            scaleX=2.5f;
            scaleY=2.5f;
            return;
        }
        if (field080>0 && field07C==4 && field080>0)
            field07C=0;
    }
    if (F1024_PHASE(this).stageAt62>1) {
        scaleX=(scaleX)*g_F1055_FadeScaleAt006598A4;
        scaleY=(scaleY)*g_F1055_FadeScaleAt006598A4;
        if (color[0]>=25)
            color[0]-=25;
        else {
            color[0]=0;
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==field070)
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    return;
}
