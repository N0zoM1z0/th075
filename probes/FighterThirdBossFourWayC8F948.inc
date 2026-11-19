// F948 original pinned Japanese TH075 giant 004AC040 native action 0xC8
// (004B009E..004B02B9): 539 CODE B/149 original x86.
// This genuine natural source has 149 original mnemonic and GPR roles,
// but emits only 529B because the 82KB original saved-this (-0x64)
// and integer-to-x87 signed temporary (-0x94) do not yet have their
// native owner positions in the partial C++ parent (source -0x10/-0x40).
// Three physically wrong x86 widths are NOT to be hidden with padding,
// manual ASM, fake locals, or separate-case 'exact' credit.
case 0xC8: {
    field3AC=1;
    ConfigureStormAt454BC0(3,4,0xFF);
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if ((velocityX)>g_F948_C8UpperAt00657854) {
        velocityX=(velocityX)-g_F948_C8DragAt00658350;
        if ((velocityX)<g_F948_C8UpperAt00657854)
            velocityX=11.0f;
    }
    if (inputY<0) {
        if (static_cast<int>(facing)*inputX>0) {
            ResetPrimaryCounters(0xCD);
            break;
        }
        ResetPrimaryCounters(0xCC);
        break;
    }
    if ((reinterpret_cast<signed short&>(scriptCounterF00))>0 &&
        static_cast<int>(facing)*inputX<=0) {
        ResetPrimaryCounters(0xCF);
        break;
    }
    if (AdvanceNestedFrame()==(field070)) {
        if (static_cast<int>(facing)*inputX>0 &&
            (reinterpret_cast<signed short&>(scriptCounterF00))<2) {
            SetAuxActionAt40FB40(4);
            ++reinterpret_cast<signed short&>(scriptCounterF00);
            break;
        }
        ResetPrimaryCounters(0xCF);
        break;
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=14.5f;
        SpawnAt453C80(0x7D,
            float((facing)*80)+(x),
            (*(&y))+g_F948_C8VolleyYAt00658268,
            facing,1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_F948_C8VolleyYAt00658268,
            facing,1);
        PlaySharedSound(31);
    }
    break;
}
