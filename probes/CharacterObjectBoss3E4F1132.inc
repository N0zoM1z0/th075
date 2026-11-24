// F1132: genuine Japanese native 0x3E4 at PE 0051DAE8..0051E01F,
// original 1335 CODE B/261 x86 inside ONE nonexact 81KB game callable.
case 0x3E4: {
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
            float(field0DA)*FloatConstants::FourFifths);
    }
    if (animationStage==1) {
        field0D8=short(AngleAt00483300(
            (*(&owner->opponent->y))+GeometryConstants::Hundred-y,
            owner->opponent->x-x) /
            GeometryConstants::RadiansPerDegree);
        SetPolarVelocity(float(field0D8),20.0f);
        if (x-owner->opponent->x<GeometryConstants::Twenty &&
            x-owner->opponent->x>GeometryConstants::NegativeTwenty &&
            y-owner->opponent->y<GeometryConstants::HundredTwenty &&
            y-owner->opponent->y>GeometryConstants::Eighty) {
            ++owner->fieldEFA;
            PlaySharedSound(0x2E);
            ClearFrameInfo();
            if (owner->opponent->spiritCooldown>0) {
                if (owner->opponent->spiritCooldown>5)
                    owner->opponent->spiritCooldown=
                        short(owner->opponent->spiritCooldown-5);
                else {
                    owner->opponent->spiritCooldown=0;
                    owner->opponent->spirit=1000;
                }
                return;
            }
            // A positive cooldown returns after either update. Only
            // a nonpositive cooldown reaches the spirit policy.
            if (owner->opponent->spirit<990)
                owner->opponent->spirit=
                    short(owner->opponent->spirit+10);
            else {
                owner->opponent->spirit=1000;
                if (owner->opponent->field39C==0) {
                    if (owner->opponent->field36C<g_F1132_DoubleAt00659228)
                        owner->opponent->field36C=
                            (*(&owner->opponent->field36C))+FloatConstants::Half;
                    else
                        owner->opponent->field36C=900.0f;
                }
            }
            return;
        }
    }
    x=x+velocityX;
    y=y-velocityY;
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(1);
    return;
}
