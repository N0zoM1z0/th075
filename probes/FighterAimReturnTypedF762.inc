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
                field3AC=0;
            }
            if ((animationStage)<11 && y>FloatConstants::Zero && (animationStage)>2) {
                velocityX=-30.0f;
                velocityY=velocityY-FloatConstants::ThreeFifths;
                if (y+velocityY<=FloatConstants::Zero) {
                    ClearMotionFields();
                    ResetSecondaryCounter(15);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>10 && (animationStage)<14 && !CheckHorizontalLimits()) {
                if (facing==1)
                    x=(field2D8)+FloatConstants::Five;
                if (facing==-1)
                    x=(field2DC)-FloatConstants::Five;
            }
            if ((animationStage)>8 && (animationStage)<11
                && y>FloatConstants::Zero) {
                if ((CheckHorizontalLimits() && (((x)<GeometryConstants::SixHundredForty
                        && facing==1)
                    || ((x)>GeometryConstants::SixHundredForty
                        && facing==-1)))
                    || (((field2D8)+FloatConstants::Five)>=x
                        && facing==1)
                    || (((field2DC)-FloatConstants::Five)<=x
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
                if (y+velocityY<=FloatConstants::Zero) {
                    velocityY=0.0f;
                    velocityX=(velocityX)*FloatConstants::ThreeTenths;
                    ResetSecondaryCounter(16);
                    ResetTransform(0.0f,0.0f,0.0f);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>15) {
                velocityX=(velocityX)-FloatConstants::OneAndHalf;
                if ((velocityX)<FloatConstants::Zero)
                    velocityX=0.0f;
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                PlaySound(5);
                SpawnAuxEffect(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+GeometryConstants::Hundred,
                    -facing,1);
                SpawnAuxEffect(0x7E,x,
                    (*(&y))+GeometryConstants::Hundred,
                    -facing,1);
                velocityX=-20.0f;
                velocityY=20.0f;
                if (y>FloatConstants::Zero)
                    velocityY=8.0f;
                field05C=0.8f;
            }
            if ((animationStage)==14 && (animationFrame)==0) {
                PlaySound(6);
                velocityX=30.0f;
                velocityY=-30.0f;
                fieldF04=static_cast<short>(
                    AngleAt00483300(
                        *(&(opponent->y))-y,
                        (opponent->x-x)
                          *static_cast<float>(facing))
                      /GeometryConstants::RadiansPerDegree);
                if ((fieldF04)>-15)
                    fieldF04=-15;
                SetPolarVelocity(static_cast<float>(-static_cast<int>(fieldF04)),28.0f);
                ResetTransform(0.0f,80.0f,0.0f);
                rotationZ=-(AngleAt00483300(velocityY,*(&velocityX))
                             /GeometryConstants::RadiansPerDegree
                              +GeometryConstants::Fifteen);
            }
            if ((animationStage)==15 && (animationFrame)==0) {
                field314=static_cast<float>(fieldF04);
                SpawnBattleEffect(0x338,x,y,
                    facing,1);
            }
            if ((animationStage)==18 && (animationFrame)==0 && (scriptCounterF00)==0)
                ResetSecondaryCounter(19);
            if ((animationStage)==11 && (animationFrame)==0)
                ResetSecondaryCounter(9);
            break;
        }
