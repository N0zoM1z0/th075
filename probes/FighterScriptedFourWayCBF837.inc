// F837 selected 005214B0 actor original interior CB: 496 B, 141 x86,
// 12 genuine original PE fields. Natural +F00 prefix signed-short ++
// and actual native source order recover all non-parent-JMP bytes.
// This is NOT an independently callable original game function.
case 0xCB: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        velocityX=0.0f;
        velocityY=0.0f;
        field05C=0.0f;
    }
    if (y>FloatConstants::Zero && (animationStage)>0) {
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
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==1 && (animationFrame)==0) {
        velocityX=-10.0f;
        velocityY=5.0f;
        field05C=0.6f;
        SpawnAuxEffect(0x7D,
            x-float((facing)*80),
            (*(&y))+g_ContactProjectionAt00657888,
            -(facing),1);
        SpawnAuxEffect(0x7E,x,
            (*(&y))+g_ContactProjectionAt00657888,
            -(facing),1);
        PlaySharedSound(31);
    }
    if ((animationStage)==3 && (scriptCounterF00)<1) {
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
    }
    return;
}
