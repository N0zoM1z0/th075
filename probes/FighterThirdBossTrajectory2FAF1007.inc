// F1007 native Japanese 004AC040 real state2FA:
 // original 004BF16E..004BF40E 672 CODE B/186x86,
 // 18 physical PE targets. Real ground collision, original
 // mode+2 signed byte, recurring raw-X0x38E stage4..10,
 // randomized horizontal motion and two world X bounds
 // original 0065945C/00657888.
 // Source 669B/186: all mnemonic roles align, one native
 // final shared-tail JMP width 5B vs compiled2B. 113 GPR
 // roles differ in 2FA. Crucially adding real 2FA repairs
 // prior 2E6 last native near JMP (now 2058B/590 native
 // GPR/mnemonic/width geometry). Whole fighter NONEXACT.
// F1007 SHA-pinned Japanese original 004AC040 fighter case 2FA.
case 0x2FA: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        S16(0xF06)=0;
        S16(0xF08)=g_F1004_ModeAt006714D0+2;
    }
    if (POS48>=g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            SetAuxActionAt40FB40(15);
            ResetAt453E20();
            POS48=0.0f;
            break;
        }
    }
    ++S16(0xF00);
    if (S16(0x62)>3 && S16(0x62)<11 && S16(0xF00)>8) {
        S16(0xF00)=0;
        F32(0x314)=-45.0f;
        SpawnWithFloatAt453A70(0x38E,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D40(12);
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=static_cast<short>(
            RandAt455580(60,120)-g_F1004_ModeAt006714D0*20);
    }
    if (S16(0x62)==2 && S16(0x64)==0) {
        POS54=16.0f;
        POS5C=0.5f;
        POS=float(RandAt455580(0,6)+12);
        if ((*reinterpret_cast<signed char*>(RAW+0x66)==1 &&
             F32(0x44)>=g_F1007_RightBoundAt0065945C) ||
            (*reinterpret_cast<signed char*>(RAW+0x66)==-1 &&
             F32(0x44)<g_ContactProjectionAt00657888))
            POS=-POS;
    }
    if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF02)<1) {
        ++S16(0xF02);
        SetAuxActionAt40FB40(4);
    }
    if (S16(0x62)==15 && S16(0x64)==0)
        SetAuxActionAt40FB40(13);
    break;
}
