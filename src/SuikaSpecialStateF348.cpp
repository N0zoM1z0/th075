#include "GeometryConstants.hpp"
#include "SuikaFighter.hpp"
#include <windows.h>
// Native-bounded borrowed state only. Original random/gfx and sound method
// bodies, full fighter layout and owned objects are all external.
// F348: native zero and +20.0f operands have real float-constant fields at
// 0065782C / 0065786C, not mutable state globals. Using natural float
// literals with a direct float-lvalue macro reproduces the native x87
// evaluation order at each comparison and projectile launch. This is the
// complete original function, not a cropped or masked reconstruction.
class SuikaSoundF313 {public: void Play(int index);};
#define F(T,off) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define O(T,off) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(F(void*,0x2e8))+(off)))

#define FLOAT(off) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (off))
#define OPPONENT_FLOAT(off) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(F(void*,0x2e8)) + (off))

#define SHOT(n) SpawnProjectile((n), \
 (OPPONENT_FLOAT(0x44)+20.0f)-static_cast<float>(Rand(0,40)), \
 (O(float,0x48)+GeometryConstants::Forty)+static_cast<float>(Rand(0,100)), \
 F(unsigned char,0x66),1)
void SuikaFighter::AdvanceAuxiliary()
{
    if (FLOAT(0x50)==0.0f && F(signed char,0x3ac)>0)
        F(unsigned char,0x3ac)=0;
    if (F(short,0xf1c)>0) {
        --F(short,0xf1c);
        reinterpret_cast<SuikaSoundF313*>(F(void*,0x2e8))->Play(3);
        if(F(signed char,0x39d)==2 && Rand(0,100)<25) {
            SHOT(0x336);
        }
        if(F(signed char,0x39d)==1) {
            if(Rand(0,100)<25) {
                SHOT(0x337);
            }
            if (F(short,0x3b6)>0) {
                if (F(short,0x3b6)>3) {
                    F(short,0x3b6)-=3;
                } else {
                    F(short,0x3b6)=0;
                    F(short,0x3b0)=1000;
                }
                return;
            }
            if(F(short,0x3b0)<997) F(short,0x3b0)+=3;
            else F(short,0x3b0)=1000;
        }
    }
    if(F(short,0xf1e)>0) {
        if(F(short,0x3b0)>4) {
            reinterpret_cast<SuikaSoundF313*>(this)->Play(4);
        } else {
            reinterpret_cast<SuikaSoundF313*>(this)->Play(F(short,0x3b0)-1);
            F(short,0xf1e)=0;
        }
        if(O(short,0x324)<=0 || F(short,0x3a0)<=0)
            F(short,0xf1e)=0;
    }
    if(GeometryConstants::FiveHundredForty<FLOAT(0x44)-OPPONENT_FLOAT(0x44) ||
       FLOAT(0x44)-OPPONENT_FLOAT(0x44)<GeometryConstants::NegativeFiveHundredForty)
        F(short,0xf26)=60;
    if(GeometryConstants::ThreeHundredTwenty<FLOAT(0x44)-OPPONENT_FLOAT(0x44) ||
       FLOAT(0x44)-OPPONENT_FLOAT(0x44)<GeometryConstants::NegativeThreeHundredTwenty) {
        F(short,0xf26)=F(short,0xf26)+1;
        if(F(short,0xf26)>60) F(short,0xf26)=60;
    } else {
        F(short,0xf26)=0;
    }
}
#undef SHOT
#undef O
#undef F
