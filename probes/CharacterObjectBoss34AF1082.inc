// F1082: original Japanese 005129C1..00512BA7, 486 native CODE B/102 x86.
// Real game action 0x34A inside ONE nonexact 81KB CharacterObject Advance.
case 0x34A: {
    x = owner->x;
    y=0.0f;
    field08A=1;
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=2.5f;
        scaleY=2.5f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field01A=0x4E2;
        rotationY=0.0f;
        rotationZ=0.0f;
        rotationX=-80.0f;
        owner->PlaySound(0x10);
    }
    if (animationStage==1) {
        // The original compares parent action +0x60 with 0x2C0, then
        // checks the parent's distinct +0x62 WORD against 0x2C0 and 6.
        // Do not collapse this to a simpler presumed stage condition.
        if (owner->action!=0x2C0 ||
            (owner->animationStage==0x2C0 &&
             owner->animationStage>6)) {
            ResetSecondaryCounter(2);
            return;
        }
    }
    if (animationStage==2) {
        if (color[0]>15)
            color[0]-=15;
        else {
            ClearFrameInfo();
            return;
        }
    }
    rotationZ=(rotationZ)+g_F1051_ScaleCeilingAt0065747C;
    if (AdvanceNestedFrame()==animationStageCount) {
        ClearFrameInfo();
        return;
    }
    return;
}
