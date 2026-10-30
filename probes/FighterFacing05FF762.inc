// F762: actual original action 05F in 00543210. Original GPR phase still NONEXACT;
// normal game source; no independent callable CODE credit.
// Original complete action 05F inside the 58,294-byte authored fighter.
// Observed borrowed float X members in both actors; not new owner instances.
        case 0x5F: {
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                if (I32(0x4E0)>0)
                    SetNativeActionAt40FAC0(1);
            }
            if (S16(0x62)==S16(0x70)-1) {
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44 >
                    reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44)
                    *reinterpret_cast<signed char*>(RAW+0x66)=-1;
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44 <
                    reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44)
                    *reinterpret_cast<signed char*>(RAW+0x66)=1;
            }
            break;
        }
