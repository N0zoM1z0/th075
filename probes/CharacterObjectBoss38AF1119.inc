// F1119: real original TH075 game action 0x38A at PE
// 0051BFE2..0051C3ED, 1035 native CODE B/226 x86. Whole 81KB NONEXACT.
case 0x38A: {
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field080=1;
        field07C=0;
        field0D8=0;
        scaleX=0.0f;
        scaleY=0.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=0.0f;
        velocityY=0.0f;
    }
    if (animationStage<6) {
        scaleX=(scaleX)+g_F1051_ScaleStepAt00658348;
        scaleY=(scaleY)+g_F1051_ScaleStepAt00658348;
        if (scaleX>g_F1051_ScaleCeilingAt0065747C)
            scaleX=2.0f;
        if (scaleY>g_F1051_ScaleCeilingAt0065747C)
            scaleY=2.0f;
    }
    if (animationStage>5) {
        if (y+velocityY<=g_F1044_GroundAt0065782C) {
            y=0.0f;
            velocityY=0.0f;
            velocityX=0.0f;
            owner->PlaySound(11);
            ResetPrimaryCounters(0x385);
            reinterpret_cast<F1051Grandparent*>(owner)->SpawnObjectAt00453A70(
                0x347,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),facing,1);
            int shot;
            for (shot=0;shot<15;++shot)
                reinterpret_cast<F1051Grandparent*>(owner)->SpawnObjectAt00453A70(
                    0x33A,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),facing,1);
            for (shot=0;shot<15;++shot)
                reinterpret_cast<F1051Grandparent*>(owner)->SpawnObjectAt00453A70(
                    0x389,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),facing,1);
            reinterpret_cast<FighterShake453E60*>(owner)->SetCameraShake(5.0f);
            return;
        }
    }
    if (owner->animationStage==9 && animationStage<6) {
        ResetSecondaryCounter(animationStage+5);
        velocityX=float(RandomBoundaryAt00455580(0,30)+10);
        velocityY=-20.0f;
    }
    x=float(facing)*velocityX+x;
    y=y+velocityY;
    if (AdvanceNestedFrame()==field070) {
        ResetSecondaryCounter(6);
        return;
    }
    if (animationStage==6 && animationFrame==0)
        ResetSecondaryCounter(1);
    return;
}
