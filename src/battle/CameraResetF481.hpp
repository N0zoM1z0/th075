#pragma once

// The background base constructs its camera subobject at +0x04.
// The next independently observed base fields begin at +0x0C, bounding this
// state object to eight bytes. Only the fighter uses its left view bound.
class CameraResetF481 {
    unsigned int unknown00;
public:
    float viewLeft;
    CameraResetF481();
};

typedef char CameraResetStateSizeF481[
    (sizeof(CameraResetF481) == 8) ? 1 : -1];
