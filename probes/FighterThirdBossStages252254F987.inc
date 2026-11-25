// F987 original Japanese 004AC040 252/253/254, real native
 // physical 260B/72x86, 259B/72x86, 225B/63x86 respectively.
 // Source uses actual byte-prefix-decrement original MOV/SUB/MOV
 // (rather than incorrect MOVZX), gauge short side effects 252/253
 // and authentic stage6 shot 0x37 with opponent +0xEFA reset.
 // 254 has NO real afterRET DIR32 entry: source boundary via full
 // previous 253 instructions and real following 255 jump-table entry.
 // Native original 252/253 still have one AL/CL register-specific
 // x86 width mismatch each; 254 has zero mnemonic/width errors.
 // No internal exact credit, giant 82KB remains NONEXACT.
// F987 pinned native Japanese fighter 004AC040 real action 0x252.
case 0x252: {
    if ((animationStage)==0 && (animationFrame)==0) {
        --bombCount;
        ClearMotionFields();
                remainingHits=1;
        collisionResult=0;
        field3AC=0;
        scriptCounterF00=0;
    }
    if ((spiritCooldown)==0 && collisionResult==1)
        spirit=1000;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        SpawnAuxEffect(0x37,x,
            (*(&y))+GeometryConstants::Hundred,
            facing,1);
        PlaySharedSound(0x21);
        opponent->fieldEFA=0;
    }
    break;
}
// F987 pinned native Japanese fighter 004AC040 real action 0x253.
case 0x253: {
    if ((animationStage)==0 && (animationFrame)==0) {
        --bombCount;
        ClearMotionFields();
                remainingHits=1;
        collisionResult=0;
        field3AC=0;
        scriptCounterF00=0;
    }
    if ((spiritCooldown)==0 && collisionResult==1)
        spirit=1000;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        SpawnAuxEffect(0x37,x,
            (*(&y))+GeometryConstants::Hundred,
            facing,1);
        PlaySharedSound(0x21);
        opponent->fieldEFA=0;
    }
    break;
}
// F987 pinned native Japanese fighter 004AC040 real action 0x254.
case 0x254: {
    if ((animationStage)==0 && (animationFrame)==0) {
        --bombCount;
        ClearMotionFields();
                remainingHits=1;
        collisionResult=0;
        field3AC=0;
        scriptCounterF00=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetPrimaryCounters(0);
    if ((animationStage)==6 && (animationFrame)==0) {
        SpawnAuxEffect(0x37,x,
            (*(&y))+GeometryConstants::Hundred,
            facing,1);
        PlaySharedSound(0x21);
        opponent->fieldEFA=0;
    }
    break;
}
