// F857 original 191 interior, 166B/53-x86/5 actual PE fields.
// True stage5 FILD facing*100 then FADD Actor::x; Y member FLD then FADD global.
// Natural normal C++ still has real register and final-JMP byte mismatches.
case 0x191: {
    if ((animationStage)==0 && (animationFrame)==0)
        field07C=1;
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnBattleEffect(0x321,
            float((facing)*100)+(x),
            (*(&y))+g_F857ShotYAt00659298,
            (facing),1);
        PlaySound(0);
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    return;
}
