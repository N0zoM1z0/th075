#pragma once

// Borrowed receiver interfaces. The exact 0057D4E0 constructor writes E4h
// and installs vtable 00659C88. No complete owner layout is asserted;
// never instantiate or embed these incomplete receiver views.
class OwnerActor57D580F1237 {
public:
    void PlaySoundAt00453D40(short);
    void SetCameraShakeAt00453E60(float);
    void SpawnAuxEffectAt00453C80(short, float, float, signed char, signed char);
    void SpawnEffect(short, float, float, signed char, signed char);
    void SpawnTrackedEffectAt00453AC0(short, float, float, signed char, signed char, unsigned char);
};

class ObjectActor57D580F1237 {
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
    // Native empty receiver call has RET 4; original parameter typedef unknown.
    void UnknownAt0045B850(int);
};

float __cdecl AngleAt00483300(float, float);

float __cdecl AbsFloatAt00412D90(float);
