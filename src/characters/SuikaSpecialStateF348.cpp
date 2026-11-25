#include "engine/GeometryConstants.hpp"
#include "characters/SuikaFighter.hpp"

#define SHOT(pattern) SpawnBattleEffect((pattern), \
 (opponent->x + 20.0f) - static_cast<float>(RecordedRange(0,40)), \
 (opponent->y + 40.0f) + static_cast<float>(RecordedRange(0,100)), \
 static_cast<unsigned char>(facing),1)

void SuikaFighter::AdvanceAuxiliary()
{
    if (velocityX==0.0f && field3AC>0)
        field3AC=0;
    if (fieldF1C>0) {
        --fieldF1C;
        opponent->UpdateGaugeTimer(3);
        if(field39D==2 && RecordedRange(0,100)<25) {
            SHOT(0x336);
        }
        if(field39D==1) {
            if(RecordedRange(0,100)<25) {
                SHOT(0x337);
            }
            if (spiritCooldown>0) {
                if (spiritCooldown>3) {
                    spiritCooldown-=3;
                } else {
                    spiritCooldown=0;
                    spirit=1000;
                }
                return;
            }
            if(spirit<997) spirit+=3;
            else spirit=1000;
        }
    }
    if(fieldF1E>0) {
        if(spirit>4) {
            UpdateGaugeTimer(4);
        } else {
            UpdateGaugeTimer(spirit-1);
            fieldF1E=0;
        }
        if(opponent->health<=0 || spellTimer<=0)
            fieldF1E=0;
    }
    if(GeometryConstants::FiveHundredForty<x-opponent->x ||
       x-opponent->x<GeometryConstants::NegativeFiveHundredForty)
        fieldF26=60;
    if(GeometryConstants::ThreeHundredTwenty<x-opponent->x ||
       x-opponent->x<GeometryConstants::NegativeThreeHundredTwenty) {
        fieldF26=fieldF26+1;
        if(fieldF26>60) fieldF26=60;
    } else {
        fieldF26=0;
    }
}
#undef SHOT
