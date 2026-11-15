// F982 original Japanese fighter 004AC040 real 1F6 and 1F7.
// Each physical native handler is 777B/215x86/22 typed PE fields.
// Native initial motion is scaled by true DOUBLE at 006583E0
// (1F6) or 006584C8 (1F7); native stage4 F00<2 vs F00<4.
// Normal VC7.1 partial father C++ matches ordered native mnemonic/
// width geometry; original GPR mismatch count 126 per state.
// Entire 82KB game fighter remains NONEXACT, not inner-case exact.
// F982 original native 004AC040 0x1F6 double-scaled fighter action
case 0x1F6: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=(velocityX)*g_F982_Scale1F6At006583E0;
        velocityY=(velocityY)*g_F982_Scale1F6At006583E0;
        reinterpret_cast<signed short&>(field080)=99;
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))>3 && (reinterpret_cast<signed short&>(animationStage))<6) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(6);
            y=0.0f;
            break;
        }
    }
    if (field07C!=0) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        if ((reinterpret_cast<signed short&>(scriptCounterF02))>6) {
            reinterpret_cast<signed short&>(scriptCounterF02)=0;
            field07C=0;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field314=15.0f;
        field318=-20.0f;
        field31C=-60.0f;
        SpawnSevenFloatAt453B50(0x32A,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        SpawnSevenFloatAt453B50(0x329,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        field314=10.0f;
        field318=-135.0f;
        field31C=-30.0f;
        SpawnSevenFloatAt453B50(0x32A,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        SpawnSevenFloatAt453B50(0x329,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        PrepareActionAt453D40(3);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2) {
        SetAuxActionAt40FB40(2);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(5);
    break;
}
// F982 original native 004AC040 0x1F7 double-scaled fighter action
case 0x1F7: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=(velocityX)*g_F982_Scale1F7At006584C8;
        velocityY=(velocityY)*g_F982_Scale1F7At006584C8;
        reinterpret_cast<signed short&>(field080)=99;
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))>3 && (reinterpret_cast<signed short&>(animationStage))<6) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(6);
            y=0.0f;
            break;
        }
    }
    if (field07C!=0) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        if ((reinterpret_cast<signed short&>(scriptCounterF02))>6) {
            reinterpret_cast<signed short&>(scriptCounterF02)=0;
            field07C=0;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field314=15.0f;
        field318=-20.0f;
        field31C=-60.0f;
        SpawnSevenFloatAt453B50(0x32A,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        SpawnSevenFloatAt453B50(0x329,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        field314=10.0f;
        field318=-135.0f;
        field31C=-30.0f;
        SpawnSevenFloatAt453B50(0x32A,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        SpawnSevenFloatAt453B50(0x329,
            (x)+g_ThresholdAt0065782C,
            (*(&y))+g_F981_YAt00659270,
            facing,1,0,1);
        PrepareActionAt453D40(3);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<4) {
        SetAuxActionAt40FB40(2);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(5);
    break;
}
