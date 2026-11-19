// F890 original 2C2 entire 2274B/608 native x86 action with eight real unrolled F00 phases.
// Real stage8 reset/aux1 and stage9 borrowed owner X+motion, no artificial loops.
// All x87 temporary values flow to actually emitted native projectiles.
// Whole original fighter remains NONEXACT; internal state is NOT callable exact CODE.
case 0x2C2: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        fieldF04=0;
        field07C=0;
        field080=1;
        ClearMotionFields();
    }
    if ((animationStage)>9) {
        velocityY=velocityY-g_F890GravityAt006581E0;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            y=0.0f;
            ClearMotionFields();
            ResetPrimaryCounters(0x2C3);
            return;
        }
    }
    if ((animationStage)==9 && (reinterpret_cast<signed short&>(scriptCounterF02))==0) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        SpawnBattleEffect(0x34C,x,
            (opponent->y)+g_ContactProjectionAt00657888,
            (facing),1);
        PlaySound(0xE);
    }
    if (AdvanceNestedFrame()==(field070))
        ResetSecondaryCounter(0x10);
    if ((animationStage)<9 && (animationFrame)==0) {
        SpawnBattleEffect(0x34B,opponent->x,
            (opponent->y)+g_ContactProjectionAt00657888,
            (facing),1);
        if ((reinterpret_cast<signed short&>(scriptCounterF00))==0) {
            field314=0.0f;
            SpawnBattleEffect(0x34A,
                opponent->x-float(((facing))*100),
                (opponent->y)+g_F890Phase0YAt0065835C,
                (facing),1);
            SpawnBattleEffect(0x329,opponent->x,
                (opponent->y)+g_F890Phase0AltYAt006591E4,
                -((facing)),1);
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF00))==1) {
            field314=0.0f;
            Fighter::SpawnBattleEffect(0x34A,
                opponent->x+float(((facing))*100),
                opponent->y,
                -((facing)),1);
            SpawnBattleEffect(0x329,opponent->x,
                (opponent->y)-g_F890Phase1LowYAt0065788C,
                -((facing)),1);
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF00))==2) {
            field314=90.0f;
            SpawnBattleEffect(0x34A,
                opponent->x+float(((facing))*100),
                (opponent->y)+g_F890Phase0YAt0065835C,
                (facing),1);
            SpawnBattleEffect(0x329,
                opponent->x+float(((facing))*150),
                (opponent->y)+g_ContactProjectionAt00657888,
                -((facing)),1);
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF00))==3) {
            field314=-90.0f;
            Fighter::SpawnBattleEffect(0x34A,
                opponent->x-float(((facing))*100),
                opponent->y,
                (facing),1);
            SpawnBattleEffect(0x329,
                opponent->x-float(((facing))*150),
                (opponent->y)+g_ContactProjectionAt00657888,
                -((facing)),1);
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF00))==4) {
            field314=45.0f;
            SpawnBattleEffect(0x34A,
                (opponent->x)+g_ThresholdAt0065782C,
                (opponent->y)+g_F890Phase4HiYAt00659420,
                (facing),1);
            SpawnBattleEffect(0x329,
                opponent->x+float(((facing))*125),
                (opponent->y)+g_F890Phase4OtherYAt006598B4,
                -((facing)),1);
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF00))==5) {
            field314=-45.0f;
            SpawnBattleEffect(0x34A,
                (opponent->x)+g_ThresholdAt0065782C,
                (opponent->y)-g_F890Phase5YAt0065786C,
                -((facing)),1);
            SpawnBattleEffect(0x329,
                opponent->x-float(((facing))*125),
                (opponent->y)-g_ApproachUpperAt006592A4,
                (facing),1);
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF00))==6) {
            field314=45.0f;
            SpawnBattleEffect(0x34A,
                opponent->x+float(((facing))*120),
                (opponent->y)+g_ContactProjectionAt00657888,
                -((facing)),1);
            SpawnBattleEffect(0x329,
                opponent->x+float(((facing))*125),
                (opponent->y)-g_ApproachUpperAt006592A4,
                (facing),1);
        }
        if ((reinterpret_cast<signed short&>(scriptCounterF00))==7) {
            field314=-45.0f;
            SpawnBattleEffect(0x34A,
                opponent->x-float(((facing))*120),
                (opponent->y)+g_ContactProjectionAt00657888,
                (facing),1);
            SpawnBattleEffect(0x329,
                opponent->x-float(((facing))*125),
                (opponent->y)+g_F890Phase4OtherYAt006598B4,
                -((facing)),1);
        }
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        if ((animationStage)==8 && (animationFrame)==0 && (fieldF04)==0) {
            reinterpret_cast<signed short&>(scriptCounterF00)=1;
            ++fieldF04;
            ResetSecondaryCounter(1);
            field314=0.0f;
            SpawnBattleEffect(0x34A,
                opponent->x-float(((facing))*100),
                (opponent->y)+g_F890Phase0YAt0065835C,
                (facing),1);
            SpawnBattleEffect(0x329,opponent->x,
                (opponent->y)+g_F890Phase0AltYAt006591E4,
                -((facing)),1);
        }
    }
    if ((animationStage)==9 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        reinterpret_cast<int&>(x)=reinterpret_cast<int&>(opponent->x);
        reinterpret_cast<int&>(y)=0;
        velocityX=0.0f;
        velocityY=50.0f;
    }
    return;
}
