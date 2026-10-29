// F674 true original physical terminal native case 31C, source grammar.
// Original 63 x86 /219 B /7 true call fields, but 36 genuine GPR phase
// mismatches remain in the selected full parent. Explicitly NONSTRICT.
// Its real source code naturally places the original far shared exit
// beyond 2EF, restoring 2EF native 5-byte JMP; no artificial padding.
        case 0x31C: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                ResetAt453E20();
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
            if (S16(0x62)==15 && S16(0x64)==0) {
                SubactionAt454A70(0);
                SubactionAt452B30();
                PrepareActionAt453D60(0x17);
            }
            if (S16(0x62)==22 && S16(0x64)==0 && S16(0xF00)<8) {
                ++S16(0xF00);
                SetAuxActionAt40FB40(0x14);
                *reinterpret_cast<unsigned char*>(RAW+0x3CF)=1;
            }
            break;
        }
