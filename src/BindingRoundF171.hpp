#pragma once

// Call-only views. Names and complete layouts are unknown; do not instantiate,
// allocate or embed either owner. Record values retain their observed carrier
// widths without claiming the original nominal parameter types.
class InputBindingsF171 {
public:
    void SetBindings(const void* source);
};

class FighterBindingRoundF171 {
public:
    void SetBindings(const void* source);
    void BindOpponent(void* opponent);
    void RecordRoundFields(signed char index, short value,
                           unsigned char first, unsigned char second,
                           unsigned char third, unsigned int payloadA,
                           unsigned int payloadB, unsigned int payloadC);
};
