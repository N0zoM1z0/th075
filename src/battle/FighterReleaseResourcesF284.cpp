#include "battle/Fighter.hpp"
#include "battle/CommandListF283.hpp"
#include "battle/EffectManagerLifetimeF161.hpp"
#include "graphics/TextureManagerF198.hpp"

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
    delete spriteHistory;
    delete ownedObjects;
    if (drawing)
        delete static_cast<TextureManagerF198*>(drawing);
    if (overlayTextures)
        delete overlayTextures;
    if (stageTexture)
        delete stageTexture;
}
