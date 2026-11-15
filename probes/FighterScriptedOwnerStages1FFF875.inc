// F875 native original 1FF complete real stage1..6 associated owner action.
// Five actual native FILD scratch slots; original owner+0x44 x87 updates.
// Enclosing 46755B whole fighter still not exact; no inner exact credit.
case 0x1FF: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=0;
        field07C=0;
        field3AC=0;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==1 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        opponent->x=float((facing)*74)+(x);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        opponent->x=float((facing)*40)+(x);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        opponent->x=float((facing)*36)+(x);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        opponent->x=float((facing)*33)+(x);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        opponent->x=float((facing)*32)+(x);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0)
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x35);
    return;
}
