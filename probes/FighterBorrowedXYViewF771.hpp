#ifndef FIGHTER_BORROWED_XY_VIEW_F771_HPP
#define FIGHTER_BORROWED_XY_VIEW_F771_HPP
// Physical, borrowed X/Y float coordinates observed directly in original
// TH075 fighter CODE at actor/opponent +0x44/+0x48. Neither private class
// identity nor other original member meanings are inferred. Pointer-only.
struct FighterBorrowedXYViewF771 {
    unsigned int observedOwnerStorageBeforeX[17];
    float xAt44;
    float yAt48;
};
typedef char AssertF771BorrowedYAt48[(sizeof(FighterBorrowedXYViewF771)==0x4c)?1:-1];
#endif
