#include "Fighter.hpp"

// Call-only Fighter view: the method writes the observed sequencePhase byte.
class FighterNoticeF283 : public Fighter {
public:
    void SetNoticeModeByte(unsigned char mode);
};
void FighterNoticeF283::SetNoticeModeByte(unsigned char mode)
{
    sequencePhase = static_cast<signed char>(mode);
}
