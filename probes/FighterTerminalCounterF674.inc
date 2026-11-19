// F674 true original physical terminal native case 31C, source grammar.
// Original 63 x86 /219 B /7 true call fields, but 36 genuine GPR phase
// mismatches remain in the selected full parent. Explicitly NONSTRICT.
// Its real source code naturally places the original far shared exit
// beyond 2EF, restoring 2EF native 5-byte JMP; no artificial padding.
        case 0x31C: {
            if ((animationStage)==0 && (animationFrame)==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                field07C=1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(0);
            if ((animationStage)==15 && (animationFrame)==0) {
                SubactionAt454A70(0);
                SubactionAt452B30();
                PlaySharedSound(0x17);
            }
            if ((animationStage)==22 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
                ++reinterpret_cast<signed short&>(scriptCounterF00);
                SetAuxActionAt40FB40(0x14);
                reinterpret_cast<unsigned char&>(field3CF)=1;
            }
            break;
        }
