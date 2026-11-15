#pragma once

// Declaration-only receiver view. Never construct or embed this partial owner.
class ObjectMotion40FB70 {
public:
    void SetPolarVelocity(float angle, float speed);
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x050 - 0x000];
    float field050;
    float field054;
};
