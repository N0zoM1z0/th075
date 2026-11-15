// F857 original 191 interior, 166B/53-x86/5 actual PE fields.
// True stage5 FILD facing*100 then FADD xAt44; Y member FLD then FADD global.
// Natural normal C++ still has real register and final-JMP byte mismatches.
case 0x191: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0)
        field07C=1;
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnFloatXYAt453A70(0x321,
            float((facing)*100)+(x),
            (*(&y))+g_F857ShotYAt00659298,
            (facing),1);
        PrepareActionAt453D40(0);
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    return;
}
