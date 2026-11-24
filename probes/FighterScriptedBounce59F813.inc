// F813: actual original 005214B0 action 0x59 (0052327A..005233DD), 356B /95 x86.
// Actor-specific genuine signed stage 3 and auxiliary action 3.
// Native game source interior; NOT an independently callable exact function.
        case 0x59: {
            if ((animationStage)==3) {
                rotationZ=(rotationZ)+GeometryConstants::Forty;
                velocityY=velocityY-field05C;
                if (velocityY+y<=FloatConstants::Zero) {
                    scriptCounterF00=static_cast<short>((velocityX)*GeometryConstants::Hundred);
                    scriptCounterF02=static_cast<short>((*(&velocityY))*GeometryConstants::Hundred);
                    ClearMotionFields();
                    y=0.0f;
                    ResetPrimaryCounters(0x61);
                    rotationZ=0.0f;
                    SetCameraShake(2.0f);
                    ClearTransformFlag();
                    PlaySharedSound(0x16);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070))
                ResetSecondaryCounter(3);
            else if ((animationStage)==3 && (animationFrame)==0) {
                velocityX=static_cast<float>(scriptCounterF00)*g_F747_BounceXAt006590BC;
                velocityY=static_cast<float>(-scriptCounterF02)*FloatConstants::OneHundredth;
                field05C=0.7f;
                ResetTransform(0.0f, 95.0f, 0.0f);
            } else if (animationStage == 3 && animationFrame != 0) {
                // Keep the rebound motion on later frames.
            }
            break;
        }
