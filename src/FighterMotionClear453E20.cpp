#include "Fighter.hpp"

// Clear the four motion fields using their native C++ members.
void Fighter::ClearMotionFields()
{
    velocityX = 0.0f;
    velocityY = 0.0f;
    field058 = 0;
    field05C = 0.0f;
}
