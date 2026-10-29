// F614: physical original complete native action0x58 inside giant fighter
// Advance(), including actual ten-projectile burst and optional guarded
// stage-one shot. NOT independent game function or exact whole CODE credit.
case 0x58: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS = -F32(0x94);
        I32(0x54) = I32(0x98);
        POS5C = 0.8f;
        I32(0x7C) = 0;
    }
    if (POS54 + POS48 <= g_ThresholdAt0065782C) {
        I16(F614_COUNTER)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        I16(F614_COUNTER+2)=static_cast<short>((POS54)*g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48 = 0.0f;
        SetNativeActionAt40FAC0(0x59);
        InitTrajectoryAt453E60(3.0f);
        PrepareActionAt453D60(0x16);
        for (int burst=0;burst<10;++burst)
            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
        if (I16(0xEFA)>25) {
            I16(0xEFA)=0;
            SpawnDirectedAt453A70(0x3E3,I32(0x44),I32(0x48),1,1);
        }
        break;
    }
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetAuxActionAt40FB40(I16(0x62)-1);
    if (I16(0x62)==1 && I16(0x64)==0) {
#if F614_STAGE1_SPAWN
        if (I16(0xF0C)==0) {
            I16(0xF0C)=1;
            SpawnDirectedAt453A70(F614_PROJECTILE,I32(0x44),I32(0x48),
                *reinterpret_cast<signed char*>(RAW+0x66),F614_SIDE);
        }
#endif
        if (POS54 != g_ThresholdAt0065782C) {
            if (*(&POS)==g_ThresholdAt0065782C) {
                SetAuxActionAt40FB40(3);
                break;
            } else {
                SetAuxActionAt40FB40(2);
                break;
            }
        }
    }
    break;
}
