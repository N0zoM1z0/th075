// F767: authentic observed borrowed opponent/actor X and read-only Y
// lvalues restore all 381 native 2F9 opcode and widths. Its 249 real
// register/nonfield bytes remain NONEXACT in the 58KB game parent.
// F684: 00543210 original complete 0x2F9 angle-storm source grammar.
// Native 381 genuine x86 /1367 original CODE B /34 actual PE/COFF fields.
// Compiled 381 x86/1319B, 16 original wide EBP integer float temporaries
// and original GPR register roles remain NONSTRICT. Never credit case.
// CalculateAngleAt483300 / __ftol2 are native source ABI probes only.
case 0x2F9: {
            ConfigureStormAt454BC0(3,4,0xFF0000);
            if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                reinterpret_cast<signed short&>(scriptCounterF02)=0;
                reinterpret_cast<signed short&>(fieldF04)=0;
                field07C=1;
                ResetAt453E20();
            }
            if ((reinterpret_cast<signed short&>(animationStage))>1 && (reinterpret_cast<signed short&>(animationStage))<20) {
                if ((reinterpret_cast<signed short&>(animationStage))>15 || (reinterpret_cast<signed short&>(animationStage))<10) {
                    velocityY=velocityY-field05C;
                }
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(0x14);
                    y=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                PrepareActionAt453D40(0x12);
                field314=float((reinterpret_cast<signed short&>(scriptCounterF02))+(reinterpret_cast<signed short&>(scriptCounterF00))*10);
                SpawnFloatXYAt453A70(0x391,
                    float(facing*30)+(x),
                    (*(&y))+g_StormAngleShotYAt00659A18,
                    facing,1);
                for (int i=0;i<static_cast<int>(g_CloudOpponentAt006714D0)*2+4;++i)
                    SpawnFloatXYAt453A70(0x392,
                        float(facing*30)+(x),
                        (*(&y))+g_StormAngleShotYAt00659A18,
                        facing,1);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==14 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                PrepareActionAt453D40(0x12);
                field314=float((reinterpret_cast<signed short&>(scriptCounterF02))-(reinterpret_cast<signed short&>(scriptCounterF00))*10);
                SpawnFloatXYAt453A70(0x391,
                    float(facing*30)+(x),
                    (*(&y))+g_StormAngleShotYAt00659A18,
                    facing,1);
                for (int i=0;i<static_cast<int>(g_CloudOpponentAt006714D0)*2+4;++i)
                    SpawnFloatXYAt453A70(0x392,
                        float(facing*30)+(x),
                        (*(&y))+g_StormAngleShotYAt00659A18,
                        facing,1);
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
                SetNativeActionAt40FAC0(0);
                reinterpret_cast<signed short&>(aiCardTimer)=RandomBoundaryAt455580(60,100)
                       -static_cast<int>(g_CloudOpponentAt006714D0)*20;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityY=12.5f;
                velocityX=-8.0f;
                field05C=0.4f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==10 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityX=(*(&velocityX))*g_StormMotionAt00658348;
                velocityY=(*(&velocityY))*g_StormMotionAt00658348;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>(
                    CalculateAngleAt483300(
                        (*(&(opponent->y))-*(&y)),
                        ((reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44-reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44))
                           *static_cast<float>(facing))
                    /g_StormAngleDenominatorAt00657828);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==13 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                if ((reinterpret_cast<signed short&>(scriptCounterF00))<static_cast<int>(g_CloudOpponentAt006714D0)*2+1) {
                    SetAuxActionAt40FB40(0xB);
                    ++reinterpret_cast<signed short&>(scriptCounterF00);
                } else reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==14 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>(
                    CalculateAngleAt483300(
                        (*(&(opponent->y))-*(&y)),
                        ((reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44-reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44))
                           *static_cast<float>(facing))
                    /g_StormAngleDenominatorAt00657828);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==16 && (reinterpret_cast<signed short&>(animationFrame))==0
                && (reinterpret_cast<signed short&>(scriptCounterF00))<static_cast<int>(g_CloudOpponentAt006714D0)*2+1) {
                SetAuxActionAt40FB40(14);
                ++reinterpret_cast<signed short&>(scriptCounterF00);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==20 && (reinterpret_cast<signed short&>(animationFrame))==0) SetAuxActionAt40FB40(0x12);
            break;
        }
