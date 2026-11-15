#pragma once
#include "CharacterObject.hpp"
#include "SakuyaFighter.hpp"

// Borrowed receiver interfaces. The exact 004CA640 constructor writes E4h
// and installs vtable 006595B8. No complete owner layout is asserted;
// never instantiate or embed these incomplete receiver views.
class OwnerActor4CA6E0F1222 {
public:
    void PlaySoundAt00453D40(short);
    void SpawnEffect(short, float, float, signed char, signed char);
    void SpawnTrackedEffectAt00453AC0(short, float, float, signed char, signed char, unsigned char);
};

class ObjectActor4CA6E0F1222 : public CharacterObject {
public:
    void BindAnimation();
    void Advance();
    int RecordedRange(int, int);
    void PlaySharedSound(short);
};

float __cdecl AngleAt00483300(float, float);
