// Youmu action 0x2BD spawns object 0x346 before preparing the transition to
// 0x2C2. The transition copies the opponent's X position and returns early.
case 0x2BD: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        collisionResult=0;
        remainingHits=1;
        ClearMotionFields();
    }
    if ((animationStage)>8) {
        velocityX=(velocityX)-FloatConstants::OneDouble;
        if ((velocityX)<FloatConstants::Zero)
            velocityX=0.0f;
    }
    if ((animationStage)==7) {
        scaleX=(scaleX)+FloatConstants::OneFifth;
        scaleY=(scaleY)-FloatConstants::NineteenHundredths;
    }
    if ((animationStage)==9) {
        scaleX=(scaleX)-FloatConstants::OneFifth;
        scaleY=(scaleY)+FloatConstants::NineteenHundredths;
    }
    if ((scriptCounterF00)==0 && collisionResult!=0) {
        ++scriptCounterF00;
        if (collisionResult==1) {
            Fighter::SpawnTrackedEffect(0x346,x,
                (*(&y))+GeometryConstants::Hundred,
                (facing),1,0,1);
            PlaySound(0xD);
            ResetPrimaryCounters(0x2C2);
            ClearMotionFields();
            x=opponent->x;
            return;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        SetNonnegativeWord(0x28);
        PlaySharedSound(0x17);
        spellPower=(spellPower)-GeometryConstants::Hundred;
        SpawnAuxEffect(0x74,
            x-
                 float((facing)*64),
            (*(&y))+GeometryConstants::SeventySeven,
            (facing),1);
    }
    if ((animationStage)==7 && (animationFrame)==0) {
        PlaySound(0xB);
        ResetTransform(-200.0f,60.0f,0.0f);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
    }
    if ((animationStage)==10 && (animationFrame)==0) {
        scaleX=1.0f;
        scaleY=1.0f;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        ResetTransform(100.0f,60.0f,0.0f);
        scaleX=3.0f;
        scaleY=0.05f;
        velocityX=30.0f;
        UpdateGaugeTimer(0x1F4);
        SpawnAuxEffect(0x80,
            float((facing)*150)+(x),
            y,(facing),1);
    }
    return;
}
