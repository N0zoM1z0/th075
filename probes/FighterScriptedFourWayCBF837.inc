// F837 selected 005214B0 actor original interior CB: 496 B, 141 x86,
// 12 genuine original PE fields. Natural +F00 prefix signed-short ++
// and actual native source order recover all non-parent-JMP bytes.
// This is NOT an independently callable original game function.
case 0xCB: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        velocityX=0.0f;
        velocityY=0.0f;
        field05C=0.0f;
    }
    if (y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))>0) {
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f;
            velocityY=0.0f;
            field05C=0.0f;
            y=0.0f;
            reinterpret_cast<signed short&>(animationFrame)=0;
            SetNativeActionAt40FAC0(0xA);
            return;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(9);
    if ((reinterpret_cast<signed short&>(animationStage))==1 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=-10.0f;
        velocityY=5.0f;
        field05C=0.6f;
        SpawnAt453C80(0x7D,
            reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-float((facing)*80),
            (*(&y))+g_ContactProjectionAt00657888,
            -(facing),1);
        SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            -(facing),1);
        PrepareActionAt453D60(31);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(1);
    }
    return;
}
