#include "CharacterAuxAction.hpp"
#include "CombatEffects.hpp"

void CharacterAuxObject::BindAnimation()
{
    drawFrame = &(*patterns).at(action)->frames.at(animationStage);
    animationFrameCount = drawFrame->unknown04;
    animationStageCount = static_cast<short>((*patterns).at(action)->frames.size());
}
