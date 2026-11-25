#include "engine/GeometryConstants.hpp"
#include "characters/suika/SuikaFighter.hpp"

#define SHOT(pattern) SpawnBattleEffect((pattern), \
 (opponent->x + 20.0f) - static_cast<float>(RecordedRange(0,40)), \
 (opponent->y + 40.0f) + static_cast<float>(RecordedRange(0,100)), \
 static_cast<unsigned char>(facing),1)

void SuikaFighter::AdvanceAuxiliary()
{
    if (velocityX==0.0f && field3AC>0)
        field3AC=0;
    if (opponentSpiritDrainFrames>0) {
        --opponentSpiritDrainFrames;
        opponent->UpdateGaugeTimer(3);
        if(roundsRemaining==2 && RecordedRange(0,100)<25) {
            SHOT(0x336);
        }
        if(roundsRemaining==1) {
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
    if(selfSpiritDrainMode>0) {
        if(spirit>4) {
            UpdateGaugeTimer(4);
        } else {
            UpdateGaugeTimer(spirit-1);
            selfSpiritDrainMode=0;
        }
        if(opponent->health<=0 || spellTimer<=0)
            selfSpiritDrainMode=0;
    }
    if(GeometryConstants::FiveHundredForty<x-opponent->x ||
       x-opponent->x<GeometryConstants::NegativeFiveHundredForty)
        longRangeFrames=60;
    if(GeometryConstants::ThreeHundredTwenty<x-opponent->x ||
       x-opponent->x<GeometryConstants::NegativeThreeHundredTwenty) {
        longRangeFrames=longRangeFrames+1;
        if(longRangeFrames>60) longRangeFrames=60;
    } else {
        longRangeFrames=0;
    }
}
#undef SHOT
