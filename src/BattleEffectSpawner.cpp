#include "BattleEffectSpawner.hpp"
#include "TransformRecordF136.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define NODE_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(node) + (offset)))
#define FACTORY_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(EffectFactoryF136*, 0)) + (offset)))

void BattleEffectSpawnerF136::Spawn(short effect, float x, float y, signed char facing,
                                  signed char layer, unsigned char flagA,
                                  unsigned char flagB, const float* parameters,
                                  const void* transform, unsigned char mode)
{
    SpawnedEffectF136* node;
    FIELD(EffectFactoryF136*, 0)->Acquire(&node);
    node->ResetPrimaryCounters(effect);
    NODE_FIELD(float, 0x44) = x;
    NODE_FIELD(float, 0x48) = y;
    NODE_FIELD(signed char, 0x66) = facing;
    NODE_FIELD(unsigned char, 0x67) = flagA;
    NODE_FIELD(unsigned char, 0x68) = flagB;
    NODE_FIELD(unsigned char, 0x40) = 0;
    NODE_FIELD(float, 0xC8) = parameters[0];
    NODE_FIELD(float, 0xCC) = parameters[1];
    NODE_FIELD(float, 0xD0) = parameters[2];
    NODE_FIELD(float, 0xD4) = parameters[3];
    NODE_FIELD(unsigned short, 0x8A) = mode;
    NODE_FIELD(float, 0x9C) = 1.0f;
    NODE_FIELD(float, 0xA0) = 1.0f;
    NODE_FIELD(void*, 0xA4) = FACTORY_FIELD(void*, 0xA4);
    if (transform != 0) {
        node->ResetNodeTransform(0, 0, 0);
        *reinterpret_cast<TransformRecordF136*>(reinterpret_cast<unsigned char*>(node) + 0x10) =
            *static_cast<const TransformRecordF136*>(transform);
    }
    reinterpret_cast<EffectDequeF136*>(reinterpret_cast<unsigned char*>(this) +
        layer * 0x14 + 4)->PushBack(node);
}

#undef FACTORY_FIELD
#undef NODE_FIELD
#undef FIELD
