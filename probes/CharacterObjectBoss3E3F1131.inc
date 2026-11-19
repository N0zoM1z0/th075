// F1131: genuine Japanese native 0x3E3 at PE 0051D70F..0051DAE8,
// original 985 CODE B/200 x86 inside ONE nonexact 81KB game callable.
case 0x3E3: {
    facing=1;
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=0.0f;
        velocityY=-1.0f;
        field0D8=short(RecordedRange(0,360)-180);
        field0DA=15;
    }
    if (animationStage==0) {
        --field0DA;
        if (field0DA<3)
            field0DA=3;
        SetPolarVelocity(float(field0D8),
            float(field0DA)*g_F1120_XBrakingAt00659090);
    }
    if (animationStage==1) {
        field0D8=short(F1057_FloatAtan2At00483300(
            (*(&owner->opponent->y))+g_F1057_YOffsetAt00657888-y,
            owner->opponent->x-x) /
            g_F1057_AngleDivAt00657828);
        SetPolarVelocity(float(field0D8),20.0f);
        if (x-owner->opponent->x<g_F1115_DistanceAt0065786C &&
            x-owner->opponent->x>g_F1131_LeftHitAt00659230 &&
            y-owner->opponent->y<g_F1131_TopHitAt006590A8 &&
            y-owner->opponent->y>g_F1131_BottomHitAt00658268) {
            ClearFrameInfo();
            if (owner->opponent->field366<2)
                ++owner->opponent->field366;
            else {
                owner->opponent->score+=0x4E20;
            }
            PlaySharedSound(0x2E);
            return;
        }
    }
    x=x+velocityX;
    y=y-velocityY;
    if (AdvanceNestedFrame()==field070)
        ResetSecondaryCounter(1);
    return;
}
