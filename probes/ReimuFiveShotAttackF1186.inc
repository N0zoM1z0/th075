// Two real five-shot sequences with actor-observed per-shot parameter writes.
// The repeated expression evaluations are present in the original callable.
case R1186_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==8 && S16(0x64)==0) {
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySoundAt453D40(0);
        StartAnimationAt46D000(100);
    }
    if (S16(0x62)==10 && S16(0x64)==0 && S16(0xF00)<2 &&
        *reinterpret_cast<unsigned int*>(RAW+0x4F0)>0) {
#include "ReimuFiveShotVolleyF1186.inc"
        PlaySoundAt453D40(0);
        StartAnimationAt46D000(25);
        ++S16(0xF00);
        SetAuxActionAt40FB40(8);
    }
    break;
}
