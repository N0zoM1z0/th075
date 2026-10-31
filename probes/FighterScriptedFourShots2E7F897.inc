// F897: original 2E7..2EA four distinct physical 555B/167-x86 cases.
// Only stage9 sprite differs (0x38B/0x38C); native FILD scratch differs
// because each truly used float projectile has an independent source case.
// Whole 46,755B original father is NONEXACT. Do not credit split game CODE.
case F897_CASE: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=0;
        S16(0x80)=0x63;
        ResetAt453E20();
    }
    if (S16(0x62)==3 && S16(0x64)<30) {
        ++S16(0xF02);
        if (S16(0xF02)>4) {
            SpawnAt453C80(0x3E,
                reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-
                    float((*reinterpret_cast<signed char*>(RAW+0x66))*65),
                (*(&POS48))+g_F860ShotYAt006581DC,1,1);
            S16(0xF02)=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=RandomBoundaryAt455580(0,60)+60-
                      static_cast<int>(g_CloudOpponentAt006714D0);
        return;
    }
    if (S16(0x64)==0)
        I32(0x7C)=0;
    if (S16(0x62)==2 && S16(0x64)==0) {
        PrepareActionAt453D60(0x17);
        S16(0xF00)=static_cast<signed short>(F32(0x44));
        S16(0xF02)=static_cast<signed short>(F32(0x48));
        SpawnExtraRawYAt453B50(0x33D,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1,0,1);
    }
    if (S16(0x62)==9 && S16(0x64)==0) {
        SpawnExtraRawYAt453B50(F897_SECOND_SPRITE,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1,0,1);
        PrepareActionAt453D40(7);
    }
    if (S16(0x62)==11 && S16(0x64)==0) {
        InitTrajectoryAt453E60(10.0f);
        SpawnRawAt453C80(0x7F,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    return;
}
