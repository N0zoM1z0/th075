#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "characters/CharacterObject.hpp"
// Complete 855-byte native projectile-behaviour branch of AliceObject.
// Called by the seven projectile action states of AliceObject::Advance.
extern float AngleAt00483300(float,float);
void AliceObject::AdvanceProjectileBehavior() {
    if (collisionResult==5) {
        ClearFrameInfo();
    } else if (owner->action>49 && owner->action<150 && animationStage<2) {
        ClearFrameInfo();
        for(int i=0;i<1;++i) {
            owner->SpawnBattleEffect(996,x,y,1,1);
        }
        if (owner->fieldEFA>25) {
            owner->fieldEFA=0;
            owner->SpawnBattleEffect(995,x,y,1,1);
        }
    } else {
        if (animationStage==0 && animationFrame==0) {
            field0DA=static_cast<short>(field0C8);
            field0DC=static_cast<short>(field0CC);
            ResetTransform(0,0,0);
            remainingHits=1;
            collisionResult=0;
            SetPolarVelocity(static_cast<float>(field0DC),static_cast<float>(field0DA)*FloatConstants::OneHundredth);
            scaleX=1.5f;scaleY=1.5f;
            color[0]=255;
            color[1]=255;
            color[2]=255;
            color[3]=255;
            rotationZ=AngleAt00483300(velocityY,velocityX)/GeometryConstants::RadiansPerDegree;
        }
        if ((collisionResult==1 || collisionResult==2 || collisionResult==4 || collisionResult==6) && animationStage<2) {
            ResetSecondaryCounter(2);
            velocityX=0.0f;
            velocityY=0.0f;
        } else {
            if (animationStage<2) {
                SetPolarVelocity(static_cast<float>(field0DC),static_cast<float>(field0DA)*FloatConstants::OneHundredth);
                x=static_cast<float>(facing)*velocityX+x;
                y=y-velocityY;
            }
            if(animationStage==2) {
                // Parenthesized operand keeps the original x87 order (fld scaleX first).
                scaleX=(scaleX)*FloatConstants::EightyFiveHundredths;
                scaleY=scaleX;
            }
            if(x>GeometryConstants::FourteenHundred || x<GeometryConstants::NegativeHundredSixty || y>GeometryConstants::Thousand || y<GeometryConstants::NegativeHundredSixty)
                ClearFrameInfo();
            else if (AdvanceNestedFrame()==animationStageCount) ClearFrameInfo();
        }
    }
}
