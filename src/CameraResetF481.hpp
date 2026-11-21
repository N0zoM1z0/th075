#pragma once

// The background base calls ResetParameters on its +0x04 camera subobject.
// The next independently observed base fields begin at +0x0C, bounding this
// state object to eight bytes; the two member meanings remain unknown.
class CameraResetF481 {
    unsigned int unknown00;
    unsigned int unknown04;
public:
    CameraResetF481* ResetParameters();
};

typedef char CameraResetStateSizeF481[
    (sizeof(CameraResetF481) == 8) ? 1 : -1];
