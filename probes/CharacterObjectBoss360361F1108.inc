// F1108/F1109: five separate original Japanese native actions 0x360..0x364.
// Source is one genuine repeated game-logic family, instantiated at five
// distinct physical PE switch entries inside ONE NONEXACT 81KB callable.
// Original each 206 x86, but native CODE width is 952/952/951/964/964 B.
// NEXT_ID must retain 0x365/0x366/0x367/0x368/0x369 respectively.
case F1108_CASE: {
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<2) {
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
    if (animationStage==0 && animationFrame==0 &&
        field0D8==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field07C=0;
        field080=1;
        field0D8=15;
        SetNativeAngleBitsAt0040FB70(reinterpret_cast<unsigned int&>(field0C8),
            float(field0D8));
    }
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (animationStage==0) {
        SetNativeAngleBitsAt0040FB70(reinterpret_cast<unsigned int&>(field0C8),
            float(field0D8));
        --field0D8;
        if (field0D8<0)
            field0D8=0;
        rotationZ=(rotationZ)+g_F1068_ActionSpeedAt00657878;
    }
    if (x>g_F1101_RightAt00659424 ||
        x<g_F1076_LeftAt006595EC ||
        y>g_F1057_UpperBoundAt006583B4 ||
        y<g_F1076_LeftAt006595EC) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame()==field070) {
        reinterpret_cast<unsigned int&>(owner->field314)=reinterpret_cast<unsigned int&>(field0C8);
        reinterpret_cast<F1051Grandparent*>(owner)->SpawnObjectAt00453A70(
            F1108_NEXT_ID,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1);
        ClearFrameInfo();
    }
    return;
}
