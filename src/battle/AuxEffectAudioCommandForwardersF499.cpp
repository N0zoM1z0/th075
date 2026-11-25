#include "battle/CommandListF283.hpp"
#include "audio/SoundBank.hpp"

class AudioForwarderF499 {public:void PlaySharedSound(short sound);};
void AudioForwarderF499::PlaySharedSound(short sound){
 g_SoundBank->Play(sound);
}
void CommandListF283::Reset()
{
    queue.clear();
}
float g_StateFadeValue;
class BattleSceneSharedF499 {public:void SetSharedValue(float value);};
void BattleSceneSharedF499::SetSharedValue(float value){
 g_StateFadeValue = value;
}
