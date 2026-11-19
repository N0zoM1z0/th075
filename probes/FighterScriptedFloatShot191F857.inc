// F857 original 191 interior, 166B/53-x86/5 actual PE fields.
// True stage5 FILD facing*100 then FADD xAt44; Y member FLD then FADD global.
// Natural normal C++ still has real register and final-JMP byte mismatches.
case 0x191: {
    if ((animationStage)==0 && (animationFrame)==0)
        field07C=1;
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnFloatXYAt453A70(0x321,
            float((facing)*100)+(x),
            (*(&y))+g_F857ShotYAt00659298,
            (facing),1);
        PlaySound(0);
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    return;
}
