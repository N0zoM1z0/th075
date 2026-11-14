#pragma once

#include "Fighter.hpp"
// Record values keep their observed carrier widths; the original parameter
// types are not known.
class FighterBindingRoundF171 : public Fighter {
public:
    void SetBindings(const void* source);
    void BindOpponent(void* other);
    void RecordRoundFields(signed char index, short value,
                           unsigned char first, unsigned char second,
                           unsigned char third, unsigned int payloadA,
                           unsigned int payloadB, unsigned int payloadC);
};
