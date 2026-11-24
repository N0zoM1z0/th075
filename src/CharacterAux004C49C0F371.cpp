#include "SakuyaFighter.hpp"
#include "Fighter.hpp"
// Complete original R049 1757-byte character auxiliary state controller.
// The distinct active-round/two-mode actions and 30/70/57-facing effect
// offsets are independently observed in this original. The opponent call
// interface, inherited effect spawner and round-sound APIs are borrowed.
// Source uses actual native branch direction and a native short predecrement;
// no unused storage, full owner layout or invented control paths.
#define FIELD(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
void SakuyaFighter::AdvanceAuxiliary() {
    if(velocityX==0.0f && field3AC>0) field3AC=0;
    if(fieldF0C>0) {
        if(fieldF0E<=0) { EnableRoundSound(1);fieldF0E=1; }
        else { --fieldF0E; }
        field09C=0.75f;
        fieldF0C=spirit;
        if(action!=0x2C1 && action!=0x2C3) {
            if(field39D==2) {
                if(spirit>8) UpdateGaugeTimer(8);
                else fieldF0C=0;
            }
            if(field39D==1) {
                if(spirit>4) UpdateGaugeTimer(4);
                else fieldF0C=0;
            }
        }
    }
    else field09C=1.0f;
    if(fieldF12>0) {
        field084=2;field088=2;
        if(fieldF10<=0) {
            fieldF10=0;fieldF12=0;
            opponent->field3BC=0;
            opponent->field010=0;
        }
        if(fieldF10>0 && action!=0x2C0 && action!=0x2C2) {
            fieldF10=spirit;
            field3B8=2;
            if(field39D==2) {
                if(spirit>8) UpdateGaugeTimer(8);
                else fieldF10=0;
            }
            if(field39D==1) {
                if(spirit>5) UpdateGaugeTimer(5);
                else fieldF10=0;
            }
            opponent->ResetTransform(0,0,0);
            opponent->field010=0x82;
        }
    }
    if (action > 149 && action < 154 && animationStage==0 && animationFrame==0 && fieldF0A==0) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 1.0f;
            field300 = 1.0f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(817, facing * 30 + x, y + 94.0f, facing, 1, 1);
            fieldF0A = 1;
        }
    if (action > 153 && action < 158 && animationStage==0 && animationFrame==0 && fieldF0A==0) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 1.0f;
            field300 = 1.0f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(817, facing * 70 + x, y + 60.0f, facing, 1, 1);
            fieldF0A = 1;
        }
    if (action == 158 && animationStage==0 && animationFrame==0 && fieldF0A==0) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 1.0f;
            field300 = 1.0f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(817, facing * 57 + x, y + 100.0f, facing, 1, 1);
            fieldF0A = 1;
        }
    if(x-opponent->x>540.0f || x-opponent->x<-540.0f) fieldF16=60;
    if(x-opponent->x>320.0f || x-opponent->x<-320.0f) {
        fieldF16=fieldF16+1;
        if(fieldF16>60) fieldF16=60;
    } else fieldF16=0;
}
#undef FIELD
