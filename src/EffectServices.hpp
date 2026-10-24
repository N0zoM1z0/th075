#pragma once

// Declaration-only views. Never construct or embed these partial owners.
class EffectSound45B860 {
public:
    void PlaySharedSound(short sound);
};
class FighterShake453E60 {
public:
    void SetCameraShake(float amount);
};
namespace CameraShake412CB0 {
    void SetShakeAmount(float amount);
}
extern float g_CameraShakeAmountAt006713F8;
