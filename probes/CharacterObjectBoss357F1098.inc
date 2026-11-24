// F1098: genuine Japanese original 005159A0..00515C0E,
// 622 code bytes and 131 x86 instructions in PatchouliObject::Advance.
case 0x357: {
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<0x17) {
        ResetSecondaryCounter(0x17);
        return;
    }
    if (owner->action==0x189 && animationStage<0x17) {
        x=owner->x+
            float(facing*120);
        y=120.0f;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=0;
        field0DA=0;
    }
    if (field0D8==0) {
        if (scaleX<FloatConstants::One) {
            scaleX=(scaleX)+FloatConstants::OneTenth;
            scaleY=(scaleY)+FloatConstants::OneTenth;
            color[0]=unsigned char(color[0]+25);
        } else {
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
        }
        if (color[0]==0xFF && field0D8==0) {
            ++field0D8;
            field080=1;
        }
    }
    if (owner->field082==0 &&
        AdvanceNestedFrame()==animationStageCount) {
        ClearFrameInfo();
        return;
    } else if (animationStage < animationStageCount) {
        // Let the unfinished animation continue on the next tick.
    }
    return;
}
