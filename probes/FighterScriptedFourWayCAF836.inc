// F836: actual Japanese TH075 005214B0 native interior CA.
// Native 418 B/121 x86/11 physical PE fields; direct enclosing-giant exits.
// Unlike another fighter, resets native motion slots, with stage2 sprite.
// Not independently callable original CODE.
case 0xCA: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        field05C=0.0f;
    }
    if (y>FloatConstants::Zero && (animationStage)>1) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=FloatConstants::Zero) {
            velocityX=0.0f;
            velocityY=0.0f;
            field05C=0.0f;
            y=0.0f;
            animationFrame=0;
            ResetPrimaryCounters(0xA);
            return;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
    if ((animationStage)==2 && (animationFrame)==0) {
        velocityX=10.0f;
        velocityY=5.0f;
        field05C=0.6f;
        SpawnAuxEffect(0x7D,float((facing)*80)+(x),
            (*(&y))+GeometryConstants::Hundred,
            (facing),1);
        SpawnAuxEffect(0x7E,x,
            (*(&y))+GeometryConstants::Hundred,
            (facing),1);
        PlaySharedSound(31);
    }
    return;
}
