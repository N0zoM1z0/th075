#include "Fighter.hpp"

// Native 00453E20 clears +0x50/+0x54/+0x58/+0x5C. Ghidra labels this
// address ContextBase::ClearCancel, but its machine code is the fighter
// four-field motion clear, not a separate cancellation API.
void Fighter::ClearMotionFields()
{
    velocityX = 0.0f;
    velocityY = 0.0f;
    field058 = 0;
    field05C = 0.0f;
}
