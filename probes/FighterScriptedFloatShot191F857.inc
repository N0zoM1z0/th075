// F857 original 191 interior, 166B/53-x86/5 actual PE fields.
// True stage5 FILD facing*100 then FADD xAt44; Y member FLD then FADD global.
// Natural normal C++ still has real register and final-JMP byte mismatches.
case 0x191: {
    if (S16(0x62)==0 && S16(0x64)==0)
        I32(0x7C)=1;
    if (S16(0x62)==5 && S16(0x64)==0) {
        SpawnFloatXYAt453A70(0x321,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*100)+F32(0x44),
            (*(&POS48))+g_F857ShotYAt00659298,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(0);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    return;
}
