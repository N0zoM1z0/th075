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
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                ResetAt453E20();
                reinterpret_cast<signed short&>(field080)=1;
                field07C=0;
                reinterpret_cast<unsigned char&>(field3AC)=0;
            }
            if ((reinterpret_cast<signed short&>(animationStage))<11 && y>g_ThresholdAt0065782C && (reinterpret_cast<signed short&>(animationStage))>2) {
                velocityX=-30.0f;
                velocityY=velocityY-g_ApproachAt00658058;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    SetAuxActionAt40FB40(15);
                    y=0.0f;
                    break;
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))>10 && (reinterpret_cast<signed short&>(animationStage))<14 && !ContactAt454EE0()) {
                if (facing==1)
                    x=(field2D8)+g_F699_SideOffsetAt00657874;
                if (facing==-1)
                    x=(field2DC)-g_F699_SideOffsetAt00657874;
            }
            if ((reinterpret_cast<signed short&>(animationStage))>8 && (reinterpret_cast<signed short&>(animationStage))<11
                && y>g_ThresholdAt0065782C) {
                if ((ContactAt454EE0() && (((x)<g_F699_SideEdgeAt00657884
                        && facing==1)
                    || ((x)>g_F699_SideEdgeAt00657884
                        && facing==-1)))
                    || (((field2D8)+g_F699_SideOffsetAt00657874)>=reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44
                        && facing==1)
                    || (((field2DC)-g_F699_SideOffsetAt00657874)<=reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44
                        && facing==-1)) {
                    SetAuxActionAt40FB40(11);
                    ResetAt453E20();
                    break;
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))==14 || (reinterpret_cast<signed short&>(animationStage))==15) {
                if (field07C!=0 && field07C!=3 && field07C!=1) {
                    SetMotionStateAt40FBB0(0,0.0f,0);
                    SetNativeActionAt40FAC0(0x1FA);
                    break;
                }
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    velocityY=0.0f;
                    velocityX=(velocityX)*g_F728_PositiveDragAt006583FC;
                    SetAuxActionAt40FB40(16);
                    SetMotionStateAt40FBB0(0,0.0f,0);
                    y=0.0f;
                    break;
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))>15) {
                velocityX=(velocityX)-g_NewDragAt006581E0;
                if ((velocityX)<g_ThresholdAt0065782C)
                    velocityX=0.0f;
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
                SetNativeActionAt40FAC0(0);
            if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                PrepareActionAt453D40(5);
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
            if ((reinterpret_cast<signed short&>(animationStage))==14 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                PrepareActionAt453D40(6);
                velocityX=30.0f;
                velocityY=-30.0f;
                reinterpret_cast<signed short&>(fieldF04)=static_cast<short>(
                    CalculateAngleAt483300(
                        *(&(opponent->y))-y,
                        (reinterpret_cast<FighterBorrowedXViewF752*>(opponent)->xAt44-reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44)
                          *static_cast<float>(facing))
                      /g_StormAngleDenominatorAt00657828);
                if ((reinterpret_cast<signed short&>(fieldF04))>-15)
                    reinterpret_cast<signed short&>(fieldF04)=-15;
                MotionAt40FB70(static_cast<float>(-static_cast<int>(reinterpret_cast<signed short&>(fieldF04))),28.0f);
                SetMotionStateAt40FBB0(0,80.0f,0);
                rotationZ=-(CalculateAngleAt483300(velocityY,*(&velocityX))
                             /g_StormAngleDenominatorAt00657828
                              +g_F731_AimOffsetAt00657CBC);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==15 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                field314=static_cast<float>(reinterpret_cast<signed short&>(fieldF04));
                SpawnDirectedAt453A70(0x338,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==18 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0)
                SetAuxActionAt40FB40(19);
            if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0)
                SetAuxActionAt40FB40(9);
            break;
        }
