// X comparisons use the inherited Actor::x member at +0x44.
// F747: true complete original 059/05D/05E normal C++ action interiors
// in ONE 58KB fighter 00543210 giant parent. No independent CODE credit.
// Native original 059 00545109..0054526D 356 B /95 x86;
// 05D 0054526D..005453BE 337 B/101 x86;
// 05E 005453BE..0054550F 337 B/101 x86.
        case 0x59: {
            if ((animationStage)>1) {
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
            if (AdvanceNestedFrame()==(field070))
                ResetSecondaryCounter(2);
            else if ((animationStage)==2 && (animationFrame)==0) {
                velocityX=static_cast<float>(scriptCounterF00)*g_F747_BounceXAt006590BC;
                velocityY=static_cast<float>(-scriptCounterF02)*g_F747_BounceYAt00658044;
                field05C=0.7f;
                ResetTransform(0.0f,95.0f,0.0f);
            }
            break;
        }
        case 0x5D: {
            if ((animationStage)<8 && y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(8);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0);
                if (inputY>0)
                    ResetPrimaryCounters(1);
            }
            if ((animationStage)==(field070)-1) {
                if (x>opponent->x)
                    facing=-1;
                if (x<opponent->x)
                    facing=1;
            }
            if ((animationStage)==3 && (animationFrame)==0) {
                velocityY=8.0f;
                velocityX=15.5f;
                field05C=0.75f;
            }
            if ((animationStage)==8 && (animationFrame)==0)
                ResetSecondaryCounter(6);
            break;
        }
        case 0x5E: {
            if ((animationStage)<8 && y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(8);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0);
                if (inputY>0)
                    ResetPrimaryCounters(1);
            }
            if ((animationStage)==(field070)-1) {
                if (x>opponent->x)
                    facing=-1;
                if (x<opponent->x)
                    facing=1;
            }
            if ((animationStage)==3 && (animationFrame)==0) {
                velocityY=8.0f;
                velocityX=-15.5f;
                field05C=0.75f;
            }
            if ((animationStage)==8 && (animationFrame)==0)
                ResetSecondaryCounter(6);
            break;
        }
