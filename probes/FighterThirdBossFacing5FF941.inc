// F941: true independently decoded 004AC040 native 0x5F state
// 004AE300..004AE390: 144 native CODE B/44 x86/3 typed original PE fields.
// This reuses the confirmed F762 real battle-facing semantics with the
// independently confirmed original 004AC040 receiver/opponent +0x44.
// The natural C++ inside a still-PARTIAL 82KB parent has the real
// 0x5F native 44-instruction GPR/mnemonic/width sequence; the original
// entire callable game giant and saved this EBP layout remain NONEXACT.
// FighterBorrowedXViewF752 comes from the real F939 pair include.
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
