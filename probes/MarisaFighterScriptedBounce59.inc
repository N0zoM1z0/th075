// Marisa action 0x59 at 0x0048843A..0x0048859D: 356 bytes / 95 x86
// instructions. The same typed source logic is independently present in
// Youmu's 0x005214B0 case; only the enclosing stack frame differs.
        case 0x59: {
            if ((animationStage)==3) {
                rotationZ=(rotationZ)+g_F728_RandomOffsetYAt00657858;
                velocityY=velocityY-field05C;
                if (velocityY+y<=g_ThresholdAt0065782C) {
                    scriptCounterF00=(velocityX)*g_ContactProjectionAt00657888;
                    scriptCounterF02=(*(&velocityY))*g_ContactProjectionAt00657888;
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
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetSecondaryCounter(3);
            else if ((animationStage)==3 && (animationFrame)==0) {
                velocityX=static_cast<float>(scriptCounterF00)*g_F747_BounceXAt006590BC;
                velocityY=static_cast<float>(-scriptCounterF02)*g_F747_BounceYAt00658044;
                field05C=0.7f;
                ResetTransform(0.0f,95.0f,0.0f);
            }
            break;
        }
