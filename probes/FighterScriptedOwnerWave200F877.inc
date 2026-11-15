// F877 native original 200: complete 634B/177-x86/10 genuine PE call fields.
// Six actual FILD integer temps. Stage5 must FILD then FSUBR ownerX member.
// Genuine borrowed actor X lvalue repairs wrong FISUB source; no code patches.
// Whole original 46755B game function remains NONEXACT.
case 0x200: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=0;
        field07C=0;
        field3AC=0;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        return;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        opponent->x=float((facing)*74)+(x);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==1 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        opponent->x=float((facing)*46)+(x);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        opponent->x=float((facing)*23)+(x);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        opponent->x=float((facing)*13)+(x);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        reinterpret_cast<char&>(opponent->facing)=reinterpret_cast<char&>(facing);
        opponent->x=float((facing)*-6)+(x);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x64);
        opponent->x=reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-float((facing)*26);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0)
        reinterpret_cast<FighterBorrowedOwnerF874*>(opponent)->SetNativeActionAt40FAC0(0x35);
    return;
}
