#include "battle/Fighter.hpp"
#include "battle/EffectManagerLifetimeF161.hpp"
#include <windows.h>
#include <new>
#include <string.h>

ActorRenderingBase::ActorRenderingBase()
{
}

Actor::Actor()
{
}

void SoundBank::Configure()
{
}

Fighter::Fighter()
{
    soundBank.Configure();
    unsigned int scratch[7];
    memset(scratch, 0, sizeof(scratch));
    inputHistory.assign(90, 0);
    ownedObjects = new EffectManagerLifetimeF161();
    ownedObjects->BindFighter(this);
    drawing = 0;
    overlayTextures = 0;
    stageTexture = 0;
}
