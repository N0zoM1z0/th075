#pragma once
#include "CharacterObject.hpp"
#include "YukariFighter.hpp"

// Borrowed receiver interfaces. The exact 005A1560 constructor writes E4h
// and installs vtable 00659DDC. No complete owner layout is asserted;
// never instantiate or embed these incomplete receiver views.
class OwnerActor5A1600F1231 {
public:
    void PlaySoundAt00453D40(short);
    void SetCameraShakeAt00453E60(float);
    void SpawnAuxEffectAt00453C80(short, float, float, signed char, signed char);
    void SpawnEffect(short, float, float, signed char, signed char);
    void SpawnTrackedEffectAt00453AC0(short, float, float, signed char, signed char, unsigned char);
};

class ObjectActor5A1600F1231 : public CharacterObject {
public:
    void BindAnimation();
    void Advance();
    int RecordedRange(int, int);
    void PlaySharedSound(short);
    // Native empty receiver call has RET 4; original parameter typedef unknown.
    void UnknownAt0045B850(int);
};

float __cdecl AngleAt00483300(float, float);

float __cdecl AbsFloatAt00412D90(float);
