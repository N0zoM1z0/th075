// F874 selected original owner pointer +0x2E8, two native calls and owner X/float Y.
// Native outer equality/inner range forms ONE real conditional with else zero.
// 1FD has true original 6B CMP ECX,149 not yet normal VC7.1-restored.
// Original whole giant NONEXACT, no inner-case callable exact credit.
case 0x1FD: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=0;
        field07C=0;
        field3AC=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==2 && field07C==1) {
        SpawnAt453C80(0x50,
            float((facing)*80)+(x),
            (*(&y))+g_F872Volley1FAYAt00659310,
            (facing),1);
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x66);
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->ResetAt453E20();
        opponent->x=float((facing)*80)+(x);
        SetNativeActionAt40FAC0(0x1FF);
        return;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if (opponent->y==g_ThresholdAt0065782C &&
           (reinterpret_cast<signed short&>(opponent->action)<0x32 ||
            reinterpret_cast<signed short&>(opponent->action)>0x95)) {
            reinterpret_cast<signed short&>(field080)=1;
        } else {
            reinterpret_cast<signed short&>(field080)=0;
        }
    }
    return;
}
