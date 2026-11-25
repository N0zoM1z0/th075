#include "characters/CharacterObject.hpp"

void CharacterObject::BindAnimation()
{
    frameInfo = &sequences->at(action)->frames.at(animationStage);
    drawFrame = frameInfo;
    animationFrameCount = frameInfo->unknown04;
    animationStageCount = static_cast<short>(sequences->at(action)->frames.size());
    sequenceInfo = sequences->at(action);
}
