// F762: original complete 1F8 read-only borrowed X operands and
// true short-circuit Contact semantics. Not an independent game function.
// F731: complete original fighter 1F8, native 0054B43A..0054B9F9,
// 1471 full CODE B /422 original x86. Full native stage, original
// 1FA transitions, contact/ground, 7D/7E reverse projectiles,
// real stage14 geometry through 00483300 /0040FB70 /0040FBB0,
// and stage15 338 projectile. Native 80.0f and NEG before FILD
// are confirmed by physical original PE, and *(&velocityX) restores
// direct C++ raw float argument use at native 00483300 call.
// Real target-Y member lvalue preserves native MOV/FLD owner order
// around the first 00483300 angle call. Two original memory FCOMP
// still emit extra FLD/FCOMPP; native deep EBP scratch not yet exact.
// Original entire fighter NONEXACT.
        case 0x1F8: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                reinterpret_cast<unsigned char&>(field3AC)=0;
            }
            if ((animationStage)<11 && y>g_ThresholdAt0065782C && (animationStage)>2) {
                velocityX=-30.0f;
                velocityY=velocityY-g_ApproachAt00658058;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    ResetSecondaryCounter(15);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>10 && (animationStage)<14 && !CheckHorizontalLimits()) {
                if (facing==1)
                    x=(field2D8)+g_F699_SideOffsetAt00657874;
                if (facing==-1)
                    x=(field2DC)-g_F699_SideOffsetAt00657874;
            }
            if ((animationStage)>8 && (animationStage)<11
                && y>g_ThresholdAt0065782C) {
                if ((CheckHorizontalLimits() && (((x)<g_F699_SideEdgeAt00657884
                        && facing==1)
                    || ((x)>g_F699_SideEdgeAt00657884
                        && facing==-1)))
                    || (((field2D8)+g_F699_SideOffsetAt00657874)>=reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44
                        && facing==1)
                    || (((field2DC)-g_F699_SideOffsetAt00657874)<=reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44
                        && facing==-1)) {
                    ResetSecondaryCounter(11);
                    ClearMotionFields();
                    break;
                }
            }
            if ((animationStage)==14 || (animationStage)==15) {
                if (field07C!=0 && field07C!=3 && field07C!=1) {
                    ResetTransform(0.0f,0.0f,0.0f);
                    ResetPrimaryCounters(0x1FA);
                    break;
                }
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    velocityY=0.0f;
                    velocityX=(velocityX)*g_F728_PositiveDragAt006583FC;
                    ResetSecondaryCounter(16);
                    ResetTransform(0.0f,0.0f,0.0f);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>15) {
                velocityX=(velocityX)-g_NewDragAt006581E0;
                if ((velocityX)<g_ThresholdAt0065782C)
                    velocityX=0.0f;
            }
            if (AdvanceNestedFrame()==(field070))
                ResetPrimaryCounters(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                PlaySound(5);
                SpawnAt453C80(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    -facing,1);
                SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    -facing,1);
                velocityX=-20.0f;
                velocityY=20.0f;
                if (y>g_ThresholdAt0065782C)
                    velocityY=8.0f;
                field05C=0.8f;
            }
            if ((animationStage)==14 && (animationFrame)==0) {
                PlaySound(6);
                velocityX=30.0f;
                velocityY=-30.0f;
                fieldF04=static_cast<short>(
                    CalculateAngleAt483300(
                        *(&(opponent->y))-y,
                        (reinterpret_cast<FighterBorrowedXViewF752*>(opponent)->xAt44-reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44)
                          *static_cast<float>(facing))
                      /g_StormAngleDenominatorAt00657828);
                if ((fieldF04)>-15)
                    fieldF04=-15;
                SetPolarVelocity(static_cast<float>(-static_cast<int>(fieldF04)),28.0f);
                ResetTransform(0.0f,80.0f,0.0f);
                rotationZ=-(CalculateAngleAt483300(velocityY,*(&velocityX))
                             /g_StormAngleDenominatorAt00657828
                              +g_F731_AimOffsetAt00657CBC);
            }
            if ((animationStage)==15 && (animationFrame)==0) {
                field314=static_cast<float>(fieldF04);
                SpawnBattleEffect(0x338,x,y,
                    facing,1);
            }
            if ((animationStage)==18 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0)
                ResetSecondaryCounter(19);
            if ((animationStage)==11 && (animationFrame)==0)
                ResetSecondaryCounter(9);
            break;
        }
