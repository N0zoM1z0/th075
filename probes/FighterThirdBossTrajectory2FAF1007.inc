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
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        reinterpret_cast<signed short&>(fieldF04)=0;
        reinterpret_cast<signed short&>(fieldF06)=0;
        reinterpret_cast<signed short&>(fieldF08)=g_F1004_ModeAt006714D0+2;
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            SetAuxActionAt40FB40(15);
            ResetAt453E20();
            y=0.0f;
            break;
        }
    }
    ++reinterpret_cast<signed short&>(scriptCounterF00);
    if ((reinterpret_cast<signed short&>(animationStage))>3 && (reinterpret_cast<signed short&>(animationStage))<11 && (reinterpret_cast<signed short&>(scriptCounterF00))>8) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field314=-45.0f;
        SpawnWithFloatAt453A70(0x38E,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            facing,1);
        PrepareActionAt453D40(12);
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(aiCardTimer)=static_cast<short>(
            RandAt455580(60,120)-g_F1004_ModeAt006714D0*20);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityY=16.0f;
        field05C=0.5f;
        velocityX=float(RandAt455580(0,6)+12);
        if ((facing==1 &&
             (x)>g_F1007_RightBoundAt0065945C) ||
            (facing==-1 &&
             (x)<g_ContactProjectionAt00657888))
            velocityX=-(velocityX);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        SetAuxActionAt40FB40(4);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==15 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(13);
    break;
}
