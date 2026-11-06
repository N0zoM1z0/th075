#pragma once

// Borrowed receiver interfaces. The exact 005A1560 constructor writes E4h
// and installs vtable 00659DDC. No complete owner layout is asserted;
// never instantiate or embed these incomplete receiver views.
class OwnerActor5A1600F1231 {
public:
    void PlaySoundAt00453D40(short);
    void SpawnEffect(short, float, float, signed char, signed char);
    void SpawnTrackedEffectAt00453AC0(short, float, float, signed char, signed char, unsigned char);
};

class ObjectActor5A1600F1231 {
public:
    virtual void BindAnimationAt0045B880();
    virtual void AdvanceAction();
    short AdvanceNestedFrame();
    void ResetPrimaryCounters(short);
    void ResetSecondaryCounters(short);
    void SetPolarVelocity(float, float);
    void EnableTransform(float, float, float);
    int RecordedRange(int, int);
    void ClearField74();
    void PlaySharedSound(short);
};

float __cdecl AngleAt00483300(float, float);
