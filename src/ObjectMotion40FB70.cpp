#include "ObjectMotion40FB70.hpp"
#include "MathLookup.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void ObjectMotion40FB70::SetPolarVelocity(float angle, float speed) {
    FIELD(float, 0x50) = MathLookup::ReadCosTable(angle) * speed;
    FIELD(float, 0x54) = -MathLookup::ReadPhaseTable(angle) * speed;
}

#undef FIELD
