#include "CharacterObject.hpp"

// The base object constructor (0045B760): the Actor constructor runs first,
// then the object vtable (00659064) is installed and these fields cleared.
// Float members are cleared with integer stores, as the original does.
CharacterObject::CharacterObject()
{
    field080 = 0;
    field07C = 0;
    field082 = 0;
    reinterpret_cast<unsigned int&>(field08C) = 0;
    reinterpret_cast<unsigned int&>(field090) = 0;
    field094 = 0;
    field098 = 0;
    reinterpret_cast<unsigned int&>(velocityX) = 0;
    reinterpret_cast<unsigned int&>(velocityY) = 0;
    field058 = 0;
    reinterpret_cast<unsigned int&>(field05C) = 0;
    reinterpret_cast<unsigned int&>(field04C) = 0;
    field084 = 0;
    field086 = 0;
    field088 = 0;
}
