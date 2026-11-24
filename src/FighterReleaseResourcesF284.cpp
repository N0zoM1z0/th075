#include "Fighter.hpp"
#include "CommandListF283.hpp"
#include "EffectManagerLifetimeF161.hpp"
#include "TextureManagerF198.hpp"

Fighter::~Fighter()
{
    for (unsigned int index = 0; index < sequenceSlots.size(); ++index) {
        if (sequenceSlots[index]) {
            sequenceSlots[index]->frames.clear();
            delete sequenceSlots[index];
        }
    }
    sequenceSlots.clear();
    inputHistory.clear();
    delete field480;
    delete field2EC;
    if (drawing)
        delete static_cast<TextureManagerF198*>(drawing);
    if (field534)
        delete reinterpret_cast<TextureManagerF198*>(field534);
    if (stageDrawing)
        delete static_cast<TextureManagerF198*>(stageDrawing);
}
