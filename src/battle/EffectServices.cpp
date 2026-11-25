#include "battle/EffectServices.hpp"
#include "characters/CharacterObject.hpp"
#include "battle/Fighter.hpp"
#include "engine/GameLeafHelpers.hpp"

void CharacterObject::PlaySharedSound(short sound) {
    g_SoundBank->Play(sound);
}

void Fighter::SetCameraShake(float amount) {
    CameraShake412CB0::SetShakeAmount(amount);
}

void CameraShake412CB0::SetShakeAmount(float amount) {
    g_CameraShakeAmountAt006713F8 = amount;
}
