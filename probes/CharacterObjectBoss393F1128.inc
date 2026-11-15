// F1128 original Japanese action 0x393 at PE
// 0051D4F1..0051D70F: 542 native CODE B /110 x86, same NONEXACT boss.
case 0x393: {
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0.0f,0);
        field0D8=0;
        field0DA=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field080=1;
        field07C=0;
    }
    if (AdvanceNestedFrame()==field070) {
        if (field0D8<2-int(g_F1113_DifficultyAt006714D0))
            ++field0D8;
        else if (field0DA==0) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x391,0.0f,float(RandomBoundaryAt00455580(0,60)+380),1,1);
            field0DA=1;
            field0D8=0;
        } else {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x391,1280.0f,float(RandomBoundaryAt00455580(0,120)+240),-1,1);
            field0DA=0;
            field0D8=0;
        }
        ResetSecondaryCounter(1);
    }
    return;
}
