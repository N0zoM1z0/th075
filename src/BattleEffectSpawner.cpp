#include "BattleEffectSpawner.hpp"
#include "TransformRecordF136.hpp"

#define NODE_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(node) + (offset)))
#define FACTORY_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(field000) + (offset)))

void BattleEffectSpawnerF136::Spawn(short effect, float x, float y, signed char facing,
                                  signed char layer, unsigned char flagA,
                                  unsigned char flagB, const float* parameters,
                                  const void* transform, unsigned char mode)
{
    Actor* node;
    field000->Acquire(&node);
    node->ResetPrimaryCounters(effect);
    node->x = x;
    node->y = y;
    node->facing = facing;
    node->field067 = flagA;
    node->field068 = flagB;
    node->field040 = 0;
    NODE_FIELD(float, 0xC8) = parameters[0];
    NODE_FIELD(float, 0xCC) = parameters[1];
    NODE_FIELD(float, 0xD0) = parameters[2];
    NODE_FIELD(float, 0xD4) = parameters[3];
    reinterpret_cast<unsigned short&>(node->field08A) = mode;
    node->field09C = 1.0f;
    node->field0A0 = 1.0f;
    reinterpret_cast<void*&>(node->field0A4) = FACTORY_FIELD(void*, 0xA4);
    if (transform != 0) {
        node->ResetTransform(0, 0, 0);
        *reinterpret_cast<TransformRecordF136*>(reinterpret_cast<unsigned char*>(node) + 0x10) =
            *static_cast<const TransformRecordF136*>(transform);
    }
    reinterpret_cast<EffectDequeF136*>(reinterpret_cast<unsigned char*>(this) +
        layer * 0x14 + 4)->PushBack(node);
}

#undef FACTORY_FIELD
#undef NODE_FIELD
