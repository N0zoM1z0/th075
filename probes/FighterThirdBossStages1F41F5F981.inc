// F981 native Japanese original fighter 004AC040 states 1F4 and 1F5.
// Both original game case interiors exactly 830B/232 x86 with
// 23 real typed PE/COFF external targets each. Original 1F5 stage7
// ordering sets drag AFTER raw 0x7F projectile, 1F4 sets it BEFORE.
// Four actual 0x32A/0x329 sprite shots at stage8; real x87 motion,
// 1F4 auxiliary stage10 F00<1 vs 1F5 F00<3. Natural VC7.1 source
// matches native x86 mnemonic/width geometry but 135 GPR roles each
// remain wrong in incomplete 82KB parent. No independent case exact.
// F981 true Japanese original 004AC040 action 0x1F4
case 0x1F4: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=99;
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(0xC);
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
    if ((reinterpret_cast<signed short&>(animationStage))==7 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=2.0f;
        velocityY=6.5f;
        field05C=0.4f;
        SpawnRawAt453C80(0x7F,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            facing,1);
        PrepareActionAt453D40(3);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0) {
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
    }
    if ((reinterpret_cast<signed short&>(animationStage))==10 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        SetAuxActionAt40FB40(8);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==12 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(0xB);
    break;
}
// F981 true Japanese original 004AC040 action 0x1F5
case 0x1F5: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=99;
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if (y+velocityY<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(0xC);
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
    if ((reinterpret_cast<signed short&>(animationStage))==7 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=8.0f;
        velocityY=13.5f;
        SpawnRawAt453C80(0x7F,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            facing,1);
        field05C=0.5f;
        PrepareActionAt453D40(3);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0) {
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
    }
    if ((reinterpret_cast<signed short&>(animationStage))==10 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<3) {
        SetAuxActionAt40FB40(8);
        ++reinterpret_cast<signed short&>(scriptCounterF00);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==12 && (reinterpret_cast<signed short&>(animationFrame))==0)
        SetAuxActionAt40FB40(0xB);
    break;
}
