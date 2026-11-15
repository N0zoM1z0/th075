// F1087: genuine original Japanese 0x34E game action, native
// 005136C8..00513B88 (1216 CODE B/263 x86) in ONE nonexact boss.
case 0x34E: {
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        if (field0D8!=140)
            field0D8=0;
    }
    SetPolarVelocity(
        float(owner->fieldF0C)+
            g_F1085_ParentMultiplierAt0065989C*static_cast<const float&>(field0C8),
        float(field0D8));
    x=velocityX+owner->x;
    y=(*(&velocityY))*g_F1085_ParentYMultiplierAt00657F74+
        owner->y+g_F1085_YOffsetAt0065835C;
    if (field0D8<140)
        field0D8=short(field0D8+5);
    else
        field0D8=140;
    if ((owner->opponent->health<=0 ||
        owner->health<=0 ||
        owner->field3A0<=0) &&
        animationStage<2)
        ResetSecondaryCounter(2);
    if (owner->action==0x2C1 &&
        owner->animationStage==2 &&
        animationStage<2)
        ResetSecondaryCounter(2);
    if (animationStage==0) {
        if ((owner->action==0x195 && owner->animationStage==4) ||
            (owner->action==0x1F4 && owner->animationStage==14) ||
            (owner->action==0x1F5 && owner->animationStage==14)) {
            for (int shot=0;shot<8;++shot) {
                owner->field314=float(shot*45);
                reinterpret_cast<F1051Grandparent*>(owner)->SpawnObjectAt00453A70(
                    0x362,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
                    owner->facing,1);
            }
            ResetSecondaryCounter(2);
            reinterpret_cast<F1051Grandparent*>(owner)->NativePrepareAt00453D40(4);
        }
    }
    if (animationStage>1) {
        if (color[0]>10)
            color[0]-=10;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if (animationStage==1 &&
        owner->action==0x2C1 &&
        owner->animationStage==3) {
        ResetSecondaryCounter(0);
        reinterpret_cast<F1051Grandparent*>(owner)->NativePrepareAt00453D40(20);
        return;
    }
    if (AdvanceNestedFrame()==field070) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==2 && animationFrame==0) {
        ResetSecondaryCounter(0);
        owner->field36C=(owner->field36C)-g_F1085_LastYAt006592A4;
        reinterpret_cast<F1051Grandparent*>(owner)->NativePrepareAt00453D40(20);
    }
    return;
}
