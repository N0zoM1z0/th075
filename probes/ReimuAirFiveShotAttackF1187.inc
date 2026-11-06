// Native 194/195 airborne five-shot policy, with explicit per-shot values.
case R1187_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        S16(0xF00)=0;
    }
    POS54=POS54-POS5C;
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
    if (S16(0x62)==4 && S16(0x64)==0) {
        POS=-3.0f; POS54=8.0f; POS5C=0.55f;
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySoundAt453D40(0);
        StartAnimationAt46D000(100);
    }
    if (S16(0x62)==6 && S16(0x64)==0 && S16(0xF00)<2 &&
        *reinterpret_cast<unsigned int*>(RAW+0x4F0)>0) {
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySoundAt453D40(0);
        StartAnimationAt46D000(25);
        ++S16(0xF00);
        SetAuxActionAt40FB40(4);
    }
    break;
}
