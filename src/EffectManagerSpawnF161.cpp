#include "EffectManagerLifetimeF161.hpp"
#include "CharacterObject.hpp"
#include "Fighter.hpp"
#include "TransformRecordF136.hpp"

void EffectManagerLifetimeF161::Spawn(short effect, float x, float y, signed char facing,
                                  signed char layer, unsigned char flagA,
                                  unsigned char flagB, const float* parameters,
                                  const void* transform, unsigned char mode)
{
    Actor* node;
    fighter_->CreateOwnedObject(reinterpret_cast<void**>(&node));
    node->ResetPrimaryCounters(effect);
    node->x = x;
    node->y = y;
    node->facing = facing;
    node->field067 = flagA;
    node->field068 = flagB;
    node->field040 = 0;
    static_cast<CharacterObject*>(node)->field0C8 = parameters[0];
    static_cast<CharacterObject*>(node)->field0CC = parameters[1];
    static_cast<CharacterObject*>(node)->field0D0 = parameters[2];
    static_cast<CharacterObject*>(node)->field0D4 = parameters[3];
    node->field08A = mode;
    node->field09C = 1.0f;
    node->field0A0 = 1.0f;
    node->field0A4 = fighter_->field0A4;
    if (transform != 0) {
        node->ResetTransform(0, 0, 0);
        *reinterpret_cast<TransformRecordF136*>(reinterpret_cast<unsigned char*>(node) + 0x10) =
            *static_cast<const TransformRecordF136*>(transform);
    }
    entries_[layer].push_back(node);
}

