#include "Fighter.hpp"

void Fighter::BindAnimation()
{
    frameInfo = &sequenceSlots.at(action)->frames.at(animationStage);
    drawFrame = frameInfo;
    animationFrameCount = frameInfo->unknown04;
    animationStageCount = static_cast<short>(sequenceSlots.at(action)->frames.size());
    sequenceInfo = sequenceSlots.at(action);
}
