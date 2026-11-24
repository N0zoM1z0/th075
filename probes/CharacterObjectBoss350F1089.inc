// F1089: original Japanese 0x350, native 00514048..00514537,
// 1263 CODE B /273 x86 inside ONE nonexact original 81KB boss.
case 0x350: {
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
    y=(*(&velocityY))*FloatConstants::Quarter+
        owner->y+GeometryConstants::TwoHundred;
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
        if ((owner->action==0x192 && owner->animationStage==4) ||
            (owner->action==0x260 && owner->animationStage==4) ||
            (owner->action==0x261 && owner->animationStage==4) ||
            (owner->action==0x262 && owner->animationStage==4)) {
            for (int shot=0;shot<8;++shot) {
                owner->field314=float(shot*45);
                owner->SpawnBattleEffect(
                    0x364,x,y,
                    owner->facing,1);
            }
            ResetSecondaryCounter(2);
            owner->PlaySound(4);
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
        owner->PlaySound(20);
        return;
    }
    if (AdvanceNestedFrame()==animationStageCount) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==2 && animationFrame==0) {
        ResetSecondaryCounter(0);
        owner->field36C=(owner->field36C)-GeometryConstants::TwentyFive;
        owner->PlaySound(20);
    }
    return;
}
