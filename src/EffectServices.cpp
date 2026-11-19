#include "EffectServices.hpp"
#include "Fighter.hpp"
#include "GameLeafHelpers.hpp"

void EffectSound45B860::PlaySharedSound(short sound) {
    g_SoundBank->Play(sound);
}

void Fighter::SetCameraShake(float amount) {
    CameraShake412CB0::SetShakeAmount(amount);
}

void CameraShake412CB0::SetShakeAmount(float amount) {
    g_CameraShakeAmountAt006713F8 = amount;
}
