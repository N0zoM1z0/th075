#ifndef TH075_TRANSFORM_RECORD_F136_HPP
#define TH075_TRANSFORM_RECORD_F136_HPP

#include <stddef.h>

// Native 36-byte transform packet copied from Fighter+0x2F0 into Actor+0x10
// when a linked effect inherits its owner's transform. Actor also exposes
// its transform as individual fields. The compiler supplies alignment
// after the five leading bytes.
struct TransformRecordF136 {
    unsigned char flags;
    unsigned char alpha;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    short offsetX;
    short offsetY;
    short offsetZ;
    float scaleX;
    float scaleY;
    float scaleZ;
    float rotationX;
    float rotationY;
    float rotationZ;
};

typedef char TransformRecordExtentF136[(sizeof(TransformRecordF136) == 36) ? 1 : -1];
typedef char TransformRecordWordF136[(offsetof(TransformRecordF136, offsetX) == 6) ? 1 : -1];
typedef char TransformRecordScaleF136[(offsetof(TransformRecordF136, scaleX) == 12) ? 1 : -1];
typedef char TransformRecordLastF136[(offsetof(TransformRecordF136, rotationZ) == 32) ? 1 : -1];

#endif
