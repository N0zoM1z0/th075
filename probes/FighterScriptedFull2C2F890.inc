// F890 original 2C2 entire 2274B/608 native x86 action with eight real unrolled F00 phases.
// Real stage8 reset/aux1 and stage9 borrowed owner X+motion, no artificial loops.
// All x87 temporary values flow to actually emitted native projectiles.
// Whole original fighter remains NONEXACT; internal state is NOT callable exact CODE.
case 0x2C2: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        I32(0x7C)=0;
        S16(0x80)=1;
        ResetAt453E20();
    }
    if (S16(0x62)>9) {
        POS54=POS54-g_F890GravityAt006581E0;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS48=0.0f;
            ResetAt453E20();
            SetNativeActionAt40FAC0(0x2C3);
            return;
        }
    }
    if (S16(0x62)==9 && S16(0xF02)==0) {
        ++S16(0xF02);
        SpawnWithFloatAt453A70(0x34C,
            I32(0x44),
            (*reinterpret_cast<float*>(OWNER+0x48))+g_ContactProjectionAt00657888,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(0xE);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetAuxActionAt40FB40(0x10);
    if (S16(0x62)<9 && S16(0x64)==0) {
        SpawnWithFloatAt453A70(0x34B,
            *reinterpret_cast<int*>(OWNER+0x44),
            (*reinterpret_cast<float*>(OWNER+0x48))+g_ContactProjectionAt00657888,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        if (S16(0xF00)==0) {
            F32(0x314)=0.0f;
            SpawnFloatXYAt453A70(0x34A,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-float(((*reinterpret_cast<signed char*>(RAW+0x66)))*100),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_F890Phase0YAt0065835C,
                (*reinterpret_cast<signed char*>(RAW+0x66)),1);
            SpawnWithFloatAt453A70(0x329,
                *reinterpret_cast<int*>(OWNER+0x44),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_F890Phase0AltYAt006591E4,
                -((*reinterpret_cast<signed char*>(RAW+0x66))),1);
        }
        if (S16(0xF00)==1) {
            F32(0x314)=0.0f;
            SpawnFloatXRawYAt453A70(0x34A,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44+float(((*reinterpret_cast<signed char*>(RAW+0x66)))*100),
                *reinterpret_cast<int*>(OWNER+0x48),
                -((*reinterpret_cast<signed char*>(RAW+0x66))),1);
            SpawnWithFloatAt453A70(0x329,
                *reinterpret_cast<int*>(OWNER+0x44),
                (*reinterpret_cast<float*>(OWNER+0x48))-g_F890Phase1LowYAt0065788C,
                -((*reinterpret_cast<signed char*>(RAW+0x66))),1);
        }
        if (S16(0xF00)==2) {
            F32(0x314)=90.0f;
            SpawnFloatXYAt453A70(0x34A,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44+float(((*reinterpret_cast<signed char*>(RAW+0x66)))*100),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_F890Phase0YAt0065835C,
                (*reinterpret_cast<signed char*>(RAW+0x66)),1);
            SpawnFloatXYAt453A70(0x329,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44+float(((*reinterpret_cast<signed char*>(RAW+0x66)))*150),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_ContactProjectionAt00657888,
                -((*reinterpret_cast<signed char*>(RAW+0x66))),1);
        }
        if (S16(0xF00)==3) {
            F32(0x314)=-90.0f;
            SpawnFloatXRawYAt453A70(0x34A,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-float(((*reinterpret_cast<signed char*>(RAW+0x66)))*100),
                *reinterpret_cast<int*>(OWNER+0x48),
                (*reinterpret_cast<signed char*>(RAW+0x66)),1);
            SpawnFloatXYAt453A70(0x329,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-float(((*reinterpret_cast<signed char*>(RAW+0x66)))*150),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_ContactProjectionAt00657888,
                -((*reinterpret_cast<signed char*>(RAW+0x66))),1);
        }
        if (S16(0xF00)==4) {
            F32(0x314)=45.0f;
            SpawnFloatXYAt453A70(0x34A,
                (*reinterpret_cast<float*>(OWNER+0x44))+g_ThresholdAt0065782C,
                (*reinterpret_cast<float*>(OWNER+0x48))+g_F890Phase4HiYAt00659420,
                (*reinterpret_cast<signed char*>(RAW+0x66)),1);
            SpawnFloatXYAt453A70(0x329,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44+float(((*reinterpret_cast<signed char*>(RAW+0x66)))*125),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_F890Phase4OtherYAt006598B4,
                -((*reinterpret_cast<signed char*>(RAW+0x66))),1);
        }
        if (S16(0xF00)==5) {
            F32(0x314)=-45.0f;
            SpawnFloatXYAt453A70(0x34A,
                (*reinterpret_cast<float*>(OWNER+0x44))+g_ThresholdAt0065782C,
                (*reinterpret_cast<float*>(OWNER+0x48))-g_F890Phase5YAt0065786C,
                -((*reinterpret_cast<signed char*>(RAW+0x66))),1);
            SpawnFloatXYAt453A70(0x329,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-float(((*reinterpret_cast<signed char*>(RAW+0x66)))*125),
                (*reinterpret_cast<float*>(OWNER+0x48))-g_ApproachUpperAt006592A4,
                (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        }
        if (S16(0xF00)==6) {
            F32(0x314)=45.0f;
            SpawnFloatXYAt453A70(0x34A,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44+float(((*reinterpret_cast<signed char*>(RAW+0x66)))*120),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_ContactProjectionAt00657888,
                -((*reinterpret_cast<signed char*>(RAW+0x66))),1);
            SpawnFloatXYAt453A70(0x329,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44+float(((*reinterpret_cast<signed char*>(RAW+0x66)))*125),
                (*reinterpret_cast<float*>(OWNER+0x48))-g_ApproachUpperAt006592A4,
                (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        }
        if (S16(0xF00)==7) {
            F32(0x314)=-45.0f;
            SpawnFloatXYAt453A70(0x34A,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-float(((*reinterpret_cast<signed char*>(RAW+0x66)))*120),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_ContactProjectionAt00657888,
                (*reinterpret_cast<signed char*>(RAW+0x66)),1);
            SpawnFloatXYAt453A70(0x329,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-float(((*reinterpret_cast<signed char*>(RAW+0x66)))*125),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_F890Phase4OtherYAt006598B4,
                -((*reinterpret_cast<signed char*>(RAW+0x66))),1);
        }
        ++S16(0xF00);
        if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF04)==0) {
            S16(0xF00)=1;
            ++S16(0xF04);
            SetAuxActionAt40FB40(1);
            F32(0x314)=0.0f;
            SpawnFloatXYAt453A70(0x34A,
                reinterpret_cast<FighterBorrowedXViewF833*>(OWNER)->xAt44-float(((*reinterpret_cast<signed char*>(RAW+0x66)))*100),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_F890Phase0YAt0065835C,
                (*reinterpret_cast<signed char*>(RAW+0x66)),1);
            SpawnWithFloatAt453A70(0x329,
                *reinterpret_cast<int*>(OWNER+0x44),
                (*reinterpret_cast<float*>(OWNER+0x48))+g_F890Phase0AltYAt006591E4,
                -((*reinterpret_cast<signed char*>(RAW+0x66))),1);
        }
    }
    if (S16(0x62)==9 && S16(0x64)==0) {
        SetFloatMotionAt40FBB0(0.0f,0.0f,0);
        I32(0x44)=*reinterpret_cast<int*>(OWNER+0x44);
        I32(0x48)=0;
        POS=0.0f;
        POS54=50.0f;
    }
    return;
}
