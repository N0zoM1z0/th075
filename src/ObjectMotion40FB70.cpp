#include "ObjectMotion40FB70.hpp"
#include "MathLookup.hpp"


void ObjectMotion40FB70::SetPolarVelocity(float angle, float speed) {
    field050 = MathLookup::ReadCosTable(angle) * speed;
    field054 = -MathLookup::ReadPhaseTable(angle) * speed;
}
