// F834 physical original 005214B0 interior action 0xC8,
 // 657 CODE B /190 x86 and 17 actual typed PE/global fields.
 // Prefix ++ on the real +0xF00 signed short naturally emits
 // original MOV CX/ADD CX,1 instead of MOVSX ECX/ADD ECX,1.
 // All 7 direct returns target the enclosing full fighter epilogue.
 // This is NOT independently callable original exact CODE.
case 0xC8: {
    SetCommandSelection(3,4,0xFF);
    field3AC=1;
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f;
        scriptCounterF00=0;
    }
    if ((velocityX)>GeometryConstants::Fifteen) {
        velocityX=(velocityX)-FloatConstants::Half;
        if ((velocityX)<g_F834_LowerAt006590B0)
            velocityX=9.0f;
    }
    if (inputY<0) {
        if ((facing)*inputX>0) {
            ResetPrimaryCounters(0xCD);
            return;
        }
        ResetPrimaryCounters(0xCC);
        return;
    }
    if ((scriptCounterF00)>0 || (animationStage)>5) {
        if ((facing)*inputX<=0) {
            ResetPrimaryCounters(0xCF);
            return;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        if ((facing)*inputX>0) {
            if ((scriptCounterF00)<1) {
                ResetSecondaryCounter(2);
                ++scriptCounterF00;
                return;
            }
        }
        ResetPrimaryCounters(0xCF);
        return;
    }
    if ((animationFrame)==0 &&
            (facing)*inputX<=0 &&
            (scriptCounterF00)>0) {
        ResetPrimaryCounters(0xCF);
        return;
    }
    if ((animationStage)==2 && (animationFrame)==0) {
        velocityX=11.5f;
        SpawnAuxEffect(0x7D,
            float((facing)*80)+(x),
            (*(&y))+GeometryConstants::Eighty,
            (facing),1);
        SpawnAuxEffect(0x7E,x,
            (*(&y))+GeometryConstants::Eighty,
            (facing),1);
    }
    if ((animationStage)==4 && (animationFrame)==0)
        PlaySound(15);
    if ((animationStage)==8 && (animationFrame)==0)
        PlaySound(16);
    return;
}
