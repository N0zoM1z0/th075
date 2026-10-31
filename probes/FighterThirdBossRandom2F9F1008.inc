// F1008 pinned original Japanese 004AC040 2F9:
 // 1254 native CODEB /326x86 /33 real PE targets.
 // True random sprites0x38B and 7-arg sprite0x38A
 // gated by signed global mode006714D0, physical
 // two center-X globals006593D0/00658370 and
 // native F06>50 boolean offsets. Native stage5
 // opponent motion/F10, stage11/13 bounded aux.
 // Full-partial natural VC7.1 parent aligns all
 // 326 native mnemonics/width/GPR roles. Genuine
 // preceding 2F9 restores next 2FA GPR phase
 // from 113 wrong -> ZERO; whole giant NONEXACT.
// F1008 true original Japanese 004AC040 case 2F9
case 0x2F9: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=static_cast<short>(RandAt455580(0,3));
        S16(0xF06)=static_cast<short>(RandAt455580(0,100));
        I32(0x7C)=0;
        ResetAt453E20();
        S16(0x80)=99;
    }
    if (S16(0x64)==0 && (S16(0x62)==9 || S16(0x62)==10)) {
        SpawnFloatXYAt453A70(0x38B,
            F32(0x44)+g_F1008_CenterXAt006593D0
                - float(RandAt455580(0,480)),
            float(RandAt455580(0,200)+(S16(0xF06)>50)*200),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        if (g_F1004_ModeAt006714D0>0)
            SpawnFloatXYAt453A70(0x38B,
                F32(0x44)+g_F1008_AlternateXAt00658370
                    - float(RandAt455580(0,560)),
                float(RandAt455580(0,250)+(S16(0xF06)>50)*250),
                *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    if (S16(0x62)==9 && S16(0x64)==0 && g_F1004_ModeAt006714D0>1)
        SpawnSevenFloatAt453B50(0x38A,
            F32(0x44)+g_F1008_CenterXAt006593D0
                - float(RandAt455580(0,480)),
            float(RandAt455580(0,200)+(S16(0xF06)>50)*200),
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
    if (S16(0x62)==10 && S16(0x64)==0 && g_F1004_ModeAt006714D0>2)
        SpawnSevenFloatAt453B50(0x38A,
            F32(0x44)+g_F1008_AlternateXAt00658370
                - float(RandAt455580(0,560)),
            float(RandAt455580(0,250)+(S16(0xF06)>50)*250),
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=static_cast<short>(180-g_F1004_ModeAt006714D0*20);
    }
    if (S16(0x62)==5 && S16(0x64)==0) {
        if (S16(0xF02)<3) {
            ++S16(0xF02);
            SetAuxActionAt40FB40(3);
            break;
        }
        PrepareActionAt453D40(9);
        ApplyAt453E80(75);
        PrepareActionAt453D60(23);
        SpawnSevenFloatAt453B50(0x330,640.0f,320.0f,1,2,0,1);
        S16(0xF10)=1;
        reinterpret_cast<FighterSwitchF598_Boss004AC040*>(OWNER)->SetMotionStateAt40FBB0(0,0.0f,0);
        *reinterpret_cast<unsigned char*>(OWNER+0x10)=0x82;
    }
    if (S16(0x62)==11 && S16(0x64)==0) {
        if (S16(0xF00)<10) {
            ++S16(0xF00);
            SetAuxActionAt40FB40(9);
        } else {
            S16(0xF10)=0;
            *reinterpret_cast<unsigned char*>(OWNER+0x10)=0;
            S16(0xF00)=0;
        }
    }
    if (S16(0x62)==13 && S16(0x64)==0 && S16(0xF00)<10) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(11);
    }
    break;
}
