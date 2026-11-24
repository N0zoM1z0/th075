// F951: genuine original Japanese TH075 004AC040 native action0xCB
// (004B0680..004B0852): 466 CODE B/131 original x86, 11 genuine PE fields.
// Natural C++ emits all 131 native mnemonic positions, but 79 GPR roles
// still differ. Two original signed-to-x87 scratch locals live at native
// EBP−0x9C/−0xA0; partial father emits EBP−0x48/−0x4C,
// giving 4 honest width errors and a 12-byte CODE deficit.
// The 82KB original fighter parent is still structurally incomplete
// and NONEXACT. No source-only case credit.
case 0xCB: {
    SetCommandSelection(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0;
        velocityX=0.0f;
        velocityY=0.0f;
        field05C=0.0f;
    }
    if (y>g_ThresholdAt0065782C && (animationStage)>0) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f;
            velocityY=0.0f;
            field05C=0.0f;
            y=0.0f;
            animationFrame=0;
            ResetPrimaryCounters(0xA);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(9);
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=-11.0f;
        velocityY=5.0f;
        field05C=0.6f;
        SpawnAuxEffect(0x7D,
            float((facing)*68)+(x),
            (*(&y))+g_F950_CAVolleyYAt00658400,
            -(facing),1);
        SpawnAuxEffect(0x7E,
            float((facing)*68)+(x),
            (*(&y))+g_F950_CAVolleyYAt00658400,
            -(facing),1);
        PlaySharedSound(31);
    }
    else if (animationStage == 3 && animationFrame != 0) {
        // Keep the launch motion on later frames.
    }
    break;
}
