#pragma once

// The background base constructs its camera subobject at +0x04.
// The next independently observed base fields begin at +0x0C, bounding this
// state object to eight bytes; the two member meanings remain unknown.
class CameraResetF481 {
    unsigned int unknown00;
    unsigned int unknown04;
public:
    CameraResetF481();
};

typedef char CameraResetStateSizeF481[
    (sizeof(CameraResetF481) == 8) ? 1 : -1];
