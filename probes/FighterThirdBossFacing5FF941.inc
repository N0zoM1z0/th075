// F941: true independently decoded 004AC040 native 0x5F state
// 004AE300..004AE390: 144 native CODE B/44 x86/3 typed original PE fields.
// This reuses the confirmed F762 real battle-facing semantics with the
// independently confirmed original 004AC040 receiver/opponent +0x44.
// The natural C++ inside a still-PARTIAL 82KB parent has the real
// 0x5F native 44-instruction GPR/mnemonic/width sequence; the original
// entire callable game giant and saved this EBP layout remain NONEXACT.
// FighterBorrowedXViewF752 comes from the real F939 pair include.
        case 0x5F: {
            if (GetNativeActionAt40FA30()==(field070)) {
                SetNativeActionAt40FAC0(0);
                if (inputY>0)
                    SetNativeActionAt40FAC0(1);
            }
            if ((animationStage)==(field070)-1) {
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44 >
                    reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    facing=-1;
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44 <
                    reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    facing=1;
            }
            break;
        }
