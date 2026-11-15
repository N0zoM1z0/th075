// F892 original 2DB whole 556B/162x86 native PE handler.
// Both actual borrowed float owner/this X left-lvalues preserve native x87 ordering.
// Native random range 455580 call and short+516 update are WITHIN current-action guard.
// Stage15 two real projectile methods; whole original 46755B fighter NONEXACT.
case 0x2DB: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field07C=0;
        reinterpret_cast<signed short&>(field080)=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        reinterpret_cast<signed short&>(fieldF04)=0;
        ResetAt453E20();
    }
    if ((reinterpret_cast<signed short&>(animationStage))>1 && (reinterpret_cast<signed short&>(animationStage))<10) {
        if (F892AbsAt00412D90(
                reinterpret_cast<FighterBorrowedXViewF833*>(opponent)->xAt44-reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44)
                <g_F892DistAt0065787C) {
            SetAuxActionAt40FB40(10);
            return;
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage))>15) {
        velocityX=(velocityX)-g_BounceScaleAt00657F74;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(aiCardTimer)=RandomBoundaryAt455580(30,60);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0)
        velocityX=12.5f;
    if ((reinterpret_cast<signed short&>(animationStage))==10 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(2);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==15 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnFloatXRawYAt453C80(0x80,
            float((facing)*100)+(x),
            reinterpret_cast<int&>(y),(facing),1);
        SpawnDirectedAt453A70(0x336,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PrepareActionAt453D40(2);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==16 && (reinterpret_cast<signed short&>(animationFrame))==0)
        velocityX=17.5f;
    return;
}
