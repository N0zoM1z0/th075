// F1051: native original 0050A80F..0050AC27 (1048B/229 x86), ONE case
// inside the nonexact 81KB original CharacterObject::Advance.
// Parent +0xE4, target grandparent +0x2E8 are borrowed, not embedded owners.
case 0x321: {
    if (owner->action != 0x2BC) {
        ClearFrameInfo();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0,0);
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
    if (F1024_PHASE(this).stageAt62<6) {
        scaleX=(scaleX)+g_F1051_ScaleStepAt00658348;
        scaleY=(scaleY)+g_F1051_ScaleStepAt00658348;
        if (scaleX>g_F1051_ScaleCeilingAt0065747C)
            scaleX=2.0f;
        if (scaleY>g_F1051_ScaleCeilingAt0065747C)
            scaleY=2.0f;
    }
    if (F1024_PHASE(this).stageAt62>5 &&
        F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion <= g_F1044_GroundAt0065782C) {
        y=0.0f;
        velocityY=0.0f;
        velocityX=0.0f;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(0xB);
        ResetPrimaryCounters(0x322);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x347, reinterpret_cast<unsigned int&>(x), reinterpret_cast<unsigned int&>(y),
            facing, 1);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnProjectileAt00453C80(
            0x7F, reinterpret_cast<unsigned int&>(x), 0,
            facing, 1);
        for (int shot=0; shot<20; ++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x33A, reinterpret_cast<unsigned int&>(x), reinterpret_cast<unsigned int&>(y),
                facing, 1);
        }
        reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(10.0f);
        return;
    }
    if (owner->animationStage==9 && F1024_PHASE(this).stageAt62<6) {
        ResetSecondaryCounter(F1024_PHASE(this).stageAt62+5);
        velocityX=
            float(facing) *
            (F1037_POSITION(PARENT_GRANDPARENT).xPosition-F1037_POSITION(this).xPosition) /
            g_F1051_TrajectoryUpperAt006590C4;
        if (velocityX<g_F1051_TrajectoryLowerAt00658290)
            velocityX=6.0f;
        velocityY=-24.0f;
    }
    F1037_POSITION(this).xPosition=float(facing)*velocityX+
        F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+
        F1037_MOTION(this).yMotion;
    if (AdvanceNestedFrame()==field070) {
        ResetSecondaryCounter(6);
        return;
    }
    if (F1024_PHASE(this).stageAt62==6 && F1024_PHASE(this).frameAt64==0)
        ResetSecondaryCounter(1);
    return;
}
