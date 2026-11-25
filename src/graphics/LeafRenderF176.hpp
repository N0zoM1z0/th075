#pragma once

// Call-only views; never instantiate or embed these partial owners.
class AuxiliaryForwardersF176 {
public:
    // The sixth incoming dword slot is not read; native RET24 still consumes it.
    void SpawnAuxEffect(short effect, float x, float y, signed char facing,
                        signed char layer, unsigned int);
    void SpawnConfiguredAuxEffect(short effect, float x, float y,
                                  signed char facing, signed char layer,
                                  unsigned char flagA, unsigned char flagB);
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x314 - 0x000];
    float effectParameters[4];
};
