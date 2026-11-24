#include "Fighter.hpp"
#include "EffectManagerLifetimeF161.hpp"
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
    field2EC = new EffectManagerLifetimeF161();
    field2EC->BindFighter(this);
    drawing = 0;
    field534 = 0;
    stageDrawing = 0;
}
